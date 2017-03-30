#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

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

static void print_pdata(const char *tag, int size, char **data)
{
    printf("%s:\n", tag);
    for (int i = 0; i < size; i++)
        printf("%2d: %p [%s]\n", i, (void *)data[i], data[i]);
}

int main(void)
{
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

    /* Using cmp2dsd() or strcmp() would not work reliably */
    print_pdata("str2 - before (using cmpstr)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmpstr);
    print_pdata("str2 - after  (using cmpstr)", NUM_STR2, str2);
    putchar('\n');

    printf("Using cmp2dsd on str2 does not work sanely. It\n");
    printf("happens not to crash on my machine, but that\n");
    printf("is a minor miracle and cannot be guaranteed.\n");

    verbose = 1;
    print_pdata("str2 - before (using cmp2dsd)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmp2dsd);
    print_pdata("str2 - after  (using cmp2dsd)", NUM_STR2, str2);
    putchar('\n');

    print_pdata("str2 - before (using cmpstr)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmpstr);
    print_pdata("str2 - after  (using cmpstr)", NUM_STR2, str2);
    putchar('\n');

    return 0;
}
