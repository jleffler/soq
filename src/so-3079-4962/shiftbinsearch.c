/* Becomes binsearch_E() in binsearch-speed.c */

static
int binary_search(int N, const int A[N], int val)
{
    int i, step;
    for (step = 1; step < N; step <<= 1)
        ;
    for (i = 0; step; step >>= 1)
        if (i + step < N && A[i + step] <= val)
           i += step;
    if (A[i] != val)
        i = -1;
    return i;
}

#include <assert.h>
#include <stdio.h>

int main(void)
{
    const int data[] =
    {
        0, 0, 0, 2, 2, 2,
     /* 2, 2, 2, 2, 2, 2, */
        4, 6, 6, 6, 8, 8,
    };
    enum { DATA_SIZE = sizeof(data) / sizeof(data[0]) };

    /* Check monotonic non-decreasing data */
    for (int j = 0; j < DATA_SIZE - 1; j++)
        assert(data[j] <= data[j+1]);

    /* Every starting point in the data array */
    for (int j = 0; j < DATA_SIZE; j++)
    {
        const int *base = &data[j];
        /* Every valid data length for the remainder of the data array */
        for (int k = DATA_SIZE - j; k > 0; k--)
        {
            int lo = base[0] - 1;
            int hi = base[k-1] + 2;

            printf("N = %d", k);
            for (int m = 0; m < k; m++)
                printf(" A[%d]: %d", m, base[m]);
            putchar('\n');

            /* For every value from 1 less than the minimum to one more than the maximum */
            for (int i = lo; i < hi; i++)
            {
                int r = binary_search(k, base, i);
                printf("V = %2d : R = %2d, C = %2d : %s\n",
                        i, r, (r < 0) ? -1 : base[r],
                        (r < 0) ? "missing" : "found");
                if (r == -1)
                {
                    for (int n = 0; n < k; n++)
                        assert(base[n] != i);
                }
                else
                    assert(base[r] == i);
                //assert(r == -1 || (base[r] == i && (r == 0 || base[r-1] < i)));
            }
        }
    }

    return 0;
}
