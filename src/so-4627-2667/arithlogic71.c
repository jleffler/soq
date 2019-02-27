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
** Ignoring issues of overflow (small enough numbers), and mixed signs,
** the macros below work.
*/

/*
** From SO 4626-0444 (by Mitchel0022
** https://stackoverflow.com/users/5927758/mitchel0022, with assistance
** from Ryan https://stackoverflow.com/users/707111/ryan)
** If (a-b) is zero, the divisor is 1 and the result is 1.
** If (a-b) is not zero, the divisor is at least 2 and the result is 0.
** Note that EQ works without overflow if a and b are unsigned.
** They could, of course, be coerced into being unsigned.
*/
#define EQ(a, b)     (1 / (((a) - (b)) * ((a) - (b)) + 1))
#define NE(x, y)     (1 - EQ(x, y))

/*
** From SO 4627-2667 (by Ajay Brahmakshatriya
** https://stackoverflow.com/users/2858773/ajay-brahmakshatriya), comes
** the key observation that for integers, x/200 is 0 for x 0..199, and 1
** or more for higher values.
** Given EQ() and one of the other relational operators, we can easily
** deduce the other operators
*/
#define LT(x, y)     EQ((x)/(y), 0)
#define GE(x, y)     (1 - LT(x, y))
#define GT(x, y)     (GE(x, y) - EQ(x, y))
#define LE(x, y)     (1 - GT(x, y))

#include <stdio.h>
#include "stderr.h"

static inline int gt(int x, int y) { return x >  y; }
static inline int ge(int x, int y) { return x >= y; }
static inline int lt(int x, int y) { return x <  y; }
static inline int le(int x, int y) { return x <= y; }
static inline int eq(int x, int y) { return x == y; }
static inline int ne(int x, int y) { return x != y; }

static inline int func_EQ(int a, int b) { return EQ(a, b); }
static inline int func_NE(int a, int b) { return NE(a, b); }
static inline int func_GE(int a, int b) { return GE(a, b); }
static inline int func_GT(int a, int b) { return GT(a, b); }
static inline int func_LE(int a, int b) { return LE(a, b); }
static inline int func_LT(int a, int b) { return LT(a, b); }

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
                printf("x = %4d, y = %4d, %s(x,y) = %d, (x %s y) = %d%s\n",
                       data1[i], data2[j], name1, res1, op, res2, (res1 == res2) ? "" : " !!FAIL!!");
        }
    }
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    int verbose = (argc > 1);

    int a[] = { 1, 2, -4, 6, 10, 200 };
    enum { A_SIZE = sizeof(a) / sizeof(a[0]) };
    int b[] = { 1, 4, -4, 10, 20, 203 };
    enum { B_SIZE = sizeof(b) / sizeof(b[0]) };

    printf("Testing equality (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_EQ, eq, verbose, "EQ", "==");

    printf("Testing equality (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_EQ, eq, verbose, "EQ", "==");

    printf("Testing inequality (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_NE, ne, verbose, "NE", "!=");

    printf("Testing inequality (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_NE, ne, verbose, "NE", "!=");

    printf("Testing greater-than-or-equal-to (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_GE, ge, verbose, "GE", ">=");

    printf("Testing greater-than-or-equal-to (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_GE, ge, verbose, "GE", ">=");

    printf("Testing greater-than (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_GT, gt, verbose, "GT", ">");

    printf("Testing greater-than (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_GT, gt, verbose, "GT", ">");

    printf("Testing less-than-or-equal-to (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_LE, le, verbose, "LE", "<=");

    printf("Testing less-than-or-equal-to (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_LE, le, verbose, "LE", "<=");

    printf("Testing less-than (on arrays a and b)\n");
    test_array_pair(A_SIZE, a, B_SIZE, b, func_LT, lt, verbose, "LT", "<");

    printf("Testing less-than (on array a and itself)\n");
    test_array_pair(A_SIZE, a, A_SIZE, a, func_LT, lt, verbose, "LT", "<");

    return 0;
}
