#define NDEBUG 1

#include "timer.h"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* JL: added static to rquotient_xx functions */

/* JL: removed two const qualifiers */
static
int rquotient_dd(int x, int y)
{
    return (int)round((double)x / y);
}

/* JL: removed unsigned - added assert */
static
int rquotient_uu(int x, int y)
{
    assert(x >= 0 && y > 0);
    return (x + y / 2) / y;
}

/* JL: removed unsigned - added assert */
static
int rquotient_su(int x, int y)
{
    assert(y > 0);
    if (x > 0)
        return (x + y / 2) / y;
    else
        return (x - y / 2) / y;
}

static
int rquotient_ss(int x, int y)
{
    if ((x ^ y) >= 0)
        return (x + y / 2) / y;
    else
        return (x - y / 2) / y;
}

typedef int (*Divider)(int x, int y);

static void test_harness(const char *tag, Divider function)
{
    Clock clk;
    unsigned long long accumulator = 0;

    clk_init(&clk);

    clk_start(&clk);
    for (int i = 1; i < INT_MAX / 1024; i += 13)
    {
        int max_div = i / 4;
        if (max_div == 0)
            max_div = 1;
        for (int j = 1; j < max_div; j += 15)
            accumulator += (*function)(i, j);
    }
    clk_stop(&clk);

    char buffer[32];
    printf("%s: %10s  (%llu)\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)), accumulator);
}

int main(void)
{
    for (int i = 0; i < 10; i++)
    {
        test_harness("rquotient_uu", rquotient_uu);
        test_harness("rquotient_su", rquotient_su);
        test_harness("rquotient_ss", rquotient_ss);
        test_harness("rquotient_dd", rquotient_dd);
    }
    return 0;
}
