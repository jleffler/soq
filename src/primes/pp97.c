#include <stdio.h>

/*
Prime Pairs

6N±1

N=4,6,9,11,14,16,…

Not necessary to check N=5M±1
because one of the pair is a multiple of 5.

Check pair ........ (4±1)
Check pair m=0, v=1 (6±1)
Check pair m=0, v=2 (12±1)
Check pair m=0, v=3 (18±1)
For m = 1 .. infinity 
   For v in {0,2,3}
       Check pair 6(5m+v)±1

Special case m=0; v=1 - it is 6±1 which is a prime pair
Special case m=0, v=0 - it is 0±1 which isn't a prime pair.
Special case: 3..5 is a prime pair, but it doesn't fit the pattern.
*/

static void print_pp(int base)
{
    printf("%d..%d\n", base - 1, base + 1);
}

static void check_pp(int m, int v)
{
    int base = 6 * (5 * m + v);
    print_pp(base);
}

int main(void)
{
    const int off[] = { 0, 2, 3 };
    print_pp(4);
    check_pp(0, 1);
    check_pp(0, 2);
    check_pp(0, 3);
    for (int m = 1; m < 33334; m++)
    {
        for (int v = 0; v < 3; v++)
            check_pp(m, off[v]);
    }
    return 0;
}
