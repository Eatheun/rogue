#include "floorGen.h"
#include "minimap.h"
#include "npcActions.h"

struct npcActions {
    char text[(MAX_SIZE + DIST_FROM_MAINM + MAX_CORR_SIZE) * 5];
    void (*mission)(void *args);
};
