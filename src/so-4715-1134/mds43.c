/* SO 4715-1134 Sorting Multidimensional Array */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** BSD variant of qsort_r():
**      void qsort_r(void *base, size_t nel, size_t width, void *thunk,
**                   int (*compar)(void *, const void *, const void *));
** Linux variant of qsort_r():
**      void qsort_r(void *base, size_t nel, size_t width,
**                   int (*compar)(const void *, const void *, void *),
**                   void *thunk);
** The code implemented uses the BSD variant.
*/

static int str_comparator(void *thunk, const void *v1, const void *v2)
{
    char **suff = thunk;
    int i1 = *(const int *)v1;
    int i2 = *(const int *)v2;
    return strcmp(suff[i1], suff[i2]);
}

static void sort_substrings(size_t length, const char seq[length], size_t index[length])
{
    const char *suff[length];

    for (size_t i = 0; seq[i] != '\0'; i++)
    {
        suff[i] = &seq[i];
        index[i] = i;
    }
    qsort_r(index, length, sizeof(index[0]), suff, str_comparator);
}

static void test_sort_substrings(const char *str)
{
    size_t length = strlen(str);
    size_t index[length];

    sort_substrings(length, str, index);

    int width = (length > 9) ? 2 : 1;

    printf("\nString: [%s]\n", str);
    printf("Sorted data:\n");
    for (size_t i = 0; i < length; i++)
        printf("%*zu [%s]\n", width, index[i], &str[index[i]]);
    putchar('\n');

    printf("Unsorted data:\n");
    for (size_t i = 0; i < length; i++)
        printf("%*zu [%s]\n", width, i, &str[i]);
    putchar('\n');
}

int main(void)
{
    test_sort_substrings("HELLO");
    test_sort_substrings("SALAMANDER");
    test_sort_substrings("ABLE WAS I ERE I SAW ELBA");
    return 0;
}
