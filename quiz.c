#include <stdio.h>

/* You can have 0, 1 or 2 wins */

typedef struct Win { unsigned char num; unsigned char letter; } Win;
static Win windata[2];
static int wins;

static void report_win(int win, int streak, int start, char letter, const char symbol[5])
{
    printf("Win %d: %d-%c starting at %d in [%.5s]\n", win, streak, letter, start, symbol);
    windata[wins].num = streak;
    windata[wins].letter = letter;
    wins++;
}

static int check_win(const char symbol[5])
{
    int streak = 0;
    int start = -1;
    char letter = 0;
    int wins = 0;

    for (int i = 1; i < 5; i++)
    {
        if (symbol[i] == 'F' || symbol[i-1] == 'F' || symbol[i] == symbol[i-1])
        {
            /* Current and prior symbols are the same, or at least one is 'F' */
            if (start == -1)
            {
                streak = 2;
                start  = i-1;
                letter = symbol[i];
                if (letter == 'F')
                    letter = symbol[i-1];
            }
            else if (symbol[i] != 'F' && letter != 'F' && symbol[i] != letter)
            {
                /* End of a streak -- for example: AFB, FAFB, AAB, FFAB, AFFB */
                if (streak >= 3)
                    report_win(++wins, streak, start, letter, symbol);
                /* Reset start ... */
                if (symbol[i-1] != 'F')
                {
                    streak = 0;
                    start = -1;
                }
                else
                {
                    /* Step back to first 'F' not preceded by another 'F' */
                    int j = i;
                    while (symbol[j-1] == 'F')
                        j--;
                    start = j;
                    streak = i - j + 1;
                    letter = symbol[i];
                }
            }
            else
            {
                if (letter == 'F')
                    letter = symbol[i];
                streak++;
            }
        }
        else
        {
            /* Mismatch between current and prior symbol */
            if (streak >= 3)
                report_win(++wins, streak, start, letter, symbol);
            streak = 0;
            start = -1;
        }
    }
    if (streak >= 3)
        report_win(++wins, streak, start, letter, symbol);
    if (wins == 0)
        printf("No win for [%.5s]\n", symbol);
    return wins;
}

#include <time.h>
#include <stdlib.h>

int main(void)
{
    const struct test
    {
        char *symbols;
        int   wins;
        Win   windata[2];
    } tests[] =
    {
        { "AAAAA", 1, { { 5, 'A' }, { 0,   0 } } },
        { "AAAAB", 1, { { 4, 'A' }, { 0,   0 } } },
        { "AAABB", 1, { { 3, 'A' }, { 0,   0 } } },
        { "AAABC", 1, { { 3, 'A' }, { 0,   0 } } },
        { "AABBC", 0, { { 0,   0 }, { 0,   0 } } },
        { "AAFBB", 2, { { 3, 'A' }, { 3, 'B' } } },
        { "AAFBC", 1, { { 3, 'A' }, { 0,   0 } } },
        { "AAFFB", 2, { { 4, 'A' }, { 3, 'B' } } },
        { "ABCDE", 0, { { 0,   0 }, { 0,   0 } } },
        { "ABCDF", 0, { { 0,   0 }, { 0,   0 } } },
        { "ABCFE", 0, { { 0,   0 }, { 0,   0 } } },
        { "AFABB", 1, { { 3, 'A' }, { 0,   0 } } },
        { "AFFFB", 2, { { 4, 'A' }, { 4, 'B' } } },
        { "AFAFA", 1, { { 5, 'A' }, { 0,   0 } } },
        { "AFAFB", 1, { { 4, 'A' }, { 0,   0 } } },
        { "AFFFF", 1, { { 5, 'A' }, { 0,   0 } } },
        { "BAAAA", 1, { { 4, 'A' }, { 0,   0 } } },
        { "BAAAC", 1, { { 3, 'A' }, { 0,   0 } } },
        { "BCAAA", 1, { { 3, 'A' }, { 0,   0 } } },
        { "FAABB", 1, { { 3, 'A' }, { 0,   0 } } },
        { "FFAAB", 1, { { 4, 'A' }, { 0,   0 } } },
        { "FFABB", 1, { { 3, 'A' }, { 0,   0 } } },
        { "FFFAB", 1, { { 4, 'A' }, { 0,   0 } } },
        { "FFFBB", 1, { { 5, 'B' }, { 0,   0 } } },
        { "FFFFA", 1, { { 5, 'A' }, { 0,   0 } } },
        { "FFFFF", 1, { { 5, 'F' }, { 0,   0 } } },
    };
    enum { NUM_TESTS = sizeof(tests)/sizeof(tests[0]) };

    int pass = 0;
    for (size_t i = 0; i < NUM_TESTS; i++)
    {
        wins = 0;
        int num;
        if ((num = check_win(tests[i].symbols)) == tests[i].wins)
        {
            int fail = 0;
            for (int n = 0; n < num; n++)
            {
                if (windata[n].num != tests[i].windata[n].num ||
                    windata[n].letter != tests[i].windata[n].letter)
                {
                    printf("!! FAIL !! (wanted %d-%c, actual %d-%c)\n",
                           tests[i].windata[n].num, tests[i].windata[n].letter,
                           windata[n].num, windata[n].letter);
                    fail++;
                }
            }
            if (fail == 0)
                pass++;
        }
        else
            printf("!! FAIL !! (%s: wanted %d, actual %d)\n",
                   tests[i].symbols, tests[i].wins, num);
    }
    if (pass == NUM_TESTS)
        printf("== PASS ==\n");
    else
        printf("!! FAIL !! (%d pass, %d fail)\n", pass, NUM_TESTS-pass);

    printf("\nRandom play:\n");
    srand(time(0));
    for (int i = 0; i < 100; i++)
    {
        char symbols[5];
        for (int j = 0; j < 5; j++)
        {
            symbols[j] = rand() % 6 + 'A';
        }
        check_win(symbols);
    }

    return (pass != NUM_TESTS); /* 0 success, 1 failure */
}
