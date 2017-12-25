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

static void dump_argv(const char *tag, char **argv)
{
    fprintf(stderr, "%d: %s:\n", (int)getpid(), tag);
    int i = 0;
    while (*argv)
        fprintf(stderr, "%d [%s]\n", ++i, *argv++);
}

static int makeargv(char *s, char *argv[])
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

static void changeOutput(int mypipe[])
{
    fprintf(stderr, "%d: (%d closed) (%d to 1)\n", (int)getpid(), mypipe[0], mypipe[1]);
    dup2(mypipe[1], 1);
    close(mypipe[0]);
    close(mypipe[1]);
}

static void changeInput(int mypipe[])
{
    fprintf(stderr, "%d: (%d to 0) (%d closed)\n", (int)getpid(), mypipe[0], mypipe[1]);
    dup2(mypipe[0], 0);
    close(mypipe[1]);
    close(mypipe[0]);
}

static void wait_for(int pid)
{
    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
    {
        fprintf(stderr, "%d: child %d exit status 0x%.4X\n", (int)getpid(), corpse, status);
        if (pid == 0 || corpse == pid)
            break;
    }
}

static void pipeFork(char *argv[], int i, int mypipe[])
{
    int h = i;
    int mypipe1[2];
    int found = 0;
    dump_argv("pipeFork", &argv[h]);
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
    fprintf(stderr, "%d: %s - pipe (%d,%d)\n", (int)getpid(), __func__, mypipe1[0], mypipe1[1]);
    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        fprintf(stderr, "%d: pipeFork - child\n", (int)getpid());
        changeInput(mypipe);
        if (found)
            changeOutput(mypipe1);
        dump_argv("pipefork:execvp", &argv[i]);
        execvp(argv[i], &argv[i]);
        perror("exec");
        exit(1);
    default:
        if (found)
        {
            dump_argv("recurse-pipeFork", &argv[h]);
            pipeFork(argv, h, mypipe1);
        }
        break;
    }
    fprintf(stderr, "%d: pipeFork: close %d %d\n", (int)getpid(), mypipe1[0], mypipe1[1]);
    close(mypipe1[0]);
    close(mypipe1[1]);
    fprintf(stderr, "%d: waiting in pipeFork for %d\n", (int)getpid(), pid);
    wait_for(0);
}

static void runcommand(char *argv[])
{
    int i = 0;
    int mypipe[2];
    int found = 0;
    if (!(strcmp(argv[0], EXITSYMB)))
        exit(0);
    if (pipe(mypipe) == -1)
        abort();
    fprintf(stderr, "%d: %s - pipe (%d,%d)\n", (int)getpid(), __func__, mypipe[0], mypipe[1]);
    while ((argv[i] != NULL) && !found)
    {
        if (!(strcmp(argv[i], PIPESYMB)))
        {
            argv[i] = NULL;
            found = 1;
        }
        i++;
    }
    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        fprintf(stderr, "%d: runcommand - child\n", (int)getpid());
        if (found)
            changeOutput(mypipe);
        dump_argv("about to exec", argv);
        execvp(argv[0], argv);
        perror("exec");
        exit(1);
    default:
        if (found)
        {
            dump_argv("call-pipeFork", &argv[i]);
            pipeFork(argv, i, mypipe);
        }
        break;
    }
    fprintf(stderr, "%d: runcommand: close %d %d\n", (int)getpid(), mypipe[0], mypipe[1]);
    close(mypipe[0]);
    close(mypipe[1]);
    fprintf(stderr, "%d: waiting in runcommand for %d\n", (int)getpid(), pid);
    wait_for(0);
}

int main(void)
{
    char line[LINESIZE];
    char *av[ARGVMAX];

    printf("> ");
    fflush(stdout);
    while (fgets(line, LINESIZE, stdin) != NULL)
    {
        if (makeargv(line, av) > 0)
        {
            dump_argv("after reading", av);
            runcommand(av);
        }
        printf("> ");
        fflush(stdout);
    }

    return 0;
}
