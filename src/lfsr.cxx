#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#include "inputs.h"
#include "lfsr.h"

void setSeed(void) {
	unsigned int id = (unsigned int) time(NULL);
	seed = id ^ (id << 1); // fancy hashing

	printf("\e[96m<Press any key to start>\e[?25l\e[0m");
	while (true) {
		if (getComm() != 0) {
			int val = _dir ^ (seed & 0xff);
			int ret = rand(_dir) % 256;
			unsigned bits = ret | (ret << 8) | (ret << 16) | (ret << 24);
			seed ^= ret;
			break;
		}
	}
}

int rand(int num) {
	unsigned int bits = 0;
	
	bits ^= seed >> 0;
	bits ^= seed >> 10;
	bits ^= seed >> 30;
	bits ^= seed >> 31;
	bits &= 1u;
	
	seed = (seed >> 1) | (bits << 31);
	
	return seed % num;
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
