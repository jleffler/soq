/* SO 7172-2692 - 2022-04-02 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int random_int(int range)
{
    int max = RAND_MAX - (RAND_MAX % range);
    int value;
    while ((value = rand()) > max)
        ;
    return value % range;
}

static int biassed(int range)
{
    return rand() % range;
}

int main(void)
{
    enum { NUM_VALUES = 13 };
    int count[NUM_VALUES] = { 0 };
    unsigned seed = time(0);
    srand(seed);
    printf("Seed: %u - RAND_MAX = %d - Expected %d - Remainder %d\n",
           seed, RAND_MAX, RAND_MAX / 2 / NUM_VALUES, RAND_MAX % NUM_VALUES);

    for (int i = 0; i < RAND_MAX / 2; i++)
    {
        int value = random_int(NUM_VALUES);
        if (value < 0 || value >= NUM_VALUES)
        {
            printf("Bogus return value %d on iteration %d\n", value, i);
            exit(EXIT_FAILURE);
        }
        count[value]++;
    }

    printf("Unbiassed:\n");
    for (int i = 0; i < NUM_VALUES; i++)
        printf("%d: %9d\n", i, count[i]);

    for (int i = 0; i < NUM_VALUES; i++)
        count[i] = 0;

    srand(seed);
    for (int i = 0; i < RAND_MAX / 2; i++)
    {
        int value = biassed(NUM_VALUES);
        if (value < 0 || value >= NUM_VALUES)
        {
            printf("Bogus biassed return value %d on iteration %d\n", value, i);
            exit(EXIT_FAILURE);
        }
        count[value]++;
    }

    printf("Biassed:\n");
    for (int i = 0; i < NUM_VALUES; i++)
        printf("%d: %9d\n", i, count[i]);

    return 0;
}
