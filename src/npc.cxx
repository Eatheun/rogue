#include <stdio.h>
#include <stdlib.h>

#include "cells.h"
#include "npc.h"
#include "lfsr.h"

static void fillerFunc(void *args) {
	printf("Hello\n");
}

struct npc {
	int npcType;
	void (*act)(void *args);
	Coor pos;
};

static void genStats(NPC npc) {
	npc->act = fillerFunc;
}

NPC NPCNew(int npcType) {
	NPC newNpc = (NPC) malloc(sizeof(struct npc));
	newNpc->npcType = npcType;
	genStats(newNpc);
	newNpc->pos = 0xffff; // Not to be set here
	
	return newNpc;
}

void NPCFree(NPC npc) {
	free(npc);
}

int getNpcNpcType(NPC npc) { return npc->npcType; }
void setNpcNpcType(NPC npc, int npcType) { npc->npcType = npcType; }
int getNpcCoor(NPC npc) { return npc->pos; }
void setNpcCoor(NPC npc, int x, int y) { npc->pos = x * 100 + y; }
