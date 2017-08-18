/* SO 4574-5483 */
#include "stderr.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static const char filename[] = "pt-next.dat";
static double last = 0.0;

static void new_tree(int num);
static void write_file(int num);

int main(int argc, char *argv[])
{
    err_setarg0(argv[0]);
    err_setlogopts(ERR_PID|ERR_MILLI);

    int n = 4;
    if (argc == 2)
        n = atoi(argv[1]);
    write_file(0);
    last = pow(2, (n - 1));
    new_tree(1);
    return 0;
}

static void write_file(int num)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
        err_syserr("failed to create file '%s' for writing\n", filename);
    if (write(fd, &num, sizeof(num)) != sizeof(num))
        err_syserr("failed to write %d to file '%s'\n", num, filename);
    close(fd);
    err_remark("wrote %2d to '%s'\n", num, filename);
}

static int read_file(void)
{
    int num = -1;
    int fd = open(filename, O_RDONLY);
    if (fd > 0)
    {
        if (read(fd, &num, sizeof(num)) != sizeof(num))
            num = -1;
        close(fd);
    }
    err_remark("read %2d from '%s'\n", num, filename);
    return num;
}

static void wait_for_turn(int num)
{
    struct timespec ms = { .tv_sec = 0, .tv_nsec = 1000000 };
    while (read_file() != num - 1)
    {
        err_remark("dozing\n");
        nanosleep(&ms, 0);
    }
}

static void new_tree(int x)
{
    char buff[60];
    err_remark("Process = %2d\n", x);
    wait_for_turn(x);
    sprintf(buff, "I'm process %2d with pid %5d and ppid %5d\n", x, getpid(), getppid());
    write(1, buff, strlen(buff));
    write_file(x);
    if (x >= last)
        return;

    if (!fork())
    {
        new_tree(2 * x);
        exit(0);
    }

    if (!fork())
    {
        new_tree(2 * x + 1);
        exit(0);
    }

    int corpse, status;
    while ((corpse = wait(&status)) > 0)
        err_remark("child %5d exited with status 0x%.4X\n", corpse, status);
}
