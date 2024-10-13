/* SO 7020-7788 */
/*
** Count the lines, words and characters of n files.
**
** - Each file in the list must be processed (counted) by a distinct
**   process;
** - The hierarchical relationship between processes must be such that
**   the i+1 process is created by the process i;
**
** Example:
**
**  PID    PPID
** child1 parent1 File1 l=2 w=5 c=20
** child2 child1  File2 l=3 w=6 c=30
**
** Total:               l=5 w=11 c=50
**
** Each process sends the numbers to the parent with a pipe and the
** parent will sum them in 3 different variables.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "stderr.h"

static void count_file(const char *file, int counts[3])
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
        err_syserr("failed to open file '%s' for reading: ", file);
    int lines =0;
    int words = 0;
    int bytes = 0;
    int in_word = 0;
    int c;
    while ((c = getc(fp)) != EOF)
    {
        bytes++;
        if (c == '\n')
            lines++;
        if (isspace(c))
        {
            in_word = 0;
        }
        else
        {
            if (!in_word)
                words++;
            in_word = 1;
        }
    }
    counts[0] = lines;
    counts[1] = words;
    counts[2] = bytes;
    fclose(fp);
}

static inline void random_children(void)
{
    srand(getpid());
    int n = rand() % 10;
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_syserr("failed to fork: ");
        if (pid == 0)
            exit(i + 1);
    }
}

static void noisy_wait_loop(void)
{
    int status;
    int corpse;
    while ((corpse = wait(&status)) > 0)
        err_remark("child %d died with exit status 0x%.4X\n", corpse, status);
}

static void child_at_work(int fd, int argc, char **argv, int n)
{
    int data[6] = { n, getpid(), getppid(), 0, 0, 0 };
    //random_children();
    if (n < argc - 1)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_syserr("failed to fork: ");
        if (pid == 0)
        {
            child_at_work(fd, argc, argv, n + 1);
            err_error("%s() returned unexpectedly\n", __func__);
        }
    }
    count_file(argv[n], &data[3]);
    if (write(fd, data, sizeof(data)) != sizeof(data))
        err_syserr("failed to write data to pipe: ");
    close(fd);
    noisy_wait_loop();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc < 2)
        err_usage("file [...]");

    int p[2];
    if (pipe(p) != 0)
        err_syserr("failed to create pipe: ");

    pid_t pid = fork();
    if (pid < 0)
        err_syserr("failed to fork: ");
    if (pid == 0)
    {
        err_setlogopts(ERR_LOG|ERR_MILLI);
        close(p[0]);
        child_at_work(p[1], argc, argv, 1);
        err_error("function child_at_work() returned unexpectedly\n");
    }

    close(p[1]);

    int data[6];
    /*
    ** 0 = file number
    ** 1 = PID
    ** 2 = PPID
    ** 3 = lines
    ** 4 = words
    ** 5 = bytes
    */

    int lines = 0;
    int words = 0;
    int bytes = 0;
    printf("%5s  %5s\n", "PID", "PPID");
    while (read(p[0], data, sizeof(data)) == sizeof(data))
    {
        lines += data[3];
        words += data[4];
        bytes += data[5];
        printf("%5d  %5d  l=%5d w=%5d c=%5d  %s\n",
               data[1], data[2], data[3], data[4], data[5], argv[data[0]]);
    }

    printf("%-14.14sl=%5d w=%5d c=%5d\n", "Total:", lines, words, bytes);
    close(p[0]);

    noisy_wait_loop();

    return 0;
}
