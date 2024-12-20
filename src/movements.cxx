#include <stdio.h>

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../globals/directions.h"
#include "../headers/floorGen.h"
#include "../headers/inputs.h"
#include "../headers/minimap.h"
#include "../headers/movements.h"
#include "../headers/playerPos.h"

static bool isValidDir(int x, int y) {
    bool isValidX = 0 < x && x < _currRoomW - 1;
    bool isValidY = 0 < y && y < _currRoomH - 1;
    return (isValidX && isValidY) || isDoor(x, y);
}

bool move(void) {
    int tx = _px;
    int ty = _py;
    if (handleAllDir(&tx, &ty) == MAX_DIRS) {
        return false;
    }
    
    if (isValidDir(tx, ty)) {
        removePlayer();
        setPx(tx);
        setPy(ty);
        updatePlayer();
        return true;
    }
    return false;
}

static void playerPosChange(int dirHandled, int *xChk, int *yChk) {
	if (dirHandled == UP) {
		setPx(_currRoomW >> 1);
		setPy(_currRoomH - 1);
		setFloorY(_floorY - 1);
		(*yChk)--;
	} else if (dirHandled == LEFT) {
		setPx(_currRoomW - 1);
		setPy(_currRoomH >> 1);
		setFloorX(_floorX - 1);
		(*xChk)--;
	} else if (dirHandled == DOWN) {
		setPx(_currRoomW >> 1);
		setPy(0);
		setFloorY(_floorY + 1);
		(*yChk)++;
	} else if (dirHandled == RIGHT) {
		setPx(0);
		setPy(_currRoomH >> 1);
		setFloorX(_floorX + 1);
		(*xChk)++;
	}
}

bool changeRoom(void) {
	// Simplify the direction
	int tempTx = _px;
	int tempTy = _py;
	int dirHandled = handleAllDir(&tempTx, &tempTy);
	if (dirHandled == MAX_DIRS) {
		return false;
	}
	
	// Find new room
	Room newRoom;
	if ((_py == 0 && dirHandled == UP) ||
		(_px == 0 && dirHandled == LEFT) ||
		(_py == _currRoomH - 1 && dirHandled == DOWN) ||
		(_px == _currRoomW - 1 && dirHandled == RIGHT)) {
		newRoom = getAdjRoom(_currRoom, dirHandled);
	} else {
		return false;
	}

	// Update old room and set new room
	remPrevRoomMinM(_floorX, _floorY);
	setCurrRoom(newRoom);
	
	// Tracking corridors
	int xChk = (_floorX << 1) + 1;
	int yChk = (_floorY << 1) + 1;

	// Set player position and offset
	playerPosChange(dirHandled, &xChk, &yChk);
	setOffMX((MAX_SIZE - _currRoomW) >> 1);
	setOffMY((MAX_CORR_SIZE + 2 - _currRoomH) >> 1);

	bool isHCorrUpdate = false;
	if (xChk != (_floorX << 1) + 1) isHCorrUpdate = true;

	// Update maps and corridors
	visitMap(_floorX, _floorY);
	xplrCorr(xChk, yChk);
	updateMinM(_floorX, _floorY, xChk, yChk, isHCorrUpdate);
	return true;
}
