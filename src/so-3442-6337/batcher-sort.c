/* SO 34426337 */

/* Uninstrumented batchersortNR() copied from Sedgewick */
/* http://flylib.com/books/en/3.55.1.112/1/ */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stderr.h"

typedef int ITEM;

static int L;
static int R;
static int I;

static void compExch(ITEM a[], int l, int r)
{
    assert(l >= L && l <= R);
    assert(r >= L && r <= R);
    assert(r > l);
    printf("%2d: %2d cmp %2d\n", ++I, l, r);
    if (a[l] > a[r])
    {
        ITEM t = a[l];
        a[l] = a[r];
        a[r] = t;
    }
}

static void batchersortNR(ITEM a[], int l, int r)
{
    int N = r - l + 1;
    printf("N = %d\n", N);
    assert((N & (N - 1)) == 0 && N > 1); /* Power of two */
    L = l; R = r; I = 0;
    for (int p = 1; p < N; p += p)
    {
        printf("p = %d\n", p);
        for (int k = p; k > 0; k /= 2)
        {
            printf("k = %d\n", k);
            for (int j = k % p; j + k < N; j += (k + k))
            {
                printf("j = %d\n", j);
                for (int i = 0; i < N - j - k; i++)
                {
                    printf("i = %d\n", i);
                    if ((j + i) / (p + p) == (j + i + k) / (p + p))
                        compExch(a, l + j + i, l + j + i + k);
                }
            }
        }
    }
}

static void print_array(const char *tag, ITEM *a, int l, int r)
{
    printf("%s", tag);
    for (int i = l; i <= r; i++)
        printf(" %2d", a[i]);
    putchar('\n');
}

static void test_batcher_sort(ITEM *a, int l, int r)
{
    printf("Batcher Sort: %d..%d\n", l, r);
    print_array("Input: ", a, l, r);
    batchersortNR(a, l, r);
    print_array("Output:", a, l, r);
}

int main(int argc, char **argv)
{
    ITEM a[33] =
    {
         0,
        31, 58, 57, 63, 92, 15, 75, 29,
        96, 92, 84, 33, 68, 20, 64, 82,
        44, 36, 35, 31, 88, 76, 31, 36,
        58, 14, 68, 55, 67,  7, 18, 53,
    };
    int range = 4;
    err_setarg0(argv[0]);

    if (argc == 1)
    {
        argc = 2;
        argv[1] = "4";
    }

    for (int i = 1; i < argc; i++)
    {
        range = atoi(argv[i]);
        if ((range & (range - 1)) != 0 || range < 2 || range > 32)
            err_error("Range must be a power of 2 between 2 and 32 (given %d)\n", range);
        test_batcher_sort(a, 1,  range);
    }

    return 0;
}
