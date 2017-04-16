#include "stderr.h"
#include <assert.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MIN_PROC 2
#define MAX_PROC 20

enum { MAX_TUBENAMELEN = 20 };
enum { MAX_MSGLEN = 256 };
enum Mode { M_WF, M_RF, M_WB, M_RB };

/*
**  You have to split the connections into 'forward' and 'backward'
**  around the loop.  P0 (zeroth child) needs to connect forward first,
**  then connect backward; all other children need to connect backward
**  first, then connect forward.  Although the order is arbitrary, when
**  a child connects backward, it should open the read FIFO before the
**  write FIFO; when it connects forward, it should open the write FIFO
**  before the read FIFO.
**
**  Child process Pn (for n = 0; n < N; n++) connects forward to tube
**  T[(2n)%(2N)] for writing, T[(2n+1)%(2N)] for reading; and connects
**  backward to T[(2n-2+2N)%(2N)] for reading, and to T[(2n-1+2N)%(2N)]
**  for writing.  The +2N terms ensure that the LHS of % is not
**  negative.  This sequencing should ensure no blockage
**
**  When it comes to reading and writing, the rules will be similar.
**  P0 will write forward, read forward, read backward, write backward.
**  PN will read backward, write backward, write forward, read forward.
*/

static inline int tube_index(int num, int max)
{
    int idx = (num + 2 * max) % (2 * max);
    return idx;
}

static int open_fifo(enum Mode mode, int max, int num, char tubes[][MAX_TUBENAMELEN])
{
    int fd;
    int idx = 0;
    switch (mode)
    {
    case M_WF: idx = tube_index(2 * num + 0, max); break;
    case M_RF: idx = tube_index(2 * num + 1, max); break;
    case M_RB: idx = tube_index(2 * num - 2, max); break;
    case M_WB: idx = tube_index(2 * num - 1, max); break;
    default: assert(0);
    }
    const char *fifoname = tubes[idx];
    int o_mode = O_RDONLY;
    if (mode == M_WF || mode == M_WB)
        o_mode = O_WRONLY;
    err_remark("Opening FIFO %s with mode %d\n", fifoname, o_mode);
    if ((fd = open(fifoname, o_mode)) < 0)
        err_syserr("Failed to open %s with mode %d: ", fifoname, o_mode);
    err_remark("Opened  FIFO %s with mode %d - fd %d\n", fifoname, o_mode, fd);
    return fd;
}

static inline void recv_info(int num, int fd)
{
    char buffer[MAX_MSGLEN];
    int nbytes;
    if ((nbytes = read(fd, buffer, sizeof(buffer))) <= 0)
        err_syserr("P%d failed to read anything on fd %d: ", num, fd);
    err_remark("P%d received %d bytes: [%.*s]\n", num, nbytes, nbytes, buffer);
}

static inline void send_info(int num, int fd, const char *dir)
{
    char buffer[MAX_MSGLEN];
    int buflen = snprintf(buffer, sizeof(buffer), "P%d (PID %d) sent this message %s",
                    num, (int)getpid(), dir);
    int nbytes;
    if ((nbytes = write(fd, buffer, buflen)) != buflen)
        err_syserr("Failed to write properly on fd %d (%d vs %d wanted): ", fd, nbytes, buflen);
    err_remark("P%d sent %d bytes: [%.*s]\n", num, nbytes, nbytes, buffer);
}

static void be_childish(int max, int num, char tubes[][MAX_TUBENAMELEN])
{
    int wf;     /* Descriptor for writing forwards */
    int wb;     /* Descriptor for writing backwards */
    int rf;     /* Descriptor for reading forwards */
    int rb;     /* Descriptor for reading backwards */

    if (num == 0)
    {
        /* Child zero connects forwards then backwards */
        wf = open_fifo(M_WF, max, num, tubes);
        rf = open_fifo(M_RF, max, num, tubes);
        rb = open_fifo(M_RB, max, num, tubes);
        wb = open_fifo(M_WB, max, num, tubes);
        send_info(num, wf, "forwards");
        recv_info(num, rf);
        recv_info(num, rb);
        send_info(num, wb, "backwards");
    }
    else
    {
        /* Other children connect backwards then forwards */
        rb = open_fifo(M_RB, max, num, tubes);
        wb = open_fifo(M_WB, max, num, tubes);
        wf = open_fifo(M_WF, max, num, tubes);
        rf = open_fifo(M_RF, max, num, tubes);
        recv_info(num, rb);
        send_info(num, wb, "backwards");
        send_info(num, wf, "forwards");
        recv_info(num, rf);
    }

    close(wf);
    close(wb);
    close(rf);
    close(rb);
}

int main(int argc, char **argv)
{
    int n;
    err_setarg0(argv[0]);
    err_setlogopts(ERR_NOARG0|ERR_PID|ERR_MICRO);
    err_settimeformat("%H:%M:%S");

    if (argc < 2 || (n = (int)strtol(argv[1], NULL, 0)) < MIN_PROC || n > MAX_PROC)
    {
        fprintf(stderr, "Usage : %s <nombre>\n"
                "Avec <nombre> compris entre %d et %d.\n",
                argv[0], MIN_PROC, MAX_PROC);
        exit(1);
    }

    char tubes[2 * n][MAX_TUBENAMELEN];
    pid_t pid;
    pid_t pids[n];

    for (int i = 0; i < n * 2; i++)
    {
        snprintf(tubes[i], sizeof(tubes[i]), "tube%d", i);
        printf("Fifo %d: [%s]\n", i, tubes[i]);
    }

    printf("Nombre de processus à engendrer : %d\n", n);

    for (int k = 0; k < 2*n; k++)
    {
        printf("Create fifo: %s\n", tubes[k]);
        if (mkfifo(tubes[k], 0666) != 0)
            err_syserr("Failed to create FIFO %s: ", tubes[k]);
    }
    fflush(0);

    for (int i = 0; i < n; i++)
    {
        pid = fork();
        if (pid > 0)
        {
            pids[i] = pid;
            err_remark("Création du processus fils #%d : PID %d\n", i, (int)pid);
        }
        else if (pid == 0)
        {
            usleep((i + 1) * 100000);   // Tenths of a second
            err_remark("Child process #%d (PID %d) at work\n", i, (int)getpid());
            be_childish(n, i, tubes);
            int status = (i + 1) * 16;
            err_remark("Child process #%d (PID %d) exiting with status 0x%.2X\n", i, (int)getpid(), status);
            exit(status);
        }
        else
        {
            err_sysrem("Failed to fork child %d: ", i);
            for (int j = 0; j < i; j++)
            {
                err_remark("Killing %d\n", pids[j]);
                kill(SIGTERM, pids[j]);
            }
            for (int j = 0; j < 2 * n; j++)
                unlink(tubes[j]);
            err_error("Terminating!\n");
        }
    }

    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
        err_remark("Child %d died with status 0x%.4X\n", corpse, status);

    for (int j = 0; j < 2 * n; j++)
        unlink(tubes[j]);

    return 0;
}
