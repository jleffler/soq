/* SO 30794962 */

/*
** Modified binary search.
** Find highest occurrence of value in array (if there is more than one)
*/

#include <assert.h>
#include <stdio.h>

/*
** Varying J Bentley "Programming Pearls, 2nd Edition", Section 9.3
** Locate the last occurrence of t in x[0..n-1].
** Assume n >= 0, and the hypothetical elements x[-1] < t and x[n] > t
** without accessing either fictitious element.
*/
static
int bsearchl(const int *x, int n, int t)
{
    int l = -1;
    int u = n;

    assert(n >= 0);
    while (l + 1 != u)
    {
//      /* Invariant: x[l] < t && x[u] >= t && l < u */
        /* Invariant: x[l] <= t && x[u] > t && l < u */
        int m = (l + u) / 2;
        //printf("  t = %d, l = %d, u = %d, m = %d, x[%d] = %d\n",
        //       t, l, u, m, m, x[m]);
//      if (x[m] < t)
        if (x[m] <= t)
            l = m;
        else
            u = m;
    }
//  if (u >= n || x[u] != t)
    if (l < 0 || x[l] != t)
        return -1;
    assert(l >= 0 && l < n);
    return l;
}

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
                int r = bsearchl(base, k, i);
                printf("V = %2d, : R = %2d, C = %2d : %s\n",
                        i, r, (r < 0) ? -1 : base[r],
                        (r < 0) ? "missing" : "found");
                if (r == -1)
                {
                    for (int n = 0; n < k; n++)
                        assert(base[n] != i);
                }
//              assert(r == -1 || (base[r] == i && (r == 0 || base[r-1] < i)));
                assert(r == -1 || (base[r] == i && (r == k-1 || base[r+1] > i)));
            }
        }
    }

    return 0;
}
