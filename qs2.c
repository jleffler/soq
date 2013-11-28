/* SO 19607450 -- heavily extended compared with original answer */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int trace = 0;

void quicksort_last(int *A, int p, int r);
void quicksort_random(int *A, int p, int r);
void selectionsort(int *A, int p, int r);

static int partition_last(int *A, int p, int r);
static int partition_random(int *A, int p, int r);

static void dump_partition(char const *tag, int const *A, int p, int r)
{
    int i;
    printf("%s [%d..%d]:\n", tag, p, r);
    for (i = p; i <= r; i++)
    {
        printf(" %3d", A[i]);
        if ((i - p) % 10 == 9)
            putchar('\n');
    }
    if ((i - p) % 10 != 0)
        putchar('\n');
}

static void chk_sort(int *A, int p, int r)
{
    for (int i = p; i < r; i++)
    {
        if (A[i] > A[i+1])
        {
            printf("Out of order: A[%d] = %d, A[%d] = %d\n",
                   i, A[i], i+1, A[i+1]);
        }
    }
}

static void load_random(int *A, int p, int r)
{
    int range = (r - p + 1);
    for (int i = p; i <= r; i++)
        A[i] = rand() % range;
}

static void load_ascending(int *A, int p, int r)
{
    for (int i = p; i <= r; i++)
        A[i] = i;
}

static void load_descending(int *A, int p, int r)
{
    int range = (r - p + 1);
    for (int i = p; i <= r; i++)
        A[i] = range - i;
}

static void load_uniform(int *A, int p, int r)
{
    for (int i = p; i <= r; i++)
        A[i] = r;
}

static void load_organpipe(int *A, int p, int r)
{
    int range = r - p + 1;
    for (int i = p; i <= r / 2; i++)
        A[i] = i;
    for (int i = r / 2 + 1; i <= r; i++)
        A[i] = range - i;
}

static void load_invorganpipe(int *A, int p, int r)
{
    int range = (r - p + 1) / 2;
    for (int i = p; i <= r / 2; i++)
        A[i] = range - i;
    for (int i = r / 2 + 1; i <= r; i++)
        A[i] = i - range;
}

typedef void (*Load)(int *A, int p, int r);
typedef void (*Sort)(int *A, int p, int r);
typedef int  (*Part)(int *A, int p, int r);

static void test_one_sort(int *A, int p, int r, Sort sort, char const *s_tag,
                          char const *l_tag, char const *z_tag)
{
    if (trace)
        dump_partition("Before", A, p, r);
    clock_t start = clock();
    (*sort)(A, p, r);
    clock_t finish = clock();
    double sec = (finish - start) / (double)CLOCKS_PER_SEC;
    printf("%s-%s-%s: %13.6f\n", z_tag, l_tag, s_tag, sec);
    chk_sort(A, p, r);
    if (trace)
        dump_partition("After", A, p, r);
}

static int *dup_array(int *A, int p, int r)
{
    int  nbytes = sizeof(*A) * (r - p + 1);
    int *B = malloc(nbytes);
    if (B != 0)
        memmove(B, A, nbytes);
    return B;
}

static void test_set_sorts(int *A, int p, int r, char const *l_tag, char const *z_tag)
{
    struct sorter
    {
        Sort        function;
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
        int *B = dup_array(A, p, r);
        test_one_sort(B, p, r, sort[i].function, sort[i].tag, l_tag, z_tag);
        free(B);
    }
}

static void test_set_loads(int size, char const *z_tag)
{
    struct loader
    {
        Load        function;
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
    int *A = malloc(size * sizeof(int));
    for (int i = 0; i < NUM_LOADS; i++)
    {
        load[i].function(A, 0, size-1);
        test_set_sorts(A, 0, size-1, load[i].tag, z_tag);
    }
    free(A);
}

int main(void)
{
    srand(time(NULL));

    for (int i = 10; i <= 40; i+= 10)
    {
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%dK", i);
        test_set_loads(1000*i, buffer);
    }

    return 0;
}

static void quicksort_partition(int *A, int p, int r, Part partition)
{
    if (p < r)
    {
        int q = (*partition)(A, p, r);
        quicksort_partition(A, p, q-1, partition);
        quicksort_partition(A, q+1, r, partition);
    }
}

void quicksort_last(int *A, int p, int r)
{
    quicksort_partition(A, p, r, partition_last);
}

void quicksort_random(int *A, int p, int r)
{
    quicksort_partition(A, p, r, partition_random);
}

static int random_int(int p, int r)
{
    return (rand() % (r - p + 1) + p);
}

static int partition_random(int *A, int p, int r)
{
    int pivot = random_int(p, r);
    int temp = A[pivot];
    A[pivot] = A[r];
    A[r] = temp;
    const int x=A[r];
    int i=p-1;
    int j=p;

    while (j<=r)
    {
        if (A[j]<=x)
        {
            i++;
            temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
        j++;
    }
    return i;
}

static int partition_last(int *A, int p, int r)
{
    const int x=A[r];
    int i=p-1;
    int j=p;
    int temp;

    while (j<=r)
    {
        if (A[j]<=x)
        {
            i++;
            temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
        j++;
    }
    return i;
}

void selectionsort(int *A, int p, int r)
{
    int temp;
    for( ;p<r;p++){
        for(int i=p;i<=r;i++){
            if(A[p]>A[i]){
                temp=A[p];
                A[p]=A[i];
                A[i]=temp;
            }
        }
    }
}

