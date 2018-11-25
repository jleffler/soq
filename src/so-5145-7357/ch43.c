/*

KFY:

for (int i = cards.Length - 1; i > 0; i--)
{
    int n = rand.Next(i + 1);
    Swap(ref cards[i], ref cards[n]);
}

from: https://blog.codinghorror.com/the-danger-of-naivete/
*/

#include <stdio.h>
#include <stdlib.h>

static int random_int(int max)
{
    int limit = RAND_MAX - RAND_MAX % max;

    int value;
    while ((value = rand()) > limit)
        ;
    return value % max;
}

static void shuffle_once(int number)
{
    int data[number];

    for (int i = 0; i < number; i++)
        data[i] = i + 1;

    for (int i = number - 1; i > 0; i--)
    {
        int n = random_int(i + 1);
        int t = data[i];
        data[i] = data[n];
        data[n] = t;
    }

    for (int i = 0; i < number; i++)
        printf("%d", data[i]);
    putchar('\n');
}

int main(void)
{
     /* srand(time(0)); */
     /* unsigned seed = random_seed_uint32();
        srand(seed);
     */
     /* make 60000 and 3 into parameters */
     for (int i = 0; i < 60000; i++)
        shuffle_once(3);
     return 0;
}
