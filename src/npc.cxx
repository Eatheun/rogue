#include <stdio.h>
#include <stdlib.h>

#include "cells.h"
#include "const.h"
#include "inputs.h"
#include "lfsr.h"
#include "npc.h"
#include "npcActions.h"

struct npc {
	int npcType;
	NPCActions actions;
	Coor pos;
};

//////////////////////// NPC ////////////////////////

NPC NPCNew(int npcType) {
	NPC newNpc = (NPC) malloc(sizeof(struct npc));
	newNpc->npcType = npcType;
	newNpc->actions = NPCActionsNew();
	newNpc->pos = 0xffff; // Not to be set here

	return newNpc;
}

void NPCFree(NPC npc) {
	free(npc);
}

int getNpcNpcType(NPC npc) { return npc->npcType; }
void setNpcNpcType(NPC npc, int npcType) { npc->npcType = npcType; }
NPCActions getNpcActions(NPC npc) { return npc->actions; }
void setNpcActions(NPC npc, NPCActions actions) { npc->actions = actions; }
int getNpcCoor(NPC npc) { return npc->pos; }
void setNpcCoor(NPC npc, int x, int y) { npc->pos = x * 100 + y; }

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
    printTBoxBorder();
}

static void closeTBox(void) {
    printf("\e[%dA", TBOXH); // position cursor below all the fluff
    printf("\e[0m");
    printf("\e[0J");
}

bool openTextMode(NPCActions actions) {
    if (_dir == 'e') {
        printTBox(getActionsText(actions));
    } else {
        return false;
    }

    while (true) {
        if (getComm() == 'e') {
            closeTBox();
            break;
        }
    }

    return true;
}
