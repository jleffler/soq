/* SO 0242-2722 */

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
** What should the results be for:
** Division    Round Up    Nearest      Round Away
** +57 / +4      +15         +14          +15
** +59 / +4      +15         +15          +15
** +57 / -4      -14         +14          -15
** +59 / -4      -14         *15          -15
** -57 / +4      *15         *14          -15
** -59 / +4      *15         *15          -15
** -57 / -4      *15         *14          +15
** -59 / -4      *15         *15          +15
*/

static inline int signum(int n) { return (n < 0) ? -1 : (n > 0) ? +1 : 0; }

static inline int round_up(int i, int j)
{
    assert(i != INT_MIN || j != 1);
    return (i / j) + ((i % j) + j - 1) / j;
}

static inline int round_nearest(int i, int j)
{
    assert(i != INT_MIN || j != 1);
    return (i / j) + ((i % j) + (j - 1) / 2) / j;
}

static void test_one_set(int i, int j)
{
    double di = i;
    double dj = j;
    printf("i = %3d, j = %3d: up = %3d, near = %3d;"
            " division = %7.3f, round = %3ld, trunc = %7.3f\n",
            i, j, round_up(i, j), round_nearest(i, j),
            di / dj, lround(di / dj), trunc(di / dj));
}

int main(void)
{
    for (int i = 57; i <= 59; i += 2)
    {
        int j = 4;
        /* Positive, positive seems to be working correctly */
        test_one_set(+i, +j);
        /* Mixed negative, positive mostly working - maybe some hiccups */
        test_one_set(-i, +j);
        /* Mixed positive, negative is badly broken */
        test_one_set(+i, -j);
        /* Negative, negative is badly broken */
        test_one_set(-i, -j);
    }

    for (int i = 50; i <= 70; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            /* Positive, positive seems to be working correctly */
            test_one_set(+i, +j);
            /* Mixed negative, positive mostly working - maybe some hiccups */
            //test_one_set(-i, +j);
            /* Mixed positive, negative is badly broken */
            //test_one_set(+i, -j);
            /* Negative, negative is badly broken */
            //test_one_set(-i, -j);
        }
    }

    return 0;
}
