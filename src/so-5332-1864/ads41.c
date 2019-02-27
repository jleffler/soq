/* SO 5332-1864 */
/*
** Sort array so that the numbers with the all the same digits are in
** front of those that have different digits, preserving original order
** of elements within each partition (a stable partition).
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

#define GEN_IDX(arr, idx, size) ((char *)(arr) + (idx) * (size))
static void insertion_sort_gen(void *data, size_t number, size_t size,
                           int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 1; i < number; i++)
    {
        char tmp[size];
        memmove(tmp, GEN_IDX(data, i, size), size);
        size_t j;
        for (j = i; j > 0; j--)
        {
            if ((*cmp)(GEN_IDX(data, j - 1, size), tmp) <= 0)
                break;
            memmove(GEN_IDX(data, j, size), GEN_IDX(data, j - 1, size), size);
        }
        memmove(GEN_IDX(data, j, size), tmp, size);
    }
}

#if 0
static void insertion_sort_gen(void *data, size_t number, size_t size,
                           int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 1; i < number; i++)
    {
        void *vp1 = (char *)data + i * size;
        char tmp[size];
        memmove(tmp, vp1, size);
        size_t j;
        for (j = i; j > 0; j--)
        {
            void *vp2 = (char *)data + (j - 1) * size;
            int rc = (*cmp)(vp2, tmp);
            if (rc <= 0)
                break;
            void *vp3 = (char *)data + j * size;
            memmove(vp3, vp2, size);
        }
        char *vp4 = (char *)data + j * size;
        memmove(vp4, tmp, size);
    }
}
#endif

#if 0
static void insertion_sort_int(int *data, size_t number,
                               int (*cmp)(const void *v1, const void *v2))
{
    for (size_t i = 1; i < number; i++)
    {
        int t = data[i];
        size_t j;
        for (j = i; j > 0 && cmp(&data[j-1], &t) > 0; j--)
            data[j] = data[j - 1];
        data[j] = t;
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
    print_array_int("Example 1 insertion sort - before", num3, ex3);
    //insertion_sort_int(ex3, num3, cmp_numbers);
    insertion_sort_gen(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 1 insertion sort - after", num3, ex3);

    memmove(ex3, ex2, sizeof(ex2));
    num3 = NUM_EX2;
    print_array_int("Example 2 insertion sort - before", num3, ex3);
    //insertion_sort_int(ex3, num3, cmp_numbers);
    insertion_sort_gen(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 2 insertion sort - after", num3, ex3);

    return 0;
}

