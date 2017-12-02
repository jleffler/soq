/* SO 4759-5743 - Mark II */
#include "stderr.h"
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N 5

static int newProcess(void)
{
    int pid = fork();
    if (pid == 0)
    {
        // work - this process goes to sleep on the job!
        struct timespec nap = { .tv_sec = rand() % 3, .tv_nsec = rand() % 1000000000 };
        err_remark("Starting  %ld.%.9ld seconds work\n", (long)nap.tv_sec, nap.tv_nsec);
        nanosleep(&nap, 0);
        int rc = 0;
        if (rand() % 100 > 90)
            rc = rand() % 255;
        err_remark("Completed %ld.%.9ld seconds of work - exit status %d\n",
                    (long)nap.tv_sec, nap.tv_nsec, rc);
        exit(rc);
    }
    if (pid > 0 && rand() % 100 > 90)
    {
        int signum = rand() % 8 + 1;
        kill(pid, signum);
        errno = EAGAIN;
        pid = -10 * pid - signum;
    }
    return pid;
}

static inline int check_child(int pid)
{
    #undef SIGNONE
    enum { SIGNONE = 0 };
    int rc = kill(pid, SIGNONE);
    err_remark("PID %d - %s\n", pid, (rc == 0) ? "OK" : "Dead");
    return rc;
}

static void process_check(int *npids, int pids[])
{
    err_remark("Checking PID list\n");
    for (int i = 0; i < *npids; i++)
    {
        while (check_child(pids[i]) != 0)
        {
            // Child is presumably dead!
            if (*npids > 0)
                pids[i] = pids[--*npids];
        }
    }
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1)
        err_usage(" # No arguments allowed");
    int child_pid[N] = { 0 };
    srand(time(0));
    err_setlogopts(ERR_PID | ERR_MICRO);

    int processCount = 0;
    while (1)
    {
        if (processCount < N)
        {
            int pid = newProcess();
            if (pid > 0)
            {
                child_pid[processCount++] = pid;;
                err_remark("PID %d started\n", pid);
            }
            else if (pid < -1)
            {
                int signum = (-pid % 10);
                pid = pid / -10;
                err_remark("PID %d was launched but sent signal %d\n", pid, signum);
            }
            else
            {
                assert(pid == -1);
                int errnum = errno;
                err_sysrem("Failed to fork: ");
                process_check(&processCount, child_pid);
                if (errnum == EAGAIN)
                {
                    struct timespec nap = { .tv_sec = 0, .tv_nsec = (rand() % 10 + 1) * 1000000 };
                    nanosleep(&nap, 0); // sleep 1-10 milliseconds (could be too big).
                }
            }
        }
        else
        {
            int corpse;
            int status;
            if ((corpse = wait(&status)) > 0)
            {
                int known_pid = 0;
                for (int i = 0; i < processCount; i++)
                {
                    if (child_pid[i] == corpse)
                    {
                        err_remark("PID %d exit status 0x%.4X\n", corpse, status);
                        known_pid = 1;
                        child_pid[i] = child_pid[--processCount];
                        break;
                    }
                }
                if (!known_pid)
                    err_remark("Unknown PID %d exit status 0x%.4X - ignored\n", corpse, status);
            }
        }
    }
    return 0;
}
