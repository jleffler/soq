/* SO 4555-1869 */
/* Fixed per suggested duplicate - SO 1591-2322 */
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t globalMutex[2];
pthread_cond_t globalCondVar[2];

static int var_main[2] = { 0, 0 };
static pthread_cond_t cv_main[2]   = { PTHREAD_COND_INITIALIZER,  PTHREAD_COND_INITIALIZER  };
static pthread_mutex_t mtx_main[2] = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER };

static void *threadFunc1(void *args)
{
    assert(args == NULL);
    pthread_mutex_lock(&globalMutex[0]);
    printf("T1: global mutex locked\n");
    pthread_mutex_lock(&mtx_main[0]);
    printf("T1: main mutex locked\n");
    var_main[0] = 1;
    pthread_cond_signal(&cv_main[0]);
    printf("T1: main condition signalled\n");
    pthread_mutex_unlock(&mtx_main[0]);
    printf("T1: main mutex unlocked\n");
    pthread_cond_wait(&globalCondVar[0], &globalMutex[0]);
    printf("T1: global condition waited on\n");
    printf("X modified by threadFunc 1\n");
    pthread_mutex_unlock(&globalMutex[0]);
    printf("T1: global mutex unlocked\n");
    return NULL;
}

static void *threadFunc2(void *args)
{
    assert(args == NULL);
    pthread_mutex_lock(&globalMutex[1]);
    printf("T2: global mutex locked\n");
    pthread_mutex_lock(&mtx_main[0]);
    printf("T2: main mutex locked\n");
    var_main[1] = 1;
    pthread_cond_signal(&cv_main[0]);
    printf("T2: main condition signalled\n");
    pthread_mutex_unlock(&mtx_main[0]);
    printf("T2: main mutex unlocked\n");
    pthread_cond_wait(&globalCondVar[1], &globalMutex[1]);
    printf("T2: global condition waited on\n");
    printf("X Modified by threadFunc 2\n");
    pthread_mutex_unlock(&globalMutex[1]);
    printf("T2: global mutex unlocked\n");
    return NULL;
}

#include <stdarg.h>
#include <errno.h>
#include "stderr.h"

static void err_ptherr(int errnum, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    errno = errnum;
    err_print(ERR_SYSERR, ERR_EXIT, fmt, args);
    va_end(args);
    /*NOTREACHED because of ERR_SYSERR*/
}

int main(int argc, char **argv)
{
    assert(argc > 0);
    err_setarg0(argv[0]);
    pthread_t thread[2];
    int rc;

    if ((rc = pthread_mutex_init(&globalMutex[0], NULL)) != 0)
        err_ptherr(rc, "failed to initialize global mutex %d: ", 0);
    if ((rc = pthread_mutex_init(&globalMutex[1], NULL)) != 0)
        err_ptherr(rc, "failed to initialize global mutex %d: ", 1);
    if ((rc = pthread_cond_init(&globalCondVar[0], NULL)) != 0)
        err_ptherr(rc, "failed to initialize global condvar %d: ", 0);
    if ((rc = pthread_cond_init(&globalCondVar[1], NULL)) != 0)
        err_ptherr(rc, "failed to initialize global condvar %d: ", 1);
    printf("Initialization done\n");

    if ((rc = pthread_mutex_lock(&globalMutex[0])) != 0)
        err_ptherr(rc, "failed to lock global mutex %d: ", 0);
    if ((rc = pthread_mutex_lock(&globalMutex[1])) != 0)
        err_ptherr(rc, "failed to lock global mutex %d: ", 1);
    printf("Global mutexes locked\n");

    if ((rc = pthread_create(&thread[0], NULL, threadFunc1, NULL)) != 0)
        err_ptherr(rc, "failed to create thread %d: ", 0);
    if ((rc = pthread_create(&thread[1], NULL, threadFunc2, NULL)) != 0)
        err_ptherr(rc, "failed to create thread %d: ", 1);
    printf("Threads created\n");

    if ((rc = pthread_mutex_lock(&mtx_main[0])) != 0)
        err_ptherr(rc, "failed to lock main mutex %d: ", 0);
    if ((rc = pthread_mutex_lock(&mtx_main[1])) != 0)
        err_ptherr(rc, "failed to lock main mutex %d: ", 1);
    printf("Main mutexes locked\n");

    /* Let the threads lock their mutexes */
    if ((rc = pthread_mutex_unlock(&globalMutex[0])) != 0)
        err_ptherr(rc, "failed to unlock global mutex %d: ", 0);
    if ((rc = pthread_mutex_unlock(&globalMutex[1])) != 0)
        err_ptherr(rc, "failed to unlock global mutex %d: ", 1);
    printf("Global mutexes unlocked\n");

    if (var_main[0] == 0)
    {
        while ((rc = pthread_cond_wait(&cv_main[0], &mtx_main[0])) == 0 && var_main[0] == 0)
            ;
        if (rc != 0)
            err_ptherr(rc, "failed to wait on main condition %d: ", 0);
    }
    if (var_main[1] == 0)
    {
        while ((rc = pthread_cond_wait(&cv_main[1], &mtx_main[1])) != 0 && var_main[1] == 0)
            ;
        if (rc != 0)
            err_ptherr(rc, "failed to wait on main condition %d: ", 1);
    }
    printf("Main conditions waited on\n");

    if ((rc = pthread_mutex_unlock(&mtx_main[0])) != 0)
        err_ptherr(rc, "failed to unlock main mutex %d: ", 0);
    if ((rc = pthread_mutex_unlock(&mtx_main[1])) != 0)
        err_ptherr(rc, "failed to unlock main mutex %d: ", 1);
    printf("Main mutexes unlocked\n");

    if ((rc = pthread_mutex_lock(&globalMutex[0])) != 0)
        err_ptherr(rc, "failed to lock global mutex %d: ", 0);
    if ((rc = pthread_mutex_lock(&globalMutex[1])) != 0)
        err_ptherr(rc, "failed to lock global mutex %d: ", 0);
    printf("Global mutexes locked again\n");

    if ((rc = pthread_cond_signal(&globalCondVar[0])) != 0)
        err_ptherr(rc, "failed to signal global condition %d: ", 0);
    if ((rc = pthread_cond_signal(&globalCondVar[1])) != 0)
        err_ptherr(rc, "failed to signal global condition %d: ", 1);
    printf("Global conditions signalled\n");

    if ((rc = pthread_mutex_unlock(&globalMutex[0])) != 0)
        err_ptherr(rc, "failed to unlock global mutex %d: ", 0);
    if ((rc = pthread_mutex_unlock(&globalMutex[1])) != 0)
        err_ptherr(rc, "failed to unlock global mutex %d: ", 1);
    printf("Global mutexes unlocked again\n");

    if ((rc = pthread_join(thread[1], NULL)) != 0)
        err_ptherr(rc, "failed to join thread %d: ", 0);
    if ((rc = pthread_join(thread[0], NULL)) != 0)
        err_ptherr(rc, "failed to join thread %d: ", 1);
    printf("Threads joined\n");

    if ((rc = pthread_cond_destroy(&globalCondVar[0])) != 0)
        err_ptherr(rc, "failed to destroy global condition %d: ", 0);
    if ((rc = pthread_cond_destroy(&globalCondVar[1])) != 0)
        err_ptherr(rc, "failed to destroy global condition %d: ", 1);
    if ((rc = pthread_mutex_destroy(&globalMutex[0])) != 0)
        err_ptherr(rc, "failed to destroy global mutex %d: ", 0);
    if ((rc = pthread_mutex_destroy(&globalMutex[1])) != 0)
        err_ptherr(rc, "failed to destroy global mutex %d: ", 1);

    if ((rc = pthread_mutex_destroy(&mtx_main[0])) != 0)
        err_ptherr(rc, "failed to destroy main mutex %d: ", 0);
    if ((rc = pthread_mutex_destroy(&mtx_main[1])) != 0)
        err_ptherr(rc, "failed to destroy main mutex %d: ", 1);
    if ((rc = pthread_cond_destroy(&cv_main[0])) != 0)
        err_ptherr(rc, "failed to destroy main condition %d: ", 0);
    if ((rc = pthread_cond_destroy(&cv_main[1])) != 0)
        err_ptherr(rc, "failed to destroy main condition %d: ", 1);
    printf("Cleanup complete\n");

    return 0;
}

