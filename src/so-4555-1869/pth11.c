/* SO 4555-1869 */
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t globalMutex[2];
pthread_cond_t globalCondVar[2];

static void *threadFunc1(void *args)
{
   assert(args == NULL);
   pthread_mutex_lock(&globalMutex[0]);
   pthread_cond_wait(&globalCondVar[0], &globalMutex[0]);
   printf("X modified by threadFunc 1\n");
   pthread_mutex_unlock(&globalMutex[0]);
   return NULL;
}

static void *threadFunc2(void *args)
{
    assert(args == NULL);
    pthread_mutex_lock(&globalMutex[1]);
    pthread_cond_wait(&globalCondVar[1], &globalMutex[1]);
    printf("X Modified by threadFunc 2\n");
    pthread_mutex_unlock(&globalMutex[1]);
    return NULL;
}

int main(void)
{
    pthread_t thread[2];

    pthread_mutex_init(&globalMutex[0], NULL);
    pthread_mutex_init(&globalMutex[1], NULL);
    pthread_cond_init(&globalCondVar[0], NULL);
    pthread_cond_init(&globalCondVar[1], NULL);

    pthread_create(&thread[0], NULL, threadFunc1, NULL);
    pthread_create(&thread[1], NULL, threadFunc2, NULL);

    pthread_cond_signal(&globalCondVar[0]);
    pthread_cond_signal(&globalCondVar[1]);

    pthread_join(thread[1], NULL);
    pthread_join(thread[0], NULL);

    pthread_cond_destroy(&globalCondVar[0]);
    pthread_cond_destroy(&globalCondVar[1]);
    pthread_mutex_destroy(&globalMutex[0]);
    pthread_mutex_destroy(&globalMutex[1]);

    return 0;
}

