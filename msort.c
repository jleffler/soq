#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int comparator(void const *v1, void const *v2)
{
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;
    if (i1 < i2)
        return -1;
    else if (i1 > i2)
        return +1;
    else
        return 0;
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

static int *gen_int_array(size_t n, int max_val)
{
    int *a = malloc(n * sizeof(*a));
    if (a == 0)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }
    for (size_t i = 0; i < n; i++)
        a[i] = rand() % max_val;
    return(a);
}

static int *clone_int_array(int *master, size_t n)
{
    int *a = malloc(n * sizeof(*a));
    if (a == 0)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }
    for (size_t i = 0; i < n; i++)
        a[i] = master[i];
    return(a);
}

static void dump_array(FILE *fp, char const *tag, int *a, size_t n)
{
    char const *pad = "";
    fprintf(fp, "Array: %s (size %zu)\n", tag, n);
    for (size_t i = 0; i < n; i++)
    {
        fprintf(fp, "%s%d", pad, a[i]);
        pad = ",";
    }
    putc('\n', fp);
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

int main(int argc, char **argv)
{
    int n;
    int *a, *b;

    if (argc == 1)
        n = 10;
    else
        n = atoi(argv[1]);
    if (n <= 0)
        n = 10;

    printf("running experiments with n = %d\n", n);

    a = gen_int_array(n, 5000);
    b = clone_int_array(a, n);

    dump_array(stdout, "Unsorted", a, n);

    printf("Q-Sort\n");
    qsort(a, n, sizeof(int), comparator);
    dump_array(stdout, "Q-sorted", a, n);
    sort_check(a, n);

    printf("M-Sort\n");
    msort(b, n, sizeof(int), comparator);
    dump_array(stdout, "M-sorted", b, n);
    sort_check(b, n);

    free(a);
    free(b);

    return(0);
}
