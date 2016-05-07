/* SO 37092445 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

static void* thread_A (void *arg);
static void* thread_B (void *arg);
static void* thread_C (void *arg);
static void* thread_D (void *arg);

typedef struct sem_package {
    sem_t* sem1;
    sem_t* sem2;
} sem_package;

static
void* thread_A (void *arg) {
    sem_t* sem = (sem_t*) arg;

    int random_sleep = (int) (500 + ((random()) / RAND_MAX) * 2000);
    struct timespec sleep_time;
    sleep_time.tv_sec = random_sleep / 1000;
    sleep_time.tv_nsec = (random_sleep % 1000) * 1000000;

    nanosleep(&sleep_time, NULL);

    sem_post(sem);  //unblock B
    printf("\nA\n");
    return NULL;
}

static
void* thread_B (void *arg) {
    sem_package* pack = (sem_package*) arg;

    int random_sleep = (int) (500 + ((random()) / RAND_MAX) * 2000);
    struct timespec sleep_time;
    sleep_time.tv_sec = random_sleep / 1000;
    sleep_time.tv_nsec = (random_sleep % 1000) * 1000000;

    nanosleep(&sleep_time, NULL);

    sem_wait(pack->sem1);   //wait for A
    sem_post(pack->sem2);   //unblock C
    printf("\nB\n");
    return NULL;    
}

static
void* thread_C (void *arg) {
    sem_package* pack = (sem_package*) arg;

    int random_sleep = (int) (500 + ((random()) / RAND_MAX) * 2000);
    struct timespec sleep_time;
    sleep_time.tv_sec = random_sleep / 1000;
    sleep_time.tv_nsec = (random_sleep % 1000) * 1000000;

    nanosleep(&sleep_time, NULL);

    sem_wait(pack->sem2);   //wait for B
    sem_post(pack->sem1);   //unblock D
    printf("\nC\n");
    return NULL;
}

static
void* thread_D (void *arg) {
    sem_t* sem = (sem_t*) arg;

    int random_sleep = (int) (500 + ((random()) / RAND_MAX) * 2000);
    struct timespec sleep_time;
    sleep_time.tv_sec = random_sleep / 1000;
    sleep_time.tv_nsec = (random_sleep % 1000) * 1000000;

    nanosleep(&sleep_time, NULL);

    sem_wait(sem);  //wait for C
    printf("\nD\n");

    return NULL;
}

int main(void) {
    srandom((unsigned int) time(NULL)); 

    pthread_t threadA, threadB, threadC, threadD;

    sem_t sem_A_B;
    sem_t sem_C_D;
    sem_t sem_B_C;

    sem_init(&sem_A_B,0,0);
    sem_init(&sem_C_D,0,0);
    sem_init(&sem_B_C,0,0);

    struct sem_package pack1;
    pack1.sem1=&sem_A_B;
    pack1.sem2=&sem_B_C;

    struct sem_package pack2;
    pack2.sem1=&sem_C_D;
    pack2.sem2=&sem_B_C;

    pthread_create(&threadA,NULL,thread_A,&sem_A_B);
    pthread_create(&threadB,NULL,thread_B,&pack1);
    pthread_create(&threadC,NULL,thread_C,&pack2);
    pthread_create(&threadD,NULL,thread_D,&sem_C_D);

    long m;
    pthread_join(threadD, (void **) &m);

    sem_destroy(&sem_A_B);
    sem_destroy(&sem_B_C);
    sem_destroy(&sem_C_D);

    pthread_detach(threadA);
    pthread_detach(threadB);
    pthread_detach(threadC);

    return 0;
}
