#include <stdio.h>

int main(void)
{
    for (int i = -128; i < 128; i++)
    {
        signed char c = i;
        signed char r = i & -i;
        printf("x = 0x%.2hhX, x & - x = 0x%.2hhX\n", c, r);
    }
    return 0;
}
