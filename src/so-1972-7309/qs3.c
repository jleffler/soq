/* SO 1972-7309 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Data;

static inline void swap(Data *array, size_t i, size_t j)
{
    Data t = array[i];
    array[i] = array[j];
    array[j] = t;
}

static void dump_partition(char const *tag, Data *array, size_t lo, size_t hi)
{
    if (lo < hi)
    {
        size_t i;
        printf("%s: %zu..%zu\n", tag, lo, hi);
        for (i = lo; i <= hi; i++)
        {
            printf(" %4d", array[i]);
            if ((i - lo) % 10 == 9)
                putchar('\n');
        }
        if ((i - lo) % 10 != 0)
            putchar('\n');
    }
}

static size_t partition(Data *A, size_t p, size_t r)
{
    const Data x = A[r];
    size_t i = p;
    size_t j = p;

    while (j < r)
    {
        if (A[j] <= x)
            swap(A, i++, j);
        j++;
    }
    swap(A, i, r);
    return i;
}

static void quicksort_last(Data *A, size_t p, size_t r)
{
    if (p < r)
    {
        size_t q = partition(A, p, r);
        printf("quicksort: %zu (%zu..%zu=%zu)\n", q, p, r, r - p + 1);
        //if (p + 1 < q)
        //    dump_partition("L-part", A, p, q - 1);
        //dump_partition("R-part", A, q + 1, r);
        quicksort_last(A, p, q - 1);
        quicksort_last(A, q + 1, r);
    }
}

int main(void)
{
    Data data[] =
    {
        31, 14, 53, 45, 88,  0, 79, 59, 84,  5,
        83, 42, 61, 38, 24, 47, 86, 69,  8, 36,
    };
    enum { N_DATA = sizeof(data) / sizeof(data[0]) };

    dump_partition("Random", data, 0, N_DATA - 1);
    quicksort_last(data, 0, N_DATA-1);
    dump_partition("Sorted", data, 0, N_DATA - 1);

    enum { BIG_SIZE = 10000 };
    Data data2[BIG_SIZE];
    srand(time(0));

    for (int i = 0; i < BIG_SIZE; i++)
        data2[i] = rand() % BIG_SIZE;

    dump_partition("Random", data2, 0, BIG_SIZE - 1);
    quicksort_last(data2, 0, BIG_SIZE - 1);
    dump_partition("Sorted", data2, 0, BIG_SIZE - 1);

    for (int i = 0; i < BIG_SIZE; i++)
        data2[i] = i;

    dump_partition("Random", data2, 0, BIG_SIZE - 1);
    quicksort_last(data2, 0, BIG_SIZE - 1);
    dump_partition("Sorted", data2, 0, BIG_SIZE - 1);

    return 0;
}
