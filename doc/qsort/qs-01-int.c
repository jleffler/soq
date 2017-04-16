#include <stdio.h>
#include <stdlib.h>

static int cmpint(const void *v1, const void *v2)   /* Ascending */
{
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;
    // return *(int *)v1 - *(int *)v2; // NBG - UB on overflow!
    // Could be OK if you know that the data will always be such that
    // neither max - min nor min - max will trigger integer overflow.
    // This algorithm works for any type (unsigned integers, double).
    // The subtraction doesn't work well for unsigned integers.
    if (i1 < i2)
        return -1;
    else if (i1 > i2)
        return +1;
    else
        return 0;
}

static void print_idata(const char *tag, int size, int *data)
{
    printf("%s:\n", tag);
    int i;
    for (i = 0; i < size; i++)
    {
        printf(" %4d", data[i]);
        if (i % 10 == 9)
            putchar('\n');
    }
    if (i % 10 != 0)
        putchar('\n');
}

int main(void)
{
    int i_data[] =
    {
        // random -n 20 -- -999 +999 | commalist -b '        ' -n 10 -W4
        791,  870,  191, -271, -635,  658, -648, -524, -406, -247,
        147,  265, -365, -352,  740, -330,  252, -365,  550, -130,
    };
    enum { NUM_IDATA = sizeof(i_data) / sizeof(i_data[0]) };

    print_idata("i_data - before", NUM_IDATA, i_data);
    qsort(i_data, NUM_IDATA, sizeof(i_data[0]), cmpint);
    print_idata("i_data - after", NUM_IDATA, i_data);

    return 0;
}
