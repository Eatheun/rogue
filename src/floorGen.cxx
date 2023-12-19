#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../globals/directions.h"
#include "../headers/floorGen.h"
#include "../headers/inputs.h"
#include "../headers/lfsr.h"
#include "../headers/npc.h"
#include "../headers/npcActions.h"

struct floor {
	Room currRoom;
	int currRoomH;
	int currRoomW;
	Room startRoom;
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

static void copyToNpcText(char *npcText, const char textToCopy[]) {
    npcText = (char *) realloc(npcText, strlen(npcText) + strlen(textToCopy) + 1);
    strcat(npcText, textToCopy);
}

static char *genNpcText(Room npcRoom, NPC npc) {
    Coor npcRoomCoor = getRoomXY(npcRoom);
    Coor endRoomCoor = getRoomXY(_endRoom);
    bool isUp = (npcRoomCoor & 0xff) > (endRoomCoor & 0xff);
    bool isLeft = (npcRoomCoor >> 8) > (endRoomCoor >> 8);
    bool isDown = (npcRoomCoor & 0xff) < (endRoomCoor & 0xff);
    bool isRight = (npcRoomCoor >> 8) < (endRoomCoor >> 8);

    char *npcText = (char *) malloc(sizeof(char)); npcText[0] = '\0';
    if (isUp) copyToNpcText(npcText, "The room is above. ");
    if (isLeft) copyToNpcText(npcText, "The room is to the left. ");
    if (isDown) copyToNpcText(npcText, "The room is below. ");
    if (isRight) copyToNpcText(npcText, "The room is to the right. ");
    
    return npcText;
}

static void assignNpcToRoom(Room room, NPC npc, int npcInd) {
	// Append to NPCs
	room->npcs[npcInd] = npc;

	// Need some proper text for the NPC
	setActionsText(getNpcActions(npc), genNpcText(room, npc));

	// Set the coordinates
	int roomH = room->roomH;
	int roomW = room->roomW;
	int npcXBase = (roomW >> 1) - 1;
	int npcYBase = (roomH >> 1) - 1;
	int npcXOff = npcInd % 2 == 1 ? (roomW >> 1) : 0;
	int npcYOff = npcInd > 1 ? (roomH >> 1) : 0;

	setNpcCoor(
		npc,
		rand(npcXBase) + npcXOff + 1,
		rand(npcYBase) + npcYOff + 1
	);
}

static void assignNPCs(Room room) {
	// Set the total
	currFloor->totalNpcs = MAX_NPCS_ON_FLOOR;

	// Track the NPCs chosen and the rooms
	bool isChosenNpc[NUM_NPC_TYPES];
	memset(isChosenNpc, false, NUM_NPC_TYPES * sizeof(bool));

	// Assign 
	for (int i = 0; i < MAX_NPCS_ON_FLOOR; i++) {
		int newType = rand(NUM_NPC_TYPES);
		while (isChosenNpc[newType]) newType = rand(NUM_NPC_TYPES);
		isChosenNpc[newType] = true;

		// Make new NPC and calc a room for them
		NPC currNpc = NPCNew(newType);
		Room chosenRoom = roomsArr[rand(MAX_ROOMS)];
		int baseFracDigit = MAX_NPCS << 1;
		while (chosenRoom == NULL || !chance(baseFracDigit - (chosenRoom->numNPCs << 1), baseFracDigit)) {
			chosenRoom = roomsArr[rand(MAX_ROOMS)];
		}
		chosenRoom->numNPCs++;

		// Assign to said room and give them the coordinates
		for (int j = 0; j < MAX_NPCS; j++) {
			if (chosenRoom->npcs[j] == NULL) {
				assignNpcToRoom(chosenRoom, currNpc, j);
				break;
			}
		}
	}
}

NPC isNPC(int x, int y) {
	Coor coorXY = (x << 8) + y;
	Room currRoom = currFloor->currRoom;
	for (int i = 0; i < currRoom->numNPCs; i++) {
		NPC currEn = currRoom->npcs[i];
		if (getNpcCoor(currEn) == coorXY) {
			return currEn;
		}
	}
	
	return NULL;
}

NPC *getNpcsInRoom(Room room) {
	return room->npcs;
}

//////////////////////// FLOOR METADTA ////////////////////////

int getCurrRoomH(void) { return currFloor->currRoomH; }
void setCurrRoomH(int tH) { currFloor->currRoomH = tH; }

int getCurrRoomW(void) { return currFloor->currRoomW; }
void setCurrRoomW(int tW) { currFloor->currRoomW = tW; }

int getFloorX(void) { return floorX; }
void setFloorX(int tx) { floorX = tx; }

int getFloorY(void) { return floorY; }
void setFloorY(int ty) { floorY = ty; }

Room getCurrRoom(void) { return currFloor->currRoom; }
void setCurrRoom(Room newRoom) {
    currFloor->currRoom = newRoom;
    setCurrRoomH(newRoom->roomH);
    setCurrRoomW(newRoom->roomW);
}

Room getStartRoom(void) { return currFloor->startRoom; }
void setStartRoom(Room newRoom) { currFloor->startRoom = newRoom; }

Room getEndRoom(void) { return currFloor->endRoom; }
void setEndRoom(Room newRoom) { currFloor->endRoom = newRoom; }

//////////////////////// FLOOR GEN ////////////////////////

Floor FloorNew(void) {
	Floor newFloor = (Floor) malloc(sizeof(struct floor));
	newFloor->currRoom = NULL;
	newFloor->startRoom = NULL;
	newFloor->endRoom = NULL;
	newFloor->totalNpcs = 0;
	return newFloor;
}

static void FloorFreeRec(Room newRoom, Room prev) {
	if (newRoom == NULL) {
		return;
	}
	
	for (int i = 0; i < MAX_DIRS; i++) {
		Room nextRoom = getAdjRoom(newRoom, i);
		if (nextRoom == prev) {
			continue;
		}
		FloorFreeRec(nextRoom, newRoom);
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
	
	FloorFreeRec(start, start);
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

static void arrayifyRooms(Room curr, Room prev, int *index) {
	if (curr == NULL || *index >= MAX_ROOMS) {
		return;
	}

	roomsArr[*index] = curr;
	(*index)++;

	for (int i = 0; i < MAX_DIRS; i++) {
		Room nextRoom = curr->adj[i];
		if (nextRoom == prev) continue;
		arrayifyRooms(nextRoom, curr, index);
	}
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
	
	// Array-ify the rooms
	for (int i = 0; i < MAX_ROOMS; i++) roomsArr[i] = NULL;
	int index = 0;
	arrayifyRooms(start, start, &index);

	// Assign the startRoom, endRoom and currRoom
	currFloor->startRoom = seededRoom;
	currFloor->endRoom = roomsArr[rand(MAX_ROOMS)];
	while (currFloor->endRoom == NULL) currFloor->endRoom = roomsArr[rand(MAX_ROOMS)];
	setCurrRoom(seededRoom);

	// Assign the NPCs to room
	assignNPCs(seededRoom);

	// Clear the map for player exploration
	for (int i = 0; i < MAX_FLOOR_SIZE; i++) {
		for (int j = 0; j < MAX_FLOOR_SIZE; j++) {
			map[i][j] = false;
		}
	}
	map[floorY][floorX] = true;
	printf("(%d, %d)\n", floorX, floorY);

	// Set the offset
	offMX = (MAX_SIZE - _currRoomW) >> 1;
	offMY = (MAX_CORR_SIZE + 2 - _currRoomH) >> 1;
}

//////////////////////// MAP OFFSET ////////////////////////

int getOffMX(void) { return offMX; }
void setOffMX(int offx) { offMX = offx; }

int getOffMY(void) { return offMY; }
void setOffMY(int offy) { offMY = offy; }

//////////////////////// ROOM METADATA ////////////////////////


Room getAdjRoom(Room newRoom, int doorNum) {
	return newRoom->adj[doorNum];
}
void setAdjRoom(Room r1, Room r2, int doorNum) {
	r1->adj[doorNum] = r2;
}

int getRoomH(Room room) { return room->roomH; };
int getRoomW(Room room) { return room->roomW; };

static bool getRoomXYRec(Room curr, Room prev, Room goal, int *floorX, int *floorY) {
	if (curr == NULL) return false;

	if (curr == goal) return true;

	for (int i = 0; i < MAX_DIRS; i++) {
		Room next = curr->adj[i];
		if (next == prev) continue;
		int tempX = *floorX;
		int tempY = *floorY;

		if (i == UP) (*floorY)--;
		if (i == LEFT) (*floorX)--;
		if (i == DOWN) (*floorY)++;
		if (i == RIGHT) (*floorX)++;

		if (getRoomXYRec(next, curr, goal, floorX, floorY)) {
			return true;
		} else {
			// Revert back our failures
			(*floorX) = tempX;
			(*floorY) = tempY;
		}
	}

	return false;
}

Coor getRoomXY(Room room) {
	Room start = currFloor->startRoom;
	int floorX = floorY = MAX_RADIUS;
	if (getRoomXYRec(start, start, room, &floorX, &floorY)) {
		return (floorX << 8) + floorY;
	}

	return 0; // should never happen
}

bool isInEndRoom(void) {
	return currFloor->currRoom == currFloor->endRoom;
}

//////////////////////// ROOM GEN ////////////////////////

static int resize(int dim) {
    dim = dim % 2 == 0 ? dim + 1 : dim;
    return dim;
}

static void randRoomSize(Room newRoom) {
    newRoom->roomH = resize(rand(MAX_SIZE - MIN_SIZE) + MIN_SIZE);
    newRoom->roomW = resize(rand(MAX_SIZE - MIN_SIZE) + MIN_SIZE);
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
	if (newRoom == NULL) return;

	// Free enemies
	for (int i = 0; i < MAX_NPCS; i++) {
		// Free actions and npc
		NPC currNpc = newRoom->npcs[i];
		if (currNpc == NULL) continue;
		NPCActionsFree(getNpcActions(currNpc));
		NPCFree(currNpc);
	}
	free(newRoom);
}

bool isDoor(int x, int y) {
	Coor currXY = (x << 8) + y;
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
		newRoom->doors[doorNum] = (newRoom->roomW >> 1) << 8;
	} else if (doorNum == LEFT) {
		newRoom->doors[doorNum] = (newRoom->roomH >> 1);
	} else if (doorNum == DOWN) {
		newRoom->doors[doorNum] = ((newRoom->roomW >> 1) << 8) + newRoom->roomH - 1;
	} else if (doorNum == RIGHT) {
		newRoom->doors[doorNum] = ((newRoom->roomW - 1) << 8) + (newRoom->roomH >> 1);
	}
}

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
