/* SO 1375-5571 - Sign-Extending a int */

#include <assert.h>
#include <limits.h>
#include <stdio.h>

extern int getFieldSignExtended(int value, int hi, int lo);

enum { INT_BITS = CHAR_BIT * sizeof(int) };

int getFieldSignExtended(int value, int hi, int lo)
{
    assert(lo >= 0);
    assert(hi > lo);
    assert(hi < INT_BITS - 1);
    int bits = (value >> lo) & ((1 << (hi - lo + 1)) - 1);
    if (bits & (1 << (hi - lo)))
        return(bits | (~0U << (hi - lo)));
    else
        return(bits);
}

static const struct
{
    int  value;
    int  hi;
    int  lo;
    int  wanted;
} tests[] =
{
    {   0x0F,  1,  0,   -1 },
    {   0x0F,  2,  0,   -1 },
    {   0x0F,  2,  1,   -1 },
    {   0x0F,  3,  1,   -1 },
    {   0x0F,  4,  2,   +3 },
    {   0x0F,  5,  0,  +15 },
    {   0x0F,  5,  1,   +7 },
    {   0x0F,  5,  2,   +3 },
    {   0x0F,  5,  3,   +1 },
    {   0x0F,  5,  4,    0 },
    {   0x03,  2,  0,   +3 },
    {   0xF3,  2,  0,   +3 },
    {   0xF3,  3,  0,   +3 },
    {   0xF3,  4,  0,  -13 },
    {   0xF3,  5,  0,  -13 },
    {   0xF3,  6,  0,  -13 },
    {   0xF3,  7,  0,  -13 },
    {   0xF3,  7,  1,   -7 },
    {   0xF3,  7,  2,   -4 },
    {   0xF3,  7,  3,   -2 },
    {   0xF3,  7,  4,   -1 },
    {   0xF3,  8,  0, 0xF3 },
};
enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };
static const char s_pass[] = "== PASS ==";
static const char s_fail[] = "!! FAIL !!";

static void systematic_test(void)
{
    int fail = 0;
    for (int i = 0; i < NUM_TESTS; i++)
    {
        char const *pf = s_fail;
        int actual = getFieldSignExtended(tests[i].value, tests[i].hi, tests[i].lo);
        if (actual == tests[i].wanted)
            pf = s_pass;
        else
            fail++;
        printf("%s GFSX(%+4d = 0x%.4X, %d, %d) = %+4d = 0x%.8X (wanted %+4d = 0x%.8X)\n",
               pf, tests[i].value, tests[i].value, tests[i].hi, tests[i].lo, actual, actual,
               tests[i].wanted, tests[i].wanted);
    }
    printf("%s\n", (fail == 0) ? s_pass : s_fail);
}

static void exhaustive_test(void)
{
    int value = 0x5FA03CE7;
    for (int i = 1; i < INT_BITS - 1; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int actual = getFieldSignExtended(value, i, j);
            printf("%11sGFSX(%d = 0x%X, %2d, %2d) = %+10d = 0x%.8X\n", "",
                    value, value, i, j, actual, actual);
        }
    }
}

int main(void)
{
    int result1 = getFieldSignExtended(15, 2, 0);
    int result2 = getFieldSignExtended( 3, 2, 0);
    printf("GFSX(15, 2, 0) = %+d = 0x%.8X\n", result1, result1);
    printf("GFSX( 3, 2, 0) = %+d = 0x%.8X\n", result2, result2);

    printf("\nSystematic test\n");
    systematic_test();

    printf("\nExhaustive test\n");
    exhaustive_test();

    return(0);
}
