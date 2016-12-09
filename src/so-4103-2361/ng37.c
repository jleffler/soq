/* SO 41032621 */
/* Variant 1 - printing with leading blanks - sub-optimal */
#include <stdio.h>
#include <stdbool.h>

enum { MAX_ITERATION = 1000000 };

static bool duplicate_digits_1(int value)
{
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", value);
    char digits[10] = { 0 };
    char *ptr = buffer;
    char c;
    while ((c = *ptr++) != '\0')
        digits[c - '0']++;
    for (int i = 0; i < 10; i++)
    {
        if (digits[i] > 1)
            return true;
    }
    return false;
}

int main(void)
{
    int count = 0;
    for (int i = 0; i < MAX_ITERATION; i++)
    {
        if (!duplicate_digits_1(i))
        {
            count += printf(" %d", i);
            if (count > 72)
            {
                putchar('\n');
                count = 0;
            }
        }
    }
    putchar('\n');
    return 0;
}
