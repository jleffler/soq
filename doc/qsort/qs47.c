/* SO 4903-9269 - qsort() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    short year;
    char  month;
    char  day;
};

static int verbose = 0;

/* For sorting an array of char */
static int cmpchr(const void *v1, const void *v2)
{
    return(*(unsigned char *)v1 - *(unsigned char *)v2);
}

/* For sorting an array of char pointers */
static int cmpstr(const void *v1, const void *v2)
{
    if (verbose)
        printf("Compare: %p [%s] with %p [%s]\n",
                (void *)*(const char **)v1, *(const char **)v1,
                (void *)*(const char **)v2, *(const char **)v2);
    return strcmp(*(const char **)v1, *(const char **)v2);
}

/* For sorting a 2D string array in descending order */
static int cmp2dsd(const void *v1, const void *v2)
{
    if (verbose)
        printf("Compare: %p [%s] with %p [%s]\n", v1, (const char *)v1, v2, (const char *)v2);
    return -strcmp((const char *)v1, (const char *)v2);
}

static int cmpint(const void *v1, const void *v2)
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

static void print_pdata(const char *tag, int size, char **data)
{
    printf("%s:\n", tag);
    for (int i = 0; i < size; i++)
        printf("%2d: %p [%s]\n", i, (void *)data[i], data[i]);
}

static void print_adata(const char *tag, int size, int width, char data[size][width])
{
    printf("%s:\n", tag);
    for (int i = 0; i < size; i++)
        printf("%2d: [%s]\n", i, data[i]);
}

static void print_sdata(const char *tag, int size, char **data)
{
    printf("%s:\n", tag);
    for (int i = 0; i < size; i++)
        printf("%2d: [%s]\n", i, data[i]);
}

int main(void)
{
    char str0[] = "a quick brown fox jumps over the lazy dog";
    enum { NUM_STR0 = sizeof(str0) / sizeof(str0[0]) - 1 }; // Not sorting the null byte!
    char str1[][25] =
    {
        "abelone please",
        "zulus on the warpath",
        "cantankerous camels",
        "dual citizenship",
        "abacus",
        "anteater"
    };
    enum { NUM_STR1 = sizeof(str1) / sizeof(str1[0]) };
    char *str2[] =
    {
        "abelone please",
        "zulus on the warpath",
        "cantankerous camels",
        "dual citizenship",
        "abacus",
        "anteater"
    };
    enum { NUM_STR2 = sizeof(str2) / sizeof(str2[0]) };

    printf("str0 - before: [%s]\n", str0);
    qsort(str0, NUM_STR0, sizeof(str0[0]), cmpchr);
    printf("str0 - after:  [%s]\n", str0);
    putchar('\n');

    print_adata("str1 - before (using cmp2dsd)", NUM_STR1, sizeof(str1[0]), str1);
    qsort(str1, NUM_STR1, sizeof(str1[0]), cmp2dsd);
    print_adata("str1 - after", NUM_STR1, sizeof(str1[0]), str1);
    putchar('\n');

    /* Bludgeoning strcmp() sorts in ascending order */
    /* comp2dsd sorts in descending order so it is obvious both did something */
    print_adata("str1 - before (using strcmp)", NUM_STR1, sizeof(str1[0]), str1);
    qsort(str1, NUM_STR1, sizeof(str1[0]), (int (*)(const void *, const void *))strcmp);
    print_adata("str1 - after  (using strcmp)", NUM_STR1, sizeof(str1[0]), str1);
    putchar('\n');

    /* Using cmp2dsd() or strcmp() would not work reliably */
    print_sdata("str2 - before (using cmpstr)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmpstr);
    print_sdata("str2 - after  (using cmpstr)", NUM_STR2, str2);
    putchar('\n');

    printf("Using cmp2dsd on str2 does not work sanely. It\n");
    printf("happens not to crash on my machine, but that\n");
    printf("is a minor miracle and cannot be expected.\n");

    verbose = 1;
    print_pdata("str2 - before (using cmp2dsd)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmp2dsd);
    print_pdata("str2 - after  (using cmp2dsd)", NUM_STR2, str2);
    putchar('\n');

    print_pdata("str2 - before (using cmpstr)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmpstr);
    print_pdata("str2 - after  (using cmpstr)", NUM_STR2, str2);
    putchar('\n');

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
    putchar('\n');

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
