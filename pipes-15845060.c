#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "safe_functions.h"

void call(const char *filename, int in_descr, int out_descr, pid_t *sons, int n)
{
    sons[n] = safe_fork();
    if(sons[n] == 0)
    {
        safe_dup2(in_descr, STDIN_FILENO);
        safe_dup2(out_descr, STDOUT_FILENO);

        safe_execv(filename, (char **)NULL);
    }
}

int find_num(pid_t * sons, int n, pid_t id)
{
    for(int i=0; i<n; i++)
        if(sons[i] == id)
            return i;

    return -1;
}

int main(int argc, const char ** argv)
{

    int **descr;
    descr = (int**)safe_malloc(argc*sizeof(int*));
    for(int i=0; i<argc; i++)
        descr[i] = (int*) safe_malloc(2*sizeof(int));

    for(int i=1; i+1<argc; i++)
        safe_pipe(descr[i]);

    descr[0][0] = 0;
    descr[argc-1][1] = 1;

    pid_t *sons = safe_malloc((argc-1) * sizeof(pid_t));

    for(int i=1; i<argc; i++)
        call(argv[i], descr[i-1][0], descr[i][1], sons, i-1);

    int status;
    pid_t id;
    while(1)
    {
        id = safe_wait(&status);
        if(id == -1)
            break;

        if(WIFEXITED(status))
        {
            int num = find_num(sons, argc-1, id);
            safe_close(descr[num][0]);
            safe_close(descr[num+1][1]);
            continue;
        }

        if(WIFSIGNALED(status))
        {
            int num = find_num(sons, argc-1, id);
            fatal_error("Process was teminated by a signal", argv[num+1], WEXITSTATUS(status));
        }
    }

    free(sons);
    for(int i=0; i<argc; i++)
        free(descr[i]);
    free(descr);
}
