/* SO 20271977 - sort arrays x, y, z, w (type double, size n) in parallel based on values in x and y */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FLTFMT "%13.6f"

typedef struct Array4
{
    size_t  n;
    double *x;
    double *y;
    double *z;
    double *w;
} Array4;

static int trace = 0;

static void *xmalloc(size_t size)
{
    void *space = malloc(size);
    if (space == 0)
    {
        fprintf(stderr, "Out of memory (%zu)\n", size);
        exit(1);
    }
    return space;
}

void quicksort_last(Array4 *A);
void quicksort_random(Array4 *A);
void selectionsort(Array4 *A);

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

static void dump_partition(char const *tag, Array4 const *A, size_t p, size_t r)
{
    printf("%s [%zu..%zu]:\n", tag, p, r);
    for (size_t i = p; i <= r; i++)
        printf("(" FLTFMT ", " FLTFMT ", " FLTFMT ", " FLTFMT ")\n", A->x[i], A->y[i], A->z[i], A->w[i]);
}

static void chk_sort(Array4 const *A, size_t p, size_t r)
{
    for (size_t i = p; i < r; i++)
    {
        if (compare(A, i, i+1) > 0)
        {
            if (A->x[i] > A->x[i+1])
            {
                printf("Out of order: A.x[%zu] = " FLTFMT ", A.x[%zu] = " FLTFMT "\n",
                        i, A->x[i], i+1, A->x[i+1]);
            }
            else if ((A->x[i] == A->x[i+1] && A->y[i] > A->y[i+1]))
            {
                printf("Out of order: A.x[%zu] = " FLTFMT ", A.x[%zu] = " FLTFMT ", "
                        "A.y[%zu] = " FLTFMT ", A.y[%zu] = " FLTFMT "\n",
                        i, A->x[i], i+1, A->x[i+1], i, A->y[i], i+1, A->y[i+1]);
            }
        }
    }
}

static inline void set(Array4 *A, size_t p, double d)
{
    A->x[p] = d;
    A->y[p] = d + drand48() - 0.5;
    A->z[p] = d / 2.0;
    A->w[p] = d * 2.0;
}

static void load_random(Array4 *A)
{
    size_t size = A->n;
    for (size_t i = 0; i < size; i++)
    {
        A->x[i] = drand48() * size;
        A->y[i] = drand48() * size + drand48() - 0.5;
        A->z[i] = drand48() * size / 2.0;
        A->w[i] = drand48() * size * 2.0;
    }
}

static void load_ascending(Array4 *A)
{
    size_t size = A->n;
    for (size_t i = 0; i < size; i++)
        set(A, i, i);
}

static void load_descending(Array4 *A)
{
    size_t size = A->n;
    for (size_t i = 0; i < size; i++)
        set(A, i, size - i);
}

static void load_uniform(Array4 *A)
{
    size_t size = A->n;
    for (size_t i = 0; i < size; i++)
        set(A, i, size);
}

static void load_organpipe(Array4 *A)
{
    size_t size = A->n;
    for (size_t i = 0; i <= size / 2; i++)
        set(A, i, i);
    for (size_t i = size / 2 + 1; i < size; i++)
        set(A, i, size - i);
}

static void load_invorganpipe(Array4 *A)
{
    size_t size = A->n;
    size_t range = size / 2;
    for (size_t i = 0; i < size / 2; i++)
        set(A, i, range - i);
    for (size_t i = size / 2 + 1; i < size; i++)
        set(A, i, i - range);
}

typedef void (*Load)(Array4 *A);
typedef void (*Sort)(Array4 *A);
typedef size_t (*Part)(Array4 *A, size_t p, size_t r);

static void test_one_sort(Array4 *A, Sort sort, char const *s_tag,
                          char const *l_tag, char const *z_tag)
{
    size_t size = A->n;
    if (trace)
    {
        printf("%s-%s-%s:", z_tag, l_tag, s_tag);
        dump_partition("Before", A, 0, size - 1);
    }
    clock_t start = clock();
    (*sort)(A);
    clock_t finish = clock();
    double sec = (finish - start) / (double)CLOCKS_PER_SEC;
    printf("%s-%s-%s: %13.6f\n", z_tag, l_tag, s_tag, sec);
    chk_sort(A, 0, size - 1);
    if (trace)
    {
        printf("%s-%s-%s:", z_tag, l_tag, s_tag);
        dump_partition("After", A, 0, size - 1);
    }
}

static Array4 *alloc_array(size_t size)
{
    Array4 *A = xmalloc(sizeof(*A));
    A->n = size;
    A->x = xmalloc(size * sizeof(A->x[0]));
    A->y = xmalloc(size * sizeof(A->y[0]));
    A->z = xmalloc(size * sizeof(A->z[0]));
    A->w = xmalloc(size * sizeof(A->w[0]));
    return A;
}

static Array4 *dup_array(Array4 *A)
{
    size_t size = A->n;
    Array4 *B = alloc_array(size);
    if (B != 0)
    {
        B->n = size;
        memmove(B->x, A->x, size * sizeof(A->x[0]));
        memmove(B->y, A->y, size * sizeof(A->y[0]));
        memmove(B->z, A->z, size * sizeof(A->z[0]));
        memmove(B->w, A->w, size * sizeof(A->w[0]));
    }
    return B;
}

static void free_array(Array4 *A)
{
    free(A->x);
    free(A->y);
    free(A->z);
    free(A->w);
    free(A);
}

static void test_set_sorts(Array4 *A, char const *l_tag, char const *z_tag)
{
    struct sorter
    {
        Sort function;
        char const *tag;
    } sort[] =
    {
        { quicksort_last, "QS.L" },
        { quicksort_random, "QS.R" },
        { selectionsort, "SS.N" },
    };
    enum { NUM_SORTS = sizeof(sort) / sizeof(sort[0]) };
    for (int i = 0; i < NUM_SORTS; i++)
    {
        Array4 *B = dup_array(A);
        test_one_sort(B, sort[i].function, sort[i].tag, l_tag, z_tag);
        free(B);
    }
}

static void test_set_loads(size_t size, char const *z_tag)
{
    struct loader
    {
        Load function;
        char const *tag;
    } load[] =
    {
        { load_random, "R" },
        { load_ascending, "A" },
        { load_descending, "D" },
        { load_organpipe, "O" },
        { load_invorganpipe, "I" },
        { load_uniform, "U" },
    };
    enum { NUM_LOADS = sizeof(load) / sizeof(load[0]) };
    Array4 *A = alloc_array(size);
    for (int i = 0; i < NUM_LOADS; i++)
    {
        load[i].function(A);
        test_set_sorts(A, load[i].tag, z_tag);
    }
    free_array(A);
}

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

static size_t partition_random(Array4 *A, size_t p, size_t r);
static size_t partition_last(Array4 *A, size_t p, size_t r);

void quicksort_random(Array4 *A)
{
    quicksort_partition(A, 0, A->n - 1, partition_random);
}

void quicksort_last(Array4 *A)
{
    quicksort_partition(A, 0, A->n - 1, partition_last);
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

static size_t partition_last(Array4 *A, size_t p, size_t r)
{
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

void selectionsort(Array4 *A)
{
    size_t r = A->n;
    for (size_t p = 0; p < r; p++)
    {
        for (size_t i = p; i < r; i++)
        {
            if (compare(A, p, i) > 0)
                swap(A, p, i);
        }
    }
}

int main(void)
{
    srand48((long)time(0));

    for (size_t i = 10; i <= 40; i += 10)
    {
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%zuK", i);
        test_set_loads(1000*i, buffer);
    }

    return 0;
}

