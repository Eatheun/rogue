#ifndef FLOOR_GEN_H
#define FLOOR_GEN_H

#define MAX_ROOMS 9
#define MAX_NPCS_ON_FLOOR 10
#define MAX_RADIUS (MAX_ROOMS / 2 - 1)
#define MAX_FLOOR_SIZE (2 * MAX_RADIUS + 1)
#define MAX_CORR_SIZE (2 * MAX_FLOOR_SIZE + 1)
#define MIN_SIZE 11
#define MAX_SIZE 17

#define _floorX getFloorX()
#define _floorY getFloorY()
#define _currRoom getCurrRoom()
#define _currRoomH getCurrRoomH()
#define _currRoomW getCurrRoomW()
#define _offMX getOffMX()
#define _offMY getOffMY()

typedef struct floor *Floor;
typedef struct room *Room;

static bool map[MAX_FLOOR_SIZE][MAX_FLOOR_SIZE];
static bool corridors[MAX_CORR_SIZE][MAX_CORR_SIZE];
static int floorX, floorY;
static int offMX, offMY;
static Floor currFloor;

//////////////////////// NPC ////////////////////////

#include "npc.h"

int isNPC(int x, int y);
NPC *getNpcsInRoom(Room room);

//////////////////////// FLOORS ////////////////////////

int getCurrRoomH(void);
void setCurrRoomH(int tH);
int getCurrRoomW(void);
void setCurrRoomW(int tW);
int getFloorX(void);
void setFloorX(int tx);
int getFloorY(void);
void setFloorY(int ty);
Floor FloorNew(void);
void FloorClear(void);
void generateFloor(void);
Room getCurrRoom(void);
void setCurrRoom(Room newRoom);

//////////////////////// OFFSET ////////////////////////

int getOffMX(void);
void setOffMX(int offx);
int getOffMY(void);
void setOffMY(int offy);

//////////////////////// ROOMS ////////////////////////

Room RoomNew(void);
void RoomFree(Room newRoom);
bool isDoor(int x, int y);
void makeDoor(Room newRoom, int doorNum);
Room getAdjRoom(Room newRoom, int doorNum);
void setAdjRoom(Room r1, Room r2, int doorNum);
int getRoomH(Room room);
int getRoomW(Room room);

//////////////////////// MAP ////////////////////////

bool isVisited(int floorX, int floorY);
void visitMap(int floorX, int floorY);
bool isCorrXplrd(int corrX, int corrY);
void xplrCorr(int corrX, int corrY);

#endif // FLOOR_GEN_H