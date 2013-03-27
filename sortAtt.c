/*
** SSCCE for Stack Overflow 14824668
** http://stackoverflow.com/questions/14824668/
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
** NB: sort_check_generic() does not check conservation properties of sort.
**
** All data in the array to be sorted must be in the array when sorted.  No
** rows missing.  No rows added.  Where there were N copies of a value V in
** the unsorted data, there must also be N copies of the value V in the
** sorted data.
*/

typedef int (*Comparator)(void const *v1, void const *v2);

static int sort_check_generic(void *array, size_t n, size_t s, Comparator cmp)
{
    size_t fail = 0;
    char *base = array;

    for (size_t i = 1; i < n; i++)
    {
        /* Check whether comparator works correctly */
        int cmp10 = cmp(&base[(i-1)*s], &base[(i-0)*s]);
        int cmp01 = cmp(&base[(i-0)*s], &base[(i-1)*s]);
        if ((cmp10  > 0 && cmp01  > 0) || (cmp10  < 0 && cmp01  < 0) ||
            (cmp10 == 0 && cmp01 != 0) || (cmp10 != 0 && cmp01 == 0))
        {
            fprintf(stderr, "Bogus comparator (%d vs %d) for elements %zu and %zu\n",
                    cmp10, cmp01, i-1, i-0);
            fail++;
        }

        /* Check whether elements are ordered correctly */
        if (cmp(&base[(i-1)*s], &base[(i-0)*s]) > 0)
        {
            fprintf(stderr, "Elements %zu and %zu are out of order\n", i-1, i);
            fail++;
        }
    }
    return fail;
}

static void sort_check(int *array, size_t n)
{
    size_t fail = 0;

    for (size_t i = 1; i < n; i++)
    {
        if (array[i-1] > array[i])
        {
            fprintf(stderr, "Elements %zu (value %d) and %zu (value %d) are out of order\n",
                    i-1, array[i-1], i, array[i]);
            fail++;
        }
    }
    if (fail != 0)
        exit(1);
}

static void dump_int_array(int *a, int n)
{
    printf("%d: ", n);
    for (int i = 0; i < n; i++)
        printf(" %d", a[i]);
    putchar('\n');
}

static void ms2_intR(int a[], int lo, int hi, int scratch[])
{
    int i, j, k, md;

    assert(lo < hi && a != 0);
    if (lo + 1 >= hi)
        return;

    //printf("-->> ms2_intR [%d..%d)\n", lo, hi);
    //dump_int_array(&a[lo], hi - lo);
    md = (lo + hi) / 2;

    ms2_intR(a, lo, md, scratch);
    ms2_intR(a, md, hi, scratch);

    i = lo;    // lhs index
    j = md;    // rhs index
    k = 0;     // index into scratch

    while (i < md && j < hi)
    {
        if (a[i] < a[j])
            scratch[k++] = a[i++];
        else
            scratch[k++] = a[j++];
    }
    while (i < md)
        scratch[k++] = a[i++];
    while (j < hi)
        scratch[k++] = a[j++];

    for (k = 0, i = lo; i < hi; i++, k++)
        a[i] = scratch[k];

    //printf("<<-- ms2_intR [%d..%d)\n", lo, hi);
    //dump_int_array(&a[lo], hi - lo);
}

static void ms2_int(int a[], int n)
{
    int *scratch = (int *)malloc(n * sizeof(int));

    if (scratch != 0)
    {
        ms2_intR(a, 0, n, scratch);
        free(scratch);
    }
}

static void msort_intR(int a[], int lo, int hi, int scratch[])
{
    int i, j, k, m;

    if (lo >= hi)
        return;

    //printf("-->> msort_intR(%u)\n", hi - lo + 1);
    //dump_int_array(&a[lo], hi - lo + 1);
    m = (lo + hi) / 2;

    msort_intR(a, lo, m, scratch);
    msort_intR(a, m+1, hi, scratch);

    i = lo;    // lhs index
    j = m + 1; // rhs index
    k = 0;     // index into scratch

    while (i <= m && j <= hi)
    {
        if (a[i] < a[j])
            scratch[k++] = a[i++];
        else
            scratch[k++] = a[j++];
    }
    while (i <= m)
        scratch[k++] = a[i++];
    while (j <= hi)
        scratch[k++] = a[j++];

    for (k = 0, i = lo; i <= hi; i++, k++)
        a[i] = scratch[k];

    //printf("<<-- msort_intR(%u)\n", hi -lo + 1);
    //dump_int_array(&a[lo], hi - lo + 1);
}

static void msort_int(int a[], int n)
{
    int *scratch = (int *)malloc(n * sizeof(int));

    if (scratch != 0)
    {
        msort_intR(a, 0, n-1, scratch);
        free(scratch);
    }
}

static int cmp(const void *v1, const void *v2)
{
    int x = *(int*) v1;
    int y = *(int*) v2;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

static void msort_generic_int(void *b, size_t n, size_t s, Comparator cmp, void *scratch)
{
    if (n <= 1)
        return;     /* Already sorted */

    printf("-->> msort_generic_int(%zu)\n", n);
    dump_int_array((int *)b, n);

    size_t n1 = n / 2;
    size_t n2 = n - n1;

    char *b1 = b;
    char *b2 = (char *) b + (n1 * s);

    msort_generic_int(b1, n1, s, cmp, scratch);
    msort_generic_int(b2, n2, s, cmp, scratch);

    char *tmp = scratch;

    while (n1 > 0 && n2 > 0)
    {
        if ((*cmp)(b1, b2) <= 0)
        {
            memcpy(tmp, b1, s);
            tmp += s;
            b1 += s;
            --n1;
        }
        else
        {
            memcpy(tmp, b2, s);
            tmp += s;
            b2 += s;
            --n2;
        }
    }
    if (n1 > 0)
        memcpy(tmp, b1, n1 * s);
    else if (n2 > 0)
        memcpy(tmp, b2, n2 * s);
    memcpy(b, scratch, n * s);

    dump_int_array((int *)b, n);
    printf("<<-- msort(%zu)\n", n);
}

static void msort_generic(void *b, size_t n, size_t s, Comparator cmp)
{
    void *scratch = malloc(n * s);
    if (scratch != 0)
    {
        msort_generic_int(b, n, s, cmp, scratch);
        free(scratch);
    }
}

static void msort(void *b, size_t n, size_t s, int (*cmp)(const void *v1, const void *v2))
{
    if (n <= 1)
        return;     /* Already sorted */

    //printf("-->> msort(%zu)\n", n);
    //dump_array(stdout, "Entry to msort()", (int *)b, n);
    void *t = malloc(s*n);

    if (t == NULL)
    {
        fprintf(stderr, "Error: No Memory.\n");
        //printf("<<-- msort(%zu)\n", n);
        return;
    }

    size_t n1 = n / 2;
    size_t n2 = n - n1;

    char *b1 = b;
    char *b2 = (char *) b + (n1 * s);

    msort(b1, n1, s, cmp);
    msort(b2, n2, s, cmp);

    char *tmp = t;

    while (n1 > 0 && n2 > 0)
    {
        if ((*cmp)(b1, b2) <= 0)
        {
            memcpy(tmp, b1, s);
            tmp += s;
            b1 += s;
            --n1;
        }
        else
        {
            memcpy(tmp, b2, s);
            tmp += s;
            b2 += s;
            --n2;
        }
    }
    if (n1 > 0)
        memcpy(tmp, b1, n1 * s);
    else if (n2 > 0)
        memcpy(tmp, b2, n2 * s);
    memcpy(b, t, n * s);
    free(t);

    //dump_array(stdout, "Exit from msort()", (int *)b, n);
    //printf("<<-- msort(%zu)\n", n);
}

static int *gen_int_array(int n, int max_val)
{
    int *a = malloc(n*sizeof(int));
    if (a != 0)
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % max_val;
        }
    }
    return a;
}

static int *clone_int_array(int *a, int n)
{
    int *b = (int *)malloc(n * sizeof(int));
    if (b != 0)
    {
        for (int i = 0; i < n; i++)
            b[i] = a[i];
    }
    return b;
}

static void sort_test(int n)
{
    printf("running experiments with n=%d\n", n);

    int *a = gen_int_array(n, 5000);
    int *b = clone_int_array(a, n);
    int *c = clone_int_array(a, n);
    int *d = clone_int_array(a, n);

    if (a != 0)
    {
        msort_generic(a, n, sizeof(int), cmp);
        if (sort_check_generic(a, n, sizeof(int), cmp) != 0)
            printf("Failed to sort with msort_generic()\n");
        sort_check(a, n);
        free(a);
    }

    if (b != 0)
    {
        ms2_int(b, n);
        if (sort_check_generic(b, n, sizeof(int), cmp) != 0)
            printf("Failed to sort with ms2_int()\n");
        sort_check(b, n);
        free(b);
    }

    if (c != 0)
    {
        msort_int(c, n);
        if (sort_check_generic(c, n, sizeof(int), cmp) != 0)
            printf("Failed to sort with msort_int()\n");
        sort_check(c, n);
        free(c);
    }

    if (d != 0)
    {
        msort(d, n, sizeof(int), cmp);
        if (sort_check_generic(d, n, sizeof(int), cmp) != 0)
            printf("Failed to sort with msort()\n");
        sort_check(d, n);
        if (n < 50)
            dump_int_array(d, n);
        free(d);
    }
}

int main(int argc, char **argv)
{
    int n = 10;

    if (argc > 1)
        n = atoi(argv[1]);
    else
    {
        printf("enter n: ");
        if (scanf("%d", &n) != 1 || n < 10)
        {
            fprintf(stderr, "bad input (%d: should be at least 10). Goodbye\n", n);
            exit(1);
        }
    }

    if (n <= 0)
        n = 10;

    if (argc > 2)
        srand((int)time(0));

    sort_test(n);

    return(0);
}
