/* SO 37092445 */
#include "posixver.h"
/* Pragma needed on Mac OS X to suppress warnings about sem_init() and sem_destroy() */
/* NB: Mac OS X does not implement them - returning errno 78 Function not implemented */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "stderr.h"
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

static void *thread_function(void *arg);

typedef struct sem_package
{
    sem_t *sem1;
    sem_t *sem2;
    char  *name;
} sem_package;

static
void *thread_function(void *arg)
{
    sem_package *pack = (sem_package *)arg;

    int random_sleep = (int)(500 + ((random()) / RAND_MAX) * 2000);
    struct timespec sleep_time = { .tv_sec  = random_sleep / 1000,
                                   .tv_nsec = (random_sleep % 1000) * 1000000
                                 };

    nanosleep(&sleep_time, NULL);

    if (pack->sem1)
    {
        if (sem_wait(pack->sem1) != 0)   // wait for predecessor
            err_syserr("sem_wait(): thread %s\n", pack->name);
    }
    printf("\n%s\n", pack->name);
    //fflush(stdout);
    if (pack->sem2)
    {
        if (sem_post(pack->sem2) != 0)   // unblock successor
            err_syserr("sem_post(): thread %s\n", pack->name);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[argc-argc]);
    srandom((unsigned int)time(NULL));

    pthread_t threadA, threadB, threadC, threadD;

    sem_t sem_A_B;
    sem_t sem_C_D;
    sem_t sem_B_C;

    if (sem_init(&sem_A_B, 0, 0) != 0 ||
        sem_init(&sem_C_D, 0, 0) != 0 ||
        sem_init(&sem_B_C, 0, 0))
        err_syserr("sem_init()");

    struct sem_package pack1 = { NULL,     &sem_A_B, "A" };
    struct sem_package pack2 = { &sem_A_B, &sem_B_C, "B" };
    struct sem_package pack3 = { &sem_B_C, &sem_C_D, "C" };
    struct sem_package pack4 = { &sem_C_D, NULL,     "D" };

    int ptherr;
    if ((ptherr = pthread_create(&threadA, NULL, thread_function, &pack1)) != 0 ||
        (ptherr = pthread_create(&threadB, NULL, thread_function, &pack2)) != 0 ||
        (ptherr = pthread_create(&threadC, NULL, thread_function, &pack3)) != 0 ||
        (ptherr = pthread_create(&threadD, NULL, thread_function, &pack4)) != 0)
    {
        errno = ptherr;
        err_syserr("pthread_create()");
    }

    void *vp;
    if ((ptherr = pthread_join(threadD, &vp)) != 0)
    {
        errno = ptherr;
        err_sysrem("pthread_join()");
    }

    if (sem_destroy(&sem_A_B) != 0 ||
        sem_destroy(&sem_B_C) != 0 ||
        sem_destroy(&sem_C_D))
        err_syserr("sem_destroy()");

    if ((ptherr = pthread_detach(threadA)) != 0)
    {
        errno = ptherr;
        err_sysrem("pthread_detach() thread %s\n", "A");
    }

    if ((ptherr = pthread_detach(threadB)) != 0)
    {
        errno = ptherr;
        err_sysrem("pthread_detach() thread %s\n", "B");
    }

    if ((ptherr = pthread_detach(threadC)) != 0)
    {
        errno = ptherr;
        err_sysrem("pthread_detach() thread %s\n", "C");
    }

    printf("\nAll done\n\n");
    return 0;
}
