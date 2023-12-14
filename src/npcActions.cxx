#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#include "inputs.h"
#include "floorGen.h"
#include "minimap.h"
#include "npcActions.h"

struct npcActions {
    char text[TXTH * TXTW];
    void (*mission)(void *args);
};

static void printTBox() {
    printf("\e[%d;1", MAX_SIZE + ESC_OFF); // position cursor below all the fluff
    for (int i = 0; i < (DIST_FROM_MAINM >> 1); i++) putchar('\n');

    // Print textbox
    printf(BLKBCK);
    printf(WHTXT);
    for (int i = 0; i < TBOXH; i++) {
        for (int j = 0; j < TBOXW; j++) {
            putchar('#');
        }
        putchar('\n');
    }
}

static void closeTBox() {
    printf("\e[%dA", TBOXH); // position cursor below all the fluff
    printf("\e[0m");
    printf("\e[0J");
}

bool openTextMode(char *text) {
    if (_dir == 'e') {
        printTBox();
    } else {
        return false;
    }

    while (true) {
        if (getch() == 'e') {
            closeTBox();
            break;
        }
    }

    return true;
}
