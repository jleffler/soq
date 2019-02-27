/* SO 1960-7450 -- heavily extended compared with original answer */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int Data;

static int trace = 0;

void quicksort_last(Data *A, size_t p, size_t r);
void quicksort_random(Data *A, size_t p, size_t r);
void selectionsort(Data *A, size_t p, size_t r);

static size_t partition_last(Data *A, size_t p, size_t r);
static size_t partition_random(Data *A, size_t p, size_t r);

static inline void swap(Data *array, size_t i, size_t j)
{
    Data t = array[i];
    array[i] = array[j];
    array[j] = t;
}

static void dump_partition(char const *tag, Data const *A, size_t p, size_t r)
{
    size_t i;
    printf("%s [%zu..%zu]:\n", tag, p, r);
    for (i = p; i <= r; i++)
    {
        printf(" %3d", A[i]);
        if ((i - p) % 10 == 9)
            putchar('\n');
    }
    if ((i - p) % 10 != 0)
        putchar('\n');
}

static void chk_sort(Data *A, size_t p, size_t r)
{
    for (size_t i = p; i < r; i++)
    {
        if (A[i] > A[i + 1])
        {
            printf("Out of order: A[%zu] = %d, A[%zu] = %d\n",
                   i, A[i], i + 1, A[i + 1]);
        }
    }
}

static void load_random(Data *A, size_t p, size_t r)
{
    size_t range = (r - p + 1);
    for (size_t i = p; i <= r; i++)
        A[i] = rand() % range;
}

static void load_ascending(Data *A, size_t p, size_t r)
{
    for (size_t i = p; i <= r; i++)
        A[i] = i;
}

static void load_descending(Data *A, size_t p, size_t r)
{
    size_t range = (r - p + 1);
    for (size_t i = p; i <= r; i++)
        A[i] = range - i;
}

static void load_uniform(Data *A, size_t p, size_t r)
{
    for (size_t i = p; i <= r; i++)
        A[i] = r;
}

static void load_organpipe(Data *A, size_t p, size_t r)
{
    size_t range = r - p + 1;
    for (size_t i = p; i <= r / 2; i++)
        A[i] = i;
    for (size_t i = r / 2 + 1; i <= r; i++)
        A[i] = range - i;
}

static void load_invorganpipe(Data *A, size_t p, size_t r)
{
    size_t range = (r - p + 1) / 2;
    for (size_t i = p; i <= r / 2; i++)
        A[i] = range - i;
    for (size_t i = r / 2 + 1; i <= r; i++)
        A[i] = i - range;
}

typedef void (*Load)(Data *A, size_t p, size_t r);
typedef void (*Sort)(Data *A, size_t p, size_t r);
typedef size_t (*Part)(Data *A, size_t p, size_t r);

static void test_one_sort(Data *A, size_t p, size_t r, Sort sort, char const *s_tag,
                          char const *l_tag, char const *z_tag)
{
    if (trace)
        dump_partition("Before", A, p, r);
    clock_t start = clock();
    (*sort)(A, p, r);
    clock_t finish = clock();
    double sec = (finish - start) / (double)CLOCKS_PER_SEC;
    printf("%s-%s-%s: %13.6f\n", z_tag, l_tag, s_tag, sec);
    chk_sort(A, p, r);
    if (trace)
        dump_partition("After", A, p, r);
}

static Data *dup_array(Data *A, size_t p, size_t r)
{
    size_t nbytes = sizeof(*A) * (r - p + 1);
    Data *B = malloc(nbytes);
    if (B != 0)
        memmove(B, A, nbytes);
    return B;
}

static void test_set_sorts(Data *A, size_t p, size_t r, char const *l_tag, char const *z_tag)
{
    struct sorter
    {
        Sort        function;
        char const *tag;
    } sort[] =
    {
        { quicksort_last, "QS.L" },
        { quicksort_random, "QS.R" },
        { selectionsort, "SS.N" },
    };
    enum { NUM_SORTS = sizeof(sort) / sizeof(sort[0]) };
    for (size_t i = 0; i < NUM_SORTS; i++)
    {
        Data *B = dup_array(A, p, r);
        test_one_sort(B, p, r, sort[i].function, sort[i].tag, l_tag, z_tag);
        free(B);
    }
}

static void test_set_loads(size_t size, char const *z_tag)
{
    struct loader
    {
        Load        function;
        char const *tag;
    } load[] =
    {
        { load_random, "R" },
        { load_ascending, "A" },
        { load_descending, "D" },
        { load_organpipe, "O" },
        { load_invorganpipe, "I" },
        { load_uniform, "U" },
    };
    enum { NUM_LOADS = sizeof(load) / sizeof(load[0]) };
    Data *A = malloc(size * sizeof(*A));
    for (size_t i = 0; i < NUM_LOADS; i++)
    {
        load[i].function(A, 0, size - 1);
        test_set_sorts(A, 0, size - 1, load[i].tag, z_tag);
    }
    free(A);
}

int main(void)
{
    srand(time(NULL));

    for (size_t i = 10; i <= 40; i += 10)
    {
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%zuK", i);
        test_set_loads(1000 * i, buffer);
    }
    return 0;
}

static void quicksort_partition(Data *A, size_t p, size_t r, Part partition)
{
    if (p < r)
    {
        size_t q = (*partition)(A, p, r);
        if (p + 1 < q)
            quicksort_partition(A, p, q - 1, partition);
        quicksort_partition(A, q + 1, r, partition);
    }
}

void quicksort_last(Data *A, size_t p, size_t r)
{
    quicksort_partition(A, p, r, partition_last);
}

void quicksort_random(Data *A, size_t p, size_t r)
{
    quicksort_partition(A, p, r, partition_random);
}

static size_t random_int(size_t p, size_t r)
{
    return(rand() % (r - p + 1) + p);
}

static size_t partition_random(Data *A, size_t p, size_t r)
{
    size_t pivot = random_int(p, r);
    swap(A, pivot, r);
    const Data x = A[r];
    size_t i = p;
    size_t j = p;

    while (j <= r)
    {
        if (A[j] <= x)
            swap(A, i++, j);
        j++;
    }
    assert(i > 0);
    return i - 1;
}

static size_t partition_last(Data *A, size_t p, size_t r)
{
    const Data x = A[r];
    size_t i = p;
    size_t j = p;

    while (j <= r)
    {
        if (A[j] <= x)
            swap(A, i++, j);
        j++;
    }
    assert(i > 0);
    return i - 1;
}

void selectionsort(Data *A, size_t p, size_t r)
{
    for ( ; p < r; p++)
    {
        for (size_t i = p; i <= r; i++)
        {
            if (A[p] > A[i])
                swap(A, p, i);
        }
    }
}

