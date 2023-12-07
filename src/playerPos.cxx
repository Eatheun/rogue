#include <stdio.h>

#include "cells.h"
#include "floorGen.h"
#include "playerPos.h"

int getPx(void) {
    return px;
}

void setPx(int tx) {
    px = tx;
}

int getPy(void) {
    return py;
}

void setPy(int ty) {
    py = ty;
}

void removePlayer(void) {
    printf("\e[%d;%dH", py + _offMY, (px + _offMX) * 2); // Go to player position
    if (isNPC(px, py) != NUM_NPC_TYPES) {
        int ret = isNPC(px, py);
        printf("%s", npcCells[ret]);
    } else {
        printf(FLOOR);
    }
    printf("\e[0m"); // reset colour
}

void updatePlayer(void) {
    printf("\e[%d;%dH", py + _offMY, (px + _offMX) * 2); // Go to player position
    printf(PLAYER);
    printf("\e[0m"); // reset colour
}
