#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For sorting an array of char pointers */
static int cmpstr(const void *v1, const void *v2)
{
    return strcmp(*(const char **)v1, *(const char **)v2);
}

static void print_sdata(const char *tag, int size, char **data)
{
    printf("%s:\n", tag);
    for (int i = 0; i < size; i++)
        printf("%2d: [%s]\n", i, data[i]);
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

    print_sdata("str2 - before (using cmpstr)", NUM_STR2, str2);
    qsort(str2, NUM_STR2, sizeof(str2[0]), cmpstr);
    print_sdata("str2 - after  (using cmpstr)", NUM_STR2, str2);
    putchar('\n');

    return 0;
}
