/*
** How to create a pipeline of N processes?
*/

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef int Pipe[2];

static void err_setarg0(const char *argv0);
static void err_sysexit(char const *fmt, ...);
static void err_syswarn(char const *fmt, ...);

static void exec_last_command(int ncmds, char ***cmds, Pipe output)
{
    assert(ncmds >= 1);
    /* Fix stdout to write end of pipe */
    dup2(output[1], 1);
    close(output[0]);
    close(output[1]);

    if (ncmds > 1)
    {
        pid_t pid;
        Pipe input;
        if (pipe(input) != 0)
            err_sysexit("Failed to create pipe");
        if ((pid = fork()) < 0)
            err_sysexit("Failed to fork");
        if (pid == 0)
        {
            /* Child */
            exec_last_command(ncmds-1, cmds, input);
        }
        /* Fix standard input to read end of pipe */
        dup2(input[0], 0);
        close(input[0]);
        close(input[1]);
    }
    execvp(cmds[ncmds-1][0], cmds[ncmds-1]);
    err_sysexit("Failed to exec %s", cmds[ncmds-1][0]);
    /*NOTREACHED*/
}

static void exec_pipeline(int ncmds, char ***cmds)
{
    assert(ncmds >= 1);
    pid_t pid;
    if ((pid = fork()) < 0)
        err_syswarn("Failed to fork");
    if (pid != 0)
        return;

    if (ncmds > 1)
    {
        Pipe input;
        if (pipe(input) != 0)
            err_sysexit("Failed to create pipe");
        if ((pid = fork()) < 0)
            err_sysexit("Failed to fork");
        if (pid == 0)
        {
            /* Child */
            exec_last_command(ncmds-1, cmds, input);
        }
        /* Fix standard input to read end of pipe */
        dup2(input[0], 0);
        close(input[0]);
        close(input[1]);
    }
    execvp(cmds[ncmds-1][0], cmds[ncmds-1]);
    err_sysexit("Failed to exec %s", cmds[ncmds-1][0]);
    /*NOTREACHED*/
}

static void corpse_collector(void)
{
    pid_t parent = getpid();
    pid_t corpse;
    int   status;
    while ((corpse = waitpid(0, &status, 0)) != -1)
    {
        fprintf(stderr, "%d: child %d status 0x%.4X\n",
                (int)parent, (int)corpse, status);
    }
}

/*  who | awk '{print $1}' | sort | uniq -c | sort -n */
static char *cmd0[] = { "who",                0 };
static char *cmd1[] = { "awk",  "{print $1}", 0 };
static char *cmd2[] = { "sort",               0 };
static char *cmd3[] = { "uniq", "-c",         0 };
static char *cmd4[] = { "sort", "-n",         0 };

static char **cmds[] = { cmd0, cmd1, cmd2, cmd3, cmd4 };
static int   ncmds = sizeof(cmds) / sizeof(cmds[0]);

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc == 1)
        exec_pipeline(ncmds, cmds); 
    else
        err_sysexit("Too many arguments (%d)", argc);
    corpse_collector();
    return(0);
}

#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static const char *arg0 = "<undefined>";

static void err_setarg0(const char *argv0)
{
    arg0 = argv0;
}

static void err_vsyswarn(char const *fmt, va_list args)
{
    int errnum = errno;
    fprintf(stderr, "%s:%d: ", arg0, (int)getpid());
    vfprintf(stderr, fmt, args);
    if (errnum != 0)
        fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
    putc('\n', stderr);
}

static void err_syswarn(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
}

static void err_sysexit(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
    exit(1);
}
