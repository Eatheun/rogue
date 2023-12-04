#ifndef ENEMIES_H
#define ENEMIES_H

#define DEF_COST 2
#define MAX_NPCS 4

enum npcType {
	SKELETON = 3,
	GOBLIN = 5,
	OGRE = 7,
	DRAGON = 10
};

typedef struct npc *NPC;

NPC NPCNew(int enLvl);
void NPCFree(NPC npc);
int getNpcNpcType(NPC npc);
void setNpcNpcType(NPC npc, int enLvl);
int getNpcCoor(NPC npc);
void setNpcCoor(NPC npc, int x, int y);

#endif // ENEMIES_H