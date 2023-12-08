#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inputs.h"
#include "floorGen.h"
#include "minimap.h"

static void setStdClr(void) {
    printf(BLKBCK);
    printf(WHTXT);
}

static void handlePrintBlock(int i, int j, bool isOpenMap) {
    int xChk = j - 1;
    int yChk = i - 1;
    int corrX = xChk >> 1;
    int corrY = yChk >> 1;
    if (xChk % 2 == 0 && yChk % 2 == 0 && 
        isVisited(corrX, corrY)) {
        if (corrX == _floorX && corrY == _floorY) {
            printf(isOpenMap ? OPNM_CURR_ROOM : MINM_CURR_ROOM);
        } else {
            printf(isOpenMap ? OPNM_ROOM : MINM_ROOM);
        }
    } else if (isCorrXplrd(xChk + 1, yChk + 1)) {
        if (xChk % 2 == 1 && yChk % 2 == 0) {
            printf(isOpenMap ? OPNM_HCORR : MINM_HCORR);
        } else {
            printf(isOpenMap ? OPNM_VCORR : MINM_VCORR);
        }

    } else {
        printf(isOpenMap ? OPNM_EMPTY : MINM_EMPTY);
    }
}

//////////////////////// MINI ////////////////////////

static void printBorder(void) {
    for (int i = 0; i < MAX_CORR_SIZE + 2; i++) {
        printf(MINM_BORDER);
    }
}

static void moveDown(void) {
    printf("\e[1B\e[%dD", MAX_CORR_SIZE + 2);
}

void printMinimap(void) {
    printf("\e[1;%dH", (MAX_SIZE + 1) * 2); // Go to first line
    setStdClr();

    // Top border
    printBorder();
    moveDown();

    // Map body
    for (int i = 0; i < MAX_CORR_SIZE; i++) {
        printf(MINM_BORDER);
        for (int j = 0; j < MAX_CORR_SIZE; j++) {
            handlePrintBlock(i, j, false);

            setStdClr(); // gotta reset
        }
        printf(MINM_BORDER);
        moveDown();
    }

    // Bottom border
    printBorder();
    moveDown();

    printf("\e[0m");
}

void remPrevRoomMinM(int prevFx, int prevFy) {
    printf("\e[%d;%dH", 1 + (prevFy + 1) * 2, (MAX_SIZE + 1) * 2 + 1); // go to prev room y
    printf("\e[%dC", 1 + prevFx * 2); // shift across
    printf(MINM_ROOM);
    printf("\e[0m");
}

void updateMinM(int newFx, int newFy, int corrX, int corrY, bool isHCorrUpdate) {
    // Printing room
    printf("\e[%d;%dH", 1 + (newFy + 1) * 2, (MAX_SIZE + 1) * 2 + 1); // go to new room y
    printf("\e[%dC", 1 + newFx * 2); // shift across
    printf(MINM_CURR_ROOM);
    setStdClr();

    // Printing corridor
    printf("\e[%d;%dH", 2 + corrY, (MAX_SIZE + 1) * 2 + 1); // go to corr y
    printf("\e[%dC", corrX); // shift across
    if (isHCorrUpdate) {
        printf(MINM_HCORR);
    } else {
        printf(MINM_VCORR);
    }
    printf("\e[0m");
}

//////////////////////// OPEN ////////////////////////

static void printOpenBorder(void) {
    for (int i = 0; i < MAX_CORR_SIZE + 2; i++) {
        printf(OPNM_BORDER);
        printf("\e[1A");
    }
    printf("\e[2E");
}

static void printOpenMap(void) {
    printf("\e[2J\e[1;1H"); // Clear and go to start
    setStdClr();

    // Top border
    printOpenBorder();

    // Map body
    for (int i = 0; i < MAX_CORR_SIZE; i++) {
        printf(OPNM_BORDER);
        printf("\e[1A");
        for (int j = 0; j < MAX_CORR_SIZE; j++) {
            handlePrintBlock(i, j, true);

            printf("\e[1A");
            setStdClr(); // gotta reset
        }
        printf(OPNM_BORDER);
        printf("\e[1E");
    }

    // Bottom border
    printOpenBorder();

    printf("\e[0m");
}

static void closeMap(void) {
    printf("\e[2J\e[1;1H"); // basically clears
}

bool openMapMode(void) {
    if (_dir == 'm') {
        printOpenMap();
    } else {
        return false;
    }

    while (true) {
        if (getComm() == 'm') {
            closeMap();
            break;
        }
    }

    return true;
}
