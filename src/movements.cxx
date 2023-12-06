#include <stdio.h>

#include "cells.h"
#include "directions.h"
#include "floorGen.h"
#include "inputs.h"
#include "movements.h"
#include "playerPos.h"

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

bool changeRoom(void) {
	// Simplify the direction
	int tempTx = _px;
	int tempTy = _py;
	int dirHandled = handleAllDir(&tempTx, &tempTy);
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
		setFloorY(_floorY - 1);
	} else if (dirHandled == LEFT) {
		setPx(_currRoomW - 1);
		setPy(_currRoomH / 2);
		setFloorX(_floorX - 1);
	} else if (dirHandled == DOWN) {
		setPx(_currRoomW / 2);
		setPy(0);
		setFloorY(_floorY + 1);
	} else if (dirHandled == RIGHT) {
		setPx(0);
		setPy(_currRoomH / 2);
		setFloorX(_floorX + 1);
	}
	
	visitMap(_floorX, _floorY);
	return true;
}
