#ifndef ROGUE_INPUT_H
#define ROGUE_INPUT_H

#define GOUP(c) (c == 'w')
#define GOLEFT(c) (c == 'a')
#define GODOWN(c) (c == 's')
#define GORIGHT(c) (c == 'd')

#define _dir getDir()

static char dir;

int getDir(void);
char getComm(void);
int handleWASD(int *tx, int *ty);
int handleArrows(int *tx, int *ty);
int handleAllDir(int *tx, int *ty);
void awaitRes(char input);

#endif // ROGUE_INPUT_H