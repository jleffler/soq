#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

static int roundup1(int x, int n)
{
    return((x + (n-1))/n);
}

static int roundup3(int x, int n)
{
    if (x > 0 && n > 0)
    {
        if (x >= INT_MAX - n)
            return((x - 1)/n + 1);
        else
            return((x + (n-1))/n);
    }
    else if (x < 0 && n < 0)
    {
        if (x == INT_MIN)
            return((x - 1)/n + 1);
        else
            return((x + (n-1))/n);
    }
    else
        return((x + (n-1))/n);
}

static int roundup2(int x, int n)
{
    return((x - 1) / n + 1);
}

int main(void)
{
    static const int values[] =
    {
        //INT_MIN,
        //INT_MIN+1, INT_MIN+2, INT_MIN+3, INT_MIN+4,
        //INT_MIN+5, INT_MIN+6, INT_MIN+7, INT_MIN+8,
        INT_MAX,
        INT_MAX-1, INT_MAX-2, INT_MAX-3, INT_MAX-4,
        INT_MAX-5, INT_MAX-6, INT_MAX-7, INT_MAX-8,
        //-20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10,
        //-9, -8, -7, -6, -5, -4, -3, -2, -1,
        0,
        +20, +19, +18, +17, +16, +15, +14, +13, +12, +11, +10,
        +9, +8, +7, +6, +5, +4, +3, +2, +1,
        //-56, -57, -58, -59, -60, -61, -62, -63, -64, -65,
        +56, +57, +58, +59, +60, +61, +62, +63, +64, +65,
    };
    enum { NUM_VALUES = sizeof(values) / sizeof(values[0]) };
    static const int divisors[] =
    {
        +10, +9, +8, +7, +6, +5, +4, +3, +2, +1,
        -10, -9, -8, -7, -6, -5, -4, -3, -2, -1,
    };
    enum { NUM_DIVISORS = sizeof(divisors) / sizeof(divisors[0]) };

    int pass = 0;
    int fail = 0;
    bool last_failed = false;
    int pass_line = 0;
    for (int i = 0; i < NUM_DIVISORS; i++)
    {
        for (int j = 0; j < NUM_VALUES; j++)
        {
            if (values[j] == INT_MIN && divisors[i] == -1)
                continue;
            int r1 = roundup1(values[j], divisors[i]);
            int r2 = roundup2(values[j], divisors[i]);
            int r3 = roundup2(values[j], divisors[i]);
            if (r1 != r2 || r1 != r3)
            {
                if (!last_failed)
                {
                    pass_line = 0;
                    putchar('\n');
                }
                printf("!! FAIL !! %d / %d gives r1 = %d r2 = %d, r3 = %d\n",
                       values[j], divisors[i], r1, r2, r3);
                last_failed = true;
                fail++;
            }
            else
            {
                //printf("== PASS == %d / %d gives r1 = %d r2 = %d, r3 = %d\n",
                //       values[j], divisors[i], r1, r2, r3);
                putchar('.');
                pass_line++;
                pass++;
                if (pass_line >= 60)
                {
                    pass_line = 0;
                    putchar('\n');
                }
                last_failed = false;
            }
        }
    }
    putchar('\n');
    printf("PASS %d; FAIL %d\n", pass, fail);
    return 0;
}

