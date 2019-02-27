/* SO 4929-0953 */
#include <stdio.h>

static inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void sortnet_12_13_23(int num1, int num2, int num3)
{
    if (num1 > num2) swap(&num1, &num2);
    if (num1 > num3) swap(&num1, &num3);
    if (num2 > num3) swap(&num2, &num3);
    printf("%s - sorted order (%2d, %2d, %2d)\n", "1/2, 1/3, 2/3", num1, num2, num3);
}

static void sortnet_12_23_12(int num1, int num2, int num3)
{
    if (num1 > num2) swap(&num1, &num2);
    if (num2 > num3) swap(&num2, &num3);
    if (num1 > num2) swap(&num1, &num2);
    printf("%s - sorted order (%2d, %2d, %2d)\n", "1/2, 2/3, 1/2", num1, num2, num3);
}

static void sortnet_13_23_12(int num1, int num2, int num3)
{
    if (num1 > num3) swap(&num1, &num3);
    if (num2 > num3) swap(&num2, &num3);
    if (num1 > num2) swap(&num1, &num2);
    printf("%s - sorted order (%2d, %2d, %2d)\n", "1/3, 2/3, 1/2", num1, num2, num3);
}

static void sortnet_13_12_23(int num1, int num2, int num3)
{
    if (num1 > num3) swap(&num1, &num3);
    if (num1 > num2) swap(&num1, &num2);
    if (num2 > num3) swap(&num2, &num3);
    printf("%s - sorted order (%2d, %2d, %2d)\n", "1/3, 1/2, 2/3", num1, num2, num3);
}

static void sortnet_23_12_23(int num1, int num2, int num3)
{
    if (num2 > num3) swap(&num2, &num3);
    if (num1 > num2) swap(&num1, &num2);
    if (num2 > num3) swap(&num2, &num3);
    printf("%s - sorted order (%2d, %2d, %2d)\n", "2/3, 1/2, 2/3", num1, num2, num3);
}

static void sortnet_23_13_12(int num1, int num2, int num3)
{
    if (num2 > num3) swap(&num2, &num3);
    if (num1 > num3) swap(&num1, &num3);
    if (num1 > num2) swap(&num1, &num2);
    printf("%s - sorted order (%2d, %2d, %2d)\n", "1/2, 2/3, 1/2", num1, num2, num3);
}

int main(void)
{
    int lo = -7;        // +1, -2
    int hi = +6;        // +4, +4
    int jp = +6;        // +1, +2
    for (int i = lo; i < hi; i += jp)
    {
        for (int j = lo; j < hi; j += jp)
        {
            for (int k = lo; k < hi; k += jp)
            {
                sortnet_12_13_23(i, j, k);
                sortnet_12_23_12(i, j, k);
                sortnet_13_12_23(i, j, k);
                sortnet_13_23_12(i, j, k);
                sortnet_23_12_23(i, j, k);
                sortnet_23_13_12(i, j, k);
                putchar('\n');
            }
        }
    }
    return 0;
}
