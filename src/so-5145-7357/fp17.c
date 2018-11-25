#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int random_int(int max)
{
    int limit = RAND_MAX - RAND_MAX % max;

    int value;
    while ((value = rand()) > limit)
        ;
    return value % max;
}

static void shuffle_once(int max)
{
    int deck[max];
    for (int i = 0; i < max; i++)
        deck[i] = 1;

    int i = 0;
    for (int n = max; n > 0; --n)
    {
        int skip = random_int(n);
        while (1)
        {
            if (deck[i])
            {
                if (!skip)
                    break;
                --skip;
            }
            if (++i > 9)
                i = 0;
        }
        deck[i] = 0;
        printf("%d", i + 1);
    }
    putchar('\n');
}

int main(void)
{
     srand(time(0));
     /* unsigned seed = random_seed_uint32();
        srand(seed);
     */
     /* make 60000 and 3 into parameters */
     for (int i = 0; i < 60000; i++)
        shuffle_once(3);
     return 0;
}
