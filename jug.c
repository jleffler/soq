#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *array;
    int size;
    int level;
} parameters;

typedef struct
{
    int *lhs_data;
    int *rhs_data;
    int *dst_data;
    int lhs_size;
    int rhs_size;
    int dst_size;
} arrayArgs;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *pth_mergesort(void *);
void *pth_merge(void *arguments);

static void print_parameters(const char *tag, parameters *p)
{
    pthread_mutex_lock(&mtx);
    printf("%s: (size %d, level %d)", tag, p->size, p->level);
    for (int i = 0; i < p->size; i++)
        printf(" %d", p->array[i]);
    putchar('\n');
    fflush(stdout);
    pthread_mutex_unlock(&mtx);
}

int main(void)
{
    int size = 20;
    srand(time(NULL));

    int *numbers = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        numbers[i] = rand() % 1000;

    int split_level = 3;
    parameters p = { numbers, size, split_level };

    print_parameters("main", &p);
    pth_mergesort(&p);
    print_parameters("post", &p);

    free(numbers);

    return 0;
}

/* For values in the range 0..1000, the body could be 'return i1 - i2' but this is extensible */
static int compareFunction(const void *vp1, const void *vp2)
{
    int v1 = *(int *)vp1;
    int v2 = *(int *)vp2;
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return +1;
    else
        return 0;
}

void *pth_mergesort(void *parameter)
{
    parameters *param = parameter;
    print_parameters("pth_mergesort", param);
    if (param->level > 0 && param->size > 1)
    {
        int k = 0;
        parameters lhs;
        parameters rhs;
        lhs.size = param->size / 2;
        rhs.size = param->size - lhs.size;
        lhs.array = malloc(lhs.size * sizeof(int));
        rhs.array = malloc(rhs.size * sizeof(int));
        for (int i = 0; i < lhs.size; i++, k++)
            lhs.array[i] = param->array[i];

        for (int j = 0; j < rhs.size; j++, k++)
            rhs.array[j] = param->array[k];
        lhs.level = param->level - 1;
        rhs.level = param->level - 1;

        pthread_t sorting_thread_1;
        pthread_create(&sorting_thread_1, NULL, pth_mergesort, &lhs);

        pthread_t sorting_thread_2;
        pthread_create(&sorting_thread_2, NULL, pth_mergesort, &rhs);

        pthread_join(sorting_thread_1, NULL);
        pthread_join(sorting_thread_2, NULL);
        print_parameters("post-split-1", &lhs);
        print_parameters("post-split-2", &rhs);

        //Create set of merging arguments
        arrayArgs mergeArray;
        mergeArray.lhs_data = lhs.array;
        mergeArray.lhs_size = lhs.size;
        mergeArray.rhs_data = rhs.array;
        mergeArray.rhs_size = rhs.size;
        mergeArray.dst_data = param->array;
        mergeArray.dst_size = param->size;

        //Create merging thread
        pthread_t merging_thread;
        pthread_create(&merging_thread, NULL, pth_merge, &mergeArray);
        pthread_join(merging_thread, NULL);
        print_parameters("post-merge", param);

        free(lhs.array);
        free(rhs.array);
    }
    else if (param->size > 1)
    {
        qsort(param->array, param->size, sizeof(int), compareFunction);
        print_parameters("post-qsort", param);
    }
    return 0;
}

void *pth_merge(void *arguments)
{
    arrayArgs *args = arguments;
    int i, j;
    int k = 0;

    assert(args->lhs_size + args->rhs_size == args->dst_size);
    for (i = 0, j = 0; i < args->lhs_size && j < args->rhs_size; k++)
    {
        if (args->lhs_data[i] <= args->rhs_data[j])
            args->dst_data[k] = args->lhs_data[i++];
        else
            args->dst_data[k] = args->rhs_data[j++];
    }
    while (j < args->rhs_size)
        args->dst_data[k++] = args->rhs_data[j++];
    while (i < args->lhs_size)
        args->dst_data[k++] = args->lhs_data[i++];
    assert(k == args->dst_size);
    return 0;
}
