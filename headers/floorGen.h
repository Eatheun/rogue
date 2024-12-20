#ifndef FLOOR_GEN_H
#define FLOOR_GEN_H

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../headers/npc.h"

#define _floorX getFloorX()
#define _floorY getFloorY()
#define _currRoom getCurrRoom()
#define _currRoomH getCurrRoomH()
#define _currRoomW getCurrRoomW()
#define _startRoom getStartRoom()
#define _endRoom getEndRoom()
#define _offMX getOffMX()
#define _offMY getOffMY()

typedef struct floor *Floor;
typedef struct room *Room;

static bool map[MAX_FLOOR_SIZE][MAX_FLOOR_SIZE];
static bool corridors[MAX_CORR_SIZE][MAX_CORR_SIZE];
static int floorX, floorY;
static int offMX, offMY;
static Floor currFloor;
static Room roomsArr[MAX_ROOMS]; // For room access

//////////////////////// NPC ////////////////////////

NPC isNPC(int x, int y);
NPC *getNpcsInRoom(Room room);

//////////////////////// FLOOR METADTA ////////////////////////

int getCurrRoomH(void);
void setCurrRoomH(int tH);

int getCurrRoomW(void);
void setCurrRoomW(int tW);

int getFloorX(void);
void setFloorX(int tx);

int getFloorY(void);
void setFloorY(int ty);

Room getCurrRoom(void);
void setCurrRoom(Room newRoom);

Room getStartRoom(void);
void setStartRoom(Room newRoom);

Room getEndRoom(void);
void setEndRoom(Room newRoom);

//////////////////////// FLOOR GEN ////////////////////////

Floor FloorNew(void);
void FloorClear(void);
void generateFloor(void);

//////////////////////// MAP OFFSET ////////////////////////

int getOffMX(void);
void setOffMX(int offx);

int getOffMY(void);
void setOffMY(int offy);

//////////////////////// ROOM METADATA ////////////////////////

Room getAdjRoom(Room newRoom, int doorNum);
void setAdjRoom(Room r1, Room r2, int doorNum);

int getRoomH(Room room);
int getRoomW(Room room);

Coor getRoomXY(Room room);
bool isInEndRoom(void);

//////////////////////// ROOM GEN ////////////////////////

Room RoomNew(void);
void RoomFree(Room newRoom);
bool isDoor(int x, int y);
void makeDoor(Room newRoom, int doorNum);

//////////////////////// MAP ////////////////////////

bool isVisited(int floorX, int floorY);
void visitMap(int floorX, int floorY);
bool isCorrXplrd(int corrX, int corrY);
void xplrCorr(int corrX, int corrY);

#endif // FLOOR_GEN_H