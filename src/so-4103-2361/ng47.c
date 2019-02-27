/* SO 4103-2621 */
/* Variant 3 - printing without leading blanks */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum { MAX_ITERATION = 10000000 };

static bool duplicate_digits_3(int value)
{
    char digits[10] = { 0 };
    while (value > 0)
    {
        if (++digits[value % 10] > 1)
            return true;
        value /= 10;
    }
    return false;
}

int main(void)
{
    int count = 0;
    const char *pad = "";
    for (int i = 0; i < MAX_ITERATION; i++)
    {
        if (!duplicate_digits_3(i))
        {
            count += printf("%s%d", pad, i);
            pad = " ";
            if (count > 72)
            {
                putchar('\n');
                count = 0;
                pad = "";
            }
        }
    }
    putchar('\n');
    return 0;
}
