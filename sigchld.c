#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static siginfo_t sig_info;
static volatile sig_atomic_t sig_num;
static void *sig_ctxt;

static void catcher(int signum, siginfo_t *info, void *vp)
{
    sig_num = signum;
    sig_info = *info;
    sig_ctxt = vp;
}

static void set_handler(int signum)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = catcher;
    sigemptyset(&sa.sa_mask);

    if (sigaction(signum, &sa, 0) != 0)
    {
        int errnum = errno;
        fprintf(stderr, "Failed to set signal handler (%d: %s)\n", errnum, strerror(errnum));
        exit(1);
    }
}

static void prt_interrupt(FILE *fp)
{
    if (sig_num != 0)
    {
        fprintf(fp, "Signal %d from PID %d\n", sig_info.si_signo, (int)sig_info.si_pid);
        sig_num = 0;
    }
}

static void five_kids(void)
{
    for (int i = 0; i < 5; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            break;
        else if (pid == 0)
        {
            printf("PID %d - exiting with status %d\n", (int)getpid(), i);
            exit(i);
        }
        else
        {
            int status = 0;
            pid_t corpse = wait(&status);
            printf("Child: %d; Corpse: %d; Status = 0x%.4X\n", pid, corpse, (status & 0xFFFF));
            prt_interrupt(stdout);
            fflush(0);
        }
    }
}

int main(void)
{
    printf("SIGCHLD set to SIG_DFL\n");
    signal(SIGCHLD, SIG_DFL);
    five_kids();

    printf("SIGCHLD set to SIG_IGN\n");
    signal(SIGCHLD, SIG_IGN);
    five_kids();

    printf("SIGCHLD set to catcher()\n");
    set_handler(SIGCHLD);
    five_kids();

    return(0);
}
