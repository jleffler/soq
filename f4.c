#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int debug = 0;

static void dump_partition(char const *tag, int a[], int start, int end)
{
    int i;
    printf("%s (%d..%d)%s", tag, start, end, (end > start + 10) ? "\n" : ":");
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
    int pivot;
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

        /* Routine thin partition - based on first element in range */
        pivot = a[start];
        if (debug) printf("pivot = %d\n", pivot);
        int l = start + 1;
        int r = end;
        while (l < r)
        {
            while (l < r && a[l] <= pivot)
                l++;
            while (l < r && a[r-1] >= pivot)
                r--;
            if (l < r)
            {
                if (debug) printf("B[%d,%d]<=>(%d,%d) ", l, r-1, a[l], a[r-1]);
                int temp = a[--r];
                a[r] = a[l];
                a[l] = temp;
                if (debug) printf("A[%d,%d]<=>(%d,%d)\n", l, r, a[l], a[r]);
            }
        }

        if (debug)
            dump_partition("loop:", a, start, end);

        int temp = a[start];
        a[start] = a[--l];
        a[l] = temp;

        assert(l >= start && l < end);
        if (debug) dump_partition("swap:", a, start, end);

        if (rank - 1 == l)
            value = a[l];
        else if (rank - 1 < l)
            value = order(a, start, l, rank);
        else
            value = order(a, l + 1, end, rank);
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
    int a[10] = { 27, 32, 23, 36, 24, 31, 25, 38, 29, 30 };
    int b[10];
    enum { SIZE = sizeof(a) / sizeof(a[0]) };
    int rank;

    int opt;
    while ((opt = getopt(argc, argv, "d")) != -1)
    {
        switch (opt)
        {
        case 'd':
            debug = 1;
            break;
        default:
            /* Ignore */
            break;
        }
    }

    while (printf("enter the rank (1..%d): ", SIZE) > 0 && scanf("%d", &rank) == 1)
    {
        printf("Rank: %d\n", rank);
        if (rank > 0 && rank <= SIZE)
        {
            memmove(b, a, sizeof(b));
            dump_partition("Before:", b, 0, SIZE);
            int value = order(b, 0, 10, rank);
            printf("rank %d is value %d (a[%d] = %d)\n", rank, value, rank-1, b[rank-1]);
            dump_partition("After: ", b, 0, SIZE);
            check_partition(b, 0, SIZE, rank-1);
        }
        else
            printf("Invalid value %d (should be 1..%d)\n", rank, SIZE);
    }
    putchar('\n');

    return 0;
}
