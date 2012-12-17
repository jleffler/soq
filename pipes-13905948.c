#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static int fd[2];
static volatile sig_atomic_t t = 1;
static int parent;

static void okay(int sign)
{
    t = (sign == 0);
}

static void ch(void)
{
    int pid = getpid();
    printf("Child %i: at work\n", pid);
    close(fd[0]);
    while (t == 1)
    {
        printf("Child %d: pausing on t\n", pid);
        pause();
    }
    srand((unsigned)time(NULL) ^ pid);
    int x = rand() % 101;
    int y = rand() % 101;
    int z = rand() % 101;
    int r = rand() % 101;
    char b[50];
    sprintf(b, "%i %i %i %i %i", pid, x, y, z, r);
    printf("Child %d: sending %s\n", pid, b);
    while (write(fd[1], b, 50) < 0)
        printf("Child %d: write failed\n", pid);

    close(fd[1]);
    printf("Child %d: exiting\n", pid);
    exit(0);
}

int main(void)
{
    int cs[3];
    pipe(fd);
    parent = getpid();
    printf("%d at work\n", parent);

    struct sigaction sa;
    sa.sa_flags = 0;
    sigfillset(&sa.sa_mask);

    sa.sa_handler = okay;
    sigaction(SIGUSR1, &sa, 0);

    if ((cs[0] = fork()) < 0)
        perror("fork 1");
    else if (cs[0] == 0)
        ch();
    else if ((cs[1] = fork()) < 0)
        perror("fork 2");
    else if (cs[1] == 0)
        ch();
    else if ((cs[2] = fork()) < 0)
        perror("fork 3");
    else if (cs[2] == 0)
        ch();
    else
    {
        printf("Children: %i %i %i\n", cs[0], cs[1], cs[2]);
        close(fd[1]);

        kill(cs[0], SIGUSR1);
        kill(cs[1], SIGUSR1);
        kill(cs[2], SIGUSR1);
        printf("Children signalled\n");

        char buffer[64];
        int nbytes;
        while ((nbytes = read(fd[0], buffer, sizeof(buffer)-1)) > 0)
        {
            buffer[nbytes] = '\0';
            printf("Adult %d: read <<%s>>\n", parent, buffer);
        }

        int status;
        waitpid(cs[0], &status, 0);
        printf("Child 1 ended\n");
        waitpid(cs[1], &status, 0);
        printf("Child 2 ended\n");
        waitpid(cs[2], &status, 0);
        printf("Child 3 ended\n");
        close(fd[0]);
    }
    printf("%d exiting\n", (int)getpid());
    return 0;
}
