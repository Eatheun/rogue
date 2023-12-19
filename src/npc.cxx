#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../headers/inputs.h"
#include "../headers/lfsr.h"
#include "../headers/npc.h"
#include "../headers/npcActions.h"
#include "../headers/textbox.h"

struct npc {
	int npcType;
	NPCActions actions;
	Coor pos;
};

//////////////////////// NPC ////////////////////////

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
NPCActions getNpcActions(NPC npc) { return npc->actions; }
void setNpcActions(NPC npc, NPCActions actions) { npc->actions = actions; }
int getNpcCoor(NPC npc) { return npc->pos; }
void setNpcCoor(NPC npc, int x, int y) { npc->pos = (x << 8) + y; }

//////////////////////// TEXT ////////////////////////

void printNpcCell(NPC npc) {
	// getting the character
	char npcCell[128];
    char fp[] = "./data/npcCells.txt";
    getNpcFileData(npc, npcCell, fp);

	// print
	printf("%s", npcCell);
}

static char *getNpcTypeText(NPC npc, char typeText[]) {
    // getting and printing type title
    char fp[] = "./data/npcTBoxTypePrint.txt";
    getNpcFileData(npc, typeText, fp);

    return typeText;
}

bool interactNPC(NPC npc) {
    if (_dir == 'e') {
        char typeText[128];
        getNpcTypeText(npc, typeText);
        printTBox(getActionsText(npc->actions), typeText);
    } else {
        return false;
    }

    while (true) {
        if (getComm() == 'e') {
            closeTBox();
            break;
        }
    }

    return true;
}

//////////////////////// FILES ////////////////////////

char *getNpcFileData(NPC npc, char buf[], char fp[]) {
    FILE *fileToRead = fopen(fp, "r");
    if (fileToRead == NULL) {
        printf("\e[32E\e[0m");
        fprintf(stderr, "Missing file %s\n", fp);
        Sleep(2000);
        exit(1);
    }

    // Get the data
    int npcType = npc->npcType;
    fgets(buf, 128, fileToRead);
    for (int i = 0; i < npcType; i++) fgets(buf, 128, fileToRead);
    buf[strlen(buf) - 1] = '\0';

    fclose(fileToRead);

    return buf;
}
