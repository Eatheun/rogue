#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <dirent.h>

#define GCC_PATH "C:\\msys64\\ucrt64\\bin\\gcc"

int main(void) {
    char *args[32];
    args[0] = GCC_PATH;
    int argIndex = 1;

    struct dirent *curr;
    DIR *cwd = opendir("./");
    char *fn;
    while (curr = readdir(cwd)) {
        fn = curr->d_name;
        if (strcmp(fn, "Make.c") != 0 && strstr(fn, ".c") != NULL) {
            printf("%s\n", fn);
            args[argIndex] = strdup(fn);
            argIndex++;
        }
    }
    args[argIndex] = "-o";
    argIndex++;
    args[argIndex] = "../rogue";
    argIndex++;
    args[argIndex] = NULL;

    printf("Running: ");
    for (int i = 0; i < argIndex; i++) printf("%s ", args[i]);
    putchar('\n');
    spawnvp(P_WAIT, GCC_PATH, args);

    for (int i = 1; i < argIndex - 2; i++) free(args[i]);

    closedir(cwd);
    return 0;
}
