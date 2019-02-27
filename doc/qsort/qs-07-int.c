#include <stdio.h>
#include <stdlib.h>

#ifndef COMPARATOR_SOURCE
#define COMPARATOR_SOURCE altcmp2.c
#endif

#define STRINGIZER(x)   # x
#define STRINGMAKER(x)  STRINGIZER(x)

static
#include STRINGMAKER(COMPARATOR_SOURCE)

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
        0, 1, 1, 2, 3, 0, 0, 1, -1, 0, -1, 0, 1,
    };
    enum { NUM_IDATA = sizeof(i_data) / sizeof(i_data[0]) };

    print_idata("i_data - before", NUM_IDATA, i_data);
    qsort(i_data, NUM_IDATA, sizeof(i_data[0]), cmpint);
    print_idata("i_data - after", NUM_IDATA, i_data);

    return 0;
}
