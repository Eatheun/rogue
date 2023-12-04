#ifndef CELLS_H
#define CELLS_H

#define PLAYER "\e[48;5;196m\e[38;5;255mPP"
#define FLOOR "\e[48;5;17m  "
#define WALL "\e[48;5;116m  "

#define SKELETON_CELL "\e[48;5;88m\e[38;5;231mSS"
#define GOBLIN_CELL "\e[48;5;88m\e[38;5;95mGG"
#define OGRE_CELL "\e[48;5;88m\e[38;5;82mOO"
#define DRAGON_CELL "\e[48;5;88m\e[38;5;221mDD"

// format: 4-digit int, xxyy
//	e.g. 1034 = (10, 34)
typedef int Coor;

#endif // CELLS_H