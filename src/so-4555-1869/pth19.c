/* SO 4555-1869 */
/* Fixed per suggested duplicate - SO 1591-2322 */
#include "stderr.h"
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadControl
{
    pthread_t       ctl_thread;
	pthread_mutex_t mtx_thread;
	pthread_cond_t  cvr_thread;
	pthread_mutex_t mtx_parent;
	pthread_cond_t  cvr_parent;
	int             var_parent;
	int             thr_number;
} ThreadControl;

static void err_ptherr(int errnum, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    errno = errnum;
    err_print(ERR_SYSERR, ERR_EXIT, fmt, args);
    va_end(args);
    /*NOTREACHED because of ERR_SYSERR*/
}

static void *threadFunc(void *args)
{
	ThreadControl *ct = args;
    int rc;
    if ((rc = pthread_mutex_lock(&ct->mtx_thread)) != 0)
        err_ptherr(rc, "failed to lock thread mutex %d: ", ct->thr_number);
    printf("T%d: thread mutex locked\n", ct->thr_number);
    if ((rc = pthread_mutex_lock(&ct->mtx_parent)) != 0)
        err_ptherr(rc, "failed to lock parent mutex %d: ", ct->thr_number);
    printf("T%d: parent mutex locked\n", ct->thr_number);
    ct->var_parent = 1;
    if ((rc = pthread_cond_signal(&ct->cvr_parent)) != 0)
        err_ptherr(rc, "failed to signal parent condition %d: ", ct->thr_number);
    printf("T%d: parent condition signalled\n", ct->thr_number);
    if ((rc = pthread_mutex_unlock(&ct->mtx_parent)) != 0)
        err_ptherr(rc, "failed to unlock parent mutex %d: ", ct->thr_number);
    printf("T%d: parent mutex unlocked\n", ct->thr_number);
    if ((rc = pthread_cond_wait(&ct->cvr_thread, &ct->mtx_thread)) != 0)
        err_ptherr(rc, "failed to wait on thread condition %d: ", ct->thr_number);
    printf("T%d: thread condition waited on\n", ct->thr_number);
    printf("X modified by thread %d\n", ct->thr_number);
    if ((rc = pthread_mutex_unlock(&ct->mtx_thread)) != 0)
        err_ptherr(rc, "failed to unlock thread mutex %d: ", ct->thr_number);
    printf("T%d: thread mutex unlocked\n", ct->thr_number);
    return NULL;
}

static void init_thread_control(int thr_number, ThreadControl *ct)
{
	int rc;
    ct->thr_number = thr_number;
    ct->var_parent = 0;
    // ct->ctl_thread = 0;     // Neither portable nor necessary
    if ((rc = pthread_mutex_init(&ct->mtx_thread, NULL)) != 0)
        err_ptherr(rc, "failed to initialize thread mutex %d: ", ct->thr_number);
    if ((rc = pthread_cond_init(&ct->cvr_thread, NULL)) != 0)
        err_ptherr(rc, "failed to initialize thread condition %d: ", ct->thr_number);
    if ((rc = pthread_mutex_init(&ct->mtx_parent, NULL)) != 0)
        err_ptherr(rc, "failed to initialize parent mutex %d: ", ct->thr_number);
    if ((rc = pthread_cond_init(&ct->cvr_parent, NULL)) != 0)
        err_ptherr(rc, "failed to initialize parent condition %d: ", ct->thr_number);
    printf("Initialization complete for thread %d\n", ct->thr_number);
}

static void destroy_thread_control(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_cond_destroy(&ct->cvr_thread)) != 0)
        err_ptherr(rc, "failed to destroy thread condition %d: ", ct->thr_number);
    if ((rc = pthread_mutex_destroy(&ct->mtx_thread)) != 0)
        err_ptherr(rc, "failed to destroy thread mutex %d: ", ct->thr_number);
    if ((rc = pthread_mutex_destroy(&ct->mtx_parent)) != 0)
        err_ptherr(rc, "failed to destroy parent mutex %d: ", ct->thr_number);
    if ((rc = pthread_cond_destroy(&ct->cvr_parent)) != 0)
        err_ptherr(rc, "failed to destroy parent condition %d: ", ct->thr_number);
    printf("Cleanup complete for thread %d\n", ct->thr_number);
}

static void lock_thread_mutex(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_mutex_lock(&ct->mtx_thread)) != 0)
        err_ptherr(rc, "failed to lock thread mutex %d: ", ct->thr_number);
}

static void unlock_thread_mutex(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_mutex_unlock(&ct->mtx_thread)) != 0)
        err_ptherr(rc, "failed to unlock thread mutex %d: ", ct->thr_number);
}

static void lock_parent_mutex(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_mutex_lock(&ct->mtx_parent)) != 0)
        err_ptherr(rc, "failed to lock parent mutex %d: ", ct->thr_number);
}

static void unlock_parent_mutex(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_mutex_unlock(&ct->mtx_parent)) != 0)
        err_ptherr(rc, "failed to unlock parent mutex %d: ", ct->thr_number);
}

static void wait_parent_condition(ThreadControl *ct)
{
    if (ct->var_parent == 0)
    {
		int rc;
		printf("Parent waiting on condition from thread %d\n", ct->thr_number);
        while ((rc = pthread_cond_wait(&ct->cvr_parent, &ct->mtx_parent)) == 0 && ct->var_parent == 0)
            ;
        if (rc != 0)
            err_ptherr(rc, "failed to wait on parent condition %d: ", ct->thr_number);
    }
}

static void create_thread(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_create(&ct->ctl_thread, NULL, threadFunc, ct)) != 0)
        err_ptherr(rc, "failed to create thread %d: ", ct->thr_number);
}

static void signal_thread_condition(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_cond_signal(&ct->cvr_thread)) != 0)
        err_ptherr(rc, "failed to signal thread condition %d: ", ct->thr_number);
}

static void join_thread(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_join(ct->ctl_thread, NULL)) != 0)
        err_ptherr(rc, "failed to join thread %d: ", ct->thr_number);
}

int main(int argc, char **argv)
{
    assert(argc > 0);
    err_setarg0(argv[0]);
    int nthreads = 2;
    if (argc == 2)
    {
        nthreads = atoi(argv[1]);
        if (nthreads < 2 || nthreads > 20)
            err_error("Number of threads out of control ('%s' mapped to %d; %s)\n",
                      argv[1], nthreads, "should be in range 2..20");
    }
    ThreadControl thr_ctl[nthreads];

    for (int i = 0; i < nthreads; i++)
        init_thread_control(i+1, &thr_ctl[i]);

    for (int i = 0; i < nthreads; i++)
        lock_thread_mutex(&thr_ctl[i]);
    printf("Thread mutexes locked\n");

    for (int i = 0; i < nthreads; i++)
        lock_parent_mutex(&thr_ctl[i]);
    printf("Parent mutexes locked\n");

    for (int i = 0; i < nthreads; i++)
        create_thread(&thr_ctl[i]);
    printf("Threads created\n");

    for (int i = 0; i < nthreads; i++)
        unlock_thread_mutex(&thr_ctl[i]);
    printf("Thread mutexes unlocked\n");

    for (int i = 0; i < nthreads; i++)
        wait_parent_condition(&thr_ctl[i]);
    printf("Parent conditions waited on\n");

    for (int i = 0; i < nthreads; i++)
        unlock_parent_mutex(&thr_ctl[i]);
    printf("Parent mutexes unlocked\n");

    for (int i = 0; i < nthreads; i++)
        lock_thread_mutex(&thr_ctl[i]);
    printf("Thread mutexes locked again\n");

    for (int i = 0; i < nthreads; i++)
        signal_thread_condition(&thr_ctl[i]);
    printf("Thread conditions signalled\n");

    for (int i = 0; i < nthreads; i++)
        unlock_thread_mutex(&thr_ctl[i]);
    printf("Thread mutexes unlocked again\n");

    for (int i = 0; i < nthreads; i++)
        join_thread(&thr_ctl[i]);
    printf("Threads joined\n");

    for (int i = 0; i < nthreads; i++)
        destroy_thread_control(&thr_ctl[i]);

    return 0;
}
