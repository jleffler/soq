/* SO 4627-2667 and 4626-0444 inspired this */

/*
** Sadistic teacher insists on logic using only arithmetic operators:
**    +, -, *, /, % (and assignment).
** Calculation requires:
** -- If H > 200, R1 = 1.5 else R1 = 0.0
** -- If H > 150, R2 = 1.3 else R2 = 0.0
** -- If H >   0, R3 = 1.1 else R3 = 0.0
** -- Determine R = R1 + R2 + R3 for given H.
**
*/

/*
** From SO 4626-0444 (by Mitchel0022
** https://stackoverflow.com/users/5927758/mitchel0022, with assistance
** from Ryan https://stackoverflow.com/users/707111/ryan)
** If (a-b) is zero, the divisor is 1 and the result is 1.
** If (a-b) is not zero, the divisor is at least 2 and the result is 0.
*/
#define EQUAL(a, b)     (1 / (((a) - (b)) * ((a) - (b)) + 1))

/*
** From SO 4627-2667 (by Ajay Brahmakshatriya
** https://stackoverflow.com/users/2858773/ajay-brahmakshatriya), comes
** the key observation that for integers, x/200 is 0 for x 0..199, and 1
** or more for higher values.
*/
#define GE(x, y)        (1 - EQUAL((x)/(y), 0))

#include <stdio.h>

static inline int gt(int x, int y) { return x >  y; }
static inline int ge(int x, int y) { return x >= y; }
static inline int lt(int x, int y) { return x <  y; }
static inline int le(int x, int y) { return x <= y; }
static inline int eq(int x, int y) { return x == y; }
static inline int ne(int x, int y) { return x != y; }

static inline int func_EQUAL(int a, int b) { return EQUAL(a, b); }
static inline int func_GE(int a, int b) { return GE(a, b); }

typedef int (*Compare)(int x, int y);

static void test_array_pair(int size1, const int *data1, int size2, const int *data2,
                            Compare cmp1, Compare cmp2,
                            int verbose, const char *name1, const char *op)
{
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2; j++)
        {
            int res1 = (*cmp1)(data1[i], data2[j]);
            int res2 = (*cmp2)(data1[i], data2[j]);
            if (verbose || res1 != res2)
                printf("x = %4d, y = %4d, %s(x,y) = %d, (x %s y) = %d\n",
                       data1[i], data2[j], name1, res1, op, res2);
        }
    }
}

int main(void)
{
    int a[] = { 1, 2, -4, 6, 10, 200 };
    enum { A_SIZE = sizeof(a) / sizeof(a[0]) };
    int b[] = { 1, 4, -4, 10, 20, 203 };
    enum { B_SIZE = sizeof(b) / sizeof(b[0]) };

    printf("Testing equality (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_EQUAL, eq, 0, "EQUAL", "==");
#if 0
    for (int i = 0; i < A_SIZE; i++)
    {
        for (int j = 0; j < B_SIZE; j++)
            printf("x = %4d, y = %4d, EQUAL(x,y) = %d, (x == y) = %d\n",
                   a[i], b[j], EQUAL(a[i], b[j]), a[i] == b[j]);
    }
#endif

    printf("Testing equality (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_EQUAL, eq, 0, "EQUAL", "==");
#if 0
    for (int i = 0; i < A_SIZE; i++)
    {
        for (int j = 0; j < A_SIZE; j++)
            printf("x = %4d, y = %4d, EQUAL(x,y) = %d, (x == y) = %d\n",
                   a[i], a[j], EQUAL(a[i], a[j]), a[i] == a[j]);
    }
#endif

    printf("Testing greater-than-or-equal-to (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_GE, ge, 0, "GE", ">=");
#if 0
    for (int i = 0; i < A_SIZE; i++)
    {
        for (int j = 0; j < B_SIZE; j++)
            printf("x = %4d, y = %4d, GE(x,y) = %d, (x > y) = %d\n",
                   a[i], b[j], GE(a[i], b[j]), a[i] >= b[j]);
    }
#endif

    printf("Testing greater-than-or-equal-to (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_GE, ge, 0, "GE", ">=");
#if 0
    for (int i = 0; i < A_SIZE; i++)
    {
        for (int j = 0; j < A_SIZE; j++)
            printf("x = %4d, y = %4d, GE(x,y) = %d, (x > y) = %d\n",
                   a[i], a[j], GE(a[i], a[j]), a[i] >= a[j]);
    }
#endif

    return 0;
}
