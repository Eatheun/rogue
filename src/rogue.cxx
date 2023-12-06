#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cells.h"
#include "directions.h"
#include "floorGen.h"
#include "npc.h"
#include "inputs.h"
#include "lfsr.h"
#include "movements.h"
#include "playerPos.h"

//////////////////////////////// ANSI Functions ////////////////////////////////

void clear(void)
{
	printf("\e[2J\n\e[1;1H");
}

void printFullMap(void)
{
	for (int i = 0; i < _currRoomH; i++)
	{
		for (int j = 0; j < _currRoomW; j++)
		{
			if (ISPLAYER(j, i))
			{
				printf(PLAYER);
			}
			else if (ISWALL(j, i) && !isDoor(j, i))
			{
				printf(WALL);
			}
			else if (isNPC(j, i) != NUM_NPC_TYPES)
			{
				int ret = isNPC(j, i);
				printf("%s", npcCells[ret]);
			}
			else
			{
				printf(FLOOR);
			}
			printf("\e[0m"); // reset colour
		}
		putchar('\n');
	}
}

// We don't want a weird cursor on the screen
void removeCursor(void)
{
	printf("\e[%d;1H\e[?25l", _currRoomH + 1); // Position cursor at the bottom and hide it
}

void reenableCursor(void) {
	printf("\e[1;1H\e[?25h");
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(int argc, char **argv)
{
	clear();
	setSeed();
	clear(); // Clear and start
	
	generateFloor();

	setPx(_currRoomW / 2);
	setPy(_currRoomH / 2);

	printFullMap();
	removeCursor();

	while (true) {
		if (getComm() != 0) {
			// Check if we're quitting
			if (_dir == 'q') break;

			if (!move()) {
				if (changeRoom()) {
					clear();
					printFullMap();
				}
			}
			removeCursor();
		}
	}
	
	reenableCursor();
	clear();
	FloorClear();
	return 0;
}
