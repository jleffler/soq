/* SO 4715-1134 Sorting Multidimensional Array */
#include <stdio.h>
#include <string.h>

static void sort_substrings(size_t length, const char seq[length], size_t index[length])
{
    const char *suff[length];

    for (size_t i = 0; seq[i] != '\0'; i++)
    {
        suff[i] = &seq[i];
        index[i] = i;
    }

    for (size_t j = 0; j < length; j++)     /* bubblesort pointers */
    {
        for (size_t i = 0; i < length - 1 - j; i++)
        {
            if (strcmp(suff[index[i]], suff[index[i + 1]]) > 0)
            {
                int tmp = index[i];
                index[i] = index[i+1];
                index[i+1] = tmp;
            }
        }
    }
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
