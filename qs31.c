/* SO 22274067 Sorting an array based on proximity to mean */
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
** Implement BSD qsort_r() under the name Qsort_r()
**
** void qsort_r(void *base, size_t nel, size_t width, void *thunk,
**              int (*compar)(void *, const void *, const void *));
**
** The qsort_r() function behaves identically to qsort(), except that it
** takes an additional argument, thunk, which is passed unchanged as the
** first argument to function pointed to compar.  This allows the
** comparison function to access additional data without using global
** variables, and thus qsort_r() is suitable for use in functions which
** must be reentrant.
*/

typedef int (*Comparator)(void *, const void *, const void *);

extern void Qsort_r(void *base, size_t num, size_t size, void *thunk, Comparator cmp);

static
void swap(void *val1, void *val2, size_t size)
{
    char temp[size];

    memmove(temp, val1, size);
    memmove(val1, val2, size);
    memmove(val2, temp, size);
}

/* Generate random number in range p..r inclusive */
static size_t random_int(size_t p, size_t r)
{
    assert(p <= r);
    size_t q = rand() % (r - p + 1) + p;
    return q;
}

static inline size_t thin_partition_random(void *base, size_t size,
    size_t lo, size_t hi, void *thunk, Comparator cmp)
{
    /* Use a random element as the pivot */
    assert(hi > 0);
    size_t m = random_int(lo, hi - 1);
    swap((char *)base + size * m, (char *)base + size * lo, size);

    /*
    ** Set l and r and move the array elements such
    ** that for all i in [lo..r), a[i] <= pivot,
    ** and for all i in [r+1..hi), a[i] >= pivot.
    */

    size_t l = lo + 1;
    size_t r = hi;
    while (l < r)
    {
        if (cmp(thunk, (char *)base + size * l, (char *)base + size * lo) <= 0)
            l++;
        else
            swap((char *)base + size * l, (char *)base + size * --r, size);
    }

    /* Put pivot element into place */
    swap((char *)base + size * lo, (char *)base + size * --l, size);
    return r;
}

/* Sorts the elements of a between low and high inclusive */
/* Sort short sub-partition recursively and iterate to sort longer */
void Qsort_r(void *base, size_t num, size_t size, void *thunk, Comparator cmp)
{
    size_t low = 0;
    size_t high = num - 1;

    while (low < high)
    {
        size_t r = thin_partition_random(base, size, low, high, thunk, cmp);
        size_t l = r - 1;
        assert(l >= low && high >= r);
        if (l - low > high - r)
        {
            if (high - r > 1)
                Qsort_r((char *)base + size * r, high - r + 1, size, thunk, cmp);
            high = l;
        }
        else
        {
            if (l - low > 1)
                Qsort_r((char *)base + size * low, l - low + 1, size, thunk, cmp);
            low = r;
        }
    }
}

/* -- Test harness -- */

#include <stdio.h>

static void dump_array(int n, double *d, double mean)
{
    for (int i = 0; i < n; i++)
        printf("[%d] = %8.4f (delta = %8.4f)\n", i, d[i], fabs(d[i] - mean));
}

static
int comp(void *thunk, const void *pa, const void *pb)
{
    double aValue = fabs(*(double *)thunk - *(double *)pa);
    double bValue = fabs(*(double *)thunk - *(double *)pb);
    if (aValue > bValue)
       return 1;
    else if (aValue < bValue)
       return -1;
    else return 0;
}

static void test(int n, double *d)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += d[i];
    double mean= sum / n;

    printf("Mean: %8.4f\n", mean);
    printf("Before:\n");
    dump_array(n, d, mean);
    Qsort_r(d, n, sizeof(double), &mean, comp);
    printf("After:\n");
    dump_array(n, d, mean);
}

int main(void)
{
    double d[] = { 3.1416, 2.7813, 1.613, 9.8126, 0.1213 };
    enum { NUM_D = sizeof(d) / sizeof(d[0]) };
    test(NUM_D, d);

    double data[] =
    {
        1.23, 3.29, 8.18, 2.51, 4.18, 9.99,
        6.75, 1.01, 4.68, 8.21, 6.38,
    };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };
    test(NUM_DATA, data);

    return 0;
}
