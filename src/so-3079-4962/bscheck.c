/* SO 4477-2009 */
/* Semi-generic integer binary search exhaustive tester */

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "stderr.h"

extern int binary_search(const int *base, int num, int value);

#include "bsearch.c"

static const char optstr[] = "hx";
static const char usestr[] = "[-hx]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -x  Print verbose information\n"
    ;

int main(int argc, char **argv)
{
    int trace = 0;
    const int data[] =
    {
        10, 12, 12, 12, 13, 14, 14, 17, 19, 19,
        19, 20, 20, 21, 21, 22, 23, 23, 24, 25,
        26, 26, 27, 30, 32, 32, 33, 33, 34, 34,
        35, 36, 37, 38, 40, 40, 40, 41, 42, 44,
        44, 46, 47, 49, 49, 49, 49, 50, 50, 51,
        52, 54, 56, 56, 57, 59, 60, 60, 61, 62,
        65, 65, 67, 68, 68, 68, 68, 68, 69, 72,
        74, 74, 74, 79, 86, 86, 87, 87, 87, 88,
        88, 89, 89, 89, 91, 91, 91, 92, 93, 93,
        93, 94, 95, 96, 97, 97, 98, 98, 98, 99,
    };
    enum { DATA_SIZE = sizeof(data) / sizeof(data[0]) };

    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'x':
            trace = 1;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    /* Check monotonic non-decreasing data */
    for (int j = 0; j < DATA_SIZE - 1; j++)
        assert(data[j] <= data[j+1]);

    /* Every starting point in the data array */
    int test_count = 0;
    for (int j = 0; j < DATA_SIZE; j++)
    {
        const int *base = &data[j];
        /* Every valid data length for the remainder of the data array */
        for (int k = DATA_SIZE - j; k > 0; k--)
        {
            int lo = base[0] - 1;
            int hi = base[k-1] + 2;

            if (trace)
            {
                printf("N = %d", k);
                for (int m = 0; m < k; m++)
                    printf(" A[%d]: %d", m, base[m]);
                putchar('\n');
            }

            /* For every value from 1 less than the minimum to one more than the maximum */
            for (int i = lo; i < hi; i++)
            {
                test_count++;
                int r = binary_search(base, k, i);
                if (trace)
                {
                    printf("V = %2d, : R = %2d, C = %2d : %s\n",
                            i, r, (r < 0) ? -1 : base[r],
                            (r < 0) ? "missing" : "found");
                }
                if (r == -1)
                {
                    for (int n = 0; n < k; n++)
                    {
                        if (base[n] == i)
                            printf("!! j = %d, k = %d, n = %d, base[%d] = %d, i = %d\n",
                                    j, k, n, n, base[n], i);
                        assert(base[n] != i);
                    }
                }
                assert(r == -1 || base[r] == i);
            }
        }
    }
    printf("All %d tests passed\n", test_count);

    return 0;
}
