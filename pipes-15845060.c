#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

//#include "error.h"
//#include "safe_functions.h"

#include "stderr.h"

extern pid_t safe_fork(void);
extern void  safe_dup2(int old_fd, int new_fd);
extern void  safe_execv(const char *prog, char **argv);
extern void  safe_pipe(int *pipe_fds);
extern void *safe_malloc(size_t size);
extern int   safe_wait(int *status);
extern void  safe_close(int fd);

static void close_pipes(int **descr, int argc)
{
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (descr[i][j] > 1)
                safe_close(descr[i][j]);
        }
    }
}

static void call(char *filename, int in_descr, int out_descr, pid_t *sons, int n, int **descr, int argc)
{
    sons[n] = safe_fork();
    if (sons[n] == 0)
    {
        char *argv[2] = { filename, NULL };
        safe_dup2(in_descr, STDIN_FILENO);
        safe_dup2(out_descr, STDOUT_FILENO);
        close_pipes(descr, argc);
        safe_execv(argv[0], argv);
    }
}

static int find_num(pid_t *sons, int n, pid_t id)
{
    for (int i=0; i<n; i++)
    {
        if (sons[i] == id)
            return i;
    }
    return -1;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int **descr;
    descr = (int**)safe_malloc(argc*sizeof(int*));

    for (int i=0; i<argc; i++)
        descr[i] = (int*) safe_malloc(2*sizeof(int));

    for (int i=1; i+1<argc; i++)
        safe_pipe(descr[i]);

    descr[0][0] = 0;
    descr[argc-1][1] = 1;

    pid_t *sons = safe_malloc((argc-1) * sizeof(pid_t));

    for (int i=1; i<argc; i++)
        call(argv[i], descr[i-1][0], descr[i][1], sons, i-1, descr, argc);

    close_pipes(descr, argc);

    while (1)
    {
        int status;
        pid_t id = safe_wait(&status);

        if (id == -1)
            break;

        if (WIFEXITED(status))
        {
            int num = find_num(sons, argc-1, id);
            safe_close(descr[num][0]);
            safe_close(descr[num+1][1]);
            continue;
        }

        if (WIFSIGNALED(status))
        {
            int num = find_num(sons, argc-1, id);
            err_error("Process %s was terminated by signal %d", argv[num+1], WEXITSTATUS(status));
        }
    }

    free(sons);
    for (int i=0; i<argc; i++)
        free(descr[i]);
    free(descr);

    return(0);
}


extern pid_t safe_fork(void)
{
    pid_t pid = fork();
    if (pid < 0)
        err_syserr("Failed to fork()");
    return pid;
}

extern void safe_dup2(int old_fd, int new_fd)
{
    if (dup2(old_fd, new_fd) != 0)
        err_syserr("Failed to dup2(%d, %d)", old_fd, new_fd);
}

extern void safe_execv(const char *prog, char **argv)
{
    execv(prog, argv);
    err_syserr("Failed to execv(\"%s\")", prog);
}

extern void safe_pipe(int *pipe_fds)
{
    assert(pipe_fds != 0);
    if (pipe(pipe_fds) != 0)
        err_syserr("Failed to pipe()");
}

extern void *safe_malloc(size_t size)
{
    void *vp = malloc(size);
    if (vp == 0)
        err_syserr("Out of memory");
    return vp;
}

extern int safe_wait(int *status)
{
    assert(status != 0);
    return wait(status);
}

extern void safe_close(int fd)
{
    if (close(fd) < 0)
        err_syserr("Failed to close(%d)\n", fd);
}
