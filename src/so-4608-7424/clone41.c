#define _GNU_SOURCE
#include "stderr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sched.h>
#include <fcntl.h>

#define STACK_SIZE 1024 * 1024 * 8

#ifndef BASEDIR
#define BASEDIR "/home/centos"
#endif

static int thread_func(void *arg)
{
    assert(arg == 0);
    int i;
    char cdir[1024];
    for (i = 0; i < 100; i++)
    {
        switch (i % 3)
        {
        case 0:
            if (chdir(BASEDIR "/dirtest/dir000") != 0)
                err_syserr("chdir failed in child - 1\n");
            break;
        case 1:
            if (chdir(BASEDIR "/dirtest/dir001") != 0)
                err_syserr("chdir failed in child - 2\n");
            break;
        case 2:
            if (chdir(BASEDIR "/dirtest/dir002") != 0)
                err_syserr("chdir failed in child - 3\n");
            break;
        }
        if (getcwd(cdir, sizeof(cdir)) != cdir)
            err_syserr("getcwd() failed in child\n");
        fprintf(stderr, "Child Thread in # %d: %s\n", i, cdir);
    }

    return 1;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[argc - argc]);

    void *pstack = malloc(STACK_SIZE);
    int ret, i;
    char cdir[1024];
    ret = clone(thread_func,
                (void *)((char *)pstack + STACK_SIZE),
                CLONE_VM | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD,
                NULL);
    if (ret == -1)
    {
        fprintf(stderr, "Thread create failed\n");
        goto mem;
    }
    for (i = 0; i < 100; i++)
    {
        if (getcwd(cdir, sizeof(cdir)) != cdir)
            err_syserr("getcwd() failed in main\n");
        fprintf(stderr, "Main Function in # %d: %s\n", i, cdir);
    }
    ret = waitpid(ret, 0, 0);
    if (ret == -1)
    {
        fprintf(stderr, "waitpid failed\n");
    }
mem:

    free(pstack);
    return 1;
}
