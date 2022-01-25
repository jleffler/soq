/* SO 7074-5657 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "stderr.h"

enum { MAX_KIDS = 20 };
static volatile sig_atomic_t s = 0;

static char message[] = "Signal XX received\n";

static void h(int n)
{
    ++s;
    message[7] = (n / 10) + '0';
    message[8] = (n % 10) + '0';
    write(2, message, sizeof(message) - 1);
}

int main(int argc, char *argv[])
{
    err_setarg0(argv[0]);
    if (argc != 2)
        err_usage("num-children");

    int num_kids = atoi(argv[1]);
    if (num_kids <= 0 || num_kids > MAX_KIDS)
        err_error("Inappropriate number of processes (%s not in range 1..%d)\n",
                  argv[1], MAX_KIDS);

    struct sigaction sa = { 0 };
    sa.sa_handler = h;
    if (sigfillset(&sa.sa_mask) != 0)
        err_syserr("sigfillset() 1 failed");

    /* NSIG is not defined by POSIX - it works on Linux and macOS though */
    for (int n = 1; n < NSIG; ++n)
    {
        /* Should skip SIGCHLD (and SIGKILL and SIGSTOP) */
        /* Could detect whether a signal was being ignored */
        sigaction(n, &sa, 0);
    }

    sigset_t ms;
    if (sigfillset(&ms) != 0)
        err_syserr("sigfillset() 2 failed");
    /* Block all signals by default */
    sigprocmask(SIG_SETMASK, &ms, NULL);

    if (sigemptyset(&ms) != 0)
        err_syserr("sigemptyset() failed");

    // Launch kids
    for (int n = 1; n <= num_kids; ++n)
    {
        int pid = fork();
        if (pid < 0)
            err_syserr("fork() failed");
        if (pid != 0)
        {
            printf("%d: Started %d\n", n, pid);
            sigsuspend(&ms);
            printf("%d: Signalled!\n", n);
        }
        else
        {
            int sig = n % 3 + 1;    /* SIGHUP, SIGINT, SIGQUIT on most systems */
            //nanosleep(&(struct timespec){.tv_sec = 0, .tv_nsec = 1500000}, 0);
            //kill(getppid(), 1 + rand() % 3);
            kill(getppid(), sig);
            exit(sig);
        }
    }

    // Wait for kids to die
    int corpse, status;
    while ((corpse = wait(&status)) != -1)
        printf("%d - 0x%.4X\n", corpse, status);
    printf("%d\n", s);
    return 0;
}
