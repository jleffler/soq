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

#include <stdio.h>

static char *powa(unsigned int code, char *buffer)
{
    unsigned int div = code / 26;
    unsigned int rem = code % 26;
    if (div > 0)
        buffer = powa(div-1, buffer);
    *buffer++ = rem + 'A';
    *buffer = '\0';
    return buffer;
}

int main(void)
{
    char buffer[32];
    unsigned int col, row;

    printf("Enter column and row numbers: ");
    if (scanf("%u %u", &col, &row) == 2)
    {
        if (col == 0 || row == 0)
            fprintf(stderr, "Both row and column must be larger than zero (row = %u, col = %u)\n", row, col);
        else
        {
            char *end = powa(col-1, buffer);
            snprintf(end, sizeof(buffer) - (end - buffer), "%u", row);
            printf("Col %u, Row %u, Cell %s\n", col, row, buffer);
        }
    }
    return 0;
}

