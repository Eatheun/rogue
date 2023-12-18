#include <stdio.h>
#include <string.h>

#include "../globals/cells.h"
#include "../headers/end.h"
#include "../headers/floorGen.h"
#include "../headers/inputs.h"
#include "../headers/textbox.h"

static void printScreen(FILE *openfp) {
    printf(WHTXT);
    char buf[128] = "";
    while (fgets(buf, 128, openfp) != NULL) {
        int lineLen = strlen(buf);
        for (int i = 0; i < lineLen; i++) {
            if (buf[i] == '#') {
                printf(PURPBCK);
            } else if (buf[i] == '@') {
                printf(WHTBCK);
            } else if (buf[i] == ' ') {
                printf(BLKBCK);
            } else if (buf[i] == '$') {
                printf(GMOSHDBCK);
            } else {
                printf("\e[0m");
            }
            if (buf[i] == '\n') {
                putchar(buf[i]);
            } else {
                putchar(' '); putchar(' ');
            }
        }
    }
    fclose(openfp);
}

static void gameWin(void) {
    char fp[] = "./data/screens/gameWin.txt";
    FILE *openfp = fopen(fp, "r");
    if (openfp == NULL) fprintf(stderr, "Missing file %s\n", fp);

    printScreen(openfp);
}

static void gameOver(void) {
    char fp[] = "./data/screens/gameOver.txt";
    FILE *openfp = fopen(fp, "r");
    if (openfp == NULL) fprintf(stderr, "Missing file %s\n", fp);

    printScreen(openfp);
}

// Note that we assume that NPC tile has been checked
bool guessRoom(void) {
    char text[] = "Are you sure this is the exit?";
    char title[] = "Guess Room?";
    if (_dir == 'e' && openOptionTBox(text, title)) {
        printf("\e[1;1H\e[2J"); // clear
        if (isInEndRoom()) {
            gameWin();
        } else {
            gameOver();
        }

        return true;
    } else {
        return false;
    }
}
