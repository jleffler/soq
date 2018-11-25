#include "posixver.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "microsleep.h"

static volatile sig_atomic_t sig_caught = 0;

static void catcher(int signum)
{
    sig_caught = signum;
}

int main(void)
{
    int pid, i;
    size_t counter = 0;

    pid = fork();

    if (pid == -1)
    {
        printf("fork error\n");
    }
    else if (pid == 0)
    {
        (void) signal(SIGALRM, catcher);
        while (1)
        {
            //pause(); // removing this causes killer loop
            counter++;
            if (sig_caught != 0)
            {
                printf("Count = %zu\n", counter);
                sig_caught = 0;
            }
            //micro_sleep(10000);
        }
    }
    else
    {
        for (i = 0; i < 5; i++)
        {
            sleep(1);
            kill(pid, SIGALRM);
        }
        micro_sleep(1000);
        kill(pid, SIGTERM);
    }
    return 0;
}

