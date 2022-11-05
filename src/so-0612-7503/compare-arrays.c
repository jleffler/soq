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
#include <stdbool.h>
#include "fyshuffle.h"
#include "randseed.h"

typedef int (*Formatter)(const void *ptr, char **pbuffer, size_t *plength);
typedef int (*Comparator)(const void *p1, const void *p2);

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
                          size_t number, size_t size, Comparator compare)
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stderr.h"

/*
** Algorithm proposed by Bar Gelfer (https://stackoverflow.com/users/20280604/bar-gelfer)
** in https://stackoverflow.com/a/74122335 for shuffling an array of integers into a
** secondary array.  Note that it destroys the input array.
*/

static inline void shuffle_array(int *ordered_array, int *shuffled_array, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        size_t index = (rand() % (len - i));
        shuffled_array[i] = ordered_array[index];
        ordered_array[index] = ordered_array[len - i];
    }
}

static inline void *array_entry(void *base, size_t number, size_t size, size_t index)
{
    assert(index < number);
    char *data = (char *)base + index * size;
    return data;
}

static inline const void *array_entry_c(const void *base, size_t number, size_t size, size_t index)
{
    assert(index < number);
    const char *data = (const char *)base + index * size;
    return data;
}

static int cmp_int(const void *p1, const void *p2)
{
    int v1 = *(int *)p1;
    int v2 = *(int *)p2;
    return (v1 > v2) - (v1 < v2);
}

static void dump_generic_array(const char *tag, size_t number, size_t size,
                               const void *data, Formatter format)
{
    printf("%s (%zu):\n", tag, number);
    const char *pad = "";
    size_t linelen = 0;
    char *buffer = 0;
    size_t length = 0;
    for (size_t i = 0; i < number; i++)
    {
        (*format)(array_entry_c(data, number, size, i), &buffer, &length);
        int nbytes = printf("%s%s", pad, buffer);
        if (nbytes <= 0)
            err_syserr("printf() failed!\n");
        linelen += nbytes;
        pad = "  ";
        if (linelen >= 72)
        {
            putchar('\n');
            pad = "";
            linelen = 0;
        }
    }
    if (linelen > 0)
        putchar('\n');
    free(buffer);
}

static void print_sorted_copy_of_array(const char *tag, size_t number, size_t size,
                                       const void *data, void *copy,
                                       Comparator compare, Formatter format)
{
    printf("-->> %s()\n", __func__);
    memmove(copy, data, size * number);
    qsort(copy, number, size, compare);
    size_t rc = check_conservation(data, copy, number, size, cmp_int);
    if (rc != 0)
        err_error("%s(): %zu differences between an unsorted array and its sorted copy\n",
                  __func__, rc);
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Original data  %s array", tag);
    dump_generic_array(buffer, number, size, data, format);
    snprintf(buffer, sizeof(buffer), "Sorted copy of %s array", tag);
    dump_generic_array(buffer, number, size, copy, format);
    printf("<<-- %s()\n", __func__);
}

enum { MAX_INT_FMT_LEN = 16 };
static int format_int(const void *ptr, char **pbuffer, size_t *plength)
{
    if (*plength < MAX_INT_FMT_LEN || *pbuffer == NULL)
    {
        void *new_space = realloc(*pbuffer, MAX_INT_FMT_LEN);
        if (new_space == NULL)
            return -1;
        *pbuffer = new_space;
        *plength = MAX_INT_FMT_LEN;
    }
    return snprintf(*pbuffer, *plength, "%2d", *(int *)ptr);
}

static void print_array_differences(size_t number, size_t size,
                                    const char *a1_name, const void *a1_data,
                                    const char *a2_name, const void *a2_data,
                                    Comparator compare, Formatter format)
{
    printf("-->> %s() (%zu x %zu)\n", __func__, number, size);
    void *a1_copy = malloc(size * number);
    void *a2_copy = malloc(size * number);
    if (a1_copy == 0 || a2_copy == 0)
    {
        free(a1_copy);
        free(a2_copy);
        printf("<<-- %s() - error exit (memory allocation failed)\n", __func__);
        return;
    }

    print_sorted_copy_of_array(a1_name, number, size, a1_data, a1_copy, compare, format);
    print_sorted_copy_of_array(a2_name, number, size, a2_data, a2_copy, compare, format);

    char *a1_buffer = 0;
    char *a2_buffer = 0;
    size_t a1_buflen = 0;
    size_t a2_buflen = 0;
    const char *a1_base = a1_copy;
    const char *a2_base = a2_copy;

    size_t j = 0;
    for (size_t i = 0; i < number && j < number; i++)
    {
        const char *a1_value = a1_base + i * size;
        const char *a2_value = a2_base + j * size;
        int rc = (*compare)(a1_value, a2_value);
        (*format)(a1_value, &a1_buffer, &a1_buflen);
        (*format)(a2_value, &a2_buffer, &a2_buflen);
        if (rc == 0)
        {
            printf("Equality: (%s[%zu] = %s) and (%s[%zu] = %s)\n",
                   a1_name, i, a1_buffer, a2_name, j, a2_buffer);
            j++;
        }
        else if (rc < 0)
        {
            printf("Mismatch: (%s[%zu] = %s)  <  (%s[%zu] = %s)\n",
                   a1_name, i, a1_buffer, a2_name, j, a2_buffer);
            while (++i < number &&
                   (a1_value = a1_base + i * size) &&
                   (*compare)(a1_value, a2_value) < 0)
            {
                (*format)(a1_value, &a1_buffer, &a1_buflen);
                printf("Mismatch: (%s[%zu] = %s)  <  (%s[%zu] = %s)\n",
                       a1_name, i, a1_buffer, a2_name, j, a2_buffer);
            }
            if (i < number && j < number &&
                (a1_value = a1_base + i * size) &&
                (*compare)(a1_value, a2_value) == 0)
            {
                (*format)(a1_value, &a1_buffer, &a1_buflen);
                printf("  Resync: (%s[%zu] = %s)  =  (%s[%zu] = %s)\n",
                       a1_name, i, a1_buffer, a2_name, j, a2_buffer);
                j++;
            }
        }
        else
        {
            printf("Mismatch: (%s[%zu] = %s)  >  (%s[%zu] = %s)\n",
                   a1_name, i, a1_buffer, a2_name, j, a2_buffer);
            while (++j < number &&
                   (a2_value = a2_base + j * size) &&
                   (*compare)(a1_value, a2_value) < 0)
            {
                (*format)(a2_value, &a2_buffer, &a2_buflen);
                printf("Mismatch: (%s[%zu] = %s)  >  (%s[%zu] = %s)\n",
                       a1_name, i, a1_buffer, a2_name, j, a1_buffer);
            }
            if (i < number && j < number &&
                (a2_value = a2_base + j * size) &&
                (*compare)(a1_value, a2_value) == 0)
            {
                (*format)(a2_value, &a2_buffer, &a2_buflen);
                printf("  Resync: (%s[%zu] = %s)  =  (%s[%zu] = %s)\n",
                       a1_name, i, a1_buffer, a2_name, j, a2_buffer);
                j++;
            }
        }
    }

    free(a1_buffer);
    free(a2_buffer);
    free(a1_copy);
    free(a2_copy);
    printf("<<-- %s()\n", __func__);
}

static void test_conservation(const char *tag, size_t number,
                              const char *a1_name, const int *a1_data,
                              const char *a2_name, const int *a2_data)
{
    printf("\n%s:\n", tag);
    dump_generic_array(a1_name, number, sizeof(a1_data[0]), a1_data, format_int);
    dump_generic_array(a2_name, number, sizeof(a2_data[0]), a2_data, format_int);
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
    test_conservation("array1 vs array2", ARRAY1_SIZE, "array1", array1, "array2", array2);
    print_array_differences(ARRAY1_SIZE, sizeof(array1[0]),
                            "array1", array1, "array2", array2, cmp_int, format_int);

#ifdef USE_GENERIC_BAR_GELFER_SHUFFLE
    printf("\nBar Gelfer shuffle:\n");
    /*
    ** The subterfuge of copying array1 to array3 is necessary because
    ** shuffle_array() modifies both its input parameters.
    */
    int array3[ARRAY1_SIZE];
    int array4[ARRAY1_SIZE];
    memmove(array3, array1, sizeof(array3));
    memmove(array4, array1, sizeof(array4));
    dump_generic_array("Before shuffling - array3", ARRAY1_SIZE, sizeof(array3[0]), array3, format_int);
    shuffle_array(array3, array4, ARRAY1_SIZE);
    dump_generic_array("After shuffling  - array3", ARRAY1_SIZE, sizeof(array3[0]), array3, format_int);
    test_conservation("array1 vs array4", ARRAY1_SIZE, "array1", array1, "array4", array4);

    print_array_differences(ARRAY1_SIZE, sizeof(array1[0]),
                            "array1", array1, "array4", array4, cmp_int, format_int);
#endif /* USE_GENERIC_BAR_GELFER_SHUFFLE */

    printf("\nFisher-Yates shuffle:\n");
    uint16_t fy_seed[3];
    random_seed_bytes(sizeof(fy_seed), fy_seed);
    printf("# Seed: 0x%.4X%.4X%.4X\n", fy_seed[0], fy_seed[1], fy_seed[2]);
    int array5[ARRAY1_SIZE];
    memmove(array5, array1, sizeof(array5));
    fisher_yates_shuffle(array5, ARRAY1_SIZE, sizeof(array5[0]), fy_seed);
    test_conservation("array1 vs array5", ARRAY1_SIZE, "array1", array1, "array5", array5);

    return 0;
}

#endif /* TEST */
