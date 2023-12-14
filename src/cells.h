#ifndef CELLS_H
#define CELLS_H

//////////////////////// BACKGROUNDS ////////////////////////

#define BLKBCK "\e[48;2;0;0;0m"
#define CYABCK "\e[48;5;116m"
#define DRKBLUBCK "\e[48;5;17m"
#define REDBCK "\e[48;5;196m"

//////////////////////// TEXT ////////////////////////

#define WHTXT "\e[38;2;255;255;255m"

//////////////////////// CELLS ////////////////////////

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
	JESTER,
	LIBRARIAN,
	PLAYWRIGHT,
	MASON,
	CARPENTER,
	MINSTREL,
	NUM_NPC_TYPES
};

#define MERCHANT_CELL "\e[48;2;255;0;0m\e[38;5;231mMe"
#define SMITH_CELL "\e[48;2;255;0;0m\e[38;5;95mSm"
#define BARBER_CELL "\e[48;2;255;0;0m\e[38;5;82mBa"
#define TAILOR_CELL "\e[48;2;255;0;0m\e[38;5;221mTa"
#define ARTIST_CELL "\e[48;2;255;0;0m\e[38;5;231mAr"
#define COOK_CELL "\e[48;2;255;0;0m\e[38;5;231mCk"
#define COBBLER_CELL "\e[48;2;255;0;0m\e[38;5;231mCb"
#define CARTOGRAPHER_CELL "\e[48;2;255;0;0m\e[38;5;231mCa"
#define SORCERER_CELL "\e[48;2;255;0;0m\e[38;5;231mSo"
#define JESTER_CELL "\e[48;2;255;0;0m\e[38;5;231mJe"
#define LIBRARIAN_CELL "\e[48;2;255;0;0m\e[38;5;231mLi"
#define PLAYWRIGHT_CELL "\e[48;2;255;0;0m\e[38;5;231mPw"
#define MASON_CELL "\e[48;2;255;0;0m\e[38;5;231mMa"
#define CARPENTER_CELL "\e[48;2;255;0;0m\e[38;5;231mCr"
#define MINSTREL_CELL "\e[48;2;255;0;0m\e[38;5;231mMi"

static const char *npcCells[NUM_NPC_TYPES] = {
    MERCHANT_CELL,
    SMITH_CELL,
    BARBER_CELL,
    TAILOR_CELL,
    ARTIST_CELL,
    COOK_CELL,
    COBBLER_CELL,
    CARTOGRAPHER_CELL,
    SORCERER_CELL,
	JESTER_CELL,
	LIBRARIAN_CELL,
	PLAYWRIGHT_CELL,
	MASON_CELL,
	CARPENTER_CELL,
	MINSTREL_CELL,
};

#endif // CELLS_H