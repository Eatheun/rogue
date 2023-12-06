#ifndef NPC_H
#define NPC_H

#define MAX_NPCS 4

typedef struct npc *NPC;

NPC NPCNew(int enLvl);
void NPCFree(NPC npc);
int getNpcNpcType(NPC npc);
void setNpcNpcType(NPC npc, int enLvl);
int getNpcCoor(NPC npc);
void setNpcCoor(NPC npc, int x, int y);

#endif // NPC_H