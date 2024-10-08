/* SO 7063-3743 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stderr.h"

static const char optstr[] = "vh";
static const char usestr[] = "[-vh]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -v  Print details of calculation as it is done\n"
    ;

static int solution(int A[], int N);

static int vflag = 0;
static int n_width = 0;
static int s_width = 0;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'v':
            vflag = 1;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (optind != argc)
        err_usage(usestr);

    int N;
    if (scanf("%d", &N) != 1)
        err_error("failed to read array size\n");
    if (N < 2 || N > 100000)
        err_error("array size %d out of range 2..100,000\n", N);

    /* VLA - but size was checked and won't overflow stack */
    int array[N];

    for (int i = 0; i < N; i++)
    {
        if (scanf("%d", &array[i]) != 1)
            err_error("failed to read element %d of array\n", i);
        if (array[i] < -1000 || array[i] > +1000)
            err_error("element %d (%d) is out of range -1000..+1000\n", i, array[i]);
    }

    n_width = snprintf(0, 0, "%d", N - 1);
    s_width = snprintf(0, 0, "%d", (N - 1) * -1000);

    int result = solution(array, N);

    printf("result: %d\n", result);
    return 0;
}

static inline int abs_diff(int a, int b)
{
    return abs(a - b);
}

static int solution(int A[], int N)
{
    int total = 0;

    /* First pass over array - O(N) */
    for (int i = 0; i < N; i++)
        total += A[i];

    if (vflag)
        printf("N = %d; total = %d\n", N, total);

    /* Second pass over array - O(N) */
    int lhs = A[0];
    int min_gap = abs_diff(lhs, total - lhs);
    if (vflag)
    {
        printf("A[%*d] = %5d: lhs = %*d, rhs = %*d, |lhs - rhs| = %*d ** minimum so far\n",
               n_width, 0, A[0], s_width, lhs, s_width, total - lhs,
               s_width, abs_diff(lhs, total - lhs));
    }
    for (int i = 1; i < N; i++)
    {
        lhs += A[i];
        int diff = abs_diff(lhs, total - lhs);
        if (vflag)
        {
            const char *marker = (diff < min_gap) ? " ** minimum so far" : "";
            printf("A[%*d] = %5d: lhs = %*d, rhs = %*d, |lhs - rhs| = %*d%s\n",
                   n_width, i, A[i], s_width, lhs, s_width, total - lhs,
                   s_width, abs_diff(lhs, total - lhs), marker);
        }
        if (diff < min_gap)
            min_gap = diff;
    }

    return min_gap;
}

