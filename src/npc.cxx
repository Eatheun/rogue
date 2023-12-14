#include <stdio.h>
#include <stdlib.h>

#include "cells.h"
#include "lfsr.h"
#include "npc.h"
#include "npcActions.h"

struct npc {
	int npcType;
	NPCActions actions;
	Coor pos;
};

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
int getNpcCoor(NPC npc) { return npc->pos; }
void setNpcCoor(NPC npc, int x, int y) { npc->pos = x * 100 + y; }
