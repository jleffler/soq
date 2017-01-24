/* SO 4178-6918 */
/* Wikipedia.org Quicksort */
/* Hoare Partioning Scheme */

/* Pseudo-code
**
**  algorithm quicksort(A, lo, hi) is
**      if lo < hi then
**          p := partition(A, lo, hi)
**          quicksort(A, lo, p)
**          quicksort(A, p + 1, hi)
**
**  algorithm partition(A, lo, hi) is
**      pivot := A[lo]
**      i := lo - 1
**      j := hi + 1
**      loop forever
**          do
**              i := i + 1
**          while A[i] < pivot
**
**          do
**              j := j - 1
**          while A[j] > pivot
**
**          if i >= j then
**              return j
**
**          swap A[i] with A[j]
**
*/

#include <stdbool.h>

static void swap_ints(int *A, int i, int j)
{
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

static int partition(int *A, int lo, int hi)
{
    int pivot = A[lo];
    int i = lo - 1;
    int j = hi + 1;
    while (true)
    {
        do
            i++;
        while (A[i] < pivot);
        do
            j--;
        while (A[j] > pivot);
        if (i >= j)
            return j;
        //swap A[i] with A[j]
        swap_ints(A, i, j);
    }
    /*NOTREACHED*/
}

static void quicksort(int *A, int lo, int hi)
{
    if (lo < hi)
    {
        int p = partition(A, lo, hi);
        quicksort(A, lo, p);
        quicksort(A, p + 1, hi);
    }
}

#include <stdio.h>
#include <string.h>

static void dump_int_array(const char *tag, int *data, int lo, int hi)
{
    printf("%s (%d):", tag, hi - lo + 1);
    for (int i = lo; i <= hi; i++)
        printf(" %d", data[i]);
    putchar('\n');
}

static void check_sorted(int *data, int lo, int hi)
{
    for (int i = lo + 1; i < hi; i++)
    {
        if (data[i-1] > data[i])
            printf("Inversion @ A[%d] = %d vs A[%d] = %d\n", i-1, data[i-1], i, data[i]);
    }
}

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
        4, 7, 8, 8, 4, 4, 4, 4, 9, 6,
        9, 0, 2, 7, 6, 5, 9, 2, 7, 7,
        //9, 7, 0, 9, 5, 4, 8, 7, 9, 9,
        //2, 9, 9, 7, 0, 3, 9, 6, 8, 5,
        //5, 1, 4, 5, 5, 4, 0, 2, 6, 1,
        //5, 8, 1, 0, 1, 9, 8, 4, 8, 0,
    };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };

    int data_copy[NUM_DATA];
    for (int size = 1; size < NUM_DATA; size++)
    {
        memcpy(data_copy, data, NUM_DATA * sizeof(data[0]));
        dump_int_array("Before", data_copy, 0, size - 1);
        quicksort(data_copy, 0, size - 1);
        dump_int_array("After ", data_copy, 0, size - 1);
        check_sorted(data_copy, 0, size - 1);
    }

    return 0;
}
