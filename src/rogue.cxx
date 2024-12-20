#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../globals/directions.h"
#include "../headers/end.h"
#include "../headers/floorGen.h"
#include "../headers/inputs.h"
#include "../headers/lfsr.h"
#include "../headers/minimap.h"
#include "../headers/movements.h"
#include "../headers/npc.h"
#include "../headers/npcActions.h"
#include "../headers/playerPos.h"

//////////////////////////////// ANSI Functions ////////////////////////////////

void clear(void) {
	printf("\e[2J\n\e[1;1H");
}

static void putBlock(void) {
	putchar(EMPTY); putchar(EMPTY);
}

static void printWalls(void) {
	printf(CYABCK);
	for (int i = 0; i < _currRoomW; i++) { // Top
		if (isDoor(i, 0)) {
			printf(DRKBLUBCK);
			putBlock();
			printf(CYABCK);
		} else {
			putBlock();
		}
	}

	printf("\e[1B\e[2D");
	for (int i = 1; i < _currRoomH; i++) { // Right
		if (isDoor(_currRoomW - 1, i)) {
			printf(DRKBLUBCK);
			putBlock();
			printf(CYABCK);
		} else {
			putBlock();
		}
		printf("\e[1B\e[2D");
	}

	printf("\e[1A\e[2D");
	for (int i = 1; i < _currRoomW; i++) { // Bottom
		if (isDoor(i, _currRoomH - 1)) {
			printf(DRKBLUBCK);
			putBlock();
			printf(CYABCK);
		} else {
			putBlock();
		}
		printf("\e[4D");
	}

	printf("\e[1A");
	if (_currRoomW != MAX_SIZE) printf("\e[2C"); // edge of the map
	for (int i = 1; i < _currRoomH - 1; i++) { // Left
		if (isDoor(0, i)) {
			printf(DRKBLUBCK);
			putBlock();
			printf(CYABCK);
		} else {
			putBlock();
		}
		printf("\e[1A\e[2D");
	}
}

static void printInside(void) {
	printf("\e[1B\e[2C");
	printf(DRKBLUBCK);
	for (int i = 1; i < _currRoomH - 1; i++) {
		for (int j = 1; j < _currRoomW - 1; j++) {
			if (isNPC(j, i)) {
				NPC ret = isNPC(j, i);
				printNpcCell(ret);
				printf(DRKBLUBCK);
			} else {
				putBlock();
			}
		}
		printf("\e[1B\e[%dD", (_currRoomW - 2) << 1);
	}
}

static void printPlayer(void) {
	printf("\e[%d;%dH", _offMY+ _py + 1, ((_offMX + _px) << 1) + 1);
	printf(REDBCK); printf(WHTXT);
	putchar('P'); putchar('l');
}

void printFullMap(void) {
	printf("\e[%d;%dH", _offMY + 1, (_offMX << 1) + 1); // Center the map

	// Print walls, inside, then player
	printWalls();
	printInside();
	printPlayer();

	printf("\e[0m"); // reset colour
}

void clearFullMap(void) {
	printf("\e[1;%dH", (MAX_SIZE << 1) + 1); // go to start of deletion
	for (int i = 0; i < MAX_SIZE + 1; i++) {
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
	clear(); // Begin the sequence
	setSeed();
	clear(); // Clear and start
	
	generateFloor();

	setPx(_currRoomW >> 1);
	setPy(_currRoomH >> 1);

	printFullMap();
	printMinimap();
	removeCursor();

	char fillerText[] = "Lorem ipsum dolor sit amet consectetur adipiscing elit, sed do eiusmod tempor";
	NPC npcRet;
	while (true) {
		if (getComm() != 0) {
			// Check if we're quitting
			if (_dir == 'q') break;

			if (move()) {

			} else if (changeRoom()) {
				clearFullMap();
				printFullMap();
			} else if (openMapMode()) {
				// Should have closed map 
				printFullMap();
				printMinimap();
			} else if ((npcRet = isNPC(_px, _py)) && interactNPC(npcRet)) {

			} else if (guessRoom()) {
				while (true) if (getComm() != 0) break; 
				break;
			}
			removeCursor();
		}
	}
	
	reenableCursor();
	clear();
	FloorClear();
	return 0;
}
