#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For sorting a 2D string array in descending order */
static int cmp2dsd(const void *v1, const void *v2)
{
    return -strcmp((const char *)v1, (const char *)v2);
}

static void print_adata(const char *tag, int size, int width, char data[size][width])
{
    printf("%s:\n", tag);
    for (int i = 0; i < size; i++)
        printf("%2d: [%s]\n", i, data[i]);
}

int main(void)
{
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

    return 0;
}
