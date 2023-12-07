#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cells.h"
#include "directions.h"
#include "floorGen.h"
#include "npc.h"
#include "inputs.h"
#include "lfsr.h"
#include "minimap.h"
#include "movements.h"
#include "playerPos.h"

//////////////////////////////// ANSI Functions ////////////////////////////////

void clear(void) {
	printf("\e[2J\n\e[1;1H");
}

void printFullMap(void) {
	printf("\e[%d;%dH", _offMY, _offMX * 2); // Center the map

	for (int i = 0; i < _currRoomH; i++) {
		for (int j = 0; j < _currRoomW; j++) {
			if (ISPLAYER(j, i)) {
				printf(PLAYER);
			}
			else if (ISWALL(j, i) && !isDoor(j, i)) {
				printf(WALL);
			}
			else if (isNPC(j, i) != NUM_NPC_TYPES) {
				int ret = isNPC(j, i);
				printf("%s", npcCells[ret]);
			}
			else {
				printf(FLOOR);
			}
			printf("\e[0m"); // reset colour
		}
		printf("\e[1B\e[%dD", _currRoomW * 2); // go down one line
	}

	// printMinimap();
}

void clearFullMap(void) {
	printf("\e[1;%dH", MAX_SIZE * 2 + 1); // go to start of deletion
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("\e[1K"); // clear map line
		printf("\e[1B"); // go down
	}
}

// We don't want a weird cursor on the screen
void removeCursor(void) {
	printf("\e[%d;1H\e[?25l", MAX_CORR_SIZE + 3); // Position cursor at the bottom and hide it
}

void reenableCursor(void) {
	printf("\e[1;1H\e[?25h");
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(int argc, char **argv) {
	clear();
	setSeed();
	clear(); // Clear and start
	
	generateFloor();

	setPx(_currRoomW / 2);
	setPy(_currRoomH / 2);

	printFullMap();
	printMinimap();
	removeCursor();

	while (true) {
		if (getComm() != 0) {
			// Check if we're quitting
			if (_dir == 'q') break;

			if (move()) {

			} else if (changeRoom()) {
				clearFullMap();
				printFullMap();
			} else if (openMapMode()) {

			}
			removeCursor();
		}
	}
	
	reenableCursor();
	clear();
	FloorClear();
	return 0;
}
