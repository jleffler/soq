/* SO 37092445 */
/* Pragma needed on Mac OS X to suppress warnings about sem_init() and sem_destroy() */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

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
        sem_wait(pack->sem1);   // wait for predecessor
    printf("\n%s\n", pack->name);
    fflush(stdout);
    if (pack->sem2)
        sem_post(pack->sem2);   // unblock successor
    return NULL;
}

int main(void)
{
    srandom((unsigned int)time(NULL));

    pthread_t threadA, threadB, threadC, threadD;

    sem_t sem_A_B;
    sem_t sem_C_D;
    sem_t sem_B_C;

    sem_init(&sem_A_B, 0, 0);
    sem_init(&sem_C_D, 0, 0);
    sem_init(&sem_B_C, 0, 0);

    struct sem_package pack1 = { NULL,     &sem_A_B, "A" };
    struct sem_package pack2 = { &sem_A_B, &sem_B_C, "B" };
    struct sem_package pack3 = { &sem_B_C, &sem_C_D, "C" };
    struct sem_package pack4 = { &sem_C_D, NULL,     "D" };

    pthread_create(&threadA, NULL, thread_function, &pack1);
    pthread_create(&threadB, NULL, thread_function, &pack2);
    pthread_create(&threadC, NULL, thread_function, &pack3);
    pthread_create(&threadD, NULL, thread_function, &pack4);

    void *vp;
    pthread_join(threadD, &vp);

    sem_destroy(&sem_A_B);
    sem_destroy(&sem_B_C);
    sem_destroy(&sem_C_D);

    pthread_detach(threadA);
    pthread_detach(threadB);
    pthread_detach(threadC);

    printf("\nAll done\n\n");
    return 0;
}
