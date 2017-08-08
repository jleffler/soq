/* SO 4555-1869 */
/* Fixed per suggested duplicate - SO 1591-2322 */
#include "stderr.h"
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct ThreadControl
{
	pthread_mutex_t mtx_thread;
	pthread_cond_t  cvr_thread;
	pthread_mutex_t mtx_parent;
	pthread_cond_t  cvr_parent;
	int             var_parent;
	int             thr_number;
} ThreadControl;

static ThreadControl thr_ctl[2] =
{
	{
		.mtx_thread = PTHREAD_MUTEX_INITIALIZER, 
		.cvr_thread = PTHREAD_COND_INITIALIZER, 
		.mtx_parent = PTHREAD_MUTEX_INITIALIZER, 
		.cvr_parent = PTHREAD_COND_INITIALIZER, 
		.var_parent = 0,
		.thr_number = 1,
	},
	{
		.mtx_thread = PTHREAD_MUTEX_INITIALIZER, 
		.cvr_thread = PTHREAD_COND_INITIALIZER, 
		.mtx_parent = PTHREAD_MUTEX_INITIALIZER, 
		.cvr_parent = PTHREAD_COND_INITIALIZER, 
		.var_parent = 0,
		.thr_number = 2,
	},
};

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
    pthread_mutex_lock(&ct->mtx_thread);
    printf("T%d: thread mutex locked\n", ct->thr_number);
    pthread_mutex_lock(&ct->mtx_parent);
    printf("T%d: parent mutex locked\n", ct->thr_number);
    ct->var_parent = 1;
    pthread_cond_signal(&ct->cvr_parent);
    printf("T%d: parent condition signalled\n", ct->thr_number);
    pthread_mutex_unlock(&ct->mtx_parent);
    printf("T%d: parent mutex unlocked\n", ct->thr_number);
    pthread_cond_wait(&ct->cvr_thread, &ct->mtx_thread);
    printf("T%d: thread condition waited on\n", ct->thr_number);
    printf("X modified by thread %d\n", ct->thr_number);
    pthread_mutex_unlock(&ct->mtx_thread);
    printf("T%d: thread mutex unlocked\n", ct->thr_number);
    return NULL;
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

static void create_thread(pthread_t *pt, ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_create(pt, NULL, threadFunc, ct)) != 0)
        err_ptherr(rc, "failed to create thread %d: ", ct->thr_number);
}

static void signal_thread_condition(ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_cond_signal(&ct->cvr_thread)) != 0)
        err_ptherr(rc, "failed to signal thread condition %d: ", ct->thr_number);
}

static void join_thread(pthread_t *pt, ThreadControl *ct)
{
	int rc;
    if ((rc = pthread_join(*pt, NULL)) != 0)
        err_ptherr(rc, "failed to join thread %d: ", ct->thr_number);
}

int main(int argc, char **argv)
{
    assert(argc > 0);
    err_setarg0(argv[0]);
    pthread_t thread[2];

	lock_thread_mutex(&thr_ctl[0]);
	lock_thread_mutex(&thr_ctl[1]);
    printf("Thread mutexes locked\n");

	lock_parent_mutex(&thr_ctl[0]);
	lock_parent_mutex(&thr_ctl[1]);
    printf("Parent mutexes locked\n");

	create_thread(&thread[0], &thr_ctl[0]);
	create_thread(&thread[1], &thr_ctl[1]);
    printf("Threads created\n");

    /* Let the threads lock their mutexes */
	unlock_thread_mutex(&thr_ctl[0]);
	unlock_thread_mutex(&thr_ctl[1]);
    printf("Thread mutexes unlocked\n");

    wait_parent_condition(&thr_ctl[0]);
    wait_parent_condition(&thr_ctl[1]);
    printf("Parent conditions waited on\n");

	unlock_parent_mutex(&thr_ctl[0]);
	unlock_parent_mutex(&thr_ctl[1]);
    printf("Parent mutexes unlocked\n");

	lock_thread_mutex(&thr_ctl[0]);
	lock_thread_mutex(&thr_ctl[1]);
    printf("Thread mutexes locked again\n");

	signal_thread_condition(&thr_ctl[0]);
	signal_thread_condition(&thr_ctl[1]);
    printf("Thread conditions signalled\n");

	unlock_thread_mutex(&thr_ctl[0]);
	unlock_thread_mutex(&thr_ctl[1]);
    printf("Thread mutexes unlocked again\n");

    join_thread(&thread[0], &thr_ctl[0]);
    join_thread(&thread[1], &thr_ctl[1]);
    printf("Threads joined\n");

	destroy_thread_control(&thr_ctl[0]);
	destroy_thread_control(&thr_ctl[1]);

    return 0;
}
