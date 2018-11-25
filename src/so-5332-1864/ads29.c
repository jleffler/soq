/* SO 5332-1864 */
/*
** Sort array so that the numbers with the same digits are in front of
** those that ve different digits - in a stable sort
*/

#include <stdbool.h>

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

//#include "mergesort.h"
#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include <stddef.h>

typedef int (*Comparator)(const void *vp1, const void *vp2);
extern void merge_sort(void *array, size_t arrlen, size_t size, Comparator cmp);

#endif /* MERGESORT_H_INCLUDED */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int ex2[] = { 12, 33, 1, 19, 44, 11, 27, 76, 13 };
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
    print_array_int("Example 1 stable partition - before", num3, ex3);
    merge_sort(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 1 stable partition - after", num3, ex3);

    memmove(ex3, ex2, sizeof(ex2));
    num3 = NUM_EX2;
    print_array_int("Example 2 stable partition - before", num3, ex3);
    merge_sort(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 2 stable partition - after", num3, ex3);

    return 0;
}

/* SO 1802-8773: Merge Sort */
/* Genericized Merge Sort */

#undef DEBUG

/* Debug */
#ifdef DEBUG
static void enter_func(const char *func);
static void exit_func(const char *func);
#else
#define enter_func(f)       ((void)0)
#define exit_func(f)        ((void)0)
#endif

static void merge(void *left, size_t size, size_t l_len, void *right,
                  size_t r_len, void *output, Comparator cmp)
{
    char  *l_pos = left;
    char  *r_pos = right;
    char  *l_end  = l_pos + l_len * size;
    char  *r_end  = r_pos + r_len * size;
    char  *o_pos = output;
    enter_func(__func__);
    while (r_pos < r_end && l_pos < l_end)
    {
        if ((*cmp)(r_pos, l_pos) < 0)
        {
            memmove(o_pos, r_pos, size);
            o_pos += size;
            r_pos += size;
        }
        else
        {
            memmove(o_pos, l_pos, size);
            o_pos += size;
            l_pos += size;
        }
    }
    /* Only one of these conditions is active */
    if (r_pos < r_end)
        memmove(o_pos, r_pos, r_end - r_pos);
    if (l_pos < l_end)
        memmove(o_pos, l_pos, l_end - l_pos);
    exit_func(__func__);
}

void merge_sort(void *array, size_t arrlen, size_t size, Comparator cmp)
{
    if (arrlen <= 1)
        return;

    char *base = array;
    size_t mid = arrlen / 2;
    size_t l_len = mid;
    size_t r_len = arrlen - mid;
    char l_data[l_len * size];
    char r_data[r_len * size];

    enter_func(__func__);
    memmove(l_data, base, l_len * size);
    memmove(r_data, base + l_len * size, r_len * size);
    merge_sort(l_data, l_len, size, cmp);
    merge_sort(r_data, r_len, size, cmp);
    merge(l_data, size, l_len, r_data, r_len, array, cmp);
    exit_func(__func__);
}

#ifdef DEBUG
static void enter_func(const char *func)
{
    printf("-->> %s\n", func);
}

static void exit_func(const char *func)
{
    printf("<<-- %s\n", func);
}
#endif
