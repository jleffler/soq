/* SO 3921-5727 */
#include <stdio.h>

extern int one(const char *s1, const char *s2);

static
int inner_one(const char *s1, const char *s2)
{
    if (s1[0] == '\0' && s2[0] == '\0')
        return 0;
    else if (s1[0] == s2[0])
        return 0 + inner_one(s1+1, s2+1);
    else if (s1[1] == s2[0])
        return 1 + inner_one(s1+1, s2+0);
    else if (s1[0] == s2[1])
        return 1 + inner_one(s1+0, s2+1);
    else if (s1[1] == s2[1])
        return 1 + inner_one(s1+1, s2+1);
    else
        return 2;
}

int one(const char *s1, const char *s2)
{
    return inner_one(s1, s2) == 1 ? 1 : 0;
}

//int one(const char *s1, const char *s2)
//{
//    int result = inner_one(s1, s2) == 1 ? 1 : 0;
//    printf("%d\n", result);
//    return result;
//}

static int test_one(const char *s1, const char *s2, int answer)
{
    int fail;
    int result = one(s1, s2);
    if (result == answer)
    {
        printf("** PASS ** [%s] <=> [%s] yields %d as required\n", s1, s2, result);
        fail = 0;
    }
    else
    {
        printf("!! FAIL !! [%s] <=> [%s] yields %d instead of %d\n",
                s1, s2, result, answer);
        fail = 1;
    }
    return fail;
}

struct pair
{
    const char *s1;
    const char *s2;
    int         answer;
};

static int test_both_ways(const struct pair *test)
{
    return test_one(test->s1, test->s2, test->answer) +
           test_one(test->s2, test->s1, test->answer);
}

int main(void)
{
    struct pair tests[] =
    {
        { "abcde",  "abcdf", 1 },
        { "abc",    "abc",   0 },
        { "dor",    "dors",  1 },
        { "Xabcd",  "abcd",  1 },
        { "Xabcd",  "Yabcd", 1 },
        { "abXcd",  "abcd",  1 },
        { "abXcd",  "abYcd", 1 },
        { "abXZcd", "abYcd", 0 },
        { "abcde",  "acbde", 0 },
        { "abcc",   "bccc",  0 },
        { "wxyz",   "bccc",  0 },
        { "wx",     "bc",    0 },
        { "wx",     "b",     0 },
        { "bx",     "b",     1 },
        { "wb",     "b",     1 },
        { "",       "",      0 },
        { "w",      "b",     1 },
        { "abbb",   "bccc",  0 },
    };
    enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };

    int fail = 0;
    for (int i = 0; i < NUM_TESTS; i++)
        fail += test_both_ways(&tests[i]);

    if (fail != 0)
    {
        printf("Ooops! %d failures\n", fail);
        return 1;
    }
    puts("OK!");
    return 0;
}
