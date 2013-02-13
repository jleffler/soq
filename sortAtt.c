#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

static void msort_intR(int a[], int lo, int hi, int scratch[])
{
    int i, j, k, m;

    if (lo >= hi)
        return;

    printf("-->> msort_intR(%u)\n", hi - lo + 1);
    dump_int_array(&a[lo], hi - lo + 1);
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

    for (k=0, i=lo; i<=hi; i++, k++)
        a[i] = scratch[k];

    printf("<<-- msort_intR(%u)\n", hi -lo + 1);
    dump_int_array(&a[lo], hi - lo + 1);
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

static void msort(void *b, size_t n, size_t s, int (*cmp)(const void *v1, const void *v2) )
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

int main(int argc, char **argv)
{
    int n = 10;
    int *a;
    int *b = 0;
    int *c = 0;
    int *d;

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

    printf("running experiments with n=%d\n", n);

    a = gen_int_array(n, 5000);
    c = clone_int_array(a, n);
    d = clone_int_array(a, n);

    msort_int(c, n);
    msort(d, n, sizeof(int), cmp);

    sort_check(d, n);
    sort_check(c, n);

    if (n < 50)
        dump_int_array(d, n);

    free(a);
    free(b);
    free(c);
    free(d);

    return(0);
}

