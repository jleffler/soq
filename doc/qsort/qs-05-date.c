#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    short year;
    char  month;
    char  day;
};

static int cmpDate(const void *v1, const void *v2)
{
    struct Date d1 = *(struct Date *)v1;
    struct Date d2 = *(struct Date *)v2;

    if (d1.year < d2.year)
        return -1;
    else if (d1.year > d2.year)
        return +1;
    else if (d1.month < d2.month)
        return -1;
    else if (d1.month > d2.month)
        return +1;
    else if (d1.day < d2.day)
        return -1;
    else if (d1.day > d2.day)
        return +1;
    else
        return 0;
}

static void print_ddata(const char *tag, int size, struct Date *data)
{
    printf("%s:\n", tag);
    int i;
    for (i = 0; i < size; i++)
    {
        printf(" %4d-%.2d-%.2d", data[i].year, data[i].month, data[i].day);
        if (i % 6 == 5)
            putchar('\n');
    }
    if (i % 6 != 0)
        putchar('\n');
}

int main(void)
{
    struct Date d_data[] =
    {
        // random -n 10 -T '        { %{%Y, %l, %e}[-2000000000:+2000000000]T },'
        { 1973,  4, 24 }, { 2025,  9,  1 }, { 1979, 12, 18 },
        { 1948,  7,  1 }, { 1924,  9, 12 }, { 2012,  5, 24 },
        { 2004,  4, 21 }, { 2026,  5,  6 }, { 1962,  1, 12 },
        { 1911,  9, 22 }, { 1941,  5,  1 }, { 1940,  4, 29 },
    };
    enum { NUM_DDATA = sizeof(d_data) / sizeof(d_data[0]) };

    print_ddata("d_data - before", NUM_DDATA, d_data);
    qsort(d_data, NUM_DDATA, sizeof(d_data[0]), cmpDate);
    print_ddata("d_data - after", NUM_DDATA, d_data);
    putchar('\n');

    return 0;
}
