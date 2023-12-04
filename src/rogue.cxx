#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cells.h"
#include "directions.h"
#include "floorGen.h"
#include "enemies.h"
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
			else if (isEnemy(j, i) != 0)
			{
				int ret = isEnemy(j, i);
				if (ret == SKELETON) {
					printf(SKELETON_CELL);
				} else if (ret == GOBLIN) {
					printf(GOBLIN_CELL);
				} else if (ret == OGRE) {
					printf(OGRE_CELL);
				} else if (ret == DRAGON) {
					printf(DRAGON_CELL);
				} else {
					printf(FLOOR);
				}
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

//////////////////////////////// Seed Functions ////////////////////////////////

void playerSetSeed(void)
{
	setSeed(); // Random!!!
	clear();
	printf("<Press any three keys to start>\n");
	for (int i = 0; i < 3; i++)
	{
		while (true)
		{
			if (getComm() != 0)
			{
				rand(_dir);
				break;
			}
		}
	}
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(int argc, char **argv)
{
	playerSetSeed();
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
