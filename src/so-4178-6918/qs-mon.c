/* SO 4178-6918 Quick Sort Again */
/* Common monitoring code */

#include "qs-mon.h"
#include <stdio.h>

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
