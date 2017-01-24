/* SO 4178-6918 */
/* Wikipedia.org Quicksort */

/*
** Wikipedia Quicksort Pseudo-code (Hoare Partitioning)
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
*/

#include "qs-mon.h"
#include <stdbool.h>
#include <stdio.h>

static int partition(int *A, int lo, int hi)
{
    int pivot = A[lo];
    printf("-->> P(%d,%d) - pivot %d\n", lo, hi, pivot);
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
        {
            dump_data("Post-partition", A, lo, hi);
            printf("Partition element: A[%d] = %d\n", j, A[j]);
            return j;
        }
        //swap A[i] with A[j]
        swap_ints(A, i, j);
    }
    /*NOTREACHED*/
}

void quicksort(int *A, int lo, int hi)
{
    if (lo < hi)
    {
        int p = partition(A, lo, hi);
        quicksort(A, lo, p);
        quicksort(A, p + 1, hi);
    }
}

