#ifndef MINIMAP_H
#define MINIMAP_H

#define BLKBCK "\e[48;2;0;0;0m"
#define WHTXT "\e[38;2;255;255;255m"
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

//////////////////////// MINI ////////////////////////

void printMinimap(void);
void remPrevRoomMinM(int prevFx, int prevFy);
void updateMinM(int newFx, int newFy, int corrX, int corrY, bool isHCorrUpdate);

//////////////////////// OPEN ////////////////////////

bool openMapMode(void);

#endif // MINIMAP_H