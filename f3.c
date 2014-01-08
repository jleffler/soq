#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static int debug = 0;

static void dump_partition(char const *tag, int a[], int start, int end)
{
    int i;
    int w = (end > 10) ? 2 : 1;
    printf("%s (%d..%d)%s", tag, start, end, (end > start + 10) ? "\n" : ":");
    for (i = start; i < end; i++)
    {
        printf(" [%*d] = %d", w, i, a[i]);
        if (i % 10 == 9)
            putchar('\n');
    }
    if (i % 10 != 0)
        putchar('\n');
}

static void check_partition(int a[], int start, int end, int rank)
{
    int ok = 1;
    assert(start >= 0 && start < end);
    assert(rank >= start && rank < end);
    for (int i = 0; i < rank; i++)
    {
        if (a[i] > a[rank])
        {
            ok = 0;
            printf("BUG: a[%d] = %d should be no larger than a[%d] = %d\n",
                   i, a[i], rank, a[rank]);
        }
    }
    for (int i = rank + 1; i < end; i++)
    {
        if (a[i] < a[rank])
        {
            ok = 0;
            printf("BUG: a[%d] = %d should be no smaller than a[%d] = %d\n",
                   i, a[i], rank, a[rank]);
        }
    }
    if (!ok)
        assert(0);
}

/*
** Find the value of the element in a[rank] in sorted order.
** The range to be scanned is [start..end).  The elements of
** a can be reordered
*/
static int order(int a[], int start, int end, int rank)
{
    int i, k, pivot;
    int value;

    if (debug)
    {
        printf("-->> %s: %d..%d (%d)\n", __func__, start, end, rank);
        dump_partition("into:", a, start, end);
    }

    if (start == end)
    {
        assert(start == rank - 1);
        value = a[start];
    }
    else
    {
        assert(start < end);
        assert(rank > start && rank - 1 <= end);

        k = start + 1;
        pivot = a[start];
        if (debug) printf("pivot = %d\n", pivot);
        for (i = start + 1; i < end; i++)
        {
            if (a[i] < pivot)
            {
                if (i != k)
                {
                    if (debug) printf("B[%d,%d]<=>(%d,%d) ", i, k, a[i], a[k]);
                    int temp = a[k];
                    a[k] = a[i];
                    a[i] = temp;
                    if (debug) printf("A[%d,%d]<=>(%d,%d)\n", i, k, a[i], a[k]);
                }
                k++;
            }
        }

        if (debug)
        {
            printf("i = %d, k = %d\n", i, k);
            dump_partition("loop:", a, start, end);
        }

        int temp = a[start];
        a[start] = a[--k];
        a[k] = temp;

        assert(k >= start && k < end);
        if (debug) dump_partition("swap:", a, start, end);

        if (rank - 1 == k)
            value = a[rank - 1];
        else if (rank - 1 < k)
            value = order(a, start, k, rank);
        else
            value = order(a, k + 1, end, rank);
    }

    if (debug)
    {
        printf("<<-- %s: %d..%d (rank = %d is value = %d)\n", __func__, start, end, rank, value);
        dump_partition("-->>:", a, start, end);
    }

    return value;
}

int main(int argc, char **argv)
{
    int a[] = { 27, 32, 23, 36, 24, 31, 25, 38, 29, 30 };
    enum { SIZE = sizeof(a) / sizeof(a[0]) };
    long seed = time(0);

    int opt;
    while ((opt = getopt(argc, argv, "ds:")) != -1)
    {
        switch (opt)
        {
        case 'd':
            debug = 1;
            break;
        case 's':
            seed = atol(optarg);
            break;
        default:
            /* Ignore */
            break;
        }
    }

    for (int rank = 0; rank < SIZE; rank++)
    {
        int b[SIZE];
        printf("Rank: %d\n", rank + 1);
        memmove(b, a, sizeof(b));
        dump_partition("Before:", b, 0, SIZE);
        int value = order(b, 0, SIZE, rank + 1);
        printf("rank %d is value %d (b[%d] = %d)\n", rank + 1, value, rank, b[rank]);
        dump_partition("After: ", b, 0, SIZE);
        check_partition(b, 0, SIZE, rank);
    }

    srand(seed);
    printf("Seed: %ld\n", seed);
    for (int i = 0; i < 10; i++)
    {
        enum { X_SIZE = 30 };
        int x_size = 21 + i;
        int y[X_SIZE];
        int x[X_SIZE];
        debug = 0;
        for (int j = 0; j < x_size; j++)
            x[j] = rand() % 50 + 50;
        for (int j = 0; j < x_size; j++)
        {
            memmove(y, x, sizeof(y));
            dump_partition("Before:", y, 0, x_size);
            int value = order(y, 0, x_size, j + 1);
            printf("rank %d is value %d (y[%d] = %d)\n", j + 1, value, j, y[j]);
            dump_partition("After: ", y, 0, x_size);
            check_partition(y, 0, x_size, j);
        }
    }

    return 0;
}
