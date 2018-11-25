/* SO 4972-0718 */
#include "posixver.h"
#include "stderr.h"
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TNUM 4

static pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;
static int cnt = 0;
static int trace = 0;

/* Code from question */
static void *t_function_0(void *data)
{
    int tid = (uintptr_t)data;
    int inc = 0;
    while (cnt < 1000)
    {
        pthread_mutex_lock(&mutx);
        cnt++;
        pthread_mutex_unlock(&mutx);
        inc++;
        if (trace) printf("%d\n", tid);
    }
    if (trace) printf("%d done (%d increments)\n", tid, inc);
    return (void *)(uintptr_t)inc;
}

/* Original code from answer by @snr */
static void *t_function_1(void *data)
{
    int tid = (uintptr_t)data;
    int inc = 0;
    pthread_mutex_lock(&mutx);
    while (cnt < 1000)
    {
        cnt++;
        if (trace) printf("%d\n", tid);
        inc++;
    }
    pthread_mutex_unlock(&mutx);
    if (trace) printf("%d done (%d increments)\n", tid, inc);
    return (void *)(uintptr_t)inc;
}

/* Revised code from answer by @snr */
static void *t_function_2(void *data)
{
    int tid = (uintptr_t)data;
    int inc = 0;
    while (cnt < 1000)
    {
        pthread_mutex_lock(&mutx);
        if (cnt < 1000)
        {
            cnt++;
            inc++;
        }
        pthread_mutex_unlock(&mutx);
        if (trace) printf("%d\n", tid);
    }
    if (trace) printf("%d done (%d increments)\n", tid, inc);
    return (void *)(uintptr_t)inc;
}

/* Support function for commentary answer by JL */
static int get_count(void)
{
    pthread_mutex_lock(&mutx);
    int cnt_val = cnt;
    pthread_mutex_unlock(&mutx);
    return cnt_val;
}

/* Code from commentary answer by JL - only reading cnt when mutex is locked */
static void *t_function_3(void *data)
{
    int tid = (uintptr_t)data;
    int inc = 0;
    while (get_count() < 1000)
    {
        pthread_mutex_lock(&mutx);
        if (cnt < 1000)
        {
            cnt++;
            inc++;
        }
        pthread_mutex_unlock(&mutx);
        if (trace) printf("%d\n", tid);
    }
    if (trace) printf("%d done (%d increments)\n", tid, inc);
    return (void *)(uintptr_t)inc;
}

/* 'Esoteric' code from commentary answer by JL - only reading cnt when mutex is locked */
static void *t_function_4(void *data)
{
    int tid = (uintptr_t)data;
    int inc = 0;
    int copy_cnt = 0;
    while (copy_cnt < 1000)
    {
        pthread_mutex_lock(&mutx);
        if (cnt < 1000)
        {
            cnt++;
            inc++;
        }
        copy_cnt = cnt;
        pthread_mutex_unlock(&mutx);
        if (trace) printf("%d\n", tid);
    }
    if (trace) printf("%d done (%d increments)\n", tid, inc);
    return (void *)(uintptr_t)inc;
}

static const char optstr[] = "t01234";
static const char usestr[] = "[-t01234]";

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    static void *(*functions[])(void *) =
    {
        t_function_0, t_function_1, t_function_2,
        t_function_3, t_function_4,
    };
    int variant = 0;
    int opt;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
            variant = opt - '0';
            break;
        case 't':
            trace = 1;
            break;
        default:
            err_usage(usestr);
        }
    }

    printf("Variant %d: ", variant);
    fflush(stdout);

    pthread_t p_thread[TNUM];
    int thr_id[TNUM];

    clock_t start = clock();

    for (int i = 0; i < TNUM; i++)
    {
        thr_id[i] = pthread_create(&p_thread[i], NULL, functions[variant], (void *)(uintptr_t)i);
        if (thr_id[i] < 0)
        {
            errno = thr_id[i];
            err_syserr("failed to create thread %d\n", i);
        }
    }

    int inc[TNUM];
    for (int i = 0; i < TNUM; i++)
    {
        void *vp;
        pthread_join(p_thread[i], &vp);
        inc[i] = (int)(uintptr_t)vp;
        if (trace) printf("Join %d: %d increments\n", i, inc[i]);
    }

    clock_t end = clock();

    printf("time : %.6lfs  ", (double)(end - start) / CLOCKS_PER_SEC);
    printf("result : %d  ", cnt);
    const char *pad = " [ ";
    for (int i = 0; i < TNUM; i++)
    {
        printf("%s%d", pad, inc[i]);
        pad = ", ";
    }
    printf(" ]\n");
    return 0;
}
