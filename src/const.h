#ifndef CONST_H
#define CONST_H

//////////////////////// COORDINATES ////////////////////////

// format: 4-digit int, xxyy
//	e.g. 1034 = (10, 34)
typedef int Coor;

//////////////////////// FLOOR GEN ////////////////////////

#define MAX_ROOMS 9
#define MAX_NPCS_ON_FLOOR 10
#define MAX_RADIUS (MAX_ROOMS / 2 - 1)
#define MAX_FLOOR_SIZE (2 * MAX_RADIUS + 1)
#define MAX_CORR_SIZE (2 * MAX_FLOOR_SIZE + 1)
#define MIN_SIZE 11
#define MAX_SIZE 17

//////////////////////// INPUTS ////////////////////////

#define UP_ARROW_TAB 0x41
#define DOWN_ARROW_TAB 0x42
#define RIGHT_ARROW_TAB 0x43
#define LEFT_ARROW_TAB 0x44

#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define RIGHT_ARROW 0x4d
#define LEFT_ARROW 0x4b

//////////////////////// MINIMAP ////////////////////////

#define MINM_BORDER "#"
#define MINM_EMPTY " "
#define MINM_ROOM "\e[48;5;116m "
#define MINM_CURR_ROOM "\e[48;2;255;200;16m "
#define MINM_HCORR "-"
#define MINM_VCORR "|"

#define OPNM_BORDER "##\e[1B\e[2D##"
#define OPNM_EMPTY "  \e[1B\e[2D  "
#define OPNM_ROOM "\e[48;5;116m  \e[1B\e[2D  "
#define OPNM_CURR_ROOM "\e[48;2;255;200;16m  \e[1B\e[2D  "
#define OPNM_HCORR "--\e[1B\e[2D--"
#define OPNM_VCORR "||\e[1B\e[2D||"

#define ESC_OFF 1
#define BORD_OFF 1
#define CORR_MULT 2
#define DIST_FROM_MAINM 2

//////////////////////// NPC ////////////////////////

#define MAX_NPCS 4

//////////////////////// NPC ACTIONS ////////////////////////

#define TXTH 5
#define TBOXH (TXTH + ((1 + 1) << 1))
#define TBOXW (((MAX_SIZE + BORD_OFF) << 1) + DIST_FROM_MAINM + MAX_CORR_SIZE)
#define TXTW (TBOXW - ((1 + 1) << 1))

#endif // CONST_H