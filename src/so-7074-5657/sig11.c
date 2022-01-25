/* SO 7074-5657 */
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

volatile int s = 0;

void h(int n)
{
    signal(n, h);
    ++s;
}

int main(int argc, char *argv[])
{
    sigset_t ms;
    int n;

    for (n = 1; n < NSIG; ++n)
        signal(n, h);
    sigfillset(&ms);
    sigprocmask(SIG_SETMASK, &ms, NULL);
    sigemptyset(&ms);

    // first part
    for (n = 1; n <= atoi(argv[1]); ++n)
        if (fork())
            sigsuspend(&ms);
        else
        {
            kill(getppid(), 1 + rand() % 3);
            exit(0);
        }

    // the kill part
    while (wait(NULL) != -1)
        ;
    printf("%d\n", s);
    return 0;
}
