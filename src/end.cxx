#include <stdio.h>

#include "../globals/cells.h"
#include "../headers/end.h"
#include "../headers/floorGen.h"
#include "../headers/inputs.h"

static void printWin(void) {
    printf("\e[1B");
    printf("YOU WIN!        ");
    printf("\e[16D");
}

static void printLoss(void) {
    printf("\e[1B");
    printf("You lose :(     ");
    printf("\e[16D");
}

// Note that we assume that NPC tile has been checked
bool guessRoom(void) {
    if (_dir == 'e') {
        if (isInEndRoom()) {
            printWin();
        } else {
            printLoss();
        }

        return true;
    } else {
        return false;
    }
}
