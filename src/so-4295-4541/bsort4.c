#include <assert.h>
#include <stdio.h>

static void bsort_4(int *A, int N, int parity)
{
    assert(parity == 0 || parity == 1);
    assert(N < 1024 * 1024);
    int posn[N];
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if ((A[i] & 1) == parity)
            posn[count++] = i;
    }
    if (count < 2)
        return;
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (A[posn[j + 1]] < A[posn[j]])
            {
                int t = A[posn[j + 1]];
                A[posn[j + 1]] = A[posn[j]];
                A[posn[j]] = t;
            }
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
