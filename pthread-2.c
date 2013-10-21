#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_CHAR 1024
#define BUFFER_SIZE 8

static void err_error(char *fmt, ...)
{
    int errnum = errno;
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (errnum != 0)
        fprintf(stderr, "errno = %d (%s)\n", errnum, strerror(errnum));
    pthread_exit(0);
}


typedef struct {
    pthread_mutex_t mutex;
    sem_t full;
    sem_t empty;
    size_t count;
    char* buffer;
} Context;

static void *Reader(void* arg) {
    Context* context = (Context*) arg;
    for (int i = 0; i < NUM_CHAR; ++i) {
        if (sem_wait(&context->full))
            err_error("Reader: sem_wait() failed\n");
        if (pthread_mutex_lock(&context->mutex))
            err_error("Reader: pthread_mutex_lock() failed\n");
        char c = context->buffer[i % BUFFER_SIZE];
        size_t s = context->count;
        if (pthread_mutex_unlock(&context->mutex))
            err_error("Reader: pthread_mutex_unlock() failed\n");
        if (sem_post(&context->empty))
            err_error("Reader: sem_post() failed\n");
        fprintf(stderr, "r: i = %d, s = %zd, c = %c = %c\n", i, s, c, 'a' + (i % 26));
        printf("%c", c);
    }
    printf("\n");
    return NULL;
}

static void *Writer(void* arg) {
    Context* context = (Context*) arg;
    struct timespec rq = { .tv_sec = 0, .tv_nsec = 200000000 };
    struct timespec rm;
    for (int i = 0; i < NUM_CHAR; ++i) {
        if (sem_wait(&context->empty))
            err_error("Writer: sem_wait() failed\n");
        if (pthread_mutex_lock(&context->mutex))
            err_error("Writer: pthread_mutex_lock() failed\n");
        //context->buffer[i % BUFFER_SIZE] = 'a' + (rand() % 26);
        context->buffer[i % BUFFER_SIZE] = 'a' + (i % 26);
        context->count++;
        float ranFloat = (float) rand() / RAND_MAX;
        if (ranFloat < 0.05)
            nanosleep(&rq, &rm);
        if (pthread_mutex_unlock(&context->mutex))
            err_error("Writer: pthread_mutex_unlock() failed\n");
        if (sem_post(&context->full))
            err_error("Writer: sem_post() failed\n");
    }
    return NULL;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    pthread_t reader, writer;
    Context context;
    srand(time(NULL));
    int status = 0;
    if ((status = pthread_mutex_init(&context.mutex, NULL)) != 0)
        err_error("pthread_mutex_init() failed (%d)\n", (errno = status));
    if ((status = sem_init(&context.full, 0, 0)) != 0)
        err_error("sem_init(&context.full) failed (%d)\n", status);
    if ((status = sem_init(&context.empty, 0, BUFFER_SIZE)) != 0)
        err_error("sem_init(&context.empty) failed (%d)\n", status);
    context.buffer = buffer;
    context.count = 0;

    status = pthread_create(&reader, NULL, Reader, &context);
    status = pthread_create(&writer, NULL, Writer, &context);

    pthread_join(reader, NULL);   // This line seems to be necessary
    pthread_join(writer, NULL);   // This line seems to be necessary

    pthread_exit(NULL);
    return 0;
}

