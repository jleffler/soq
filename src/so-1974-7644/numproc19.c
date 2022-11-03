/*
** SO 7430-0464: How can I limit the number of parallel child processes?
** https://stackoverflow.com/questions/74300464
** SO 1974-7344: Shell: run four processes in parallel
** https://stackoverflow.com/questions/19747644
**
** The question code for SO 1974-7344 runs a simulation (instead of
** sleep), and can't predict how long a simulation will take (so sleep
** with random delay is a good model).  The object is to have N (4)
** processes running all the time, starting a new one as soon as one of
** the current N is complete.
**
** The question for SO 7430-0464 asks how to limit the processes.  This
** code uses a fixed limit (4 child processes) and number of tasks to
** run (20), but is trivially adaptable to run arbitrary numbers of
** processes with arbitrary limits.  It doesn't use o/s facilities to
** enforce the limit; it simply ensures it does not run too many
** processes.
**
** Clearly, the be_childish() function can be revised to do whatever
** task is appropriate - as identified by the task number argument.
** This might be to run a series of commands read from a file, or any
** other more or less devious technique for choosing what to do.
**
** As noted by the _Noreturn in the signature, it is crucial that the
** be_childish() function does not return.  If it executes another
** program, the post-exec code should report an appropriate error and
** exit with a non-zero status.
**
** For use in production code, you'd consider carefully how much of
** the output is required and where it should be logged to.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

enum { MAX_KIDS = 4 };
enum { DEF_TASKS = 20 };

static _Noreturn void be_childish(int tasknum)
{
    /*
    ** Each child must generate different random numbers - seeding with
    ** time() is pointless.  There are better random number generators,
    ** but this is adequate for the demonstration.
    */
    srand(getpid());
    struct timespec nap = { .tv_sec = rand() % 5, .tv_nsec = (rand() % 1000) * 1000000 };
    int millisecs = nap.tv_nsec / 1000000;
    printf("PID %5d (PPID %5d): Task %2d - dozing %d.%.3d\n",
            getpid(), getppid(), tasknum, (int)nap.tv_sec, millisecs);
    nanosleep(&nap, 0);
    printf("PID %5d (PPID %5d): Task %2d - done\n", getpid(), getppid(), tasknum);
    exit(tasknum);
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
}

int main(void)
{
    pid_t kids[MAX_KIDS];
    size_t nkids = 0;

    setvbuf(stdout, NULL, _IOLBF, 0);

    for (size_t task = 0; task < DEF_TASKS; task++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "failed to fork(): (%d) %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
            be_childish(task);
        kids[nkids++] = pid;

        printf("Kid: %5d; Number of kids: %2zu\n", pid, nkids);
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
