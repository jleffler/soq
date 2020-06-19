/*
@(#)File:           mkpath.c
@(#)Purpose:        Create all directories in path
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2020
@(#)Derivation:     mkpath.c 1.16 2020/06/19 15:08:10
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "mkpath.h"
#include "emalloc.h"

#include <errno.h>
#include <string.h>
/* "sysstat.h" == <sys/stat.h> with fixup for (old) Windows - inc mode_t */
#include "sysstat.h"

typedef struct stat Stat;

static int do_mkdir(const char *path, mode_t mode)
{
    Stat            st;
    int             status = 0;

    if (stat(path, &st) != 0)
    {
        /* Directory does not exist. EEXIST for race condition */
        if (mkdir(path, mode) != 0 && errno != EEXIST)
            status = -1;
    }
    else if (!S_ISDIR(st.st_mode))
    {
        errno = ENOTDIR;
        status = -1;
    }

    return(status);
}

/**
** mkpath - ensure all directories in path exist
** Algorithm takes the pessimistic view and works top-down to ensure
** each directory in path exists, rather than optimistically creating
** the last element and working backwards.
*/
int mkpath(const char *path, mode_t mode)
{
    char           *pp;
    char           *sp;
    int             status;
    char           *copypath = STRDUP(path);

    status = 0;
    pp = copypath;
    while (status == 0 && (sp = strchr(pp, '/')) != 0)
    {
        if (sp != pp)
        {
            /* Neither root nor double slash in path */
            *sp = '\0';
            status = do_mkdir(copypath, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == 0)
        status = do_mkdir(path, mode);
    FREE(copypath);
    return (status);
}

#ifdef TEST

#include <stdio.h>
#include <unistd.h>

/*
** Stress test with parallel running of mkpath() function.
** Before the EEXIST test, code would fail.
** With the EEXIST test, code does not fail.
**
** Test shell script
** PREFIX=mkpath.$$
** NAME=./$PREFIX/sa/32/ad/13/23/13/12/13/sd/ds/ww/qq/ss/dd/zz/xx/dd/rr/ff/ff/ss/ss/ss/ss/ss/ss/ss/ss
** : ${MKPATH:=mkpath}
** ./$MKPATH $NAME &
** [...repeat a dozen times or so...]
** ./$MKPATH $NAME &
** wait
** rm -fr ./$PREFIX/
*/

int main(int argc, char **argv)
{
    int             i;

    for (i = 1; i < argc; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (fork() == 0)
            {
                int rc = mkpath(argv[i], 0777);
                if (rc != 0)
                    fprintf(stderr, "%d: failed to create (%d: %s): %s\n",
                            (int)getpid(), errno, strerror(errno), argv[i]);
                exit(rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
            }
        }
        int status;
        int fail = 0;
        while (wait(&status) != -1)
        {
            if (WEXITSTATUS(status) != 0)
                fail = 1;
        }
        if (fail == 0)
            printf("created: %s\n", argv[i]);
    }
    return(0);
}

#endif /* TEST */
