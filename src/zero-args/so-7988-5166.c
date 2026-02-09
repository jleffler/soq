#include <stdio.h>

// When calling `just`, pass a different amount of arguments: `just run 6 arg1 arg2 ...;`
int main(int argc, char* argv[])
{
    // This is impossible because there is always a command name
    if (argc <= 0) {
        printf("Impossible! No arguments have been passed!\n");
    }

    if (argc == 1) {
        printf("One argument has been passed (argv[0] = [%s])\n", argv[0]);
    }

    if (argc == 2) {
        printf("Two arguments have been passed (argv[0] = [%s], argv[1] = [%s])\n", argv[0], argv[1]);
    }
}
