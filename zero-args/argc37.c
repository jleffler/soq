#include <assert.h>
#include <stdio.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    assert(argv[argc] == NULL);
    err_setarg0(argv[0]);
    printf("argc = %d\n", argc);
    if (argc == 0)
        err_remark("it is very unusual for a program to be executed with argc == 0\n");
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = '%s'\n", i, argv[i]);
    }
    return 0;
}
