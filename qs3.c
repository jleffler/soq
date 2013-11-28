/* SO 19727309 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void dump_partition(char const *tag, int *array, int lo, int hi)
{
    if (lo < hi)
    {
        int i;
        printf("%s: %d..%d\n", tag, lo, hi);
        for (i = lo; i <= hi; i++)
        {
            printf(" %4d", array[i]);
            if ((i - lo) % 10 == 9)
                putchar('\n');
        }
        if ((i - lo) % 10 != 0)
            putchar('\n');
    }
}

static int partition(int *A, int p, int r)
{
    const int x=A[r];
    int i=p-1;
    int j=p;
    int temp;

    while (j < r)
    {
        if (A[j] <= x)
        {
            i++;
            temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
        j++;
    }
    temp=A[i+1];
    A[i+1]=A[r];
    A[r]=temp;
    return i+1;
}

static void quicksort_last(int *A, int p, int r)
{
    if (p < r)
    {
        int q=partition(A, p, r);
        printf("quicksort: %p (%d..%d)\n", (void *)&q, p, r);
        //dump_partition("L-part", A, p, q-1);
        //dump_partition("R-part", A, q+1, r);
        quicksort_last(A, p, q-1);
        quicksort_last(A, q+1, r);
    }
}

int main(void)
{
    int data[] =
    {
        31, 14, 53, 45, 88,  0, 79, 59, 84,  5,
        83, 42, 61, 38, 24, 47, 86, 69,  8, 36,
    };
    enum { N_DATA = sizeof(data) / sizeof(data[0]) };

    dump_partition("Random", data, 0, N_DATA-1);
    quicksort_last(data, 0, N_DATA-1);
    dump_partition("Sorted", data, 0, N_DATA-1);

    enum { BIG_SIZE = 10000 };
    int data2[BIG_SIZE];
    srand(time(0));

    for (int i = 0; i < BIG_SIZE; i++)
        data2[i] = rand() % BIG_SIZE;

    dump_partition("Random", data2, 0, BIG_SIZE-1);
    quicksort_last(data2, 0, BIG_SIZE-1);
    dump_partition("Sorted", data2, 0, BIG_SIZE-1);

    for (int i = 0; i < BIG_SIZE; i++)
        data2[i] = i;

    dump_partition("Random", data2, 0, BIG_SIZE-1);
    quicksort_last(data2, 0, BIG_SIZE-1);
    dump_partition("Sorted", data2, 0, BIG_SIZE-1);

    return 0;
}
