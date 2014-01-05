#include <assert.h>
#include <stdio.h>

static int debug = 1;

static void dump_partition(char const *tag, int a[], int start, int end)
{
    int i;
    printf("%s: (%d..%d)%s", tag, start, end, (end > start + 10) ? "\n" : ":");
    for (i = start; i < end; i++)
    {
        printf(" [%d] = %d", i, a[i]);
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
        if (a[i] >= a[rank])
        {
            ok = 0;
            printf("BUG: a[%d] = %d should be smaller than a[%d] = %d\n",
                   i, a[i], rank, a[rank]);
        }
    }
    for (int i = rank+1; i < end; i++)
    {
        if (a[i] <= a[rank])
        {
            ok = 0;
            printf("BUG: a[%d] = %d should be larger than a[%d] = %d\n",
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
    int mark;
    int i, j, k, pivot;
    int value;

    if (debug)
    {
        printf("-->> %s: %d..%d (%d)\n", __func__, start, end, rank);
        dump_partition("into", a, start, end);
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

        j = k = start;
        pivot = a[start];
        if (debug) printf("pivot = %d\n", pivot);
        for (i = start + 1; i < end; i++)
        {
            if (a[i] < pivot)
            {
                if (debug) printf("B[%d,%d]<=>(%d,%d) ", i, k, a[i], a[k]);
                int temp = a[k];
                a[k] = a[i];
                a[i] = temp;
                if (debug) printf("A[%d,%d]<=>(%d,%d)\n", i, k, a[i], a[k]);
                j = i;
                k++;
            }
        }

        if (debug)
        {
            printf("i = %d, j = %d, k = %d\n", i, j, k);
            dump_partition("loop", a, start, end);
        }

        int temp = a[j];
        a[j] = a[k];
        a[k] = temp;
        mark = k;

        assert(mark >= start && mark < end);
        if (debug) dump_partition("swap", a, start, end);

        if (rank - 1 == mark)
            value = a[rank - 1];
        else if (rank - 1 < mark)
            value = order(a, start, mark - 1, rank);
        else
            value = order(a, mark + 1, end, rank);
    }

    if (debug)
    {
        printf("<<-- %s: %d..%d (rank = %d is value = %d)\n", __func__, start, end, rank, value);
        dump_partition("-->>", a, start, end);
    }

    return value;
}

int main(void)
{
    int a[10] = { 27, 32, 23, 36, 24, 31, 25, 38, 29, 30 };
    enum { SIZE = sizeof(a) / sizeof(a[0]) };
    int rank;
    while (printf("enter the rank (1..%d): ", SIZE) > 0 && scanf("%d", &rank) == 1)
    {
        printf("Rank: %d\n", rank);
        if (rank > 0 && rank <= SIZE)
        {
            int value = order(a, 0, 10, rank);
            printf("rank %d is value %d (a[%d] = %d)\n", rank, value, rank-1, a[rank-1]);
            dump_partition("After", a, 0, SIZE);
            check_partition(a, 0, SIZE, rank-1);
        }
        else
            printf("Invalid value %d (should be 1..%d)\n", rank, SIZE);
    }
    return 0;
}

