#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static int fd[2];
static int t = 1;
static int parent;

static void okay(int sign)
{
    int pid = getpid();
    if (pid == parent)
        printf("Adult %d: signal %d - setting t to 0\n", pid, sign);
    else
        printf("Child %d: signal %d - setting t to 0\n", pid, sign);
    t = 0;
}

static void rr(int sign)
{
    printf("Adult %d: signal %d - reading input\n", (int)getpid(), sign);
    char b[50];
    while (read(fd[0], &b, 50) < 0)
    {
        printf("Adult %d: read in rr() failed\n", (int)getpid());
    }
    printf("Adult %d: got <<%s>>\n", (int)getpid(), b);
}

static void ch(void)
{
    int pid = getpid();
    printf("Child %i: at work\n", pid);
    close(fd[0]);
    while (t == 1)
    {
        printf("Child %d: sleeping on t\n", pid);
        sleep(1);
    }
    srand((unsigned)time(NULL) ^ pid); // init
    int x = rand() % 101;
    int y = rand() % 101;
    int z = rand() % 101;
    int r = rand() % 101;
    char b[50];
    sprintf(b, "%i %i %i %i %i", pid, x, y, z, r);
    printf("Child %d: sending %s\n", pid, b);
    while (write(fd[1], b, 50) < 0)
    {
        printf("Child %d: write failed\n", pid);
    }
    kill(parent, SIGUSR2);
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
    sa.sa_handler = rr;
    sigaction(SIGUSR2, &sa, 0);

    if ((cs[0] = fork()) < 0)
        perror("fork 1");
    else if (cs[0] == 0)
        ch();   /* Child 1 */
    else if ((cs[1] = fork()) < 0)
        perror("fork 2");
    else if (cs[1] == 0)
        ch();   /* Child 2 */
    else if ((cs[2] = fork()) < 0)
        perror("fork 3");
    else if (cs[2] == 0)
        ch();   /* Child 3 */
    else
    {
        /* Parent */
        printf("Children: %i %i %i\n", cs[0], cs[1], cs[2]);
        close(fd[1]);
        //sleep(1);
        kill(cs[0], SIGUSR1);
        //sleep(1);
        kill(cs[1], SIGUSR1);
        //sleep(1);
        kill(cs[2], SIGUSR1);
        printf("Children signalled\n");
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
