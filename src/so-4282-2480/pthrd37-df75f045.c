/* SO 4282-2480 */

/*
** Objective: N threads cooperate on M cycles or iterations of a task.
** A new random number is needed for each cycle, but all threads must
** use the same random number on each cycle.
** Any thread may evaluate the new random number.
*/

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stderr.h"

enum { MAX_THREADS = 3 };
enum { MAX_CYCLES  = 5 };

static pthread_mutex_t mtx_waiting = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cnd_waiting = PTHREAD_COND_INITIALIZER;
static int             num_waiting = 0;
static int             cycle   = -1;

static float gl_rand = 0;
static long  gl_long = 0;

static float next_iteration_random_number(int tid, int iteration)
{
    pthread_mutex_lock(&mtx_waiting);
    assert(cycle == iteration || cycle == iteration - 1);
    num_waiting++;
    printf("-->> TID %d, I = %d (C = %d, W = %d)\n",
           tid, iteration, cycle, num_waiting);
    while (cycle != iteration && num_waiting != MAX_THREADS)
    {
        assert(num_waiting > 0 && num_waiting <= MAX_THREADS);
        printf("-CW- TID %d, I = %d (C = %d, W = %d)\n",
               tid, iteration, cycle, num_waiting);
        pthread_cond_wait(&cnd_waiting, &mtx_waiting);
    }
    assert(cycle == iteration || num_waiting == MAX_THREADS);
    printf("---- TID %d, I = %d (C = %d, W = %d)\n",
           tid, iteration, cycle, num_waiting);

    if (cycle != iteration)
    {
        gl_long = lrand48();
        gl_rand = (float)gl_long;
        num_waiting = 0;
        cycle = iteration;
        printf("---- TID %d generates cycle %d: L = %ld, F = %g\n",
               tid, cycle, gl_long, gl_rand);
        pthread_cond_broadcast(&cnd_waiting);
    }

    printf("<<-- TID %d, I = %d (C = %d, W = %d) L = %ld, F = %g\n",
           tid, iteration, cycle, num_waiting, gl_long, gl_rand);
    pthread_mutex_unlock(&mtx_waiting);
    return gl_rand;
}

static void *thread_function(void *vp)
{
    int tid = (int)(uintptr_t)vp;     // Thuggish!

    for (int i = 0; i < MAX_CYCLES; i++)
    {
        float f = next_iteration_random_number(tid, i);
        printf("TID %d at work: I = %d, F = %g\n", tid, i, f);
        fflush(stdout);
        struct timespec rq;
        rq.tv_sec = 0;
        rq.tv_nsec = (((gl_long & 0xFF) + (0xF * i))) % 200 * 50000000;
        assert(rq.tv_nsec >= 0 && rq.tv_nsec < 10000000000);
        nanosleep(&rq, 0);
    }

    return 0;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    assert(argc == 1);

    pthread_t thread[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++)
    {
        int rc = pthread_create(&thread[i], 0, thread_function, (void *)(uintptr_t)i);
        if (rc != 0)
        {
            errno = rc;
            err_syserr("failed to create thread %d", i);
        }
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        void *vp;
        int rc = pthread_join(thread[i], &vp);
        if (rc != 0)
        {
            errno = rc;
            err_syserr("Failed to join TID %d", i);
        }
        printf("TID %d returned %p\n", i, vp);
    }

    return 0;
}
