/* SO 5332-1864 */
/*
** Sort array so that the numbers in the data element of the structure
** with the all the same digits are before of those with different
** digits, preserving the original order of elements within each
** partition (a stable partition).  Any stable sorting algorithm could
** be used.
*/

#include <stdbool.h>

typedef int SortedData;
typedef struct Sortable
{
    SortedData  data;
    int         posn;
} Sortable;

static bool is_all_same_digit(int num)
{
    int lsd = num % 10;
    while ((num /= 10) != 0)
    {
        if (num % 10 != lsd)
            return false;
    }
    return true;
}

static int cmp_numbers(const void *v1, const void *v2)
{
    Sortable *n1 = (Sortable *)v1;
    Sortable *n2 = (Sortable *)v2;
    bool b1 = is_all_same_digit(n1->data);
    bool b2 = is_all_same_digit(n2->data);
    if (b1 == b2)
        return 0;
    else if (b1 == false)
        return +1;
    else
        return -1;
}

#include <stdlib.h>
#include <string.h>

/* Crude algorithm - vaguely resembling bubble sort */
static void stable_partition(void *data, size_t number, size_t size,
                             int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 0; i < number; i++)
    {
        int swaps = 0;
        for (size_t j = i + 1; j < number; j++)
        {
            void *vp1 = (char *)data + (j - 1) * size;
            void *vp2 = (char *)data + (j - 0) * size;
            int rc = (*cmp)(vp1, vp2);
            if (rc > 0)
            {
                /* Swap 'em */
                char tmp[size];
                memmove(tmp, vp1, size);
                memmove(vp1, vp2, size);
                memmove(vp2, tmp, size);
                swaps++;
            }
        }
        if (swaps == 0)
            break;
    }
}

#include <stdio.h>

typedef int (*Comparator)(const void *v1, const void *v2);
typedef void (*SortFunction)(void *data, size_t number, size_t width, Comparator cmp);

static void print_array_sortable(const char *tag, size_t size, Sortable array[size])
{
    size_t width = 0;
    const char *pad = "";
    printf("%s (%zu):\n", tag, size);
    for (size_t i = 0; i < size; i++)
    {
        int nb = printf("%s{ %2d, %2d }", pad, array[i].data, array[i].posn);
        if (nb <= 0)
            break;
        width += nb;
        if (width >= 80 - sizeof("-1234567890"))
            pad = "\n", width = 0;
        else
            pad = ", ";
    }
    putchar('\n');
}

static void check_sorted(size_t size, Sortable array[size], Comparator cmp)
{
    for (size_t i = 1; i < size; i++)
    {
        if ((*cmp)(&array[i-1], &array[i]) > 0)
        {
            fprintf(stderr, "Sort ordering error: %zu { %2d, %2d } "
                            "compares bigger than %zu { %2d, %2d }\n",
                    i-1, array[i-1].data, array[i-1].posn,
                    i-0, array[i-0].data, array[i-0].posn);
        }
    }
}

static void check_stable(size_t size, Sortable array[size], Comparator cmp)
{
    for (size_t i = 1; i < size; i++)
    {
        if ((*cmp)(&array[i-1], &array[i-0]) == 0)
        {
            if (array[i-1].posn >= array[i-0].posn)
            {
                fprintf(stderr, "Stability error: %zu { %2d, %2d } "
                                  "compared with: %zu { %2d, %2d }\n",
                        i-1, array[i-1].data, array[i-1].posn,
                        i-0, array[i-0].data, array[i-0].posn);
            }
        }
    }
}

static void check_positions(size_t size, Sortable array[size])
{
    for (size_t i = 1; i < size; i++)
    {
        if (array[i-1].posn >= array[i].posn)
        {
            fprintf(stderr, "Bogus position data: %zu { %2d, %2d } "
                                  "compared with: %zu { %2d, %2d }\n",
                    i-1, array[i-1].data, array[i-1].posn,
                    i-0, array[i-0].data, array[i-0].posn);
        }
    }
}

static void test_sort(const char *tag, size_t size, Sortable array[size], SortFunction sort)
{
    Sortable copy[size];
    memmove(copy, array, sizeof(copy[0]) * size);
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Example %s - before", tag);
    print_array_sortable(buffer, size, copy);
    check_positions(size, copy);
    (*sort)(copy, size, sizeof(copy[0]), cmp_numbers);
    snprintf(buffer, sizeof(buffer), "Example %s - after", tag);
    print_array_sortable(buffer, size, copy);
    check_sorted(size, copy, cmp_numbers);
    check_stable(size, copy, cmp_numbers);
}

int main(void)
{
    Sortable ex1[] = { {  1, 10 }, { 43, 11 }, { 23, 12 }, { 55, 13 }, };
    Sortable ex2[] =
    {
        { 12, 11 }, { 33, 12 }, {  1, 13 }, { 19, 14 },
        { 44, 15 }, { 11, 16 }, { 76, 17 }, { 27, 18 },
        { 13, 19 },
    };
    Sortable ex3[] =
    {
        { 12, 10 }, { 33, 11 }, {  1, 12 }, { 12, 13 },
        { 19, 14 }, { 44, 15 }, { 11, 16 }, { 12, 17 },
        { 76, 18 }, { 27, 19 }, { 12, 20 }, { 13, 21 },
    };
    enum { NUM_EX1 = sizeof(ex1) / sizeof(ex1[0]) };
    enum { NUM_EX2 = sizeof(ex2) / sizeof(ex2[0]) };
    enum { NUM_EX3 = sizeof(ex3) / sizeof(ex3[0]) };

    test_sort("1 qsort", NUM_EX1, ex1, qsort);
    test_sort("2 qsort", NUM_EX2, ex2, qsort);
    test_sort("3 qsort", NUM_EX3, ex3, qsort);

    test_sort("1 stable partition", NUM_EX1, ex1, stable_partition);
    test_sort("2 stable partition", NUM_EX2, ex2, stable_partition);
    test_sort("3 stable partition", NUM_EX3, ex3, stable_partition);

    return 0;
}

