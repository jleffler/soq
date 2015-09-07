/*
** Convert column and row number into Excel (Spreadsheet) alphanumeric reference
** 1,1     => A1
** 27,1    => AA1
** 37,21   => AK21
** 491,321 => RW321
** 3941,87 => EUO87
** From StackOverflow question 7651397 on 2011-10-04:
** http://stackoverflow.com/questions/7651397/calc-cell-convertor-in-c
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char *xl_encode(unsigned row, char *buffer)
{
    unsigned div = row / 26;
    unsigned rem = row % 26;
    if (div > 0)
        buffer = xl_encode(div-1, buffer);
    *buffer++ = rem + 'A';
    *buffer = '\0';
    return buffer;
}

static char *xl_row_encode(unsigned row, char *buffer)
{
    return(xl_encode(row-1, buffer));
}

static unsigned xl_row_decode(const char *code)
{
    unsigned char c;
    unsigned r = 0;
    while ((c = *code++) != '\0')
    {
        if (!isalpha(c))
            break;
        c = toupper(c);
        r = r * 26 + c - 'A' + 1;
    }
    return r;
}

static const struct
{
    unsigned col;
    unsigned row;
    char     cell[10];
} tests[] =
{
    {     1,     1, "A1"       },
    {    26,     2, "Z2"       },
    {    27,     3, "AA3"      },
    {    52,     4, "AZ4"      },
    {    53,     5, "BA5"      },
    {   676,     6, "YZ6"      },
    {   702,     7, "ZZ7"      },
    {   703,     8, "AAA8"     },
    {   728,     9, "AAZ9"     },
};
enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };

int main(void)
{
    char buffer[32];
    int pass = 0;

    for (int i = 0; i < NUM_TESTS; i++)
    {
        char *end = xl_row_encode(tests[i].col, buffer);
        snprintf(end, sizeof(buffer) - (end - buffer), "%u", tests[i].row);
        unsigned n = xl_row_decode(buffer);
        const char *pf = "FAIL";

        if (tests[i].col == n && strcmp(tests[i].cell, buffer) == 0)
        {
            pf = "PASS";
            pass++;
        }
        printf("%s: Col %3u, Row %3u, Cell (wanted: %-8s vs actual: %-8s) Col = %3u\n",
               pf, tests[i].col, tests[i].row, tests[i].cell, buffer, n);
    }
    if (pass == NUM_TESTS)
        printf("== PASS == %d tests OK\n", pass);
    else
        printf("!! FAIL !! %d out of %d failed\n", (NUM_TESTS - pass), NUM_TESTS);

    return (pass == NUM_TESTS) ? 0 : 1;
}

