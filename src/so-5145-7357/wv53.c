#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void shuffle_once(int max)
{
    int array[max];

    for (int i = 0; i < max; i++)         // generate the numbers
        array[i] = i + 1;

    for (int i = 0; i < max; i++)         // shuffle the array
    {
        int index = rand() % max;
        int temp = array[i];
        array[i] = array[index];        // by randomly swapping
        array[index] = temp;
    }

    for (int i = 0; i < max; i++)         // output the numbers
        printf("%d", array[i]);
    printf("\n");
}

int main(void)
{
    srand((unsigned)time(NULL));        // seed the PRNG

    for (int i = 0; i < 60000; i++)
        shuffle_once(3);

    return 0;
}

/* Adapted to case ARRLEN = PICKED = 3 */

/* Weather Vane: https://stackoverflow.com/users/4142924/weather-vane */
/* SO Answer: https://stackoverflow.com/a/51458654 */
/* SO Question: https://stackoverflow.com/questions/51457357/ */
/* How can I use rand() to generate a different number that hasn't been generated before */
