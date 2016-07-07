#include <stdio.h>

int main(void)
{
    for (int q = 3; q < 15; q += 2)
    {
       for (int y = q + 1; y < q + 100; y++)
        {
            int x = y;
            while (x >= q)
            {
                x = (x % 2) == 0 ? x / 2 : x - q;
            }
            if (x == 0)
                printf("q = %d: x = %d --> 0\n", q, y);
        }
    }
    return 0;
}
