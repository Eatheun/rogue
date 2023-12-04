#ifndef FLOOR_GEN_H
#define FLOOR_GEN_H

#define MAX_ROOMS 9
#define MAX_FLOOR_SIZE 2 * MAX_ROOMS + 1
#define MIN_SIZE 17
#define MAX_SIZE 31

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define _floorX getFloorX()
#define _floorY getFloorY()
#define _currRoom getCurrRoom()
#define _currRoomH getCurrRoomH()
#define _currRoomW getCurrRoomW()

typedef struct floor *Floor;
typedef struct room *Room;

static bool map[MAX_FLOOR_SIZE][MAX_FLOOR_SIZE];
static int floorX, floorY;
static Floor currFloor;

//////////////////////// FLOORS ////////////////////////

int isNPC(int x, int y);

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
bool changeRoom(void);
Room getCurrRoom(void);
void setCurrRoom(Room newRoom);

//////////////////////// ROOMS ////////////////////////

Room RoomNew(void);
void RoomFree(Room newRoom);
bool isDoor(int x, int y);
void makeDoor(Room newRoom, int doorNum);
Room getAdjRoom(Room newRoom, int doorNum);
void setAdjRoom(Room r1, Room r2, int doorNum);
int getRoomH(Room room);
int getRoomW(Room room);

#endif // FLOOR_GEN_H