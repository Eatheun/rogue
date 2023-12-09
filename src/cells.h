#ifndef CELLS_H
#define CELLS_H

#define CYABCK "\e[48;5;116m"
#define DRKBLUBCK "\e[48;5;17m"
#define REDBCK "\e[48;5;196m"
#define EMPTY ' '

#define PLAYER "\e[48;5;196m\e[38;5;255mPl"
#define FLOOR "\e[48;5;17m  "
#define WALL "\e[48;5;116m  "

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
	NUM_NPC_TYPES
};

#define MERCHANT_CELL "\e[48;5;88m\e[38;5;231mMe"
#define SMITH_CELL "\e[48;5;88m\e[38;5;95mSm"
#define BARBER_CELL "\e[48;5;88m\e[38;5;82mBa"
#define TAILOR_CELL "\e[48;5;88m\e[38;5;221mTa"
#define ARTIST_CELL "\e[48;5;88m\e[38;5;231mAr"
#define COOK_CELL "\e[48;5;88m\e[38;5;231mCk"
#define COBBLER_CELL "\e[48;5;88m\e[38;5;231mCb"
#define CARTOGRAPHER_CELL "\e[48;5;88m\e[38;5;231mCa"
#define SORCERER_CELL "\e[48;5;88m\e[38;5;231mSo"

static const char *npcCells[NUM_NPC_TYPES] = {
    MERCHANT_CELL,
    SMITH_CELL,
    BARBER_CELL,
    TAILOR_CELL,
    ARTIST_CELL,
    COOK_CELL,
    COBBLER_CELL,
    CARTOGRAPHER_CELL,
    SORCERER_CELL
};

// format: 4-digit int, xxyy
//	e.g. 1034 = (10, 34)
typedef int Coor;

#endif // CELLS_H