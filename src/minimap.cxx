#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "floorGen.h"
#include "minimap.h"

static void printBorder(void) {
    for (int i = 0; i < MAX_FLOOR_SIZE + 2; i++) {
        printf(MINM_BORDER);
    }
}

static void moveDown(void) {
    printf("\e[1B\e[%dD", MAX_FLOOR_SIZE + 2);
}

void printMinimap(void) {
    printf("\e[1;%dH", (_currRoomW + 1) * 2); // Go to first line
    printf(BLKBCK);
    
    // Top border
    printBorder();
    moveDown();

    // Map body
    for (int i = 0; i < MAX_FLOOR_SIZE; i++) {
        printf(MINM_BORDER);
        for (int j = 0; j < MAX_FLOOR_SIZE; j++) {
            if (isVisited(j, i)) {
                printf(MINM_ROOM);
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
