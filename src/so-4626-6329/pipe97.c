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
** Designate the processes P0..P3.
** Designate the pipes (channels) C0..C3.
**
** C0 must be created by P0 before creating P1.
** C1 must be created by P0 before creating P1.
** C2 must be created by P1 before creating P2.
** C3 must be created by P2 before creating P3.
** P0 will write to C1 and read from C0.
** P1 will read from C1 and write to C2.
** P2 will read from C2 and write to C3.
** P3 will read from C3 and write to C0.
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
        printf("PID %d: child %d exited 0x%.4X\n", (int)getpid(), corpse, status);
}

static void check_fds(void)
{
    struct stat sb;
    char buffer[128];
    char *bufptr = buffer;
    int n = snprintf(bufptr, sizeof(buffer), "PID %d: ", (int)getpid());
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
    printf("%s: PID = %d, PPID = %d, Node = %d (PID %d), Value = %d\n", tag,
           (int)getpid(), (int)getppid(), result->node, result->pid, result->val);
    fflush(stdout);
}

static _Noreturn void be_parental(int p0[2], int p1[2])
{
    int pid = getpid();
    struct Node proc0 = { 0, rand(), pid };
    struct Node winner = { 0, 0, 0 };
    printf("PID %d (PPID %d) i = %d: parent at work\n", pid, (int)getppid(), 0);
    printf("FD {%d, %d, %d, %d}\n", p0[0], p0[1], p1[0], p1[1]);
    check_fds();

    pr_result("Opening bid", &proc0);
    close(p1[0]);
    if (write(p1[1], &proc0, sizeof(proc0)) != sizeof(proc0))
        exit(EXIT_FAILURE);

    close(p0[1]);
    if (read(p0[0], &winner, sizeof(winner)) != sizeof(winner))
        exit(EXIT_FAILURE);
    close(p0[0]);

    pr_result("Winning bid", &winner);
    if (write(p1[1], &winner, sizeof(winner)) != sizeof(winner))
        exit(EXIT_FAILURE);
    close(p1[1]);
    no_children();
    check_fds();
    exit(EXIT_SUCCESS);
}

static _Noreturn void be_childish(int i, int p0[2], int p1[2])
{
    struct Node winner;
    int pid = getpid();
    printf("PID %d (PPID %d) i = %d: child at work\n", pid, (int)getppid(), i);
    printf("FD {%d, %d, %d, %d}\n", p0[0], p0[1], p1[0], p1[1]);
    check_fds();

    srand(pid);
    close(p0[1]);
    if (read(p0[0], &winner, sizeof(winner)) != sizeof(winner))
        exit(EXIT_FAILURE);
    pr_result("Incoming bid", &winner);

    int newValue = rand();
    printf("PID: %d, new offer %d\n", pid, newValue);

    if (newValue > winner.val)
    {
        winner.node = i;
        winner.val = newValue;
        winner.pid = pid;
    }

    close(p1[0]);
    pr_result("Outgoing bid", &winner);
    if (write(p1[1], &winner, sizeof(winner)) != sizeof(winner))
        exit(EXIT_FAILURE);

    if (read(p0[0], &winner, sizeof(winner)) != sizeof(winner))
        exit(EXIT_FAILURE);
    pr_result("Final winner", &winner);
    close(p0[0]);
    no_children();
    check_fds();
    exit(i);
}

int main(int argc, const char *argv[])
{
    int numproc = 4;
    if (argc > 1)
        numproc = atoi(argv[1]);

    int seed = time(NULL);
    printf("seed: %d\n", seed);
    srand(seed);

    int tube[numproc][2];
    if (pipe(tube[0]) != 0)
        exit(EXIT_FAILURE);

    for (int i = 1; i < numproc; ++i)
    {
        if (pipe(tube[i]) != 0)
            exit(EXIT_FAILURE);
        int pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "fork error (%d: %s)\n", errno, strerror(errno));
            exit(1);
        }
        else if (pid != 0)
        {
            if (i == 1)
            {
                printf("PID %d (PPID %d) (i = %d): original parent at work\n",
                       (int)getpid(), (int)getppid(), i);
                be_parental(tube[0], tube[1]);
            }
            else
            {
                printf("PID %d (PPID %d) (i = %d): forked parent at work - about to be childish\n",
                       (int)getpid(), (int)getppid(), i);
                be_childish(i, tube[i-1], tube[i]);
            }
        }
        else
        {
            printf("PID %d (PPID %d): (i = %d) child at work\n",
                   (int)getpid(), (int)getppid(), i);
            if (i > 1)
            {
                close(tube[i-1][0]);
                close(tube[i-1][1]);
            }
        }
    }

    return 0;
}
