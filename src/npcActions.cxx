#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "../globals/const.h"
#include "../headers/floorGen.h"
#include "../headers/inputs.h"
#include "../headers/minimap.h"
#include "../headers/npcActions.h"

char fillerText[] = "Lorem ipsum dolor sit amet, consectetur adipisci elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.";

struct npcActions {
    char *text /* [TXTH * TXTW] */;
    Mission mission;
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

char *getActionsText(NPCActions actions) { return actions->text; };
void setActionsText(NPCActions actions, char *text) { actions->text = text; };
Mission getActionsMission(NPCActions actions) { return actions->mission; };
void setActionsMission(NPCActions actions, Mission mission) { actions->mission = mission; };
