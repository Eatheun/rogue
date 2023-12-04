#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#include "lfsr.h"

void setSeed(void) {
	uint32_t id = (uint32_t) time(NULL);
	seed = (id & 0xff) >> 3; // fancy hashing
	seed |= seed << 24 | seed << 16 | seed << 8; // whoooa
	seed ^= id; // whooooooooa
}

int rand(int num) {
	uint32_t bits = seed;
	
	bits ^= seed >> 1;
	bits ^= seed >> 3;
	bits ^= seed >> 27;
	bits ^= 1u;
	bits &= 0xff;
	
	seed ^= bits << 24 | bits << 16 | bits << 8 | bits;
	
	return seed % num;
}

bool chance(int numer, int denom) {
	// Getting as random as humanly possible
	uint32_t val = (uint32_t) time(NULL);
	uint32_t split = val & 0x10;
	val = (val >> 0x10) | split;
	val ^= val >> 1;
	val %= 100;
	
	val = rand(val & 0xff);
	for (int i = denom; i > numer; i--) {
		if (val % i == 0) return false; 
	}
	
	return true;
}
