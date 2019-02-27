#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

static const char *arg0 = "undefined";

static void err_error(const char *fmt, ...)
{
    int errnum = errno;
    va_list args;
    fflush(0);
    fprintf(stderr, "%s: pid %d:", arg0, (int)getpid());
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (errnum != 0)
        fprintf(stderr, "(%d: %s)", errnum, strerror(errnum));
    fputc('\n', stderr);
    exit(1);
}

static void print(const char *fmt, ...)
{
    va_list args;
    printf("pid %d: ", (int)getpid());
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    fflush(0);
}

#define PIPE_NAME   "MY_PIPE"
#define N 5
#define M 10

static struct sembuf operations;
static int semid;
static key_t key;
static int marker;

static void semWait(int semid, int sempos)
{
    operations.sem_num = sempos;
    operations.sem_op = -1;
    operations.sem_flg = 0;

    if (semop(semid, &operations, 1) < 0)
        err_error("semop wait");
}

static void semPost(int semid, int sempos)
{
    operations.sem_num = sempos;
    operations.sem_op = 1;
    operations.sem_flg = IPC_NOWAIT;

    if (semop(semid, &operations, 1) < 0)
        err_error("semop post");
}

static void worker(int id)
{
    int j;
    int fd = open(PIPE_NAME, O_RDWR);
    if (fd < 0)
        err_error("failed to open FIFO %s for read & write", PIPE_NAME);
    print("Worker %d: fd %d\n", id, fd);

    for (j = 0; j < M; j++)
    {
        int nmarker;
        print("waiting for %d\n", id);
        semWait(semid, id);
        if (read(fd, &nmarker, sizeof(int)) != sizeof(int))
            err_error("short read from FIFO");
        print("Got %d from FIFO\n", nmarker);
        nmarker = nmarker + 1;
        if (write(fd, &nmarker, sizeof(nmarker)) != sizeof(nmarker))
            err_error("short write to FIFO");
        print("Wrote %d to FIFO\n", nmarker);
        print("posting %d\n", id);
        semPost(semid, N);
    }

    if (close(fd) != 0)
        err_error("failed to close FIFO");

    print("done\n");
}

int main(int argc, char **argv)
{
    int i;
    int sarray[N+1] = {0};
    key = 23;
    marker = 0;
    arg0 = argv[0];

    if (argc != 1)
        err_error("Usage: %s\n", arg0);

    if ((semid = semget(key , N+1, 0666 | IPC_CREAT)) == -1)
        err_error("semget");

    if ((semctl(semid, N+1, SETALL, sarray)) < 0)
    {
        perror("ERROR: semctl - val\n");
        exit(-1);
    }

    if (mkfifo(PIPE_NAME, S_IFIFO | 0666) < 0)
        err_error("failed to create FIFO %s\n", PIPE_NAME);
    print("FIFO created\n");

    int fd;
    if ((fd = open(PIPE_NAME, O_RDWR)) < 0 )
        err_error("failed to open FIFO %s\n", PIPE_NAME);
    print("FIFO opened\n");

    if (write(fd, &marker, sizeof(marker)) != sizeof(marker))
        err_error("short write to FIFO");
    print("FIFO loaded\n");

    print("Master: about to fork\n");
    for (i = 0; i < N; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_error("failed to fork");
        else if (pid == 0)
        {
            worker(i);
            exit(0);
        }
    }

    print("Master: about to loop\n");
    for (i = 0; i < (M*N); i++)
    {
        print("posting to %d\n", i%N);
        semPost(semid, i%N);
        print("waiting for %d\n", N);
        semWait(semid, N);
    }

    if (close(fd) != 0)
        err_error("failed to close FIFO");

    print("Marker = %d\n", marker);

    if (semctl( semid, 1, IPC_RMID ) == -1)
        err_error("semctl remove");

    if (unlink(PIPE_NAME) != 0)
        err_error("failed to remove FIFO %s", PIPE_NAME);

    return(0);
}

