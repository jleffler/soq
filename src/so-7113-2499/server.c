#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stderr.h"

static void ft_respond(int sig, siginfo_t *info, void *context)
{
    static int  i = 0;
    (void)context;
    if (sig == SIGUSR1)
    {
        i++;
        printf("S received - %d PID: %d\n", i, info->si_pid);
        fflush(stdout);
        if (info->si_pid != 0)
        {
            if (kill(info->si_pid, SIGUSR1) != 0)
                err_syserr("failed to send signal to PID %d: ", info->si_pid);
        }
        else
            err_error("info->si_pid == 0 at iteration %d\n", i);
        if (i == 5000)
            exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    err_setarg0("server");
    struct sigaction    reaction;

    sigemptyset(&reaction.sa_mask);
    alarm(15);
    reaction.sa_flags = SA_SIGINFO;
    reaction.sa_sigaction = ft_respond;
    sigaction(SIGUSR1, &reaction, NULL);
    printf("PID = %d\n", getpid());
    fflush(stdout);
    while (1)
        pause();
    return(0);
}
