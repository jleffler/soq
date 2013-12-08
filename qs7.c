#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Quick_Sort(int *a, int p, int r);
static int  partition(int *a, int p, int r);

static void dump_partition(char const *tag, int const *data, int lo, int hi);

/* Debugging functions */
static void check_sorted(int const *data, int lo, int hi);
static int *copy_partition(int const *data, int lo, int hi);
static void check_consistency(int const *a1, int const *a2, int lo, int hi);

int main(void)
{
    int testcase, num, search;
    int i, j, *array;
    if (scanf("%d", &testcase) != 1)
        return 1;

    for (i = 0; i < testcase; i++)
    {
        if (scanf("%d", &num) != 1)
            return 1;
        array = malloc(sizeof(int)*num);
        if (array == 0)
            return 1;
        for (j = 0; j < num; j++)
        {
            if (scanf("%d", &array[j]) != 1)
                return 1;
        }

        printf("\nData set %d:\n", i);
        int *copy = copy_partition(array, 0, num-1);
        dump_partition("Before:", array, 0, num-1);
        //dump_partition("Copy", copy, 0, num-1);
        Quick_Sort(array, 0, num-1);
        dump_partition("After: ", array, 0, num-1);
        check_sorted(array, 0, num-1);
        check_consistency(array, copy, 0, num-1);
        free(copy);

        if (scanf("%d", &search) != 1)
            return 1;
        for (j = 0; j < num; j++)
        {
            if (search == array[j])
                break;
        }
        if (j < num && search == array[j])
            printf("Found %d at %d\n", search, j+1);
        else
            printf("Missing %d\n", search);

        // Prevent memory leaks
        free(array);
    }
    return 0;
}

/* Although we're interested in data[lo]..data[hi], the copy must have data[0]..data[lo-1] too */
static int *copy_partition(int const *data, int lo, int hi)
{
    assert(lo <= hi);
    size_t nbytes = (hi + 1) * sizeof(int);
    int *space = (int *)malloc(nbytes);
    if (space == 0)
    {
        fputs("Out of memory\n", stderr);
        exit(1);
    }
    memmove(space, data, nbytes);
    return(space);
}

/* Check that the two arrays contain the same sets of data */
/* Each value in a1 must be present in a2 and vice versa */
static void check_consistency(int const *a1, int const *a2, int lo, int hi)
{
    int *a3 = copy_partition(a1, lo, hi);
    int  a3_lo = lo;
    int  a3_hi = hi;
    //printf("-->> check_consistency:\n");
    //dump_partition("a1", a1, lo, hi);
    //dump_partition("a2", a2, lo, hi);
    //dump_partition("a3", a3, lo, hi);
    for (int i = lo; i <= hi; i++)
    {
        int found = 0;
        for (int j = a3_lo; j <= a3_hi; j++)
        {
            if (a2[i] == a3[j])
            {
                /* Found a match for a2[i] at a3[j] */
                /* Move a3[j] to end of array and ignore it from here on */
                //printf("Found a2[%d] = %d at a3[%d] = %d\n", i, a2[i], j, a3[j]);
                int t = a3[a3_hi];
                a3[a3_hi] = a3[j];
                a3[j] = t;
                a3_hi--;
                //dump_partition("a3-free", a3, a3_lo, a3_hi);
                //dump_partition("a3-used", a3, a3_hi+1, hi);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("No value %d for a2[%d] in a1\n", a2[i], i);
            dump_partition("a2", a2, lo, hi);
            dump_partition("a1-free", a3, a3_lo, a3_hi);
            dump_partition("a1-used", a3, a3_hi+1, hi);
        }
    }
    free(a3);
    //printf("<<-- check_consistency\n");
}

static void dump_partition(char const *tag, int const *data, int lo, int hi)
{
    printf("%s [%d..%d]%s", tag, lo, hi, (hi - lo) > 10 ? "\n" : "");
    int i;
    for (i = lo; i <= hi; i++)
    {
        printf(" %2d", data[i]);
        if ((i - lo) % 10 == 9)
            putchar('\n');
    }
    if ((i - lo) % 10 != 0 || i == lo)
        putchar('\n');
}

static void check_sorted(int const *data, int lo, int hi)
{
    //printf("-->> check_sorted:\n");
    for (int i = lo; i < hi; i++)
    {
        if (data[i] > data[i+1])
            printf("Out of order: a[%d] = %d bigger than a[%d] = %d\n", i, data[i], i+1, data[i+1]);
    }
    //printf("<<-- check_sorted\n");
}

void Quick_Sort(int *a, int p, int r)
{
    if (p < r)
    {
        int q = partition(a, p, r);
        //dump_partition("Lo Range", a, p, q-1);
        //printf("Pivot: a[%d] = %d\n", q, a[q]);
        //dump_partition("Hi Range", a, q+1, r);
        Quick_Sort(a, p, q-1);
        Quick_Sort(a, q+1, r);
    }
}

static int partition(int *a, int p, int r)
{
    assert(p <= r);
    if (p == r)
        return p;
    int i = p;
    int j = r + 1;
    int x = a[p];
    //printf("-->> partition: lo = %d, hi = %d, pivot = %d\n", p, r, x);
    while (1)
    {
        do
        {
            j--;
            //printf("---- partition 1: a[%d] = %d\n", j, a[j]);
        }   while (x < a[j]);

        do
        {
            i++;
            //printf("---- partition 2: a[%d] = %d\n", i, a[i]);
        }   while (i <= r && x > a[i]);

        if (i <= j)
        {
            //printf("---- partition: swap a[%d] = %d with a[%d] = %d\n", i, a[i], j, a[j]);
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        else
        {
            // This swap step is crucial.
            int temp = a[p];
            a[p] = a[j];
            a[j] = temp;
            //dump_partition("a-lo", a, p, j-1);
            //printf("a-pivot[%d] = %d\n", j, a[j]);
            //dump_partition("a-hi", a, j+1, r);
            //printf("<<-- partition: return j = %d; a[%d] = %d; (i = %d; a[%d] = %d)\n", j, j, a[j], i, i, a[i]);
            return j;
        }
    }
}

