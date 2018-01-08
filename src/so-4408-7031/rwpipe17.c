/* Inspired by SO 4408-7031 */
/*
*** https://stackoverflow.com/questions/44087031
** Trying to use pipe to read from write to another program?
*/

/* #include "rwpipe.h" */
#ifndef RWPIPE_H_INCLUDED
#define RWPIPE_H_INCLUDED

#include <sys/types.h>  /* ssize_t and size_t */

typedef struct RW_Pipe RW_Pipe;

extern RW_Pipe *rwp_open(char **argv);
extern int      rwp_close(RW_Pipe *rwp);
extern ssize_t  rwp_read(RW_Pipe *rwp, void *buffer, size_t buflen);
extern ssize_t  rwp_write(RW_Pipe *rwp, const void *buffer, size_t buflen);
extern pid_t    rwp_pid(RW_Pipe *rwp);

#endif /* RWPIPE_H_INCLUDED */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

struct RW_Pipe
{
    pid_t cpid;
    int to_child;
    int fr_child;
};

pid_t rwp_pid(RW_Pipe *rwp)
{
    return rwp->cpid;
}

int rwp_close(RW_Pipe *rwp)
{
    if (rwp == 0)
        return 0;

    close(rwp->to_child);
    close(rwp->fr_child);
    /* It's at least tempting to nanosleep() for a millisecond or so */
    kill(rwp->cpid, SIGTERM);
    int status;
    int corpse;
    while ((corpse = waitpid(rwp->cpid, &status, WUNTRACED|WCONTINUED)) > 0)
    {
        if (WIFEXITED(status) || WIFSIGNALED(status))
            break;
    }
    int rv = (corpse == rwp->cpid) ? status : -1;
    free(rwp);

    return rv;
}

static inline void close_pipe(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

RW_Pipe *rwp_open(char **argv)
{
    int to_child[2];
    if (pipe(to_child) != 0)
        return NULL;

    int fr_child[2];
    if (pipe(fr_child) != 0)
    {
        close_pipe(to_child);
        return NULL;
    }

    RW_Pipe *rwp = (RW_Pipe *)calloc(1, sizeof(*rwp));
    if (rwp == NULL)
    {
        close_pipe(to_child);
        close_pipe(fr_child);
        return NULL;
    }

    fflush(0);

    int pid = fork();
    if (pid == -1)
    {
        close_pipe(to_child);
        close_pipe(fr_child);
        free(rwp);
        return NULL;
    }

    if (pid == 0)
    {
        dup2(to_child[0], STDIN_FILENO);
        dup2(fr_child[1], STDOUT_FILENO);
        close_pipe(to_child);
        close_pipe(fr_child);
        execvp(argv[0], argv);
        fprintf(stderr, "Error: failed to exec command '%s' (%d: %s)\n",
                argv[0], errno, strerror(errno));
        exit(1);
    }

    close(fr_child[1]);
    close(to_child[0]);
    rwp->to_child = to_child[1];
    rwp->fr_child = fr_child[0];
    rwp->cpid = pid;

    return rwp;
}

ssize_t rwp_read(RW_Pipe *rwp, void *buffer, size_t buflen)
{
   return read(rwp->fr_child, buffer, buflen);
}

ssize_t rwp_write(RW_Pipe *rwp, const void *buffer, size_t buflen)
{
   return write(rwp->to_child, buffer, buflen);
}

#ifdef TEST

int main(void)
{
    signal(SIGPIPE, SIG_IGN);

    char *cmdv[] = { "bc", "-l", 0 };

    RW_Pipe *rwp = rwp_open(cmdv);
    if (rwp == NULL)
    {
        fprintf(stderr, "Error: failed to execute command '%s'\n", cmdv[0]);
        return EXIT_FAILURE;
    }

    char *buffer = 0;
    size_t buflen = 0;
    ssize_t ibytes;
    while ((ibytes = getline(&buffer, &buflen, stdin)) != -1)
    {
        printf("To child: %s", buffer);
        int nbytes = rwp_write(rwp, buffer, ibytes);
        if (nbytes != ibytes)
            break;

        char rbuf[BUFSIZ];
        nbytes = rwp_read(rwp, rbuf, sizeof(rbuf)-1);
        if (nbytes <= 0)
            break;
        rbuf[nbytes] = '\0';
        rbuf[strcspn(rbuf, "\r\n")] = '\0';
        printf("From child: %d [%s]\n", nbytes, rbuf);
    }

    printf("End of loop\n");
    int pid = rwp_pid(rwp);
    int rv = rwp_close(rwp);
    printf("Child %d exited with status 0x%.4X\n", pid, rv & 0xFFFF);

    return 0;
}

#endif /* TEST */
