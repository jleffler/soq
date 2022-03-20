/* SO 7063-3743 */

#include <stdio.h>
#include <stdlib.h>
#include "stderr.h"

static int solution(int A[], int N);

int main(void)
{
    err_setarg0("SO 7063-3743");
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

    /* Second pass over array - O(N) */
    int lhs = A[0];
    int min_gap = abs_diff(lhs, total - lhs);
    for (int i = 1; i < N; i++)
    {
        lhs += A[i];
        int diff = abs_diff(lhs, total - lhs);
        if (diff < min_gap)
            min_gap = diff;
    }

    return min_gap;
}

