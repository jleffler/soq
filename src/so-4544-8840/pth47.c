/* SO 4544-8840 Multithreaded C program - threads not terminating */

#include "stderr.h"     // https://github.com/jleffler/soq/tree/master/src/libsoq
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int scholarship = 4000;
static int total = 0;
static void *calculate(void *data);

enum { MAX_THREADS = 5 };
enum { MIN_PERCENT = 10, MAX_PERCENT = 25 };

struct Data
{
    char name[2];
    struct timespec doze;
    double fraction;
};

static inline double random_fraction(void)
{
    return (double)rand() / RAND_MAX;
}

static inline _Noreturn void err_ptherror(int rc, const char *fmt, ...)
{
    errno = rc;
    va_list args;
    va_start(args, fmt);
    err_print(ERR_SYSERR, ERR_STAT, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[argc-argc]);
    pthread_t tids[MAX_THREADS];
    struct Data ctrl[MAX_THREADS];
    unsigned seed = time(0);
    printf("Seed: %u\n", seed);
    srand(seed);
    int rc;

    for (int i = 0; i < MAX_THREADS; i++)
    {
        ctrl[i].name[0] = 'A' + i;
        ctrl[i].name[1] = '\0';
        ctrl[i].doze.tv_sec = 0;
        ctrl[i].doze.tv_nsec = 100000000 + 250000000 * random_fraction();
        ctrl[i].fraction = (MIN_PERCENT + (MAX_PERCENT - MIN_PERCENT) * random_fraction()) / 100;
        if ((rc = pthread_create(&tids[i], NULL, calculate, &ctrl[i])) != 0)
            err_ptherror(rc, "Failed to create thread %d\n", i);
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        if ((rc = pthread_join(tids[i], NULL)) != 0)
            err_ptherror(rc, "Failed to join thread %d\n", i);
    }

    printf("Total given out: %d\n", total);

    return 0;
}

static void *calculate(void *arg)
{
    struct Data *data = arg;
    printf("Thread %s: doze = 0.%03lds, fraction = %.3f\n",
           data->name, data->doze.tv_nsec / 1000000, data->fraction);
    int rc;
    if ((rc = pthread_mutex_lock(&mutex)) != 0)
        err_ptherror(rc, "Failed to lock mutex (1) in %s()\n", __func__);
    while (scholarship > 0)
    {
        if ((rc = pthread_mutex_unlock(&mutex)) != 0)
            err_ptherror(rc, "Failed to unlock mutex (1) in %s()\n", __func__);
        nanosleep(&data->doze, NULL);
        if ((rc = pthread_mutex_lock(&mutex)) != 0)
            err_ptherror(rc, "Failed to lock mutex (2) in %s()\n", __func__);
        double result = ceil(scholarship * data->fraction);
        total += result;
        scholarship -= result;
        if (result >= 1)
            printf("%s = %.2f\n", data->name, result);
    }
    if ((rc = pthread_mutex_unlock(&mutex)) != 0)
        err_ptherror(rc, "Failed to unlock mutex (2) in %s()\n", __func__);
    printf("Thread %s exited\n", data->name);

    return 0;
}
