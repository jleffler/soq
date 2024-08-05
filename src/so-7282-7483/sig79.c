/* SO 7282-7483 */
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// first sigHandler
static void sigHandler1(int signum)
{    
    assert(signum == SIGUSR1);
    printf("Received signal\n");
}

// second sigHandler
static void sigHandler2(int signum)
{
    assert(signum == SIGUSR2);
    printf("Received other signal\n");
}

int main(void)
{
    // Number of process
    int N = 2;

    // Assign sigHandlers
    signal(SIGUSR1, sigHandler1);
    signal(SIGUSR2, sigHandler2);

    // array for pids to activate in order;
    pid_t pid[N];

    int i;

    for (i = 0; i < N; i++)
    {
        // creation child
        pid[i] = fork();

        if (pid[i] == 0)
        {
            // if is the last child, resume the father
            if (i == N - 1)
            {
                kill(getppid(), SIGUSR2);
            }

            // expect SIGUSR1
            pause();
            printf("%i completed\n", getpid());
            exit(0);
        }
    }

    // expext that all child started
    pause();

    // active the last child
    i--;
    kill(pid[i], SIGUSR1);
    signal(SIGUSR1, sigHandler1);

    // active other child
    while (wait(NULL) != -1)
    {
        i--;
        kill(pid[i], SIGUSR1);
        signal(SIGUSR1, sigHandler1);
    }
    printf("All fine\n");
    exit(0);
}
