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
**
** Variant picking largest (from 'Quicksort is Optimal')
** No separate partition function
**
**  void quicksort(Item a[], int l, int r)
**  {
**      int i = l-1, j = r; Item v = a[r];
**      if (r <= l)
**          return;
**      for (;;)
**      {
**          while (a[++i] < v)
**              ;
**          while (v < a[--j])
**              if (j == l)
**                  break;
**          if (i >= j)
**              break;
**          exch(a[i], a[j]);
**      }
**      exch(a[i], a[r]);
**      quicksort(a, l, i-1);
**      quicksort(a, i+1, r);
**  }
**
** Note that this excludes a[i] from recursion.
*/

#include "qs-main.h"
#include <stdbool.h>
#include <stdio.h>

static int partition(int *A, int lo, int hi)
{
    int pivot = A[lo];
    printf("-->> Partition [%d..%d] pivot %d\n", lo, hi, pivot);
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

