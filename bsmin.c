/* SO 30794962 */

/*
** Modified binary search.
** Find lowest occurrence of value in array (if there is more than one)
*/

#include <assert.h>
#include <stdio.h>

static
int bsearchm(const int *A, int n, int v)
{
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi)
    {
        if (A[lo] == v)
            return lo;
        int mid = (lo + hi) / 2;
        //printf("  v = %d, lo = %d, hi = %d, mid = %d, A[%d] = %d\n",
        //       v, lo, hi, mid, mid, A[mid]);
        if (A[mid] > v)
            hi = mid - 1;
        else if (A[mid] < v)
            lo = mid + 1;
        else if (mid == lo)
            return lo;
        else if (mid == hi)
            lo = lo + 1;
        else
            hi = hi - 1;
    }

    return -1;
}

int main(void)
{
    const int data[] =
    {
        0, 0, 0, 2, 2, 4, 6, 6, 6,
    };
    enum { DATA_SIZE = sizeof(data) / sizeof(data[0]) };

    for (int j = 0; j < DATA_SIZE; j++)
    {
        const int *base = &data[j];
        for (int k = DATA_SIZE - j; k > 0; k--)
        {
            int lo = base[0] - 1;
            int hi = base[k-1] + 2;

            printf("N = %d", k);
            for (int m = 0; m < k; m++)
                printf(" A[%d]: %d", m, base[m]);
            putchar('\n');

            for (int i = lo; i < hi; i++)
            {
                int r = bsearchm(base, k, i);
                printf("V = %2d, R = %2d, C = %2d  %s\n",
                        i, r, (r < 0) ? -1 : base[r],
                        (r < 0) ? "missing" : "found");
                if (r == -1)
                {
                    for (int n = 0; n < k; n++)
                        assert(base[n] != i);
                }
                assert(r == -1 || (base[r] == i && (r == 0 || base[r-1] < i)));
            }
        }
    }

    return 0;
}
