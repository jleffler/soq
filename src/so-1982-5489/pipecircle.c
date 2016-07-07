/* SO 19825489 */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

enum { BUFFER_SIZE = 1024 };

typedef int Pipe[2];

static int debug = 0;
static void fd_close(int fd);

/* These functions normally declared in stderr.h */
static void err_setarg0(const char *argv0);
static void err_sysexit(char const *fmt, ...);
static void err_usage(char const *usestr);
static void err_remark(char const *fmt, ...);

/*
process #0 (32768) sending message: hello
process #1 (32769) relaying message: iello
process #2 (32770) relaying message: jello
process #3 (32767) relaying message: kello
*/

static void be_childish(Pipe in, Pipe out, int n)
{
    /* Close irrelevant ends of relevant pipes */
    fd_close(in[1]);
    fd_close(out[0]);
    char buffer[BUFFER_SIZE];
    ssize_t nbytes;
    while ((nbytes = read(in[0], buffer, sizeof(buffer))) > 0)
    {
        buffer[0]++;
        printf("process #%d (%d) relaying message %.*s", n, (int)getpid(), (int)nbytes, buffer);
        if (write(out[1], buffer, nbytes) != nbytes)
            err_sysexit("%d: failed to write to pipe", (int)getpid());
    }
    fd_close(in[0]);
    fd_close(out[1]);
    exit(0);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int nkids;
    if (argc != 2 || (nkids = atoi(argv[1])) <= 1 || nkids >= 10)
        err_usage("n   # for n in 2..9");

    err_remark("Parent  has PID %d\n", (int)getpid());

    Pipe pipelist[nkids];
    if (pipe(pipelist[0]) != 0)
        err_sysexit("Failed to create pipe #%d", 0);
    if (debug)
        err_remark("p[0][0] = %d; p[0][1] = %d\n", pipelist[0][0], pipelist[0][1]);

    for (int i = 1; i < nkids; i++)
    {
        pid_t pid;
        if (pipe(pipelist[i]) != 0)
            err_sysexit("Failed to create pipe #%d", i);
        if (debug)
            err_remark("p[%d][0] = %d; p[%d][1] = %d\n", i, pipelist[i][0], i, pipelist[i][1]);
        if ((pid = fork()) < 0)
            err_sysexit("Failed to create child #%d", i);
        if (pid == 0)
        {
            /* Close irrelevant pipes */
            for (int j = 0; j < i-1; j++)
            {
                fd_close(pipelist[j][0]);
                fd_close(pipelist[j][1]);
            }
            be_childish(pipelist[i-1], pipelist[i], i);
            /* NOTREACHED */
        }
        err_remark("Child %d has PID %d\n", i, (int)pid);
    }

    /* Close irrelevant pipes */
    for (int j = 1; j < nkids-1; j++)
    {
        fd_close(pipelist[j][0]);
        fd_close(pipelist[j][1]);
    }

    /* Close irrelevant ends of relevant pipes */
    fd_close(pipelist[0][0]);
    fd_close(pipelist[nkids-1][1]);

    int w_fd = pipelist[0][1];
    int r_fd = pipelist[nkids-1][0];

    /* Main loop */
    char buffer[BUFFER_SIZE];

    while (printf("Input:  ") > 0 && fgets(buffer, sizeof(buffer), stdin) != 0)
    {
        int len = strlen(buffer);
        printf("process #0 (%d) sending %s", (int)getpid(), buffer);
        if (write(w_fd, buffer, len) != len)
            err_sysexit("Failed to write to children");
        if (read(r_fd, buffer, len) != len)
            err_sysexit("Failed to read from children");
        printf("Output: %.*s", len, buffer);
    }
    fd_close(w_fd);
    fd_close(r_fd);
    putchar('\n');

    int status;
    int corpse;
    while ((corpse = wait(&status)) > 0)
        err_remark("%d exited with status 0x%.4X\n", corpse, status);

    return 0;
}

static void fd_close(int fd)
{
    if (debug)
        err_remark("%d: close(%d)\n", (int)getpid(), fd);
    if (close(fd) != 0)
        err_sysexit("%d: Failed to close %d\n", (int)getpid(), fd);
}

/* Normally in stderr.c */
static const char *arg0 = "<undefined>";

static void err_setarg0(const char *argv0)
{
    arg0 = argv0;
}

static void err_usage(char const *usestr)
{
    fprintf(stderr, "Usage: %s %s\n", arg0, usestr);
    exit(1);
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

static void err_sysexit(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
    exit(1);
}

static void err_remark(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}
