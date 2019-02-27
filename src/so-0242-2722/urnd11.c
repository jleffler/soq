/* SO 0242-2722 */

/* Unsigned integer round up, and round nearest */

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

static inline unsigned round_up(unsigned i, unsigned j)
{
    return (i / j) + ((i % j) + j - 1) / j;
}

static inline unsigned round_nearest(unsigned i, unsigned j)
{
    return (i / j) + ((i % j) + (j - 1) / 2) / j;
}

static void test_one_set(unsigned i, unsigned j)
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
    for (unsigned i = 57; i <= 59; i += 2)
    {
        unsigned j = 4;
        test_one_set(+i, +j);
    }

    for (unsigned i = 50; i <= 70; i++)
    {
        for (unsigned j = 1; j <= 10; j++)
        {
            test_one_set(+i, +j);
        }
    }

    return 0;
}
