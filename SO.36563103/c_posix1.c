#define _XOPEN_SOURCE 500

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_LEN 1024

extern char *strdup(const char *);

/* One way to create a pipeline of N processes */

/* stderr.h */
#ifndef STDERR_H_INCLUDED
#define STDERR_H_INCLUDED

static void err_setarg0(const char *argv0);
static void err_sysexit(char const *fmt, ...);
static void err_syswarn(char const *fmt, ...);

#endif /* STDERR_H_INCLUDED */

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
            exec_pipe_command(ncmds - 1, cmds, input);
        }
        /* Fix standard input to read end of pipe */
        dup2(input[0], 0);
        close(input[0]);
        close(input[1]);
    }
    execvp(cmds[ncmds - 1][0], cmds[ncmds - 1]);
    err_sysexit("Failed to exec %s", cmds[ncmds - 1][0]);
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
    pid_t pid;
    assert(ncmds >= 1);

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
    int status;
    while ((corpse = waitpid(0, &status, 0)) != -1)
    {
        fprintf(stderr, "%d: child %d status 0x%.4X\n",
                (int)parent, (int)corpse, status);
    }
}

/*  who | awk '{print $1}' | sort | uniq -c | sort -n */

static void dump_argv(const char *tag, int argc, char **argv)
{
    assert(argv != 0 && tag != 0);
    printf("%s: (%d)", tag, argc);
    for (int i = 0; i < argc; i++)
        printf(" {%s}", (argv[i] == NULL) ? "(null)" : argv[i]);
    putchar('\n');
    fflush(stdout);
    assert(argv[argc] == 0);
}

static void dump_pipeline(int cmdn, char ***cmdv)
{
    printf("SOC\n");
    for (int i = 0; i < cmdn; i++)
    {
        printf("cmd [%d]", i);
        char **args = cmdv[i];
        while (*args != 0)
            printf(" {%s}", *args++);
        putchar('\n');
    }
    printf("EOC\n");
    fflush(stdout);
}

static void exec_arguments(int argc, char **argv)
{
    dump_argv("Entering exec_arguments", argc, argv);
    /* Split the command line into sequences of arguments */
    /* Break at pipe symbols as arguments on their own */

    char ***cmdv = malloc(sizeof *cmdv * (argc / 2));
    char **args = malloc(sizeof *args * (argc + 1));
    int cmdn = 0;
    int argn = 0;

    cmdv[cmdn++] = &args[argn];

    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        //printf("Processing %d [%s]\n", i, arg);
        if (strcmp(arg, "|") == 0)
        {
            if (i == 1)
                err_sysexit("Syntax error: pipe before any command");
            if (args[argn - 1] == 0)
                err_sysexit("Syntax error: two pipes with no command between");
            arg = 0;
        }
        args[argn++] = arg;
        if (arg == 0)
            cmdv[cmdn++] = &args[argn];
    }
    if (args[argn - 1] == 0)
        err_sysexit("Syntax error: pipe with no command following");
    args[argn] = 0;

    dump_pipeline(cmdn, cmdv);
    exec_pipeline(cmdn, cmdv);
    free(cmdv);
    free(args);
}

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

static bool AllWhiteSpace(char *source)
{
    unsigned char c;
    while (isspace(c = *source))
        source++;
    return(c == '\0');
}

int main(int argc, char *argv[])
{
    err_setarg0(argv[argc-argc]);

    while (1)
    {
        char *p;
        char *array[6];
        char line[BUFFER_LEN];
        size_t length;
        long time;
        struct timeval time_start;
        struct timeval time_end;

        printf("miniShell>> ");
        fflush(stdout);
        if (!fgets(line, BUFFER_LEN, stdin))
        {
            putchar('\n');
            break;
        }

        if (AllWhiteSpace(line))
            continue;

        length = strlen(line);
        if (line[length - 1] == '\n')
            line[length - 1] = '\0';

        gettimeofday(&time_start, NULL);

        printf("Command line: %s\n", line);
        int i = 1;
        p = strtok(line, " ");

        array[0] = NULL;
        while (p != NULL)
        {
            array[i++] = p;
            p = strtok(NULL, " ");
        }
        array[i] = NULL;
        dump_argv("Before exec_arguments", i, array);
        exec_arguments(i, array);
        corpse_collector();

        gettimeofday(&time_end, NULL);
        time = (time_end.tv_sec  - time_start.tv_sec) * 1000000 +
                time_end.tv_usec - time_start.tv_usec;
        printf("Execution time %ld.%03ld ms\n", time / 1000, time % 1000);
    }

    return(0);
}
