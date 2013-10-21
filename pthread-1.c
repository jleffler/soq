#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_CHAR 1024
#define BUFFER_SIZE 8


typedef struct {
    pthread_mutex_t mutex;
    sem_t full;
    sem_t empty;
    char* buffer;
} Context;

static void *Reader(void* arg) {
    Context* context = (Context*) arg;
    for (int i = 0; i < NUM_CHAR; ++i) {
        sem_wait(&context->full);
        pthread_mutex_lock(&(context->mutex));
        char c = context->buffer[i % BUFFER_SIZE];
        pthread_mutex_unlock(&(context->mutex));
        sem_post(&context->empty);
        printf("%c", c);
    }
    printf("\n");
    fflush(0);
    return NULL;
}

static void *Writer(void* arg) {
    Context* context = (Context*) arg;
    struct timespec rq = { .tv_sec = 0, .tv_nsec = 200000000 };
    struct timespec rm;
    for (int i = 0; i < NUM_CHAR; ++i) {
        sem_wait(&context->empty);
        pthread_mutex_lock(&(context->mutex));
        context->buffer[i % BUFFER_SIZE] = 'a' + (rand() % 26);
        float ranFloat = (float) rand() / RAND_MAX;
        if (ranFloat < 0.05)
            nanosleep(&rq, &rm);
        pthread_mutex_unlock(&(context->mutex));
        sem_post(&context->full);
    }
    return NULL;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    pthread_t reader, writer;
    Context context;
    srand(time(NULL));
    (void) pthread_mutex_init(&context.mutex, NULL);
    (void) sem_init(&context.full,0,0);
    (void) sem_init(&context.empty,0, BUFFER_SIZE);
    context.buffer = buffer;

    (void) pthread_create(&reader, NULL, Reader, &context);
    (void) pthread_create(&writer, NULL, Writer, &context);

    pthread_join(reader,NULL);   // This line seems to be necessary
    pthread_join(writer,NULL);   // This line seems to be necessary

    pthread_exit(NULL);
    return 0;
}

