/* SO 4574-1842 */

/* Random number generator documented in C standard */
enum { RAND_MAX = 32767 };
static unsigned long int next = 1;
static int rand(void) // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

static void srand(unsigned int seed)
{
    next = seed;
}

/* Test code to see whether least significant bit is non-random */
/* This algorithm works reasonably well, at least to the naked eye */
#include <stdio.h>

int main(void)
{
    srand(1);
    for (int i = 0; i < 200; i++)
    {
        putchar('0' + rand() % 2);
        if (i % 50 == 49)
            putchar('\n');
    }
    return 0;
}
