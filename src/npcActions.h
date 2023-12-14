#ifndef NPC_ACTIONS_H
#define NPC_ACTIONS_H

#define TXTH 5
#define TBOXH (TXTH + ((1 + 1) << 1))
#define TBOXW (((MAX_SIZE + BORD_OFF) << 1) + DIST_FROM_MAINM + MAX_CORR_SIZE)
#define TXTW (TBOXW - (1 + 1) << 1)

typedef struct npcActions *NPCActions;

bool openTextMode(char *text);

#endif // NPC_ACTIONS_H