#include <assert.h>
#include <stdio.h>

static void bsort_4(int *A, int N, int parity)
{
    assert(parity == 0 || parity == 1);
    assert(N < 1024 * 1024);
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if ((A[i] & 1) == parity)
            count++;
    }
    if (count < 2)
        return;
    for (int i = 0; i < count - 1; i++)
    {
        int i0 = 0;
        while ((A[i0] & 1) != parity)
            i0++;
        for (int i1 = 0; i1 < i; i1++)
        {
            while ((A[i0] & 1) != parity)
                i0++;
        }
        int j0 = i0;
        for (int j = 0; j < count - 1 - i; j++)
        {
            int j1 = j0 + 1;
            while ((A[j1] & 1) != parity)
                j1++;
            /*printf("P = %d; j0 = %2d; A[j0] = %3d; j1 = %2d; A[j1] = %3d\n",*/
            /*       parity, j0, A[j0], j1, A[j1]);*/
            if (A[j1] < A[j0])
            {
                int t = A[j1];
                A[j1] = A[j0];
                A[j0] = t;
            }
            j0 = j1;
        }
    }
}

static void dump_array(const char *tag, const int *a, int n)
{
    printf("%-8s", tag);
    for (int i = 0; i < n; i++)
        printf(" %3d", a[i]);
    putchar('\n');
}

static void test_sorting(const int *data, int size, int parity)
{
    int array[size];
    for (int i = 0; i < size; i++)
        array[i] = data[i];
    dump_array("Before:", array, size);
    bsort_4(array, size, parity);
    dump_array("After:", array, size);
}

int main(void)
{
    const int array[] =
    {
        13,   5,  -3,   4,   2,  -7,  23, -33,   1,   6,
        -8,   7,  10, -51,   9,  -5,  12,  92,  69,  55,
    };
    enum { A_SIZE = sizeof(array) / sizeof(array[0]) };

    printf("Sort even numbers:\n");
    test_sorting(array, A_SIZE, 0);
    printf("Sort odd  numbers:\n");
    test_sorting(array, A_SIZE, 1);

    return 0;
}
