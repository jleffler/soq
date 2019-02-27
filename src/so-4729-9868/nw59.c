/* SO 4729-9868 */
#include <stdio.h>

void convert(long, char[]);

static int read_number(long *n)
{
    printf("Enter any 9 digit no: ");
    fflush(stdout);
    return scanf("%9ld", n);
}

int main(void)
{
    long n;
    while (read_number(&n) == 1)
    {
        if (n < 0)
            printf("Enter numbers greater than 0\n");
        else if (n >= 1000000000)
            printf("Enter numbers less than 1000000000\n");
        else if (n == 0)
            printf("zero\n");
        else
        {
            convert((n / 10000000), "crore");
            convert(((n / 100000) % 100), "lakh");
            convert(((n / 1000) % 100), "thousand");
            convert(((n / 100) % 10), "hundred");
            convert((n % 100), "");
            putchar('\n');
        }
    }
    putchar('\n');
    return 0;
}

static const char * const one[] =
{
    "", "one", "two", "three", "four", "five", "six", "seven", "eight",
    "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen"
};

static const char * const ten[] =
{
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy",
    "eighty", "ninety"
};

void convert(long n, char ch[])
{
    if (n > 19)
    {
        if (n % 10 != 0)
            printf("%s-%s ", ten[n / 10], one[n % 10]);
        else
            printf("%s ", ten[n / 10]);
    }
    else if (n != 0)
        printf("%s ", one[n]);
    if (n != 0)
        printf("%s ", ch);
}
