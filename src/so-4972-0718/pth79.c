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

typedef void *(*ThreadFunction)(void *);

static pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;
static int cnt = 0;
static int trace = 0;
static int max_count = 1000;

/* Code from question */
static void *t_function_0(void *data)
{
    int tid = (uintptr_t)data;
    int inc = 0;
    while (cnt < max_count)
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
    while (cnt < max_count)
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
    while (cnt < max_count)
    {
        pthread_mutex_lock(&mutx);
        if (cnt < max_count)
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
    while (get_count() < max_count)
    {
        pthread_mutex_lock(&mutx);
        if (cnt < max_count)
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
    while (copy_cnt < max_count)
    {
        pthread_mutex_lock(&mutx);
        if (cnt < max_count)
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

static void run_one_test(int num_threads, int variant, int width, ThreadFunction function)
{
    cnt = 0;
    printf("Variant %d: ", variant);
    fflush(stdout);

    pthread_t p_thread[num_threads];
    int thr_id[num_threads];

    clock_t start = clock();

    for (int i = 0; i < num_threads; i++)
    {
        thr_id[i] = pthread_create(&p_thread[i], NULL, function, (void *)(uintptr_t)i);
        if (thr_id[i] < 0)
        {
            errno = thr_id[i];
            err_syserr("failed to create thread %d\n", i);
        }
    }

    int inc[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
        void *vp;
        pthread_join(p_thread[i], &vp);
        inc[i] = (int)(uintptr_t)vp;
        if (trace) printf("Join %d: %d increments\n", i, inc[i]);
    }

    clock_t end = clock();

    printf("time : %.6lfs  ", (double)(end - start) / CLOCKS_PER_SEC);
    printf("result : %*d  ", width, cnt);
    const char *pad = " [ ";
    for (int i = 0; i < num_threads; i++)
    {
        printf("%s%*d", pad, width, inc[i]);
        pad = ", ";
    }
    printf(" ]\n");
}

static void run_test(int num_threads, int variant, int repeat, int width, ThreadFunction function)
{
    for (int i = 0; i < repeat; i++)
        run_one_test(num_threads, variant, width, function);
}

static ThreadFunction functions[] =
{
    t_function_0, t_function_1, t_function_2,
    t_function_3, t_function_4,
};
enum { NUM_VARIANTS = sizeof(functions) / sizeof(functions[0]) };

static const char optstr[] = "aht01234c:n:r:w:";
static const char usestr[] = "[-aht01234][-n threads][-c count][-w width][-r repeat]";
static const char hlpstr[] =
    "  -a         Run all variants\n"
    "  -c count   Maximum value for counter (default 1000)\n"
    "  -h         Print this help message and exit\n"
    "  -n threads Number of threads to use (default 4)\n"
    "  -r repeat  Run variant(s) repeatedly (default 1)\n"
    "  -t         Trace execution (very verbose)\n"
    "  -w width   Number of digits to print for counts (default 4)\n"
    "  -0         Run variant 0 (only) - code from question of SO 4972-0718\n"
    "  -1         Use variant 1 (only) - original code from answer by @snr\n"
    "  -2         Use variant 2 (only) - revised code from answer by @snr\n"
    "  -3         Use variant 3 (only) - code from commentary by JL\n"
    "  -4         Use variant 4 (only) - 'esoteric' code from commentary by JL\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    int variant = 0;
    int num_threads = 4;
    int width = 4;      /* 4 digits (1000, etc) */
    int all = 0;
    int repeat = 1;
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
        case 'a':
            all = 1;
            break;
        case 'c':
            max_count = atoi(optarg);
            break;
        case 'n':
            num_threads = atoi(optarg);
            break;
        case 'r':
            repeat = atoi(optarg);
            break;
        case 't':
            trace = 1;
            break;
        case 'w':
            width = atoi(optarg);
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (all)
    {
        for (variant = 0; variant < NUM_VARIANTS; variant++)
            run_test(num_threads, variant, repeat, width, functions[variant]);
    }
    else
        run_test(num_threads, variant, repeat, width, functions[variant]);

    return 0;
}
