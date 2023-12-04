#ifndef ENEMIES_H
#define ENEMIES_H

#define DEF_COST 2
#define MAX_ENS 4

enum enLvl {
	SKELETON = 3,
	GOBLIN = 5,
	OGRE = 7,
	DRAGON = 10
};

typedef struct enemy *Enemy;

Enemy EnemyNew(int enLvl);
void EnemyFree(Enemy enemy);
int getEnEnLvl(Enemy enemy);
void setEnEnLvl(Enemy enemy, int enLvl);
int getEnAtk(Enemy enemy);
void setEnAtk(Enemy enemy, int atk);
int getEnHp(Enemy enemy);
void setEnHp(Enemy enemy, int hp);
int getEnDef(Enemy enemy);
void setEnDef(Enemy enemy, int def);
int getEnCoor(Enemy enemy);
void setEnCoor(Enemy enemy, int x, int y);

#endif // ENEMIES_H