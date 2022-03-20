/* SO 7074-5657 */
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t s = 0;
static char message[] = "Signal XX received\n";

static void h(int n)
{
    signal(n, h);
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

    for (n = 1; n < NSIG; ++n)
        signal(n, h);
    if (sigfillset(&ms) != 0)
        err_error("sigfillset() failed\n");
    sigprocmask(SIG_SETMASK, &ms, NULL);
    if (sigemptyset(&ms) != 0)
        err_error("sigemptyset() failed\n");

    // first part
    for (n = 1; n <= atoi(argv[1]); ++n)
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
            kill(getppid(), 1 + rand() % 3);
            exit(0);
        }
    }

    // the kill part
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
