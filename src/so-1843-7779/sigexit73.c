#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static siginfo_t sig_info = { 0 };
static volatile sig_atomic_t sig_num = 0;
static void *sig_ctxt = 0;

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
        fprintf(fp, "Signal %d from PID %d (status 0x%.8X; UID %d)\n",
                sig_info.si_signo, (int)sig_info.si_pid, sig_info.si_status,
                (int)sig_info.si_uid);
        sig_num = 0;
    }
}

static void five_kids(void)
{
    const int base = 0xCC00FF40;
    for (int i = 0; i < 5; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            break;
        else if (pid == 0)
        {
            printf("PID %d - exiting with status %d (0x%.8X)\n",
                   (int)getpid(), base + i, base + i);
            exit(base + i);
        }
        else
        {
            int status = 0;
            pid_t corpse = wait(&status);
            if (corpse != -1)
                printf("Child: %d; Corpse: %d; Status = 0x%.4X - waited\n", pid, corpse, (status & 0xFFFF));
            struct timespec nap = { .tv_sec = 0, .tv_nsec = 1000000 }; // 1 millisecond
            nanosleep(&nap, 0);
            prt_interrupt(stdout);
            fflush(0);
        }
    }
}

int main(void)
{
    set_handler(SIGCHLD);
    five_kids();
}
