#include "qs-mon.h"
#include <stdbool.h>
#include <stdio.h>

/*
**  Amended pseudo-code from SO 4178-6918
**
**  Partition(A,p,r)
**  {
**      x <- A[p]
**      i <- p-1
**      j <- r+1
**      while (True) {
**          repeat
**              j <- j-1
**          until (A[j] <= x)
**          repeat
**              i <- i+1
**          until (A[i] >= x)
**          if (i A[j]
**          else
**              return(j)
**      }
**  }
**
**  Wikipedia says (Lomuto Partitioning):
**
**  algorithm quicksort(A, lo, hi) is
**      if lo < hi then
**          p := partition(A, lo, hi)
**          quicksort(A, lo, p – 1)
**          quicksort(A, p + 1, hi)
**
**  algorithm partition(A, lo, hi) is
**      pivot := A[hi]
**      i := lo     // place for swapping
**      for j := lo to hi – 1 do
**          if A[j] ≤ pivot then
**              swap A[i] with A[j]
**          i := i + 1
**      swap A[i] with A[hi]
**      return i
**
**  Wikipedia says (Hoare Partitioning):
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
**          do
**              j := j - 1
**          while A[j] > pivot
**          if i >= j then
**              return j
**          swap A[i] with A[j]
**
**  Note difference between Lomuto and Hoare in post-partition boundaries!
*/

static int partition(int a[], int start, int end)
{
    int pivot = a[start]; // select first elem as the pivot
    printf("-->> P(%d,%d) - pivot %d\n", start, end, pivot);
    int i = start - 1;      // point i and j to before/after start end of the arr
    int j = end + 1;

    while (true)
    {
        //printf("---- a[%d]=%d, a[%d]=%d\n", i, a[i], j, a[j]);
        do
        {
            j--;
            printf("---- j a[%d] = %d\n", j, a[j]);
        } while (a[j] > pivot);
        do
        {
            i++;
            printf("---- i a[%d] = %d\n", i, a[i]);
        } while (a[i] < pivot);
        if (i >= j)
            break;
        printf("-<>- a[%d]=%d, a[%d]=%d\n", j, a[j], i, a[i]);
        swap_ints(a, i, j);
        printf("-><- a[%d]=%d, a[%d]=%d\n", j, a[j], i, a[i]);
        dump_data("Post-swap", a, start, end);
    }
    dump_data("Partition", a, start, end);
    printf("<<-- P(%d) = %d\n", j, a[j]);
    return j;
}

void quicksort(int arr[], int start, int end)
{
    if (start < end)
    {
        dump_data("QS Pre-partition", arr, start, end);
        int boundary = partition(arr, start, end);
        printf("QS Partition: %d:%d:%d\n", start, boundary, end);
        dump_data("QS Pre-recursion L", arr, start, boundary);
        quicksort(arr, start, boundary);
        dump_data("QS Pre-recursion H", arr, boundary + 1, end);
        quicksort(arr, boundary + 1, end);
        dump_data("QS Post-Sort", arr, start, end);
    }
}
