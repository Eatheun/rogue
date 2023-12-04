#include <stdlib.h>

#include "cells.h"
#include "enemies.h"
#include "lfsr.h"

struct enemy {
	int enLvl;
	int atk;
	int hp;
	int def;
	Coor pos;
};

static void genStats(Enemy enemy) {
	int enLvl = enemy->enLvl;
	enemy->atk = rand(enLvl - 1);
	enemy->hp = enLvl - enemy->atk;
	enemy->def = 0;
	
	// Need to add some defense to it
	if (chance(4, 7) && enemy->hp > DEF_COST) {
		enemy->hp -= DEF_COST;
		enemy->def++;
	}
}

Enemy EnemyNew(int enLvl) {
	Enemy newEn = (Enemy) malloc(sizeof(struct enemy));
	newEn->enLvl = enLvl;
	genStats(newEn);
	newEn->pos = 0xffff; // Not to be set here
	
	return newEn;
}

void EnemyFree(Enemy enemy) {
	free(enemy);
}

int getEnEnLvl(Enemy enemy) { return enemy->enLvl; }
void setEnEnLvl(Enemy enemy, int enLvl) { enemy->enLvl = enLvl; }
int getEnAtk(Enemy enemy) { return enemy->atk; }
void setEnAtk(Enemy enemy, int atk) { enemy->atk = atk; }
int getEnHp(Enemy enemy) { return enemy->hp; }
void setEnHp(Enemy enemy, int hp) { enemy->hp = hp; }
int getEnDef(Enemy enemy) { return enemy->def; }
void setEnDef(Enemy enemy, int def) { enemy->def = def; }
int getEnCoor(Enemy enemy) { return enemy->pos; }
void setEnCoor(Enemy enemy, int x, int y) { enemy->pos = x * 100 + y; }
