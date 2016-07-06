/* SO 33338314 - vignette (see rotcols.c for real code) */
#include <stdio.h>
#include "gcd.h"

int main(void)
{
    for (int n = 4; n < 13; n++)
    {
        for (int m = 1; m < n; m++)
        {
            printf("n = %d, m = %d:\n", n, m);
            int c = gcd(n, m);
            for (int b = 0; b < c; b++)
            {
                int x = b;
                int s = n / c;
                printf("  Cycle %d: ", b+1);
                for (int i = 0; i < s; i++)
                {
                    printf("%3d", x);
                    x = (x + m) % n;
                }
                putchar('\n');
            }
        }
        putchar('\n');
    }
    return 0;
}
