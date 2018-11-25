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

static const char optstr[] = "ht01234n:c:w:";
static const char usestr[] = "[-ht01234][-n threads][-c count][-w width]";
static const char hlpstr[] =
    "  -c count   Maximum value for counter (default 1000)\n"
    "  -h         Print this help message and exit\n"
    "  -n threads Number of threads to use (default 4)\n"
    "  -t         Trace execution (very verbose)\n"
    "  -w width   Number of digits to print for counts (default 4)\n"
    "  -0         Use t_function_0 - code from question of SO 4972-0718\n"
    "  -1         Use t_function_1 - original code from answer by @snr\n"
    "  -2         Use t_function_2 - revised code from answer by @snr\n"
    "  -3         Use t_function_3 - code from commentary by JL\n"
    "  -4         Use t_function_4 - 'esoteric' code from commentary by JL\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    static void *(*functions[])(void *) =
    {
        t_function_0, t_function_1, t_function_2,
        t_function_3, t_function_4,
    };
    int variant = 0;
    int num_threads = 4;
    int width = 4;      /* 4 digits (1000, etc) */
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
        case 'n':
            num_threads = atoi(optarg);
            break;
        case 'c':
            max_count = atoi(optarg);
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

    /*
    ** The code from here down could/should be factored into a test
    ** function.  The main program could then run tests repeatedly
    ** rather than needing the test script run.pth73.sh
    */

    printf("Variant %d: ", variant);
    fflush(stdout);

    pthread_t p_thread[num_threads];
    int thr_id[num_threads];

    clock_t start = clock();

    for (int i = 0; i < num_threads; i++)
    {
        thr_id[i] = pthread_create(&p_thread[i], NULL, functions[variant], (void *)(uintptr_t)i);
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
    return 0;
}
