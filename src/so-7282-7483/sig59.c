/* SO 7282-7483 */
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void write_msg(size_t len, char *msg)
{
    int pid = getpid();
    for (int i = 5; i > 0; i--)
    {
        msg[i-1] = pid % 10 + '0';
        pid /= 10;
    }
    write(STDOUT_FILENO, msg, len);
}

// first sigHandler
static void sigHandler1(int signum)
{    
    assert(signum == SIGUSR1);
    static char msg[] = "XXXXX: Received signal SIGUSR1\n";
    write_msg(sizeof(msg) - 1, msg);
}

// second sigHandler
static void sigHandler2(int signum)
{
    assert(signum == SIGUSR2);
    static char msg[] = "XXXXX: Received signal SIGUSR2\n";
    write_msg(sizeof(msg) - 1, msg);
}

int main(void)
{
    // Number of process
    int N = 2;

    // Assign sigHandlers
    signal(SIGUSR1, sigHandler1);
    signal(SIGUSR2, sigHandler2);

    printf("%d: parent at work\n", getpid());

    // array for pids to activate in order;
    pid_t pid[N];

    for (int i = 0; i < N; i++)
    {
        // creation child
        pid[i] = fork();

        if (pid[i] == 0)
        {
            printf("%d: child %d at play\n", getpid(), i+1);
            // if is the last child, resume the father
            if (i == N - 1)
            {
                kill(getppid(), SIGUSR2);
                printf("%d: signal SIGUSR2 sent to PID %d\n", getpid(), getppid());
            }

            // expect SIGUSR1
            pause();
            printf("%d: child %d completed\n", getpid(), i+1);
            exit(i+1);
        }
        printf("%d: child %d has PID %d\n", getpid(), i+1, pid[i]);
        fflush(stdout);
    }

    // expect that all children started
    pause();

    for (int i = N; i > 0; i--)
    {
        kill(pid[i - 1], SIGUSR1);
        printf("%d: signal SIGUSR1 sent to child %d PID %d\n", getpid(), i, pid[i - 1]);
        int corpse;
        int status;
        while ((corpse = wait(&status)) > 0)
        {
            if (corpse == pid[i - 1])
            {
                printf("%d: child %d PID %d exited with status 0x%.4X\n",
                       getpid(), i, corpse, status);
                break;
            }
            else
                printf("%d: unexpected child PID %d exited with status 0x%.4X\n",
                       getpid(), corpse, status);
        }
    }

    printf("%d: All fine\n", getpid());
    return(0);
}
