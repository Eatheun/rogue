#ifndef NPC_ACTIONS_H
#define NPC_ACTIONS_H

#define TXTH 5
#define TBOXH (TXTH + ((1 + 1) << 1))
#define TBOXW (((MAX_SIZE + BORD_OFF) << 1) + DIST_FROM_MAINM + MAX_CORR_SIZE)
#define TXTW (TBOXW - ((1 + 1) << 1))

typedef struct npcActions *NPCActions;

//////////////////////// NPC ACTIONS ////////////////////////

NPCActions NPCActionsNew(void);
void NPCActionsFree(NPCActions actions);
char *getActionsText(NPCActions actions);
void setActionsText(npcActions actions, char *text);
char *getActionsMission(NPCActions actions);
void setActionsMission(npcActions actions, void (*mission)(void *args));

#endif // NPC_ACTIONS_H