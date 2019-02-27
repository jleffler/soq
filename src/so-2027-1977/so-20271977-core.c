/* SO 2027-1977 - sort 4 arrays in parallel */

/*
** sort arrays x, y, z, w (type double, size n) in parallel based on
** values in x and y
**
** To apply this to the real code, where there are 4 arrays to be sorted
** in parallel, you might write:
**
**    Array4 a;
**    a.x = x;
**    a.y = y;
**    a.z = z;
**    a.w = w;
**    a.n = n;
**    quicksort_random(&a);
**
** Or even:
**
**    quicksort_random((Array4){ .n = n, .x = x, .y = y, .z = z, .w = w });
**
** combining designated initializers and compound literals.  Or you
** could write a trivial wrapper so that you can call:
**
**    quicksort_random_wrapper(n, x, y, z, w);
*/

#include "posixver.h"

/* SOF so-20271977.h */
#include <stddef.h>
typedef struct Array4
{
    size_t  n;
    double *x;
    double *y;
    double *z;
    double *w;
} Array4;

extern void quicksort_random(Array4 *A);
/* EOF so-20271977.h */

#include <assert.h>
#include <stdlib.h> /* lrand48() */

/*
** Note that a more careful implementation would use nrand48() instead
** of lrand48() to prevent its random number generation from interfering
** with other uses of the x-rand48() functions.
*/

typedef size_t (*Part)(Array4 *A, size_t p, size_t r);

static void quicksort_partition(Array4 *A, size_t p, size_t r, Part partition);
static size_t partition_random(Array4 *A, size_t p, size_t r);

/* Quick Sort Wrapper function - specifying random partitioning */
void quicksort_random(Array4 *A)
{
    quicksort_partition(A, 0, A->n - 1, partition_random);
}

/* Main Quick Sort function */
static void quicksort_partition(Array4 *A, size_t p, size_t r, Part partition)
{
    if (p < r)
    {
        size_t q = (*partition)(A, p, r);
        assert(p <= q && q <= r);
        if (q > 0)
            quicksort_partition(A, p, q-1, partition);
        quicksort_partition(A, q+1, r, partition);
    }
}

static inline int compare(Array4 const *A, size_t p, size_t r)
{
    if (A->x[p] < A->x[r])
        return -1;
    else if (A->x[p] > A->x[r])
        return +1;
    if (A->y[p] < A->y[r])
        return -1;
    else if (A->y[p] > A->y[r])
        return +1;
    else
        return 0;
}

static inline size_t random_int(size_t p, size_t r)
{
    return(lrand48() % (r - p + 1) + p);
}

static inline void swap(Array4 *A, size_t i, size_t j)
{
    double d;
    d = A->x[i];
    A->x[i] = A->x[j];
    A->x[j] = d;
    d = A->y[i];
    A->y[i] = A->y[j];
    A->y[j] = d;
    d = A->z[i];
    A->z[i] = A->z[j];
    A->z[j] = d;
    d = A->w[i];
    A->w[i] = A->w[j];
    A->w[j] = d;
}

static size_t partition_random(Array4 *A, size_t p, size_t r)
{
    size_t pivot = random_int(p, r);
    swap(A, pivot, r);
    size_t i = p-1;
    size_t j = p;

    while (j <= r)
    {
        if (compare(A, j, r) <= 0)
            swap(A, j, ++i);
        j++;
    }
    return i;
}
