/* SO 4626-6329 */
/*
**   (process 0)--pipe0--(process 3)
**     |                    |
**     |                    |
**    pipe1                pipe3
**     |                    |
**     |                    |
**   (process 1)--pipe2--(process 2)
**
** So, the Process 0 is the parent of process 1; process 1 the
** parent of process 2; etc...
**
** Process 0 sends a random number to process 1 via pipe1; process 1
** generate an other random number, and send max between these two
** numbers to process 2 via pipe 2; etc...
**
** Process 0 is reading on pipe4, so it is blocked, waiting for
** the last message, then show the winner.
**
** What I want to do, is that the process 0 send the winner to all the
** process now.
**
** ********************************************************************
**
** Designate the 4 processes P0..P3.
** Designate the 4 pipes (channels) C0..C3.
**
** C0 must be created by P0 before creating P1.
** C1 must be created by P0 before creating P1.
** C2 must be created by P0 before creating P1 (because P1 needs to write to it).
** C3 must be created by P0 before creating P2 (because P2 needs to write to it).
** P0 will write to  C1 and read from C0.
** P1 will read from C1 and write to  C2.
** P2 will read from C2 and write to  C3.
** P3 will read from C3 and write to  C0.
**
** Hence Pn always reads from Cn and writes to C((n+1)%4).
** P0 writes then reads; the other processes read then write.
** Note that P1 and P2 should close C0 after forking the next child.
** PN (for N > 1) should close C1..C(N-1) too (it should be sufficient
** to close C(N-1) since P(N-1) closed the prior channels).
**
** Although the code does not rely on detecting EOF, the pipes will be
** closed, even though it is not crucial to the correct functioning of
** this program.
*/

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct Node
{
    int node;
    int val;
    int pid;
};

static void no_children(void)
{
    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
        printf("PID %5d: child %5d exited 0x%.4X\n", (int)getpid(), corpse, status);
}

static void check_fds(void)
{
    struct stat sb;
    char buffer[128];
    char *bufptr = buffer;
    int n = snprintf(bufptr, sizeof(buffer), "PID %5d: ", (int)getpid());
    bufptr += n;
    for (int i = 0; i < 20; i++)
    {
        if (fstat(i, &sb) != 0)
            *bufptr++ = '-';
        else
            *bufptr++ = 'o';
    }
    *bufptr++ = '\0';
    printf("%s\n", buffer);
    fflush(stdout);
}

static void pr_result(const char *tag, const struct Node *result)
{
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.12s:", tag);
    printf("%-13s PID = %5d, PPID = %5d, Node = %d (PID %5d), Value = %5d\n", buffer,
           (int)getpid(), (int)getppid(), result->node, result->pid, result->val);
    fflush(stdout);
}

static inline int new_bid(void)
{
    return rand() % 10000;
}

static inline void pr_channel(int i, int c[2])
{
    printf("%5d: C%d(%d,%d)\n", (int)getpid(), i, c[0], c[1]);
    fflush(stdout);
}

static inline void mk_channel(int i, int c[2])
{
    if (pipe(c) != 0)
    {
        fprintf(stderr, "%5d: failed to create pipe %d, (%d: %s)\n",
                (int)getpid(), i, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    pr_channel(i, c);
}

static _Noreturn void be_parental(int i_pipe[2], int o_pipe[2])
{
    int pid = getpid();
    struct Node proc0 = { 0, new_bid(), pid };
    struct Node winner = { 0, 0, 0 };
    printf("PID %5d (PPID %5d): parent at work\n", pid, (int)getppid());
    printf("FD {%d, %d, %d, %d}\n", i_pipe[0], i_pipe[1], o_pipe[0], o_pipe[1]);
    check_fds();

    pr_result("Opening bid", &proc0);
    close(o_pipe[0]);
    printf("Writing opening bid to fd %d\n", o_pipe[1]);
    if (write(o_pipe[1], &proc0, sizeof(proc0)) != sizeof(proc0))
    {
        fprintf(stderr, "%5d: failed to write entry to fd %d (%d: %s)\n",
                pid, o_pipe[1], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(i_pipe[1]);
    if (read(i_pipe[0], &winner, sizeof(winner)) != sizeof(winner))
    {
        fprintf(stderr, "%5d: failed to read entry from fd %d (%d: %s)\n",
                pid, i_pipe[0], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    //close(i_pipe[0]);

    pr_result("Winning node", &winner);
    if (write(o_pipe[1], &winner, sizeof(winner)) != sizeof(winner))
    {
        fprintf(stderr, "%5d: failed to write entry to fd %d (%d: %s)\n",
                pid, o_pipe[1], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(o_pipe[1]);

    /* Read final result once more */
    if (read(i_pipe[0], &winner, sizeof(winner)) != sizeof(winner))
    {
        fprintf(stderr, "%5d: failed to read entry from fd %d (%d: %s)\n",
                pid, i_pipe[0], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(i_pipe[0]);
    pr_result("Recirculated", &winner);

    no_children();
    check_fds();
    exit(EXIT_SUCCESS);
}

static _Noreturn void be_childish(int i, int i_pipe[2], int o_pipe[2])
{
    struct Node winner;
    int pid = getpid();
    printf("PID %5d (PPID %5d) i = %d: child at work\n", pid, (int)getppid(), i);
    printf("FD {%d, %d, %d, %d}\n", i_pipe[0], i_pipe[1], o_pipe[0], o_pipe[1]);
    check_fds();

    srand(pid);
    close(i_pipe[1]);
    if (read(i_pipe[0], &winner, sizeof(winner)) != sizeof(winner))
    {
        fprintf(stderr, "%5d: failed to read entry from fd %d (%d: %s)\n",
                pid, i_pipe[0], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    pr_result("Incoming bid", &winner);

    int newValue = new_bid();
    printf("PID: %5d, new offer %5d\n", pid, newValue);

    if (newValue > winner.val)
    {
        winner.node = i;
        winner.val = newValue;
        winner.pid = pid;
    }

    close(o_pipe[0]);
    pr_result("Outgoing bid", &winner);
    if (write(o_pipe[1], &winner, sizeof(winner)) != sizeof(winner))
    {
        fprintf(stderr, "%5d: failed to write entry to fd %d (%d: %s)\n",
                pid, o_pipe[1], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (read(i_pipe[0], &winner, sizeof(winner)) != sizeof(winner))
        exit(EXIT_FAILURE);
    pr_result("Final winner", &winner);
    close(i_pipe[0]);

    /* Relay final result to next process */
    if (write(o_pipe[1], &winner, sizeof(winner)) != sizeof(winner))
    {
        fprintf(stderr, "%5d: failed to write entry to fd %d (%d: %s)\n",
                pid, o_pipe[1], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(o_pipe[1]);

    /* There should be no children */
    no_children();
    check_fds();
    exit(i);
}

int main(int argc, const char *argv[])
{
    int numproc = 4;
    if (argc > 1)
        numproc = atoi(argv[1]);

    if (numproc < 2 || numproc > 10)
    {
        fprintf(stderr, "Number of processes %d is out of the range 2..10\n", numproc);
        exit(EXIT_FAILURE);
    }

    int seed = time(NULL);
    printf("%5d: seed: %d\n", (int)getpid(), seed);
    srand(seed);

    int tube[numproc][2];

    mk_channel(0, tube[0]);
    mk_channel(1, tube[1]);

    for (int i = 1; i < numproc; ++i)
    {
        if (i + 1 < numproc)
            mk_channel(i + 1, tube[i + 1]);
        int pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "fork error for child %d (%d: %s)\n", i, errno, strerror(errno));
            exit(1);
        }
        else if (pid == 0)
        {
            for (int c = 0; c < i; c++)
            {
                if ((i + 1) % numproc != c)
                {
                    printf("%5d: closing %2d and %2d\n", (int)getpid(), tube[c][0], tube[c][1]);
                    close(tube[c][0]);
                    close(tube[c][1]);
                }
            }
            be_childish(i, tube[i], tube[(i+1) % numproc]);
        }
    }

    for (int c = 2; c < numproc; c++)
    {
        printf("%5d: closing %2d and %2d\n", (int)getpid(), tube[c][0], tube[c][1]);
        close(tube[c][0]);
        close(tube[c][1]);
    }

    be_parental(tube[0], tube[1]);

    return 0;
}
