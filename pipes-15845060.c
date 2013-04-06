#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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

/* Report on open file descriptors (0..19) in process */
static void dump_fds(void)
{
    struct stat b;
    char buffer[32];
    sprintf(buffer, "%d: ", getpid());
    char *str = buffer + strlen(buffer);
    for (int i = 0; i < 20; i++)
        *str++ = (fstat(i, &b) == 0) ? 'o' : '-';
    *str++ = '\n';
    *str = '\0';
    fputs(buffer, stderr);
}

static void close_pipes(int **descr, int argc)
{
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (descr[i][j] > 1)
            {
                err_remark("close %d\n", descr[i][j]);
                safe_close(descr[i][j]);
            }
        }
    }
}

static void call(char *filename, int in_descr, int out_descr, pid_t *sons, int n, int **descr, int argc)
{
    sons[n] = safe_fork();
    if (sons[n] == 0)
    {
        err_remark("call: %s\n", filename);
        char *argv[2] = { filename, NULL };
        err_remark("dup2(%d, %d)\n", in_descr, STDIN_FILENO);
        err_remark("dup2(%d, %d)\n", out_descr, STDOUT_FILENO);
        safe_dup2(in_descr, STDIN_FILENO);
        safe_dup2(out_descr, STDOUT_FILENO);
        close_pipes(descr, argc);
        dump_fds();
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
    err_setlogopts(ERR_PID);
    dump_fds();

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
    {
        err_remark("Command: %s\n", argv[i]);
        call(argv[i], descr[i-1][0], descr[i][1], sons, i-1, descr, argc);
    }

    close_pipes(descr, argc);

    while (1)
    {
        int status;
        pid_t id = safe_wait(&status);
        err_remark("wait: pid %d, status 0x%.4X\n", (int)id, status);

        if (id == -1)
            break;

        if (WIFEXITED(status))
        {
            int num = find_num(sons, argc-1, id);
            //safe_close(descr[num][0]);
            //safe_close(descr[num+1][1]);
            continue;
        }

        if (WIFSIGNALED(status))
        {
            int num = find_num(sons, argc-1, id);
            err_remark("Process %s was terminated by signal %d", argv[num+1], WEXITSTATUS(status));
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
        err_syserr("Failed to fork() ");
    return pid;
}

extern void safe_dup2(int old_fd, int new_fd)
{
    if (dup2(old_fd, new_fd) < 0)
        err_syserr("Failed to dup2(%d, %d) ", old_fd, new_fd);
}

extern void safe_execv(const char *prog, char **argv)
{
    execv(prog, argv);
    err_syserr("Failed to execv(\"%s\") ", prog);
}

extern void safe_pipe(int *pipe_fds)
{
    assert(pipe_fds != 0);
    if (pipe(pipe_fds) != 0)
        err_syserr("Failed to pipe() ");
    err_remark("pipe: %d, %d\n", pipe_fds[0], pipe_fds[1]);
}

extern void *safe_malloc(size_t size)
{
    void *vp = malloc(size);
    if (vp == 0)
        err_syserr("Out of memory ");
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
