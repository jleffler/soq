/* SO 5308-6674 */
#include <stdio.h>
#include <stdlib.h>

static inline int min(int x, int y) { return (x < y) ? x : y; }

int main(int argc, char **argv)
{
    int size = 7;
    if (argc == 2)
    {
        size = atoi(argv[1]);
        if (size <= 0 || size > 99 || size % 2 != 1)
        {
            fprintf(stderr, "%s: size %s is not an odd number between 1 and 99\n",
                    argv[0], argv[1]);
            return 1;
        }
    }

    for (int i = 0; i < size; i++)
    {
        int n_size = min(i, size - i - 1);
        int n_fill = (size - 1) / 2 - n_size;
        int n_vals = 2 * n_size + 1;
        //printf("i = %d, n_vals = %d, n_fill = %d, n_size = %d\n",
        //       i, n_vals, n_fill, n_size);
        for (int j = 0; j < n_fill; j++)
            printf(" %3s", "");
        for (int j = 0; j < n_vals; j++)
            printf(" %3s", "***");
        putchar('\n');
    }
    return 0;
}

