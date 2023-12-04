#ifndef LFSR_H
#define LFSR_H

static int seed;

void setSeed();
int rand(int num);
bool chance(int numer, int denom);

#endif // LFSR_H