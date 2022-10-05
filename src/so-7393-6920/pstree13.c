/* SO 7393-6920 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stderr.h"

struct SubProcess
{
    const char *name;
    size_t nkids;
    const char **kids;
};

struct SubProcess pstree[] =
{
    { .name = "A", .nkids = 2, .kids = (const char *[]){ "B", "C" } },
    { .name = "B", .nkids = 1, .kids = (const char *[]){ "D" } },
    { .name = "C", .nkids = 0, .kids = NULL },
    { .name = "D", .nkids = 2, .kids = (const char *[]){ "E", "F" } },
    { .name = "E", .nkids = 0, .kids = NULL },
    { .name = "F", .nkids = 0, .kids = NULL },
};
enum { NUM_PSTREE = sizeof(pstree) / sizeof(pstree[0]) };

static void be_childish(const struct SubProcess *subproc);

static void wait_for_kids(const char *name)
{
    int corpse;
    int status;
    while ((corpse = wait(&status)) != -1)
        printf("Process %s: PID = %d, Child %d exited with status 0x%.4X\n", name, getpid(), corpse, status);
}

static void find_and_run(const char *name)
{
    for (size_t i = 0; i < NUM_PSTREE; i++)
    {
        if (strcmp(name, pstree[i].name) == 0)
        {
            pid_t pid = fork();
            if (pid < 0)
                err_syserr("failed to fork(): ");
            if (pid == 0)
                be_childish(&pstree[i]);
            return;
        }
    }
    err_error("failed to find a subprocess named '%s'\n", name);
}

static void be_childish(const struct SubProcess *subproc)
{
    printf("Process %s: PID = %d, PPID = %d\n", subproc->name, getpid(), getppid());
    for (size_t i = 0; i < subproc->nkids; i++)
        find_and_run(subproc->kids[i]);
    printf("Process %s: PID = %d, %zu kids launched\n", subproc->name, getpid(), subproc->nkids);
    wait_for_kids(subproc->name);
    printf("Process %s: PID = %d, %zu kids finished\n", subproc->name, getpid(), subproc->nkids);
    exit(subproc - pstree);
}

int main(void)
{
    err_setarg0("pstree");
    err_setlogopts(ERR_PID|ERR_MILLI);
    be_childish(&pstree[0]);
    return(EXIT_SUCCESS);
}
