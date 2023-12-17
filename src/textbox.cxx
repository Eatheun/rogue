#include <stdio.h>
#include <string.h>

#include "../globals/cells.h"
#include "../globals/const.h"
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

// Note that atm we only accept boolean responses
bool openOptionTBox(char *text, char *title) {
    // We gotta restrict the text to fit the options
    char strictText[OPTTXTH * TXTW + 1];
    snprintf(strictText, OPTTXTH * TXTW, "%s", text);

    // Just like normal...
    printTBox(strictText, title);

    // wait for the player response

    return true;
}

void closeTBox(void) {
    printf("\e[%d;1", MAX_SIZE + ESC_OFF); // position cursor below all the fluff
    printf("\e[0m");
    printf("\e[0J");
}
