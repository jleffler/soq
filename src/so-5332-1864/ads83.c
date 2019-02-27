/* SO 5332-1864 */
/*
** Sort array so that the numbers with the all the same digits are in
** front of those that have different digits, preserving original order
** of elements within each partition (a stable partition).
*/

/*
** This code uses selection sort, which is not a stable sort.
** Therefore, it is not an appropriate solution to the problem on hand.
** But I wanted to have a generic selection sort too.
*/

#include <stdbool.h>
#include <stdio.h>      /* Debug */

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
    int n1 = *(int *)v1;
    int n2 = *(int *)v2;
    bool b1 = is_all_same_digit(n1);
    bool b2 = is_all_same_digit(n2);
    if (b1 == b2)
        return 0;
    else if (b1 == false)
        return +1;
    else
        return -1;
}

#include <stdlib.h>
#include <string.h>

#include "genswap.h"

#define GEN_IDX(arr, idx, size) ((char *)(arr) + (idx) * (size))
static void selection_sort_gen(void *data, size_t number, size_t size,
                           int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 0; i < number - 1; i++)
    {
        size_t jmin = i;
        for (size_t j = i + 1; j < number; j++)
        {
            if ((*cmp)(GEN_IDX(data, j, size), GEN_IDX(data, jmin, size)) <= 0)
                jmin = j;
        }
        if (i != jmin)
            generic_swap(GEN_IDX(data, i, size), GEN_IDX(data, jmin, size), size);
    }
}

#if 0
static void selection_sort_gen(void *data, size_t number, size_t size,
                           int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 0; i < number - 1; i++)
    {
        size_t jmin = i;
        void *vp1 = (char *)data + jmin * size;
        for (size_t j = i + 1; j < number; j++)
        {
            void *vp2 = (char *)data + j * size;
            int rc = (*cmp)(vp2, vp1);
            if (rc < 0)
            {
                jmin = j;
                vp1 = (char *)data + jmin * size;
            }
        }
        if (jmin != i)
        {
            char *vp4 = (char *)data + i * size;
            generic_swap(vp1, vp4, size);
        }
    }
}
#endif

#if 0
static inline void swap(int *i, int *j)
{
    int t = *i;
    *i = *j;
    *j = t;
}

static void selection_sort_int(int *data, size_t number,
                               int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 0; i < number - 1; i++)
    {
        size_t jmin = i;
        for (size_t j = i + 1; j < number; j++)
        {
            if ((*cmp)(&data[j], &data[jmin]) < 0)
                jmin = j;
        }
        if (jmin != i)
            generic_swap(&data[i], &data[jmin], sizeof(data[0]));
    }
}
#endif

#include <stdio.h>

static void print_array_int(const char *tag, size_t size, int array[size])
{
    size_t width = 0;
    const char *pad = "";
    printf("%s (%zu):\n", tag, size);
    for (size_t i = 0; i < size; i++)
    {
        int nb = printf("%s%d", pad, array[i]);
        if (nb <= 0)
            break;
        width += nb;
        if (width >= 80 - sizeof("-1234567890"))
            pad = "\n";
        else
            pad = ", ";
    }
    putchar('\n');
}

static inline int max(int x, int y) { return (x > y) ? x : y; }
#define MAX(x, y)   (((x) > (y)) ? (x) : (y))
#define DIM(x)      (sizeof(x) / sizeof((x)[0]))

int main(void)
{
    int ex1[] = { 1, 43, 23, 55 };
    int ex2[] = { 12, 33, 1, 19, 44, 11, 76, 27, 13 };
    enum { NUM_EX1 = sizeof(ex1) / sizeof(ex1[0]) };
    enum { NUM_EX2 = sizeof(ex2) / sizeof(ex2[0]) };
    int ex3[max(DIM(ex1), DIM(ex2))];
    size_t num3;

    memmove(ex3, ex1, sizeof(ex1));
    num3 = NUM_EX1;
    print_array_int("Example 1 qsort - before", num3, ex3);
    qsort(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 1 qsort - after", num3, ex3);

    memmove(ex3, ex2, sizeof(ex2));
    num3 = NUM_EX2;
    print_array_int("Example 2 qsort - before", num3, ex3);
    qsort(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 2 qsort - after", num3, ex3);

    memmove(ex3, ex1, sizeof(ex1));
    num3 = NUM_EX1;
    print_array_int("Example 1 selection sort - before", num3, ex3);
    //selection_sort_int(ex3, num3, cmp_numbers);
    selection_sort_gen(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 1 selection sort - after", num3, ex3);

    memmove(ex3, ex2, sizeof(ex2));
    num3 = NUM_EX2;
    print_array_int("Example 2 selection sort - before", num3, ex3);
    //selection_sort_int(ex3, num3, cmp_numbers);
    selection_sort_gen(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 2 selection sort - after", num3, ex3);

    return 0;
}

