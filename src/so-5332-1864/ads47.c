/* SO https://stackoverflow.com/questions/53321864/sort-array-so-that-the-numbers-with-the-same-digits-are-in-front-of-those-that?noredirect=1#comment93525230_53321864 */

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

#include <stdlib.h>
#include <string.h>

/* Aka bubble sort! */
static void stable_partition(void *data, size_t number, size_t size,
                             int (*cmp)(const void *v1, const void *v2))
{
    char tmp[size];
    for (size_t i = 0; i < number; i++)
    {
        void *vp1 = (char *)data + i * size;
        for (size_t j = i + 1; j < number; j++)
        {
            void *vp2 = (char *)data + j * size;
            int rc = (*cmp)(vp1, vp2);
            if (rc < 0)
            {
                ;
                /* In order already */
            }
            else if (rc > 0)
            {
                /* Swap 'em */
                memmove(tmp, vp1, size);
                memmove(vp1, vp2, size);
                memmove(vp2, tmp, size);
            }
            else
            {
                ;
                /* Do nothing */
            }
        }
    }
}

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
    int ex1[] = { 1,43,23,55 };
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
    stable_partition(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 1 stable partition - after", num3, ex3);

    memmove(ex3, ex2, sizeof(ex2));
    num3 = NUM_EX2;
    print_array_int("Example 2 stable partition - before", num3, ex3);
    stable_partition(ex3, num3, sizeof(ex3[0]), cmp_numbers);
    print_array_int("Example 2 stable partition - after", num3, ex3);

    return 0;
}

