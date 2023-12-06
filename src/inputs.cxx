#include <conio.h>

#include "inputs.h"
#include "directions.h"

int getDir() {
    return dir;
}

char getComm(void) {
    return dir = getch();
}

int handleWASD(int *tx, int *ty) {
    if (GOUP(_dir)) {
        (*ty)--;
        return UP;
    } else if (GOLEFT(_dir)) {
        (*tx)--;
        return LEFT;
    } else if (GODOWN(_dir)) {
        (*ty)++;
        return DOWN;
    } else if (GORIGHT(_dir)) {
        (*tx)++;
        return RIGHT;
    }
    return MAX_DIRS;
}

int handleArrows(int *tx, int *ty) {
    // Check for the first 16 and 8 bits
    if (_dir == 0x1b) {
        getComm();
        getComm();
    } else if (_dir == 0x5b) {
        getComm();
    }
    
    // Process
    if (_dir == UP_ARROW) {
        (*ty)--;
        return UP;
    } else if (_dir == LEFT_ARROW) {
        (*tx)--;
        return LEFT;
    } else if (_dir == DOWN_ARROW) {
        (*ty)++;
        return DOWN;
    } else if (_dir == RIGHT_ARROW) {
        (*tx)++;
        return RIGHT;
    }
    return MAX_DIRS;
}

int handleAllDir(int *tx, int *ty) {
    int ret = handleWASD(tx, ty);
    if (ret == MAX_DIRS) {
        ret = handleArrows(tx, ty);
    }

    return ret;
}
