#ifndef NPC_ACTIONS_H
#define NPC_ACTIONS_H

typedef struct npcActions *NPCActions;
typedef void (*Mission)(void *args);

//////////////////////// NPC ACTIONS ////////////////////////

NPCActions NPCActionsNew(void);
void NPCActionsFree(NPCActions actions);
char *getActionsText(NPCActions actions);
void setActionsText(NPCActions actions, char *text);
Mission getActionsMission(NPCActions actions);
void setActionsMission(NPCActions actions, Mission mission);

#endif // NPC_ACTIONS_H