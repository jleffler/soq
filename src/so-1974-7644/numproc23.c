/*
** SO 1974-7644: Shell: run four processes in parallel
** https://stackoverflow.com/questions/19747644
**
** Question code runs a simulation (instead of sleep), and can't predict
** how long a simulation will take (so sleep with random delay is a good
** model).  The object is to have N (4) processes running all the time,
** starting a new one as soon as one of the current N is complete.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "stderr.h"
#include "timespec_io.h"
#include "randseed.h"
#include "prng48.h"

enum { MAX_KIDS = 4 };
enum { DEF_TASKS = 20 };

static _Noreturn void be_childish(int tasknum)
{
    unsigned short seed[3];
    random_seed_bytes(sizeof(seed), seed);
    prng48_seed(seed);
    struct timespec nap = { .tv_sec = prng48_rand(1, 4), .tv_nsec = prng48_rand(0, 999999999) };
    char buffer[32];
    fmt_timespec(&nap, 6, buffer, sizeof(buffer));
    printf("PID %5d (PPID %5d): Task %2d - dozing %s\n", getpid(), getppid(), tasknum, buffer);
    fflush(stdout);
    nanosleep(&nap, 0);
    printf("PID %5d (PPID %5d): Task %2d - done\n", getpid(), getppid(), tasknum);
    fflush(stdout);
    exit(0);
}

static size_t dead_kid(pid_t corpse, size_t nkids, pid_t *kids)
{
    for (size_t i = 0; i < nkids; i++)
    {
        if (kids[i] == corpse)
        {
            kids[i] = kids[--nkids];
            return nkids;
        }
    }
    printf("PID %5d exited but was not a known child\n", corpse);
    fflush(stdout);
    return nkids;
}

static int cmp_pid(const void *vp1, const void *vp2)
{
    pid_t v1 = *(pid_t *)vp1;
    pid_t v2 = *(pid_t *)vp2;
    return (v1 > v2) - (v1 < v2);
}

static void print_kids(size_t nkids, pid_t *kids)
{
    qsort(kids, nkids, sizeof(kids[0]), cmp_pid);
    printf("Kids (%zu):", nkids);
    for (size_t i = 0; i < nkids; i++)
        printf(" %5d", kids[i]);
    putchar('\n');
    fflush(stdout);
}

int main(void)
{
    err_setarg0("numproc23");

    pid_t kids[MAX_KIDS];
    size_t nkids = 0;

    for (size_t task = 0; task < DEF_TASKS; task++)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_syserr("failed to fork(): ");
        if (pid == 0)
            be_childish(task);
        kids[nkids++] = pid;

        struct timespec now;
        clock_gettime(CLOCK_REALTIME, &now);
        char buffer[32];
        fmt_timespec(&now, 6, buffer, sizeof(buffer));

        printf("Kid: %5d; Number of kids: %2zu; Time: %s\n", pid, nkids, buffer);
        fflush(stdout);
        print_kids(nkids, kids);
        if (nkids >= MAX_KIDS)
        {
            int status;
            int corpse = waitpid(-1, &status, 0);
            if (corpse < 0)
                break;
            printf("Child %5d exited with status 0x%.4X\n", corpse, status);
            nkids = dead_kid(corpse, nkids, kids);
        }
    }

    int corpse;
    int status;
    while (nkids > 0 && (corpse = waitpid(-1, &status, 0)) > 0)
    {
        printf("Child %5d exited with status 0x%.4X\n", corpse, status);
        nkids = dead_kid(corpse, nkids, kids);
        print_kids(nkids, kids);
    }

    return 0;
}
