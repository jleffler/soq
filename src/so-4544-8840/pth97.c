/* SO 4544-8840 Multithreaded C program - threads not terminating */
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define FRACTION 0.25

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int scholarship = 4000;
static int total = 0;
static void *calculate(void *data);

struct Data
{
    const char *name;
    int doze;
};

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    struct Data a = { "A", 2 };
    struct Data b = { "B", 1 };
    struct Data c = { "C", 1 };

    pthread_create(&tid1, NULL, calculate, &a);
    pthread_create(&tid2, NULL, calculate, &b);
    pthread_create(&tid3, NULL, calculate, &c);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("Total given out: %d\n", total);

    return 0;
}

static void *calculate(void *arg)
{
    struct Data *data = arg;
    float result;
    while (scholarship > 0)
    {
        sleep(data->doze);
        pthread_mutex_lock(&mutex);
        result = ceil(scholarship * FRACTION);
        total += result;
        scholarship -= result;
        if (result >= 1)
            printf("%s = %.2f\n", data->name, result);
        pthread_mutex_unlock(&mutex);
    }
    printf("Thread %s exited\n", data->name);

    return 0;
}
