/* SO 4544-8840 Multithreaded C program - threads not terminating */
#include <math.h>
#include <pthread.h>
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

int main(void)
{
    pthread_t tids[MAX_THREADS];
    struct Data ctrl[MAX_THREADS];
    srand(time(0));

    for (int i = 0; i < MAX_THREADS; i++)
    {
        ctrl[i].name[0] = 'A' + i;
        ctrl[i].name[1] = '\0';
        ctrl[i].doze.tv_sec = 0;
        ctrl[i].doze.tv_nsec = 100000000 + 250000000 * random_fraction();
        ctrl[i].fraction = (MIN_PERCENT + (MAX_PERCENT - MIN_PERCENT) * random_fraction()) / 100;
        if (pthread_create(&tids[i], NULL, calculate, &ctrl[i]) != 0)
            exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_THREADS; i++)
        pthread_join(tids[i], NULL);

    printf("Total given out: %d\n", total);

    return 0;
}

static void *calculate(void *arg)
{
    struct Data *data = arg;
    printf("Thread %s: doze = 0.%03lds, fraction = %.3f\n",
           data->name, data->doze.tv_nsec / 1000000, data->fraction);
    pthread_mutex_lock(&mutex);
    while (scholarship > 0)
    {
        pthread_mutex_unlock(&mutex);
        nanosleep(&data->doze, NULL);
        pthread_mutex_lock(&mutex);
        double result = ceil(scholarship * data->fraction);
        total += result;
        scholarship -= result;
        pthread_mutex_unlock(&mutex);
        if (result >= 1)
            printf("%s = %.2f\n", data->name, result);
    }
    pthread_mutex_unlock(&mutex);
    printf("Thread %s exited\n", data->name);

    return 0;
}
