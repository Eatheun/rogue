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

void printMinimap(void);

#endif // MINIMAP_H