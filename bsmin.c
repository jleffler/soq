/* SO 30794962 */

/*
** Modified binary search.
** Find lowest occurrence of value in array (if there is more than one)
*/

#include <assert.h>
#include <stdio.h>

#if defined(EVALUATE)
static int RETURN(int rv, const char *fn, int ctr)
{
    printf("%s: %d\n", fn, ctr);
    return rv;
}
#else
#define RETURN(rv, fn, ctr) (rv)
#endif

static
int bsearchm(const int *A, int n, int v)
{
    int lo = 0;
    int hi = n - 1;

#if defined(EVALUATE)
    int counter = 0;
#endif

    if (A[lo] == v)
        return RETURN(lo, __func__, counter);
        //return lo;
    while (lo <= hi)
    {
#if defined(EVALUATE)
        counter++;
#endif
        int mid = (lo + hi) / 2;
        //printf("  v = %d, lo = %d, hi = %d, mid = %d, A[%d] = %d\n",
        //       v, lo, hi, mid, mid, A[mid]);
        if (A[mid] > v)
            hi = mid - 1;
        else if (A[mid] < v)
            lo = mid + 1;
        else if (mid == lo)
            return RETURN(lo, __func__, counter);
            //return lo;
        else if (mid == hi)
            lo++;
        else
            hi--;
    }

    return RETURN(-1, __func__, counter);
    //return -1;
}

/*
** From J Bentley "Programming Pearls, 2nd Edition", Section 9.3
** Locate the first occurrence of t in x[0..n-1].
** Assume n >= 0, and the hypothetical elements x[-1] < t and x[n] > t
** without accessing either fictitious element.
*/
static
int bsearchf(const int *x, int n, int t)
{
    int l = -1;
    int u = n;

#if defined(EVALUATE)
    int counter = 0;
#endif

    assert(n >= 0);
    while (l + 1 != u)
    {
#if defined(EVALUATE)
        counter++;
#endif
        /* Invariant: x[l] < t && x[u] >= t && l < u */
        int m = (l + u) / 2;
        //printf("  t = %d, l = %d, u = %d, m = %d, x[%d] = %d\n",
        //       t, l, u, m, m, x[m]);
        if (x[m] < t)
            l = m;
        else
            u = m;
    }
    if (u >= n || x[u] != t)
        return RETURN(-1, __func__, counter);
        //return -1;
    assert(u >= 0 && u < n);
    return RETURN(u, __func__, counter);;
    //return u;
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
                int r1 = bsearchm(base, k, i);
                int r2 = bsearchf(base, k, i);
                printf("V = %2d, R1 = %2d, C1 = %2d : R2 = %2d, C2 = %2d : %s\n",
                        i,
                        r1, (r1 < 0) ? -1 : base[r1],
                        r2, (r2 < 0) ? -1 : base[r2],
                        (r1 < 0) ? "missing" : "found");
                assert(r1 == r2);
                if (r1 == -1)
                {
                    for (int n = 0; n < k; n++)
                        assert(base[n] != i);
                }
                assert(r1 == -1 || (base[r1] == i && (r1 == 0 || base[r1-1] < i)));
            }
        }
    }

    return 0;
}
