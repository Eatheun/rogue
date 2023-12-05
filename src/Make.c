#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <dirent.h>

#define GCC_PATH "C:\\msys64\\ucrt64\\bin\\gcc"

#define WHITESPACE 80

#define RESET "\e[0m"
#define WHTXT "\e[38;5;255m"
#define BLKBK "\e[48;5;0m"
#define MACCASXT "\e[1m\e[48;2;255;255;0m\e[38;2;255;0;0m"

int main(void) {
    char *args[32];
    args[0] = GCC_PATH;
    int argIndex = 1;

    struct dirent *curr;
    DIR *cwd = opendir("./");
    char *fn;
    while (curr = readdir(cwd)) {
        fn = curr->d_name;
        if (strcmp(fn, "Make.c") != 0 && strstr(fn, ".cxx") != NULL) {
            // Cool colours :o
            int cuR = 72 + 20 * argIndex;
            int cuG = 48 + 12 * argIndex;
            int cuB = 256 + (-16) * argIndex;
            char cuBack[64];
            sprintf(cuBack, "\e[48;2;%d;%d;%dm", cuR, cuG, cuB);

            printf("%s%s%s", cuBack, WHTXT, fn);
            for (int i = 0; i < WHITESPACE - strlen(fn); i++) putchar(' ');
            printf(RESET);
            putchar('\n');
            args[argIndex] = strdup(fn);
            argIndex++;
        }
    }
    args[argIndex] = "-o";
    argIndex++;
    args[argIndex] = "../rogue";
    argIndex++;
    args[argIndex] = NULL;

    printf("\n%s%sRunning:\n%sgcc ", BLKBK, WHTXT, MACCASXT);
    for (int i = 1; i < argIndex; i++) printf("%s ", args[i]);
    printf(RESET);
    putchar('\n');
    spawnvp(P_WAIT, GCC_PATH, args);

    for (int i = 1; i < argIndex - 2; i++) free(args[i]);

    closedir(cwd);
    return 0;
}
