/*
** How to create a pipeline of N processes?
*/

/* stderr.h */
#ifndef STDERR_H_INCLUDED
#define STDERR_H_INCLUDED

static void err_setarg0(const char *argv0);
static void err_sysexit(char const *fmt, ...);
static void err_syswarn(char const *fmt, ...);

#endif /* STDERR_H_INCLUDED */

/* pipeline.c */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
/*#include "stderr.h"*/

typedef int Pipe[2];

/* exec_nth_command() and exec_pipe_command() are mutually recursive */
static void exec_pipe_command(int ncmds, char ***cmds, Pipe output);

/* With the standard output plumbing sorted, execute Nth command */
static void exec_nth_command(int ncmds, char ***cmds)
{
    assert(ncmds >= 1);
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
            exec_pipe_command(ncmds-1, cmds, input);
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

/* Given pipe, plumb it to standard output, then execute Nth command */
static void exec_pipe_command(int ncmds, char ***cmds, Pipe output)
{
    assert(ncmds >= 1);
    /* Fix stdout to write end of pipe */
    dup2(output[1], 1);
    close(output[0]);
    close(output[1]);
    exec_nth_command(ncmds, cmds);
}

/* Execute the N commands in the pipeline */
static void exec_pipeline(int ncmds, char ***cmds)
{
    assert(ncmds >= 1);
    pid_t pid;
    if ((pid = fork()) < 0)
        err_syswarn("Failed to fork");
    if (pid != 0)
        return;
    exec_nth_command(ncmds, cmds);
}

/* Collect dead children until there are none left */
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

static void exec_arguments(int argc, char **argv)
{
    /* Split the command line into sequences of arguments */
    /* Break at pipe symbols as arguments on their own */
    char **cmdv[argc/2];            // Way too many
    char  *args[argc+1];
    int cmdn = 0;
    int argn = 0;

    cmdv[cmdn++] = &args[argn];
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
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
}

#include <signal.h>

typedef void (*SigHandler)(int signum);

static void sigchld_status(void)
{
    const char *handling = "Handler";
    SigHandler sigchld = signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, sigchld);
    if (sigchld == SIG_IGN)
        handling = "Ignored";
    else if (sigchld == SIG_DFL)
        handling = "Default";
    printf("SIGCHLD set to %s\n", handling);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    sigchld_status();
    if (argc == 1)
    {
        /* Run the built in pipe-line */
        exec_pipeline(ncmds, cmds); 
    }
    else
    {
        /* Run command line specified by user */
        exec_arguments(argc, argv);
    }
    corpse_collector();
    return(0);
}

/* stderr.c */
/*#include "stderr.h"*/
#include <stdio.h>
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
