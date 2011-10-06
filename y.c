#include <stdio.h>
#include <stdlib.h>

static int signum(int n)
{
    return (n < 0) ? -1 : (n > 0) ? +1 : 0;
}

enum { LO = -7, HI = -LO + 1 };

int main(void)
{
    printf("%4.4s ", "");
    for (int j = LO; j < HI; j++)
    {
        if (j == 0)
            continue;
        printf(" %4d", j);
    }
    putchar('\n');

    for (int i = -20; i < 21; i++)
    {
        printf("%4d:", i);
        for (int j = LO; j < HI; j++)
        {
            if (j == 0)
                continue;
            int m = (j - signum(j));
            int k = (i + m) / j;
            printf(" %4d", k);
        }
        putchar('\n');
    }
    return(0);
}
