#ifndef NPC_H
#define NPC_H

#include "npcActions.h"

#define MAX_NPCS 4

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

//////////////////////// TEXT ////////////////////////

bool openTextMode(NPCActions actions);

#endif // NPC_H