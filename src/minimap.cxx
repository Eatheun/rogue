#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cells.h"
#include "directions.h"
#include "inputs.h"
#include "floorGen.h"
#include "minimap.h"
#include "npc.h"

static void setStdClr(void) {
    printf(BLKBCK);
    printf(WHTXT);
}

static void handlePrintMapBlock(int i, int j, bool isOpenMap) {
    int xChk = j - 1;
    int yChk = i - 1;
    int corrX = xChk >> 1;
    int corrY = yChk >> 1;
    if (xChk % CORR_MULT == 0 && yChk % CORR_MULT == 0 && 
        isVisited(corrX, corrY)) {
        if (corrX == _floorX && corrY == _floorY) {
            printf(isOpenMap ? OPNM_CURR_ROOM : MINM_CURR_ROOM);
        } else {
            printf(isOpenMap ? OPNM_ROOM : MINM_ROOM);
        }
    } else if (isCorrXplrd(xChk + 1, yChk + 1)) {
        if (xChk % CORR_MULT == 1 && yChk % CORR_MULT == 0) {
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
    for (int i = 0; i < MAX_CORR_SIZE + BORD_OFF * 2; i++) {
        printf(MINM_BORDER);
    }
}

static void moveDown(void) {
    printf("\e[1B\e[%dD", MAX_CORR_SIZE + BORD_OFF * 2);
}

void printMinimap(void) {
    printf("\e[1;%dH", MAX_SIZE * 2 + DIST_FROM_MAINM + ESC_OFF); // Go to first line
    setStdClr();

    // Top border
    printBorder();
    moveDown();

    // Map body
    for (int i = 0; i < MAX_CORR_SIZE; i++) {
        printf(MINM_BORDER);
        for (int j = 0; j < MAX_CORR_SIZE; j++) {
            handlePrintMapBlock(i, j, false);

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
    printf("\e[%d;%dH", (prevFy + 1) * 2 + ESC_OFF, (MAX_SIZE) * 2 + DIST_FROM_MAINM + ESC_OFF + BORD_OFF); // go to prev room y
    printf("\e[%dC", 1 + prevFx * 2); // shift across
    printf(MINM_ROOM);
    printf("\e[0m");
}

void updateMinM(int newFx, int newFy, int corrX, int corrY, bool isHCorrUpdate) {
    // Printing room
    printf("\e[%d;%dH", (newFy + 1) * 2 + ESC_OFF, (MAX_SIZE) * 2 + DIST_FROM_MAINM + ESC_OFF + BORD_OFF); // go to new room y
    printf("\e[%dC", newFx * 2 + ESC_OFF); // shift across
    printf(MINM_CURR_ROOM);
    setStdClr();

    // Printing corridor
    printf("\e[%d;%dH", corrY + ESC_OFF + BORD_OFF, (MAX_SIZE) * 2 + DIST_FROM_MAINM + ESC_OFF + BORD_OFF); // go to corr y
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
    for (int i = 0; i < MAX_CORR_SIZE + BORD_OFF * 2; i++) {
        printf(OPNM_BORDER);
        printf("\e[1A");
    }
    printf("\e[2E");
}

static int handleNpcType(NPC npc) {
    if (npc == NULL) return NUM_NPC_TYPES;
    int npcType = getNpcNpcType(npc);
    return npcType;
}

static char handleNpcTypeChar(int npcType) {
    return npcType + 97;
}

static void printNpcRec(Room curr, Room prev, int currFx, int currFy) {
    if (curr == NULL || !isVisited(currFx, currFy)) {
        return;
    }

    // Find start of the room to edit
    printf("\e[%d;%dH", (currFy * 2 + 2) * 2 + 1, (currFx * 2 + 2) * 2 + 1);

    // Colours!
    if (curr == _currRoom) {
        printf("\e[48;2;255;200;16m"); // piss colour
    } else {
        printf("\e[48;5;116m"); // cyan colour
    }
    printf(WHTXT);

    // Get the npcs and print them out
    NPC *npcList = getNpcsInRoom(curr);
    int npcType;
    for (int i = 0; i < MAX_NPCS; i++) {
        if (i == 2) printf("\e[1B\e[2D"); // move down and back

        npcType = handleNpcType(npcList[i]); // print 1st
        if (npcType == NUM_NPC_TYPES) {
            // shift across and continue
            printf("\e[1C");
            continue;
        }

        printf("%c", handleNpcTypeChar(npcType));
    }

    // Loop through adjacent rooms
    for (int i = 0; i < MAX_DIRS; i++) {
        Room next = getAdjRoom(curr, i);
        if (next == prev) continue;

        int tempFx = currFx;
        int tempFy = currFy;
        if (i == UP) {
            tempFy--;
        } else if (i == LEFT) {
            tempFx--;
        } else if (i == DOWN) {
            tempFy++;
        } else if (i == RIGHT) {
            tempFx++;
        }
        printNpcRec(next, curr, tempFx, tempFy);
    }
}

// We gotta recursively find and print all npcs to their rooms
static void printRoomNpcs(void) {
    Room start = _currRoom;

    printNpcRec(start, start, _floorX, _floorY);
    setStdClr();
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
            handlePrintMapBlock(i, j, true);

            printf("\e[1A");
            setStdClr(); // gotta reset
        }
        printf(OPNM_BORDER);
        printf("\e[1E");
    }

    // Bottom border
    printOpenBorder();

    // Print out the NPCs
    printRoomNpcs();

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
