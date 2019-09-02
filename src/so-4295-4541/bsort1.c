#include <stdio.h>

#define DIM(x)  (sizeof(x) / sizeof(*(x)))

static
void bsort_1(int *A, int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (A[j + 1] < A[j])
            {
                int t = A[j + 1];
                A[j + 1] = A[j];
                A[j] = t;
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

int main(void)
{
    int array[] =
    {
        13,   5,  -3,   4,   2,  -7,  23, -33,   1,   6,
        -8,   7,  10, -51,   9,  -5,  12,  92,  69,  55,
    };

    dump_array("Before:", array, DIM(array));
    bsort_1(array, DIM(array));
    dump_array("After:", array, DIM(array));

    return 0;
}
