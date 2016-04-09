#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int *array;
    int arraySize;
    int level_of_split;
} parameters;


pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *pth_mergesort(void *);

static void print_parameters(const char *tag, parameters *p)
{
    pthread_mutex_lock(&mtx);
    printf("%s: (size %d, level %d)", tag, p->arraySize, p->level_of_split);
    for (int i = 0; i < p->arraySize; i++)
        printf(" %d", p->array[i]);
    putchar('\n');
    fflush(stdout);
    pthread_mutex_unlock(&mtx);
}

int main(void)
{
    // Get the number of integers to sort
    printf("%s", "How many numbers to sort? ");
    int size;
    scanf("%d", &size);
    srand(time(NULL));

    int *numbers = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        numbers[i] = rand() % 1000;

    printf("%s", "\nLevel of split: ");
    int split_level;
    scanf("%d", &split_level);

    if (split_level > 0)
    {
        // Create first set of arguments
        parameters *param_1 = malloc(sizeof(parameters *));
        param_1->arraySize = size / 2;
        param_1->level_of_split = split_level - 1;
        param_1->array = malloc(param_1->arraySize * sizeof(int));
        int k = 0;
        for (int i = 0; i < param_1->arraySize; i++, k++)
        {
            param_1->array[i] = numbers[i];
        }
        print_parameters("main-1", param_1);

        // Create second set of arguments
        parameters *param_2 = malloc(sizeof(parameters *));
        param_2->arraySize = size - param_1->arraySize;
        param_2->level_of_split = split_level - 1;
        param_2->array = malloc(param_2->arraySize * sizeof(int));
        for (int j = 0; j < param_2->arraySize; j++, k++)
        {
            param_2->array[j] = numbers[k];
        }
        print_parameters("main-2", param_2);

        // Create first merging thread
        pthread_t sorting_thread_1;
        pthread_create(&sorting_thread_1, NULL, pth_mergesort, param_1);

        // Create second merging thread
        pthread_t sorting_thread_2;
        pthread_create(&sorting_thread_2, NULL, pth_mergesort, param_2);

        pthread_join(sorting_thread_1, NULL);
        pthread_join(sorting_thread_2, NULL);

        print_parameters("post-1", param_1);
        print_parameters("post-2", param_2);
    }
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
    if (param->level_of_split > 0 && param->arraySize > 1)
    {
        int k = 0;
        parameters *leftSide = malloc(sizeof(parameters *));
        parameters *rightSide = malloc(sizeof(parameters *));
        leftSide->arraySize = param->arraySize / 2;
        rightSide->arraySize = param->arraySize - leftSide->arraySize;
        leftSide->array = malloc(leftSide->arraySize * sizeof(int));
        rightSide->array = malloc(rightSide->arraySize * sizeof(int));
        for (int i = 0; i < leftSide->arraySize; i++, k++)
        {
            leftSide->array[i] = param->array[i];
        }

        for (int j = 0; j < rightSide->arraySize; j++, k++)
        {
            rightSide->array[j] = param->array[k];
        }
        leftSide->level_of_split = param->level_of_split - 1;
        rightSide->level_of_split = param->level_of_split - 1;

        pthread_t sorting_thread_1;
        pthread_create(&sorting_thread_1, NULL, pth_mergesort, leftSide);

        pthread_t sorting_thread_2;
        pthread_create(&sorting_thread_2, NULL, pth_mergesort, rightSide);

        pthread_join(sorting_thread_1, NULL);
        pthread_join(sorting_thread_2, NULL);
    }
    else if (param->arraySize > 1)
    {
        qsort(param->array, param->arraySize, sizeof(int), compareFunction);
    }
    return 0;
}
