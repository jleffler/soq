#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { MAX_ITERATIONS = 100000 };

/* lz = 1 or 0 - consider that the number has a leading zero or not */
static bool has_duplicate_digits(int value, int lz)
{
    assert(value >= 0 && value < MAX_ITERATIONS + 1);
    assert(lz == 0 || lz == 1);
    char digits[10] = { [0] = lz };
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
    int lz = 0;
    int p10 = 1;
    int log_p10 = 0;    /* log10(0) is -infinity - but 0 works better */
    int linelen = 0;
    const char *pad = "";

    /* The + 1 allows the cycle to reset for the leading zero pass */
    for (int i = 0; i < MAX_ITERATIONS + 1; i++)
    {
        if (i >= 10 * p10 && lz == 0)
        {
            /* Passed through range p10 .. (10*p10-1) once without leading zeros */
            /* Repeat, adding leading zeros this time */
            lz = 1;
            i = p10;
        }
        else if (i >= 10 * p10)
        {
            /* Passed through range p10 .. (10*p10-1) without and with leading zeros */
            /* Continue through next range, without leading zeros to start with */
            p10 *= 10;
            log_p10++;
            lz = 0;
        }

        if (!has_duplicate_digits(i, lz))
        {
            /* Adds a leading zero if lz == 1; otherwise, it doesn't */
            linelen += printf("%s%.*d", pad, log_p10 + lz + 1, i);
            pad = " ";
            if (linelen > 72)
            {
                putchar('\n');
                pad = "";
                linelen = 0;
            }
        }
    }
    putchar('\n');
    return 0;
}
