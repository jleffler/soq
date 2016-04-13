#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define err_sysexit err_syserr

static void exec_pipeline(int cmdn, char ***cmdv)
{
    for (int i = 0; i < cmdn; i++)
    {
        printf("cmd [%d]", i);
        char **args = cmdv[i];
        while (*args != 0)
            printf(" {%s}", *args++);
        putchar('\n');
    }
    printf("EOC\n");
}

static void exec_arguments(int argc, char **argv)
{
    char ***cmdv = malloc(sizeof *cmdv * (argc/2));
    char **args = malloc(sizeof *args * (argc+1));
    int cmdn = 0;
    int argn = 0;

    cmdv[cmdn++] = &args[argn];

    for (int i=1; i < argc; i++)
    {
        char *arg = argv[i];
        printf("Processing %d [%s]\n", i, arg);
        if (strcmp(arg, "|") == 0)
        {
            if (i == 1)
                err_sysexit("Syntax error: pipe before any command");
            if (args[argn-1] == 0)
                err_sysexit("Syntax error: two pipes with no command between");
            arg = 0;
        }
        args[argn++] = arg;
        if (arg == 0)
            cmdv[cmdn++] = &args[argn];
    }
    if (args[argn-1] == 0)
        err_sysexit("Syntax error: pipe with no command following");
    args[argn] = 0;

    exec_pipeline(cmdn, cmdv);
    free(cmdv);
    free(args);
}

int main(void)
{
    char line[] = "ls | wc -l";
    int i = 1;
    char *p = strtok(line, " ");
    char *array[50];

    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    exec_arguments(i, array);

    //char argv[][10] = { "apathy", "ls" , "|", "wc", "-l", 0 };
    //exec_arguments(4, argv);
    return 0;
}
