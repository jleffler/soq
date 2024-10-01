#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "stderr.h"

static void ft_send_signal(int pid)
{
    if (kill(pid, SIGUSR1) != 0)
        err_syserr("failed to send initial signal to PID %d: ", pid);
    printf("%d: sent signal to PID = %d\n", getpid(), pid);
    fflush(stdout);
}

static void ft_signal_handler(int sig, siginfo_t *info, void *context)
{
    static int  i = 0;

    (void)context;
    if (sig == SIGUSR1)
    {
        printf("C received - %d PID: %d\n", i, info->si_pid);
        fflush(stdout);
        i++;
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

int main(int ac, char **av)
{
    err_setarg0("client");
    struct sigaction    action;
    sigset_t            set;

    if (ac != 2)
        err_usage("PID");

    alarm(15);
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = ft_signal_handler;
    action.sa_mask = set;
    sigaction(SIGUSR1, &action, NULL);
    ft_send_signal(atoi(av[1]));
    while(1)
        pause();
    return (0);
}
