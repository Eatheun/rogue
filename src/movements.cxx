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
    if (handleWASD(&tx, &ty) == MAX_DIRS && handleArrows(&tx, &ty) == MAX_DIRS) {
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
