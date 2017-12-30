/* SO 4672-0692 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARGVMAX 100
#define LINESIZE 1024
#define PIPESYMB "|"
#define EXITSYMB "exit"

static void logmsg(const char *func, const char *fmt, ...)
{
    char buffer[1024];
    char *base = buffer + snprintf(buffer, sizeof(buffer), "%d: %s(): ", (int)getpid(), func);
    va_list args;
    va_start(args, fmt);
    vsnprintf(base, sizeof(buffer) - (base - buffer), fmt, args);
    va_end(args);
    fprintf(stderr, "%s\n", buffer);
}

static void dump_fds(const char *func, int max_fd)
{
    char buffer[64] = "fds ";
    char *base = buffer + strlen(buffer);
    for (int i = 0; i < max_fd; i++)
    {
        struct stat sb;
        if (fstat(i, &sb) == 0)
            *base++ = 'o';
        else
            *base++ = '-';
    }
    *base = '\0';
    logmsg(func, "%s", buffer);
}

static void dump_argv(const char *func, const char *tag, char **argv)
{
    logmsg(func, "%s:", tag);
    int i = 0;
    while (*argv != 0)
        logmsg(func, "argv[%d] = \"%s\"", i++, *argv++);
    dump_fds(func, 20);
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
    logmsg(__func__, "(%d closed) (%d to 1)", mypipe[0], mypipe[1]);
    dup2(mypipe[1], 1);
    close(mypipe[0]);
    close(mypipe[1]);
}

static void changeInput(int mypipe[])
{
    logmsg(__func__, "(%d to 0) (%d closed)", mypipe[0], mypipe[1]);
    dup2(mypipe[0], 0);
    close(mypipe[1]);
    close(mypipe[0]);
}

static void wait_for(const char *func, int pid)
{
    int corpse;
    int status;
    dump_fds(__func__, 20);
    while ((corpse = waitpid(pid, &status, 0)) > 0)
    {
        logmsg(func, "child %d exit status 0x%.4X", corpse, status);
        if (pid == 0 || corpse == pid)
            break;
    }
}

static void pipeFork(char *argv[], int i, int mypipe[])
{
    int h = i;
    int mypipe1[2];
    int found = 0;
    dump_argv(__func__, "entry", &argv[h]);
    while ((argv[h] != NULL) && !found)
    {
        if (!(strcmp(argv[h], PIPESYMB)))
        {
            argv[h] = NULL;
            found = 1;
        }
        h++;
    }
    if (found)
    {
        if (pipe(mypipe1) == -1)
            abort();
        logmsg(__func__, "pipe (%d,%d)", mypipe1[0], mypipe1[1]);
    }
    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        exit(1);
    case 0:
        logmsg(__func__, "- child");
        changeInput(mypipe);
        if (found)
            changeOutput(mypipe1);
        dump_argv(__func__, "execvp", &argv[i]);
        execvp(argv[i], &argv[i]);
        perror("exec");
        exit(1);
    default:
        logmsg(__func__, "forked child %d", pid);
        if (found)
        {
            close(mypipe[0]);
            close(mypipe[1]);
            dump_argv(__func__, "recurse", &argv[h]);
            pipeFork(argv, h, mypipe1);
        }
        break;
    }
    if (found)
    {
        logmsg(__func__, "close %d %d", mypipe1[0], mypipe1[1]);
        close(mypipe1[0]);
        close(mypipe1[1]);
    }
    logmsg(__func__, "close %d %d", mypipe[0], mypipe[1]);
    close(mypipe[0]);
    close(mypipe[1]);
    logmsg(__func__, "waiting for %d", pid);
    wait_for(__func__, pid);
}

static void runcommand(char *argv[])
{
    int i = 0;
    int mypipe[2];
    int found = 0;
    fflush(0);
    if (!(strcmp(argv[0], EXITSYMB)))
        exit(0);
    if (pipe(mypipe) == -1)
        abort();
    logmsg(__func__, "pipe (%d,%d)", mypipe[0], mypipe[1]);
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
        logmsg(__func__, "- child");
        if (found)
            changeOutput(mypipe);
        dump_argv(__func__, "execvp", argv);
        execvp(argv[0], argv);
        perror("exec");
        exit(1);
    default:
        logmsg(__func__, "forked child %d", pid);
        if (found)
        {
            dump_argv(__func__, "call-pipeFork", &argv[i]);
            pipeFork(argv, i, mypipe);
        }
        break;
    }
    logmsg(__func__, "close %d %d", mypipe[0], mypipe[1]);
    close(mypipe[0]);
    close(mypipe[1]);
    logmsg(__func__, "waiting for %d", pid);
    wait_for(__func__, pid);
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
            dump_argv(__func__, "after reading", av);
            runcommand(av);
        }
        printf("> ");
        fflush(stdout);
    }
    putchar('\n');

    return 0;
}
