#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#include "../headers/inputs.h"
#include "../headers/lfsr.h"

void setSeed(void) {
	unsigned int id = (unsigned int) time(NULL);
	seed = id ^ (id << 1); // fancy hashing

	printf("\e[1;4;96m<Press any key to start>\e[?25l\e[0m");
	while (true) {
		if (getComm() != 0) {
			int val = _dir ^ (seed & 0xff);
			int ret = rand(_dir) % 256;
			unsigned bits = ret | (ret << 8) | (ret << 16) | (ret << 24);
			seed ^= ret;
			break;
		}
	}

	seed &= 0x7f007f00;
}

static int lfsrRand(void) {
	unsigned int bits = 0;
	
	bits ^= seed >> 0;
	bits ^= seed >> 10;
	bits ^= seed >> 30;
	bits ^= seed >> 31;
	bits &= 1u;
	
	seed = (seed >> 1) | (bits << 31);

	return seed;
}

static int cantor(int x, int y) {
	return (x + y) * (x + y + 1) / 2 + y;
}

static int cantorRand(void) {
	int first2b = seed >> 16;
	int second2b = seed & 0xffff;
	seed = cantor(first2b, second2b);
	
	return seed;
}

int rand(int num) {
	unsigned int randUInt = (unsigned int) cantorRand();
	return randUInt % num;
}

bool chance(int numer, int denom) {
	// Getting as random as humanly possible
	int val = (int) time(NULL);
	int split = val & 0x10;
	val = (val >> 0x10) | split;
	val ^= val >> 1;
	val %= 100;
	
	val = rand(val & 0xff);
	for (int i = denom; i > numer; i--) {
		if (val % i == 0) return false; 
	}
	
	return true;
}
