#ifndef PLAYERPOS_H
#define PLAYERPOS_H

#define _px getPx()
#define _py getPy()

static int px, py;

int getPx(void);
void setPx(int tx);
int getPy(void);
void setPy(int ty);
void removePlayer(void);
void updatePlayer(void);

#endif // PLAYERPOS_H