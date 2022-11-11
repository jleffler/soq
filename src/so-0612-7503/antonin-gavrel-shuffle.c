/*
** Answer: https://stackoverflow.com/a/48625145/15168 
** by Antonin Gavrel https://stackoverflow.com/users/3161139/antonin-gavrel
** Question: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
*/

/*
** Comment by YT:
** When I tested this code on an array of 20 elements, the last element
** was never swapped, and the second last seldom swapped.  When I tested
** it on an array of 10 elements, 60% of the time the last element was
** unchanged, and 60% of the time the second last element was unchanged.
** This does not seem like a good shuffle.  (It also uses a lot of extra
** storage space, with two extra arrays of the same size as the array
** that is being shuffled.  That too is not good.)  You should not call
** srand() in the shuffle function.
*/

#include <string.h>
#include <stdlib.h>

#ifdef USE_ORIGINAL_CODE

#include <time.h>
#include <strings.h>    /* bzero() on macOS */

static inline void shuffle(size_t n, int arr[])
{
    size_t      rng;
    size_t      i;
    int         tmp[n];
    int         tmp2[n];

    memcpy(tmp, arr, sizeof(int) * n);
    bzero(tmp2, sizeof(int) * n);
    srand(time(NULL));
    i = 0;
    while (i < n)
    {
        rng = rand() % (n - i);
        while (tmp2[rng] == 1)
            ++rng;
        tmp2[rng] = 1;
        arr[i] = tmp[rng];
        ++i;
    }
}

#else

static inline void shuffle(size_t n, int arr[])
{
    int         tmp[n];
    int         tmp2[n];

    memcpy(tmp, arr, sizeof(int) * n);
    memset(tmp2, '\0', sizeof(int) * n);
    for (size_t i = 0; i < n; i++)
    {
        size_t rng = rand() % (n - i);
        while (tmp2[rng] == 1)
            ++rng;
        tmp2[rng] = 1;
        arr[i] = tmp[rng];
    }
}

#endif /* USE_ORIGINAL_CODE */

#ifdef TEST

#include <inttypes.h>
#include <stdio.h>
#include "randseed.h"
#include "check-conservation.h"
#include "fyshuffle.h"

static inline int compare_int(const void *vp1, const void *vp2)
{
    int i1 = *(const int *)vp1;
    int i2 = *(const int *)vp2;
    return (i1 > i2) - (i1 < i2);
}

static void test_antonin_gavrel_shuffle(const char *tag, const int *data, size_t number, size_t numshuffles)
{
    printf("%s - array of size %zu with %zu shuffles:\n", tag, number, numshuffles);
    size_t count[number];
    memset(count, '\0', sizeof(count));
    for (size_t i = 0; i < numshuffles; i++)
    {
        int copy[number];
        memmove(copy, data, sizeof(copy));
        shuffle(number, copy);
        size_t rv = check_conservation(data, copy, number,
                                       sizeof(data[0]), compare_int);
        if (rv != 0)
            printf("%zu: data not conserved (%zu missing values)\n", i, rv);
        for (size_t j = 0; j < number; j++)
        {
            if (copy[j] == data[j])
                count[j]++;
        }
    }
    for (size_t i = 0; i < number; i++)
    {
        printf("%2zu: %zu\n", i, count[i]);
    }
    putchar('\n');
}

static void test_fisher_yates_shuffle(const char *tag, const int *data, size_t number, size_t numshuffles)
{
    printf("%s - array of size %zu with %zu shuffles:\n", tag, number, numshuffles);
    uint16_t fy_seed[3];
    random_seed_bytes(sizeof(fy_seed), fy_seed);
    printf("# Seed: 0x%.4X%.4X%.4X\n", fy_seed[0], fy_seed[1], fy_seed[2]);

    size_t count[number];
    memset(count, '\0', sizeof(count));
    for (size_t i = 0; i < numshuffles; i++)
    {
        int copy[number];
        memmove(copy, data, sizeof(copy));
        fisher_yates_shuffle(copy, number, sizeof(data[0]), fy_seed);
        size_t rv = check_conservation(data, copy, number,
                                       sizeof(data[0]), compare_int);
        if (rv != 0)
            printf("%zu: data not conserved (%zu missing values)\n", i, rv);
        for (size_t j = 0; j < number; j++)
        {
            if (copy[j] == data[j])
                count[j]++;
        }
    }
    for (size_t i = 0; i < number; i++)
    {
        printf("%2zu: %zu\n", i, count[i]);
    }
    putchar('\n');
}

int main(void)
{
    /* Created by: gen_matrix -i -C -E -v 20 -H 999 -L 100 -n size_20 */
    /* Random seed: 0xEB8A011F */
    /* These values are all unique */
    const int size_20[20] =
    {
        427, 969, 297, 394, 830, 901, 348, 874, 946, 658,
        251, 633, 567, 136, 143, 813, 407, 628, 365, 368,
    };
    enum { SIZE_20_SIZE = 20 };

    int size_10[10];
    enum { SIZE_10_SIZE = 10 };
    for (size_t i = 0; i < SIZE_10_SIZE; i++)
        size_10[i] = i + 1;

    uint32_t seed = random_seed_uint32();
    printf("# Seed: 0x%.8" PRIX32 "\n", seed);
    srand(seed);

    test_antonin_gavrel_shuffle("Antonin Gavrel Shuffle", size_20, SIZE_20_SIZE, 1000);
    test_antonin_gavrel_shuffle("Antonin Gavrel Shuffle", size_10, SIZE_10_SIZE, 1000);

    test_fisher_yates_shuffle("Fisher Yates Shuffle", size_10, SIZE_10_SIZE, 1000);
    test_fisher_yates_shuffle("Fisher Yates Shuffle", size_20, SIZE_20_SIZE, 1000);

    return 0;
}
#endif
