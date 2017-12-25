/* SO 4672-0692 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARGVMAX 100
#define LINESIZE 1024
#define PIPESYMB "|"
#define EXITSYMB "exit"

int makeargv(char *s, char *argv[])
{
    if (s == NULL || argv == NULL || ARGVMAX == 0)
        return -1;

    int ntokens = 0;
    argv[ntokens] = strtok(s, " \t\n");
    while ((argv[ntokens] != NULL) && (ntokens < ARGVMAX))
    {
        ntokens++;
        argv[ntokens] = strtok(NULL, " \t\n");
    }

    argv[ntokens] = NULL;
    return ntokens;
}

void changeOutput(int mypipe[])
{
    dup2(mypipe[1], 1);
    close(mypipe[0]);
    close(mypipe[1]);
}

void changeInput(int mypipe[])
{
    dup2(mypipe[0], 0);
    close(mypipe[1]);
    close(mypipe[0]);
}

void pipeFork(char *argv[], int i, int mypipe[])
{
    int h = i;
    int mypipe1[2];
    int found = 0;
    while ((argv[h] != NULL) && !found)
    {
        if (!(strcmp(argv[h], PIPESYMB)))
        {
            argv[h] = NULL;
            found = 1;
        }
        h++;
    }
    if (pipe(mypipe1) == -1)
        abort();
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        changeInput(mypipe);
        if (found)
            changeOutput(mypipe1);
        execvp(argv[i], &argv[i]);
        perror("exec");
        exit(1);
    default:
        if (found)
            pipeFork(argv, h, mypipe1);
    }
    close(mypipe1[0]);
    close(mypipe1[1]);
    wait(NULL);
}

void runcommand(char *argv[])
{
    int i = 0;
    int mypipe[2];
    int found = 0;
    if (!(strcmp(argv[0], EXITSYMB)))
        exit(0);
    if (pipe(mypipe) == -1)
        abort();
    while ((argv[i] != NULL) && !found)
    {
        if (!(strcmp(argv[i], PIPESYMB)))
        {
            argv[i] = NULL;
            found = 1;
        }
        i++;
    }
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        if (found)
            changeOutput(mypipe);
        execvp(argv[0], argv);
        perror("exec");
        exit(1);
    default:
        if (found)
            pipeFork(argv, i, mypipe);
    }
    close(mypipe[0]);
    close(mypipe[1]);
    wait(NULL);
}

int main(int argc, char *argv[])
{
    char line[LINESIZE];
    char *av[ARGVMAX];

    printf("> ");
    fflush(stdout);
    while (fgets(line, LINESIZE, stdin) != NULL)
    {
        if (makeargv(line, av) > 0)
            runcommand(av);
        printf("> ");
        fflush(stdout);
    }

    return 0;
}
