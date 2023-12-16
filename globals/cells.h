#ifndef CELLS_H
#define CELLS_H

//////////////////////// BACKGROUNDS ////////////////////////

#define BLKBCK "\e[48;2;0;0;0m"
#define CYABCK "\e[48;5;116m"
#define DRKBLUBCK "\e[48;5;17m"
#define REDBCK "\e[48;5;196m"

//////////////////////// TEXT ////////////////////////

#define WHTXT "\e[38;2;255;255;255m"

//////////////////////// BASIC CELLS ////////////////////////

#define EMPTY ' '
#define PLAYER "\e[48;5;196m\e[38;5;255mPl"
#define FLOOR "\e[48;5;17m  "
#define WALL "\e[48;5;116m  "

//////////////////////// NPC ////////////////////////

enum npcType {
	MERCHANT,
	SMITH,
	BARBER,
	TAILOR,
	ARTIST,
	COOK,
	COBBLER,
	CARTOGRAPHER,
	SORCERER,
	JESTER,
	LIBRARIAN,
	PLAYWRIGHT,
	MASON,
	CARPENTER,
	MINSTREL,
	NUM_NPC_TYPES
};

#endif // CELLS_H