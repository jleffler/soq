/* SO 7074-5657 */
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

static void err_error(const char *fmt, ...);

int main(int argc, char *argv[])
{
    sigset_t ms;
    int n;

    if (argc != 2)
        err_error("Usage: %s num-children\n", argv[0]);

    int num_kids = atoi(argv[1]);
    if (num_kids <= 0 || num_kids > MAX_KIDS)
        err_error("Inappropriate number of processes (%s not in range 1..%d)\n",
                  argv[1], MAX_KIDS);

    struct sigaction sa = { 0 };
    sa.sa_handler = h;
    if (sigfillset(&sa.sa_mask) != 0)
        err_error("sigfillset() failed\n");

    /* NSIG is not defined by POSIX - it works on Linux and macOS though */
    for (int n = 1; n < NSIG; ++n)
    {
        if (n != SIGCHLD && n != SIGKILL && n != SIGSTOP)
            sigaction(n, &sa, 0);
    }

    if (sigemptyset(&ms) != 0)
        err_error("sigemptyset() failed\n");

    for (n = 1; n <= num_kids; ++n)
    {
        int pid = fork();
        if (pid < 0)
            err_error("fork() failed\n");
        else if (pid != 0)
        {
            printf("%d: Started %d\n", n, pid);
            sigsuspend(&ms);
            printf("%d: Signalled!\n", n);
        }
        else
        {
            int sig = n % 3 + 1;
            kill(getppid(), sig);
            exit(sig);
        }
    }

    int corpse, status;
    while ((corpse = wait(&status)) != -1)
        printf("Dead: %5d - 0x%.4X\n", corpse, status);
    printf("%d\n", s);
    return 0;
}

static void err_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}