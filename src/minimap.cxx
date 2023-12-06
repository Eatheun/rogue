#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "floorGen.h"
#include "minimap.h"

static void printBorder(void) {
    for (int i = 0; i < MAX_CORR_SIZE + 2; i++) {
        printf(MINM_BORDER);
    }
}

static void moveDown(void) {
    printf("\e[1B\e[%dD", MAX_CORR_SIZE + 2);
}

void printMinimap(void) {
    printf("\e[1;%dH", (_currRoomW + 1) * 2); // Go to first line
    printf(BLKBCK);
    
    // Top border
    printBorder();
    moveDown();

    // Map body
    for (int i = 0; i < MAX_CORR_SIZE; i++) {
        printf(MINM_BORDER);
        for (int j = 0; j < MAX_CORR_SIZE; j++) {
            int xChk = j - 1;
            int yChk = i - 1;
            int corrX = xChk >> 1;
            int corrY = yChk >> 1;
            if (xChk % 2 == 0 && yChk % 2 == 0 && 
                isVisited(corrX, corrY)) {
                if (corrX == _floorX && corrY == _floorY) {
                    printf(MINM_CURR_ROOM);
                } else {
                    printf(MINM_ROOM);
                }
                printf(BLKBCK); // gotta reset
            } else {
                printf(MINM_EMPTY);
            }
        }
        printf(MINM_BORDER);
        moveDown();
    }

    // Bottom border
    printBorder();
    moveDown();

    printf("\e[0m");
}
