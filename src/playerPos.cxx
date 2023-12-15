#include <stdio.h>

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../headers/floorGen.h"
#include "../headers/playerPos.h"

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
    printf("\e[%d;%dH", py + _offMY + 1, (px + _offMX) * 2 + 1); // Go to player position
    if (isNPC(px, py)) {
        NPC ret = isNPC(px, py);
        printf("%s", npcCells[getNpcNpcType(ret)]);
    } else {
        printf(FLOOR);
    }
    printf("\e[0m"); // reset colour
}

void updatePlayer(void) {
    printf("\e[%d;%dH", py + _offMY + 1, (px + _offMX) * 2 + 1); // Go to player position
    printf(PLAYER);
    printf("\e[0m"); // reset colour
}
