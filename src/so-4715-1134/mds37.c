/* SO 4715-1134 Sorting Multidimensional Array */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char seq[] = "HELLO";
    size_t n = strlen(seq);
    char *suff[n];
    size_t index[n];

    for (size_t i = 0; seq[i]; i++)    /* initialize pointers and indexes */
    {
        suff[i] = &seq[i];
        index[i] = i;
    }

    for (size_t j = 0; j < n; j++)     /* bubblesort pointers */
    {
        for (size_t i = 0; i < n - 1 - j; i++)
        {
            if (strcmp(suff[index[i]], suff[index[i + 1]]) > 0)
            {
                int tmp = index[i];
                index[i] = index[i+1];
                index[i+1] = tmp;
            }
        }
    }


    printf("Sorted data:\n");
    for (size_t i = 0; i < n; i++)
        printf("%zu %s\n", index[i], suff[index[i]]);

    printf("Unsorted data:\n");
    for (size_t i = 0; i < n; i++)
        printf("%zu %s\n", i, suff[i]);

    return 0;
}
