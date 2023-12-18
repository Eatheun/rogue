#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "../globals/cells.h"
#include "../globals/const.h"
#include "../globals/directions.h"
#include "../headers/inputs.h"
#include "../headers/textbox.h"

static void printTBoxBorder(void) {
    for (int i = 0; i < TBOXW; i++) putchar('#');
    putchar('\n');
}

static void printTBoxFiller(void) {
    putchar('#');
    for (int i = 1; i < TBOXW - 1; i++) putchar(' ');
    putchar('#');
    putchar('\n');
}

static void printTBoxTitle(char *title) {
    // Make sure we limit the title length
    char strictTitle[TXTW + 1];
    snprintf(strictTitle, TXTW, "%s", title);

    putchar('#'); putchar(' ');
    printf("\e[1;4m"); // Set the underline and intensity
    printf("%s", strictTitle);

    // Reset the colours
    printf("\e[0m"); printf(BLKBCK); printf(WHTXT);

    // Padding
    for (int i = 2 + strlen(strictTitle); i < TBOXW - 1; i++) putchar(' ');
    putchar('#');

    // Move down
    putchar('\n');
}

static void printTBoxTxtLine(char *text, int *index) {
    putchar('#'); putchar(' ');
    if (text[*index] == ' ') (*index)++; // Check if we have extra line space at the start
    for (int i = 0; i < TXTW; i++) {
        if (text[*index] == '\0') {
            putchar(' ');
        } else {
            putchar(text[*index]);
            (*index)++;
        }
    }
    putchar(' '); putchar('#');
    putchar('\n'); // go down to start of next line
}

void printTBox(char *text, char *title) {
    printf("\e[%d;1", MAX_SIZE + BORD_OFF + ESC_OFF); // position cursor below all the fluff
    for (int i = 0; i < (DIST_FROM_MAINM >> 1); i++) putchar('\n');

    // Set colors
    printf(BLKBCK); printf(WHTXT);
    
    // Top part with title
    printTBoxBorder();
    printTBoxTitle(title);

    // Middle text block
    int index = 0;
    for (int i = 0; i < TXTH; i++) printTBoxTxtLine(text, &index);

    // Bottom part
    printTBoxBorder();

    // Go up
    printf("\e[%dF", TBOXH);
}

void closeTBox(void) {
    printf("\e[%d;1", MAX_SIZE + ESC_OFF); // position cursor below all the fluff
    printf("\e[0m");
    printf("\e[0J");
}

static void chaOptSpace(void) {
    int offset = (OPTTXTWSPLIT - 3) >> 1;
    for (int i = 0; i < offset; i++) putchar(' ');
}

static void setSelectClr(void) {
    printf(GRYBCK); printf(BLKTXT);
}

static void setUnselectClr (void) {
    printf(BLKBCK); printf(WHTXT);
}

static void changeOption(void (*setYesClr)(void), void (*setNoClr)(void)) {
    printf("\e[%d;2H", MAX_SIZE + BORD_OFF + TITLE_OFF + OPTTXTH + 1 + ESC_OFF); // set cursor position
    printf("\e[%dC", OPTTXTWSPLIT);
    setYesClr(); chaOptSpace(); printf("YES"); chaOptSpace(); 
    printf("\e[%dC", TBOXW - (OPTTXTWSPLIT << 2));
    setNoClr(); chaOptSpace(); printf("NO "); chaOptSpace();
}

// Note that atm we only accept boolean responses
bool openOptionTBox(char *text, char *title) {
    // We gotta restrict the text to fit the options
    char strictText[OPTTXTH * TXTW + 1];
    snprintf(strictText, OPTTXTH * TXTW, "%s", text);

    // Just like normal...
    printTBox(strictText, title);

    // Gotta print the yes/no options
    bool isYes = true;
    changeOption(setSelectClr, setUnselectClr);
    printf("\e[%d;1H", MAX_SIZE + ESC_OFF);

    // wait for the player response
    while (true) {
        if (getComm() != 0) {
            int tempX, tempY = 0;
            int ret;
            if (_dir == 'e') {
                closeTBox();
                break;
            } else if ((ret = handleAllDir(&tempX, &tempY)) != MAX_DIRS) {
                if (ret == LEFT && isYes == false) {
                    changeOption(setSelectClr, setUnselectClr);
                    isYes = true;
                } else if (ret == RIGHT && isYes == true) {
                    changeOption(setUnselectClr, setSelectClr);
                    isYes = false;
                }
                printf("\e[%d;1H", MAX_SIZE + ESC_OFF);
            }
        }
    }

    return isYes;
}
