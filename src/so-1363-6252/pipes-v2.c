/*
** How to create a pipeline of N processes?
** SO 1363-6252 C Minishell adding pipelines
*/

/* pipeline.c */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "stderr.h"

typedef int Pipe[2];

enum { DESCRIPTORS_PER_LINE = 64 };

static int vflag = 0;

static void open_fds(int max_fd)
{
    int fd;
    struct stat buff;

    fprintf(stderr, "%d: ", (int)getpid());
    for (fd = 0; fd < max_fd; fd++)
    {
        if (fstat(fd, &buff) < 0)
            putc('-', stderr);
        else
            putc('o', stderr);
        if (fd % DESCRIPTORS_PER_LINE == DESCRIPTORS_PER_LINE - 1)
            putc('\n', stderr);
    }
    if (fd % DESCRIPTORS_PER_LINE != 0)
        putc('\n', stderr);
}

static void fd_info(int fd)
{
    struct stat buff;
    if (fstat(fd, &buff) < 0)
        err_remark("Failed to fstat(%d)", fd);
    else
    {
        int flags;
        int status;
        if ((flags = fcntl(fd, F_GETFD)) < 0)
            err_syserr("Failed to fcntl(%d, F_GETFD)", fd);
        if ((status = fcntl(fd, F_GETFL)) < 0)
            err_syserr("Failed to fcntl(%d, F_GETFL)", fd);
        err_remark("fd %d: inode %lld, dev %d; F_GETFD = 0x%.4X; F_GETFL "
                   "= 0x%.4X (Mask 0x%X: Access = 0x%X)\n",
                   fd, (long long)buff.st_ino, buff.st_dev, flags, status,
                   O_ACCMODE, status & O_ACCMODE);
    }
}

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
            err_syserr("Failed to create pipe");
        err_remark("Pipe: r %d, w %d\n", input[0], input[1]);
        if (vflag)
            open_fds(10);
        if ((pid = fork()) < 0)
            err_syserr("Failed to fork");
        if (pid == 0)
        {
            /* Child */
            exec_pipe_command(ncmds - 1, cmds, input);
        }
        /* Fix standard input to read end of pipe */
        if (dup2(input[0], 0) != 0)
            err_syserr("dup2(%d, %d) in %s()", input[0], 0, __func__);
        if (close(input[0]) != 0)
            err_syserr("close(%d) in %s()", input[0], __func__);
        if (close(input[1]) != 0)
            err_syserr("close(%d) in %s()", input[0], __func__);
    }
    if (vflag)
    {
        open_fds(10);
        fd_info(0);
        err_remark("Execute: %s\n", cmds[ncmds - 1][0]);
    }
    execvp(cmds[ncmds - 1][0], cmds[ncmds - 1]);
    err_syserr("Failed to exec %s", cmds[ncmds - 1][0]);
    /*NOTREACHED*/
}

/* Given pipe, plumb it to standard output, then execute Nth command */
static void exec_pipe_command(int ncmds, char ***cmds, Pipe output)
{
    assert(ncmds >= 1);
    /* Fix stdout to write end of pipe */
    err_remark("Pipe: r %d, w %d\n", output[0], output[1]);
    if (dup2(output[1], 1) != 1)
        err_syserr("dup2(%d, %d) in %s()", output[1], 1, __func__);
    if (close(output[0]) != 0)
        err_syserr("close(%d) in %s()", output[0], __func__);
    if (close(output[1]) != 0)
        err_syserr("close(%d) in %s()", output[0], __func__);
    if (vflag)
    {
        open_fds(10);
        fd_info(0);
        err_remark("Execute: %s\n", cmds[ncmds - 1][0]);
    }
    exec_nth_command(ncmds, cmds);
}

/* Execute the N commands in the pipeline */
static void exec_pipeline(int ncmds, char ***cmds)
{
    assert(ncmds >= 1);
    pid_t pid;
    if ((pid = fork()) < 0)
        err_syserr("Failed to fork");
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
static char *cmd0[] = { "who",                0 };
static char *cmd1[] = { "awk",  "{print $1}", 0 };
static char *cmd2[] = { "sort",               0 };
static char *cmd3[] = { "uniq", "-c",         0 };
static char *cmd4[] = { "sort", "-n",         0 };

static char **cmds[] = { cmd0, cmd1, cmd2, cmd3, cmd4 };
static int ncmds = sizeof(cmds) / sizeof(cmds[0]);

static void exec_arguments(int argc, char **argv)
{
    /* Split the command line into sequences of arguments */
    /* Break at pipe symbols as arguments on their own */
    char **cmdv[argc / 2];            // Way too many
    char  *args[argc + 1];
    int cmdn = 0;
    int argn = 0;

    cmdv[cmdn++] = &args[argn];
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (strcmp(arg, "|") == 0)
        {
            if (i == 1)
                err_syserr("Syntax error: pipe before any command");
            if (args[argn - 1] == 0)
                err_syserr("Syntax error: two pipes with no command between");
            arg = 0;
        }
        args[argn++] = arg;
        if (arg == 0)
            cmdv[cmdn++] = &args[argn];
    }
    if (args[argn - 1] == 0)
        err_syserr("Syntax error: pipe with no command following");
    args[argn] = 0;
    exec_pipeline(cmdn, cmdv);
}

#include <signal.h>

typedef void (*SigHandler)(int signum);

static void sigchld_status(void)
{
    char const *handling = "Handler";
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
    int opt;
    char *argv0 = argv[0];

    setvbuf(stderr, 0, _IOLBF, BUFSIZ);
    err_setarg0(argv[0]);
    err_setlogopts(ERR_PID);
    sigchld_status();

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        switch (opt)
        {
        case 'v':
            vflag = 1;
            break;
        default:
            err_usage("[-v] [cmd1 | cmd2 ...]");
            break;
        }
    }
    argv += optind - 1;
    argc -= optind - 1;
    argv[0] = argv0;

    fd_info(0);

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

