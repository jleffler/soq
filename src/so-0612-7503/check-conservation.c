/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Check equivalence of two arrays
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "check-conservation.h"  /* SSC: Self-sufficiency check */
#include <assert.h>
#include <stdbool.h>
#include "fyshuffle.h"
#include "randseed.h"

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_check_conservation_c[];
const char jlss_id_check_conservation_c[] = "@(#)$Id$";
#endif /* lint */

/*
** Quadratic algorithm to check that two arrays contain the same data.
** Uses O(N) space in the used VLA.
*/
size_t check_conservation(const void *data1, const void *data2,
                          size_t number, size_t size,
                          int (*compare)(const void *p1, const void *p2))
{
    bool used[number];
    for (size_t i = 0; i < number; i++)
        used[i] = false;
    size_t num_bogus = 0;
    const char *base1 = data1;
    const char *base2 = data2;
    for (size_t i = 0; i < number; i++)
    {
        bool found = false;
        const char *elem1 = base1 + i * size;
        for (size_t j = 0; j < number; j++)
        {
            const char *elem2 = base2 + j * size;
            if (!used[j] && (*compare)(elem1, elem2) == 0)
            {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found)
        {
            num_bogus++;
        }
    }
    return num_bogus;
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stderr.h"

/*
** Algorithm proposed by Bar Gelfer (https://stackoverflow.com/users/20280604/bar-gelfer)
** in https://stackoverflow.com/a/74122335
*/

static void shuffle_array(int *ordered_array, int *shuffled_array, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        size_t index = (rand() % (len - i));
        shuffled_array[i] = ordered_array[index];
        ordered_array[index] = ordered_array[len - i];
    }
}

static int cmp_int(const void *p1, const void *p2)
{
    int v1 = *(int *)p1;
    int v2 = *(int *)p2;
    return (v1 > v2) - (v1 < v2);
}

static void dump_array(const char *tag, size_t size, const int *data)
{
    printf("%s (%zu):\n", tag, size);
    const char *pad = "";
    size_t length = 0;
    for (size_t i = 0; i < size; i++)
    {
        int nbytes = printf("%s%4d", pad, data[i]);
        if (nbytes <= 0)
            err_syserr("printf() failed!\n");
        length += nbytes;
        if (length >= 72)
        {
            putchar('\n');
            pad = "";
            length = 0;
        }
    }
    if (length > 0)
        putchar('\n');
}

static void print_sorted_copy_of_array(const char *tag, size_t number,
                                       const int *data, int *copy)
{
    memmove(copy, data, sizeof(copy[0]) * number);
    qsort(copy, number, sizeof(copy[0]), cmp_int);
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Original data  %s array", tag);
    dump_array(buffer, number, data);
    snprintf(buffer, sizeof(buffer), "Sorted copy of %s array", tag);
    dump_array(buffer, number, copy);
}

static void print_array_differences(size_t number,
                                    const char *a1_name, const int *a1_data,
                                    const char *a2_name, const int *a2_data)
{
    int a1_copy[number];
    int a2_copy[number];

    print_sorted_copy_of_array(a1_name, number, a1_data, a1_copy);
    print_sorted_copy_of_array(a2_name, number, a2_data, a2_copy);

    size_t i = 0;
    size_t j = 0;
    while (i < number && j < number)
    {
        if (a1_copy[i] == a2_copy[j])
        {
            printf("Equality: (%s[%zu] = %d) and (%s[%zu] = %d)\n",
                   a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
            i++;
            j++;
        }
        else if (a1_copy[i] < a2_copy[j])
        {
            printf("Mismatch: (%s[%zu] = %d)  <  (%s[%zu] = %d)\n",
                   a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
            while (++i < number && a1_copy[i] < a2_copy[j])
            {
                printf("Mismatch: (%s[%zu] = %d)  <  (%s[%zu] = %d)\n",
                       a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
            }
            if (i < number && j < number && a1_copy[i] == a2_copy[j])
            {
                printf("  Resync: (%s[%zu] = %d)  =  (%s[%zu] = %d)\n",
                       a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
                i++;
                j++;
            }
        }
        else
        {
            printf("Mismatch: (%s[%zu] = %d)  >  (%s[%zu] = %d)\n",
                   a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
            while (++j < number && a1_copy[i] > a2_copy[j])
            {
                printf("Mismatch: (%s[%zu] = %d)  >  (%s[%zu] = %d)\n",
                       a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
            }
            if (i < number && j < number && a1_copy[i] == a2_copy[j])
            {
                printf("  Resync: (%s[%zu] = %d)  =  (%s[%zu] = %d)\n",
                       a1_name, i, a1_copy[i], a2_name, j, a2_copy[j]);
                i++;
                j++;
            }
        }
    }
    assert(i == number || j == number);

    if (i < number)
    {
        while (++i < number)
        {
            assert(j == number);
            assert(a1_copy[i] > a2_copy[j - 1]);
            if (a1_copy[i] < a2_copy[j - 1])
                printf("Mismatch: (%s[%zu] = %d)  <  (%s[%zu] = %d)\n",
                        a1_name, i, a1_copy[i], a2_name, j - 1, a2_copy[j - 1]);
            else if (a1_copy[i] > a2_copy[j - 1])
                printf("Mismatch: (%s[%zu] = %d)  >  (%s[%zu] = %d)\n",
                        a1_name, i, a1_copy[i], a2_name, j - 1, a2_copy[j - 1]);
            else
                printf("Equality: (%s[%zu] = %d) and (%s[%zu] = %d)\n",
                       a1_name, i, a1_copy[i], a2_name, j - 1, a2_copy[j - 1]);
        }
    }

    if (j < number)
    {
        while (++j < number)
        {
            assert(i == number);
            assert(a1_copy[i - 1] < a2_copy[j]);
            if (a1_copy[i - 1] < a2_copy[j])
                printf("Mismatch: (%s[%zu] = %d)  <  (%s[%zu] = %d)\n",
                        a1_name, i - 1, a1_copy[i - 1], a2_name, j, a2_copy[j]);
            else if (a1_copy[i - 1] > a2_copy[j])
                printf("Mismatch: (%s[%zu] = %d)  >  (%s[%zu] = %d)\n",
                        a1_name, i - 1, a1_copy[i - 1], a2_name, j, a2_copy[j]);
            else
                printf("Equality: (%s[%zu] = %d) and (%s[%zu] = %d)\n",
                       a1_name, i - 1, a1_copy[i - 1], a2_name, j, a2_copy[j]);
        }
    }
}

static void test_conservation(const char *tag, size_t number,
                              const char *a1_name, const int *a1_data,
                              const char *a2_name, const int *a2_data)
{
    printf("\n%s:\n", tag);
    dump_array(a1_name, number, a1_data);
    dump_array(a2_name, number, a2_data);
    size_t rc = check_conservation(a1_data, a2_data, number, sizeof(a1_data[0]), cmp_int);
    if (rc == 0)
        printf("== PASS == %s is equivalent to %s\n\n", a1_name, a2_name);
    else
        printf("!! FAIL !! %s and %s have %zu differences\n\n", a1_name, a2_name, rc);
}

int main(void)
{
    err_setarg0("check-conservation");

    unsigned seed = random_seed_uint32();
    printf("# Seed: 0x%.8X\n", seed);
    srand(seed);

    /* Created by: gen_matrix -C -E -v 32 -n array1 -i -l 75 */
    /* Random seed: 0xE1F5C1C7 */
    const int array1[32] =
    {
        38, 61, 50, 88, 10, 89, 64, 73,  7, 36, 39, 20,  0, 24, 48, 49,
        67, 83, 46, 46,  0, 51, 37, 58, 46, 70,  6, 13, 91, 55, 79, 91,
    };
    enum { ARRAY1_SIZE = 32 };

    /* Created by: gen_matrix -C -E -v 32 -n array2 -i -l 75 */
    /* Random seed: 0x92132133 */
    const int array2[32] =
    {
        38, 71, 97,  8, 22, 76, 28, 55, 10, 85, 62, 27, 34,  3, 25, 18,
        29, 92, 36, 84,  1, 85, 37, 30, 85, 87, 80, 61, 57,  2,  0, 51,
    };
    enum { ARRAY2_SIZE = 32 };

    test_conservation("array1 vs array1", ARRAY1_SIZE, "array1", array1, "array1", array1);
    print_array_differences(ARRAY1_SIZE, "array1", array1, "array1", array1);
    putchar('\n');

    test_conservation("array1 vs array2", ARRAY1_SIZE, "array1", array1, "array2", array2);
    print_array_differences(ARRAY1_SIZE, "array1", array1, "array2", array2);
    putchar('\n');
    print_array_differences(ARRAY1_SIZE, "array2", array2, "array1", array1);
    putchar('\n');

    printf("\nBar Gelfer shuffle:\n");
    /*
    ** The subterfuge of copying array1 to array3 is necessary because
    ** shuffle_array() modifies both its input parameters.
    */
    int array3[ARRAY1_SIZE];
    int array4[ARRAY1_SIZE];
    memmove(array3, array1, sizeof(array3));
    memmove(array4, array1, sizeof(array4));
    dump_array("Before shuffling - array3", ARRAY1_SIZE, array3);
    shuffle_array(array3, array4, ARRAY1_SIZE);
    dump_array("After shuffling  - array3", ARRAY1_SIZE, array3);
    test_conservation("array1 vs array4", ARRAY1_SIZE, "array1", array1, "array4", array4);

    print_array_differences(ARRAY1_SIZE, "array1", array1, "array4", array4);

    printf("\nFisher-Yates shuffle:\n");
    uint16_t fy_seed[3];
    random_seed_bytes(sizeof(fy_seed), fy_seed);
    printf("# Seed: 0x%.4X%.4X%.4X\n", fy_seed[0], fy_seed[1], fy_seed[2]);
    memmove(array4, array1, sizeof(array4));
    fisher_yates_shuffle(array4, ARRAY1_SIZE, sizeof(array4[0]), fy_seed);
    test_conservation("array1 vs array4", ARRAY1_SIZE, "array1", array1, "array4", array4);

    return 0;
}

#endif /* TEST */
