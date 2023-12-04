#include <stdio.h>

#include "cells.h"
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
    printf("\e[%d;%dH", py + 1, px * 2 + 1); // Go to player position
    printf(FLOOR);
    printf("\e[0m"); // reset colour
}

void updatePlayer(void) {
    printf("\e[%d;%dH", py + 1, px * 2 + 1); // Go to player position
    printf(PLAYER);
    printf("\e[0m"); // reset colour
}
