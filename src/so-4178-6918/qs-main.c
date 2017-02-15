/* SO 4178-6918 */
/* Common main program */

#include "qs-main.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    int data[] =
    {
        /* random -n 20 0 9 | commalist -b '        ' -n 10 */
        //4, 8, 0, 0, 3, 8, 3, 6, 5, 9,
        //6, 8, 3, 6, 5, 5, 0, 8, 1, 1,
        //3, 9, 4, 7, 2, 6, 9, 0, 6, 1,
        //8, 0, 2, 1, 4, 0, 6, 5, 4, 2,
        //7, 6, 2, 5, 4, 4, 6, 0, 8, 3,
        //6, 1, 2, 7, 4, 3, 0, 0, 0, 4,
        //4, 7, 8, 8, 4, 4, 4, 4, 9, 6,
        //9, 0, 2, 7, 6, 5, 9, 2, 7, 7,
        9, 7, 0, 9, 5, 4, 8, 7, 9, 9,
        2, 9, 9, 7, 0, 3, 9, 6, 8, 5,
        //5, 1, 4, 5, 5, 4, 0, 2, 6, 1,
        //5, 8, 1, 0, 1, 9, 8, 4, 8, 0,
    };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };

    int data_copy[NUM_DATA];
    for (int end = 1; end < NUM_DATA; end++)
    {
        memcpy(data_copy, data, NUM_DATA * sizeof(data[0]));
        dump_data("Unsorted", data_copy, 0, end);
        quicksort(data_copy, 0, end);
        dump_data("PostSort", data_copy, 0, end);
        check_sorted(data_copy, 0, end);
    }

    return 0;
}

void dump_data(const char *tag, int *data, int start, int end)
{
    printf("%s (%d):", tag, end - start + 1);
    for (int i = start; i <= end; i++)
    {
        printf(" %d", data[i]);
    }
    putchar('\n');
}

void check_sorted(int *data, int lo, int hi)
{
    for (int i = lo + 1; i < hi; i++)
    {
        if (data[i-1] > data[i])
            printf("Inversion @ A[%d] = %d vs A[%d] = %d\n", i-1, data[i-1], i, data[i]);
    }
}
