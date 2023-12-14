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

//////////////////////// TEXT ////////////////////////

static void printTBoxBorder(void) {
    for (int i = 0; i < TBOXW; i++) putchar('#');
    putchar('\n');
}

static void printTBoxFiller(void) {
    putchar('#');
    for (int i = 1; i < TBOXW - 1; i++) putchar(' ');
    putchar('#');
    putchar('\n');
}

static void printTBoxTxtLine(char *text, int *index) {
    putchar('#'); putchar(' ');
    if (text[*index] == ' ') (*index)++; // Check if we have extra line space at the start
    for (int i = 0; i < TXTW; i++) {
        if (text[*index] == '\0') {
            putchar(' ');
        } else {
            putchar(text[*index]);
            (*index)++;
        }
    }
    putchar(' '); putchar('#');
    putchar('\n'); // go down to start of next line
}

static void printTBox(char *text) {
    printf("\e[%d;1", MAX_SIZE + ESC_OFF); // position cursor below all the fluff
    for (int i = 0; i < (DIST_FROM_MAINM >> 1); i++) putchar('\n');

    // Print textbox
    printf(BLKBCK);
    printf(WHTXT);
    
    // Top part
    printTBoxBorder();
    printTBoxFiller();

    // Middle text block
    int index = 0;
    for (int i = 0; i < TXTH; i++) printTBoxTxtLine(text, &index);

    // Bottom part
    printTBoxFiller();
    printTBoxBorder();
}

static void closeTBox(void) {
    printf("\e[%dA", TBOXH); // position cursor below all the fluff
    printf("\e[0m");
    printf("\e[0J");
}

bool openTextMode(char *text) {
    if (_dir == 'e') {
        printTBox(text);
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

//////////////////////// NPC ACTIONS ////////////////////////

NPCActions NPCActionsNew(void) {
    return NULL;
}
