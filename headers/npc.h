#ifndef NPC_H
#define NPC_H

#include "npcActions.h"

typedef struct npc *NPC;

//////////////////////// NPC ////////////////////////

NPC NPCNew(int enLvl);
void NPCFree(NPC npc);
int getNpcNpcType(NPC npc);
void setNpcNpcType(NPC npc, int enLvl);
NPCActions getNpcActions(NPC npc);
void setNpcActions(NPC npc, NPCActions actions);
int getNpcCoor(NPC npc);
void setNpcCoor(NPC npc, int x, int y);
void printNpcCell(NPC npc);

//////////////////////// TEXT ////////////////////////

bool openTextMode(NPC npc);

//////////////////////// FILES ////////////////////////

char *getNpcFileData(NPC npc, char buf[], char fp[]);

#endif // NPC_H