#include <stdio.h>

static int isgn(int n)
{
    return (n < 0) ? -1 : (n > 0) ? +1 : 0;
}

static int iabs(int n)
{
    return (n < 0) ? -n : +n;
}

enum { LO = -7, HI = -LO + 1 };

int main(void)
{
    printf("%4.4s ", "");
    for (int j = LO; j < HI; j++)
    {
        if (j == 0)
            continue;
        int m = (iabs(j) - 1);
        printf(" %4d/%-2d", j, m);
    }
    putchar('\n');

    for (int i = -20; i < 21; i++)
    {
        printf("%4d:", i);
        for (int j = LO; j < HI; j++)
        {
            if (j == 0)
                continue;
            int m = isgn(i) * (iabs(j) - 1);
            int k = (i + m) / j;
            //int l = (iabs(i) + (iabs(j) - 1)) / iabs(j);
            printf(" %4d   ", k);
        }
        putchar('\n');
    }
    return(0);
}
