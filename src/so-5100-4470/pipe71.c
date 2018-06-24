#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stderr.h"

#define BUFSIZE 100

static char const *errMsgPipe = "signal handled SIGPIPE\n";
static int errMsgPipeLen;

static void handler(int x)
{
    if (x == SIGPIPE)
        write(2, errMsgPipe, errMsgPipeLen);
}

static inline void print_bool(const char *tag, bool value)
{
    printf("  %5s: %s\n", (value) ? "true" : "false", tag);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    bool sig_ignore = false;
    bool sig_handle = false;
    bool after_fork = false;
    bool before_fork = false;
    bool parent_doze = false;
    static const char usestr[] = "[-abdhi]";

    int opt;
    while ((opt = getopt(argc, argv, "abdhi")) != -1)
    {
        switch (opt)
        {
        case 'a':
            after_fork = true;
            break;
        case 'b':
            before_fork = true;
            break;
        case 'd':
            parent_doze = true;
            break;
        case 'h':
            sig_handle = true;
            break;
        case 'i':
            sig_ignore = true;
            break;
        default:
            err_usage(usestr);
        }
    }

    if (optind != argc)
        err_usage(usestr);

    /* Both these happen naturally - but should be explicit when printing configuration */
    if (sig_handle && sig_ignore)
        sig_ignore = false;
    if (before_fork && after_fork)
        after_fork = false;

    printf("Configuration:\n");
    print_bool("Close read fd before fork", before_fork);
    print_bool("Close read fd after  fork", after_fork);
    print_bool("SIGPIPE handled", sig_handle);
    print_bool("SIGPIPE ignored", sig_ignore); 
    print_bool("Parent doze", parent_doze);

    err_setlogopts(ERR_PID);

    errMsgPipeLen = strlen(errMsgPipe);
    char bufin[BUFSIZE] = "empty";
    char bufout[] = "hello soner";
    int bytesin;
    pid_t childpid;
    int fd[2];

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = 0;
    sigfillset(&sa.sa_mask);
    sa.sa_handler = SIG_DFL;
    if (sig_ignore)
        sa.sa_handler = SIG_IGN;
    if (sig_handle)
        sa.sa_handler = handler;
    if (sigaction(SIGPIPE, &sa, 0) != 0)
        err_syserr("sigaction(SIGPIPE) failed: ");

    printf("Parent: %d\n", (int)getpid());

    if (pipe(fd) == -1)
        err_syserr("pipe failed: ");

    if (before_fork)
        close(fd[0]);

    int val = -999;
    bytesin = strlen(bufin);
    childpid = fork();
    if (childpid == -1)
        err_syserr("fork failed: ");

    if (after_fork)
        close(fd[0]);

    if (childpid)
    {
        if (parent_doze)
            sleep(1);
        val = write(fd[1], bufout, strlen(bufout) + 1);
        if (val < 0)
            err_syserr("write to pipe failed: ");
        err_remark("Parent wrote %d bytes to pipe\n", val);
    }
    else
    {
        bytesin = read(fd[0], bufin, BUFSIZE);
        if (bytesin < 0)
            err_syserr("read from pipe failed: ");
        err_remark("Child read %d bytes from pipe\n", bytesin);
    }

    fprintf(stderr, "[%ld]:my bufin is {%.*s}, my bufout is {%s}\n",
            (long)getpid(), bytesin, bufin, bufout);

    return 0;
}
