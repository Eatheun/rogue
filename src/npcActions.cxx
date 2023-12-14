#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "inputs.h"
#include "floorGen.h"
#include "minimap.h"
#include "npcActions.h"

char fillerText[] = "Lorem ipsum dolor sit amet, consectetur adipisci elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.";

struct npcActions {
    char *text /* [TXTH * TXTW] */;
    void (*mission)(void *args);
};

//////////////////////// NPC ACTIONS ////////////////////////

NPCActions NPCActionsNew(void) {
    NPCActions actions = (NPCActions) malloc(sizeof(struct npcActions));
    actions->text = strdup(fillerText);
    actions->mission = NULL;
    return actions;
}

void NPCActionsFree(NPCActions actions) {
    free(actions->text);
    free(actions);
}
