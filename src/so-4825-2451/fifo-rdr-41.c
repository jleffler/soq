/* SO 4825-2451 */
/*
** The question asks about epoll() which is a Linux-specific extension.
** This code was developed on a Mac running macOS High Sierra 10.13.2,
** where epoll() is not available.  However, it helps make a point, that
** once there are no processes with a FIFO open for writing, the reader
** continually gets 0 bytes returned until another process opens the
** FIFO for writing.  It goes into a busy loop unless you're careful.
** This code naps for a random time (between 0.250 and 0.750 seconds) to
** avoid busy waiting.  Another option is to close the FIFO on getting
** EOF and then reopening the FIFO; the open hangs until there is a
** process that has opened the FIFO for writing.  A third option is to
** have the reading process also open the file for writing (best to use
** a separate file descriptor for that; the result is undefined if you
** open a FIFO with O_RDWR *ccording to POSIX).  Of course, since
** open-for-reading blocks until there's a writer, and open-for-writing
** blocks until there's a reader, you can't open the writing file
** descriptor until after the reading open has succeeded.
*/

#include "fifo-tst-41.h"
#include "stderr.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

static void set_handler(void);
static void chk_signal(void);
static size_t rd_fifo(int fd, const char *name, size_t buflen, char buffer[buflen]);

static const char optstr[] = "hrw";
static const char usestr[] = "[-hrw]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -r  Reopen FIFO after getting EOF\n"
    "  -w  Open FIFO for writing too\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int wflag = 0;
    int reopen = 0;
    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'r':
            reopen = 1;
            break;
        case 'w':
            wflag = 1;
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (argc != optind)
        err_usage(usestr);

    err_setlogopts(ERR_PID|ERR_MILLI);
    set_handler();

    struct stat sb;
    if (stat(FIFO, &sb) != 0 || !S_ISFIFO(sb.st_mode))
    {
        err_remark("Creating FIFO '%s'\n", FIFO);
        if (mkfifo(FIFO, 0644) != 0)
        {
            chk_signal();
            err_syserr("failed to create FIFO '%s': ", FIFO);
        }
        chk_signal();
    }

    int wfd = -1;

    while (1)
    {
        err_remark("Open FIFO '%s' for reading\n", FIFO);
        int fd = open(FIFO, O_RDONLY);
        if (fd == -1)
        {
            chk_signal();
            err_syserr("failed to open FIFO '%s' for reading: ", FIFO);
        }
        chk_signal();
        err_remark("FIFO '%s' opened for reading\n", FIFO);
        if (wflag)
        {
            wfd = open(FIFO, O_WRONLY);
            if (wfd == -1)
            {
                chk_signal();
                err_syserr("failed to open FIFO '%s' for writing: ", FIFO);
            }
        }

        while (1)
        {
            char buffer[1024];
            size_t nbytes;
            while ((nbytes = rd_fifo(fd, FIFO, sizeof(buffer), buffer)) > 0)
                err_remark("Data: [%.*s]\n", (int)nbytes, buffer);
            if (reopen)
                break;
            random_milli_nap(250, 750);
            chk_signal();
        }

        err_remark("Close FIFO '%s'\n", FIFO);
        close(fd);
        if (wfd != -1)
        {
            close(wfd);
            wfd = -1;
        }
        chk_signal();
    }

    return 0;
}

struct Signal
{
    int         number;
    const char *name;
};

static const struct Signal trap[] =
{
    { SIGHUP,  "SIGHUP"  },
    { SIGINT,  "SIGINT"  },
    { SIGQUIT, "SIGQUIT" },
    { SIGPIPE, "SIGPIPE" },
    { SIGTERM, "SIGTERM" },
};
enum { NUM_TRAPS = sizeof(trap) / sizeof(trap[0]) };

static volatile sig_atomic_t int_flag = 0;

static void sig_handler(int signum)
{
    int_flag = signum;
}

static void set_handler(void)
{
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    for (int i = 0; i < NUM_TRAPS; i++)
    {
        int signum = trap[i].number;
        struct sigaction oa;
        if (sigaction(signum, 0, &oa) != 0)
            err_syserr("Interrogating signal handling for %d (%s) failed: ", signum, trap[i].name);
        if (oa.sa_handler != SIG_IGN)
        {
            if (sigaction(signum, &sa, 0) != 0)
                err_syserr("Setting signal handling for %d (%s) failed: ", signum, trap[i].name);
        }
    }
}

static const char *signame(int signum)
{
    for (int i = 0; i < NUM_TRAPS; i++)
    {
        if (signum == trap[i].number)
            return trap[i].name;
    }
    return "unknown signal";
}

static void chk_signal(void)
{
    if (int_flag)
        err_error("Interrupted by signal %d (%s)\n", int_flag, signame(int_flag));
}

static size_t rd_fifo(int fd, const char *name, size_t buflen, char buffer[buflen])
{
    err_remark("Read from FIFO '%s'\n", name);
    ssize_t nbytes = read(fd, buffer, buflen);
    chk_signal();
    if (nbytes < 0)
        err_syserr("Failed to read from FIFO '%s': ", name);
    err_remark("%zu bytes read from FIFO '%s'\n", (size_t)nbytes, name);
    return nbytes;
}
