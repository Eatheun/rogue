#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cells.h"
#include "floorGen.h"
#include "directions.h"
#include "inputs.h"
#include "lfsr.h"
#include "npc.h"

struct floor {
	Room currRoom;
	int currRoomH;
	int currRoomW;
	Room endRoom;
	int totalNpcs;
};

struct room {
	int roomH;
	int roomW;
	Coor doors[MAX_DIRS];
	Room adj[MAX_DIRS];
	Coor isEnd;
	int numNPCs;
	NPC npcs[MAX_NPCS];
};

//////////////////////// NPC ////////////////////////

static bool isRoomFull(Room room) {
	for (int i = 0; i < MAX_NPCS; i++) {
		if (room->npcs[i] == NULL) {
			return false;
		}
	}

	return true;
}

static Room getRoomFromFloorXY(Room start, int x, int y) {
	Room curr = start;
	int xDiff = x - MAX_RADIUS;
	int yDiff = y - MAX_RADIUS;

	// go across x
	while (curr != NULL && xDiff > 0) {
		curr = curr->adj[RIGHT];
		xDiff--;
	}
	while (curr != NULL && xDiff < 0) {
		curr = curr->adj[LEFT];
		xDiff++;
	}

	// go across y
	while (curr != NULL && yDiff > 0) {
		curr = curr->adj[DOWN];
		yDiff--;
	}
	while (curr != NULL && yDiff < 0) {
		curr = curr->adj[UP];
		yDiff++;
	}
	return curr;
}

static Room findChosenRoom(Room room, int roomInd) {
	Room chosenRoom = room;
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE && roomInd > 0; j++) {
			if (isVisited(j, i)) {
				Room maybeChosen = getRoomFromFloorXY(room, j, i);
				if (!isRoomFull(maybeChosen)) {
					chosenRoom = maybeChosen;
					roomInd--;
				}
			} 
		}
	}

	return chosenRoom;
}

static void assignNPCs(Room room) {
	// Set the total
	currFloor->totalNpcs = MAX_NPCS_ON_FLOOR;

	// Track the NPCs chosen
	bool isChosen[NUM_NPC_TYPES];
	memset(isChosen, false, NUM_NPC_TYPES * sizeof(bool));

	// Assign 
	for (int i = 0; i < MAX_NPCS_ON_FLOOR; i++) {
		int newType = rand(NUM_NPC_TYPES);
		while (isChosen[newType]) newType = rand(NUM_NPC_TYPES);
		isChosen[newType] = true;

		// Make new NPC and calc a room for them
		NPC currNpc = NPCNew(newType);
		Room chosenRoom = findChosenRoom(room, rand(MAX_ROOMS));

		// Assign said room
		for (int j = 0; j < MAX_NPCS; j++) {
			if (chosenRoom->npcs[j] == NULL) chosenRoom->npcs[j] = currNpc;
		}
	}
}

int isNPC(int x, int y) {
	int coorXY = x * 100 + y;
	Room currRoom = currFloor->currRoom;
	for (int i = 0; i < currRoom->numNPCs; i++) {
		NPC currEn = currRoom->npcs[i];
		if (getNpcCoor(currEn) == coorXY) {
			return getNpcNpcType(currEn);
		}
	}
	
	return NUM_NPC_TYPES;
}

NPC *getNpcsInRoom(Room room) {
	return room->npcs;
}

//////////////////////// FLOORS ////////////////////////

int getCurrRoomH(void) { return currFloor->currRoomH; }

void setCurrRoomH(int tH) { currFloor->currRoomH = tH; }

int getCurrRoomW(void) { return currFloor->currRoomW; }

void setCurrRoomW(int tW) { currFloor->currRoomW = tW; }

int getFloorX(void) { return floorX; }

void setFloorX(int tx) { floorX = tx; }

int getFloorY(void) { return floorY; }

void setFloorY(int ty) { floorY = ty; }

Floor FloorNew(void) {
	Floor newFloor = (Floor) malloc(sizeof(struct floor));
	newFloor->currRoom = NULL;
	newFloor->endRoom = NULL;
	newFloor->totalNpcs = 0;
	return newFloor;
}

static void floorFreeRec(Room newRoom, Room prev) {
	if (newRoom == NULL) {
		return;
	}
	
	for (int i = 0; i < MAX_DIRS; i++) {
		Room nextRoom = getAdjRoom(newRoom, i);
		if (nextRoom == prev) {
			continue;
		}
		floorFreeRec(nextRoom, newRoom);
	}
	RoomFree(newRoom);
}

void FloorClear(void) {
	Room start = currFloor->currRoom;
	
	for (int i = 0; i < MAX_FLOOR_SIZE; i++) {
		for (int j = 0; j < MAX_FLOOR_SIZE; j++) {
			map[i][j] = false;
		}
	}
	
	floorFreeRec(start, start);
	free(currFloor);
}

static bool isRoom(int tx, int ty) {
	return map[ty][tx];
}

static bool isValidRoom(int tx, int ty) {
	bool isValidTx = 0 <= tx && tx < MAX_FLOOR_SIZE;
	bool isValidTy = 0 <= ty && ty < MAX_FLOOR_SIZE;
	return isValidTx && isValidTy;
}

static Room generateFloorRec(Room newRoom, Room prevRoom, int prevX, int prevY, int *limit, int prevDoor, int prob) {
	if (*limit >= MAX_ROOMS || newRoom == NULL) {
		return NULL;
	}
	
	// Make the previous door
	if (UP <= prevDoor && prevDoor < MAX_DIRS) {
		setAdjRoom(newRoom, prevRoom, prevDoor);
		makeDoor(newRoom, prevDoor);
	}

	for (int i = 0; i < 10; i++) {
		// Randomise the chances a bit and get next room directions
		int ranGD = rand(MAX_DIRS);
		int tx = prevX;
		int ty = prevY;
		if (ranGD == UP) {
			ty--;
		} else if (ranGD == LEFT) {
			tx--;
		} else if (ranGD == DOWN) {
			ty++;
		} else if (ranGD == RIGHT) {
			tx++;
		}

		// Check if valid generation
		if (!isValidRoom(tx, ty)) {
			continue;
		}

		if (chance(prob, 7) && !isRoom(tx, ty)) {
			// Make the new room and mark coordinates on the map
			Room tempRoom = RoomNew();
			map[ty][tx] = true;

			// Reaching limit...
			(*limit)++;
	
			// Make the door and go to make new rooms
			int oppositeDir = (ranGD + 2) % MAX_DIRS;
			Room adjRoom = generateFloorRec(tempRoom, newRoom, tx, ty, limit, oppositeDir, prob - 2);
			if (adjRoom == NULL) {
				RoomFree(tempRoom);
			} else {
				makeDoor(newRoom, ranGD);
			}
			setAdjRoom(newRoom, adjRoom, ranGD);
		}
	}
	
	return newRoom;
}

void generateFloor(void) {
	// Start the generation
	currFloor = FloorNew();
	Room start = RoomNew();
	floorX = MAX_RADIUS;
	floorY = MAX_RADIUS;
	map[floorY][floorX] = true;
	
	// Generate the rooms and assign NPCs
	int limit = 0;
	Room seededRoom = generateFloorRec(start, start, floorX, floorY, &limit, MAX_DIRS, 6);
	printf("start\n");
	assignNPCs(seededRoom);
	printf("done\n");
	setCurrRoom(seededRoom);

	// Clear the map for player exploration
	for (int i = 0; i < MAX_FLOOR_SIZE; i++) {
		for (int j = 0; j < MAX_FLOOR_SIZE; j++) {
			map[i][j] = false;
		}
	}
	map[floorY][floorX] = true;

	// Set the offset
	offMX = (MAX_SIZE - _currRoomW) / 2;
	offMY = (MAX_CORR_SIZE + 2 - _currRoomH) / 2;
}

Room getCurrRoom(void) {
	return currFloor->currRoom;
}

void setCurrRoom(Room newRoom) {
    currFloor->currRoom = newRoom;
    setCurrRoomH(newRoom->roomH);
    setCurrRoomW(newRoom->roomW);
}

//////////////////////// OFFSET ////////////////////////

int getOffMX(void) { return offMX; }
void setOffMX(int offx) { offMX = offx; }
int getOffMY(void) { return offMY; }
void setOffMY(int offy) { offMY = offy; }

//////////////////////// ROOMS ////////////////////////

static int resize(int dim) {
	dim = MAX(dim, MIN_SIZE);
    dim = dim % 2 == 0 ? dim + 1 : dim;
    return dim;
}

static void randRoomSize(Room newRoom) {
    newRoom->roomH = resize(rand(MAX_SIZE));
    newRoom->roomW = resize(rand(MAX_SIZE));
}

Room RoomNew(void) {
	// Make room and size
	Room newRoom = (Room) malloc(sizeof(struct room));
	randRoomSize(newRoom);
	
	// Stub neighbours
	for (int i = 0; i < MAX_DIRS; i++) {
		newRoom->doors[i] = 0;
		newRoom->adj[i] = NULL;
	}
	
	// Stub metadata
	newRoom->isEnd = 0;
	newRoom->numNPCs = 0;
	
	// Stub enemies
	for (int i = 0; i < MAX_NPCS; i++) {
		newRoom->npcs[i] = NULL;
	}
	
	return newRoom;
}

void RoomFree(Room newRoom) {
	// Free enemies
	for (int i = 0; i < MAX_NPCS; i++) {
		NPCFree(newRoom->npcs[i]);
	}
	
	free(newRoom);
}

bool isDoor(int x, int y) {
	Coor currXY = x * 100 + y;
	for (int i = 0; i < MAX_DIRS; i++) {
		if (currXY != 0 && _currRoom->doors[i] == currXY) {
			return true;
		}
	}
	return false;
}

void makeDoor(Room newRoom, int doorNum) {
	if (newRoom == NULL) {
		return;
	}
	
	if (doorNum == UP) {
		newRoom->doors[doorNum] = newRoom->roomW / 2 * 100;
	} else if (doorNum == LEFT) {
		newRoom->doors[doorNum] = newRoom->roomH / 2;
	} else if (doorNum == DOWN) {
		newRoom->doors[doorNum] = newRoom->roomW / 2 * 100 + newRoom->roomH - 1;
	} else if (doorNum == RIGHT) {
		newRoom->doors[doorNum] = (newRoom->roomW - 1) * 100 + newRoom->roomH / 2;
	}
}

Room getAdjRoom(Room newRoom, int doorNum) {
	return newRoom->adj[doorNum];
}

void setAdjRoom(Room r1, Room r2, int doorNum) {
	r1->adj[doorNum] = r2;
}

int getRoomH(Room room) { return room->roomH; };

int getRoomW(Room room) { return room->roomW; };

//////////////////////// MAP ////////////////////////

bool isVisited(int floorX, int floorY) {
    return map[floorY][floorX];
}

void visitMap(int floorX, int floorY) {
	map[floorY][floorX] = true;
}

bool isCorrXplrd(int corrX, int corrY) {
	return corridors[corrY][corrX];
}

void xplrCorr(int corrX, int corrY) {
	corridors[corrY][corrX] = true;
}
