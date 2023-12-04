#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cells.h"
#include "floorGen.h"
#include "directions.h"
#include "inputs.h"
#include "lfsr.h"
#include "npc.h"
#include "playerPos.h"

struct floor {
	Room currRoom;
	int currRoomH;
	int currRoomW;
	Room endRoom;
	int totalEns;
};

struct room {
	int roomH;
	int roomW;
	Coor doors[MAX_DIRS];
	Room adj[MAX_DIRS];
	Coor isEnd;
	int numNPCs;
	NPC ens[MAX_NPCS];
};

//////////////////////// ENEMY ////////////////////////

static void genEnemies(Room room) {
	int numNPC = rand(MAX_NPCS);
	room->numNPCs = numNPC;
	currFloor->totalEns += numNPC;
	for (int i = 0; i < numNPC; i++) {
		// Make enemy and randomise their coordinates
		NPC newNpc = NPCNew(SKELETON); // add more floors and difficulties
		setNpcCoor(newNpc, rand(room->roomW - 2) + 1, rand(room->roomH - 2) + 1);
		room->ens[i] = newNpc;
	}
}

int isNPC(int x, int y) {
	int coorXY = x * 100 + y;
	Room currRoom = currFloor->currRoom;
	for (int i = 0; i < currRoom->numNPCs; i++) {
		NPC currEn = currRoom->ens[i];
		if (getNpcCoor(currEn) == coorXY) {
			return getNpcNpcType(currEn);
		}
	}
	
	return 0;
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
	newFloor->totalEns = 0;
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

static Room generateFloorRec(Room newRoom, Room prevRoom, int prevX, int prevY, int *limit, int prevDoor, int prob) {
	if (*limit >= MAX_ROOMS || newRoom == NULL) {
		return NULL;
	}
	
	// Make the previous door
	if (UP <= prevDoor && prevDoor < MAX_DIRS) {
		setAdjRoom(newRoom, prevRoom, prevDoor);
		makeDoor(newRoom, prevDoor);
	}
	
	// Generate enemies for the room
	genEnemies(newRoom);
	
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
	floorX = MAX_ROOMS;
	floorY = MAX_ROOMS;
	map[floorY][floorX] = true;
	
	// Generate the rooms and make the start
	int limit = 0;
	Room seededRoom = generateFloorRec(start, start, floorX, floorY, &limit, MAX_DIRS, 6);
	setCurrRoom(seededRoom);
}

bool changeRoom(void) {
	// Simplify the direction
	int tempTx = _px;
	int tempTy = _py;
	int dirHandled = handleWASD(&tempTx, &tempTy);
	if (dirHandled == MAX_DIRS) {
		dirHandled = handleArrows(&tempTx, &tempTy);
	}
	if (dirHandled == MAX_DIRS) {
		return false;
	}
	
	// Find and set new room
	Room newRoom;
	if ((_py == 0 && dirHandled == UP) ||
		(_px == 0 && dirHandled == LEFT) ||
		(_py == _currRoomH - 1 && dirHandled == DOWN) ||
		(_px == _currRoomW - 1 && dirHandled == RIGHT)) {
		newRoom = getAdjRoom(_currRoom, dirHandled);
	} else {
		return false;
	}
	setCurrRoom(newRoom);
	
	// Set player position
	if (dirHandled == UP) {
		setPx(_currRoomW / 2);
		setPy(_currRoomH - 1);
		floorY--;
	} else if (dirHandled == LEFT) {
		setPx(_currRoomW - 1);
		setPy(_currRoomH / 2);
		floorX--;
	} else if (dirHandled == DOWN) {
		setPx(_currRoomW / 2);
		setPy(0);
		floorY++;
	} else if (dirHandled == RIGHT) {
		setPx(0);
		setPy(_currRoomH / 2);
		floorX++;
	}
	
	return true;
}

Room getCurrRoom(void) {
	return currFloor->currRoom;
}

void setCurrRoom(Room newRoom) {
    currFloor->currRoom = newRoom;
    setCurrRoomH(newRoom->roomH);
    setCurrRoomW(newRoom->roomW);
}

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
		newRoom->ens[i] = NULL;
	}
	
	return newRoom;
}

void RoomFree(Room newRoom) {
	// Free enemies
	for (int i = 0; i < MAX_NPCS; i++) {
		NPCFree(newRoom->ens[i]);
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
