#include <stdio.h>

void convert(long, char[]);

char *one[] = {" ", " one", " two", " three", " four", " five", " six", " seven", "eight", " Nine", " ten", " eleven", " twelve", " thirteen", " fourteen", "fifteen", " sixteen", " seventeen", " eighteen", " nineteen"};
char *ten[] = {" ", " ", " twenty", " thirty", " forty", " fifty", " sixty", "seventy", " eighty", " ninety"};

int main(void)
{
    long n;
    printf("Enter any 9 digit no: ");
    if (scanf("%9ld", &n) != 1)
	return(1);
    if (n <= 0)
        printf("Enter numbers greater than 0\n");
    else if (n >= 1000000000)
        printf("Enter numbers less than 1000000000\n");
    else
    {
        convert((n / 10000000), "crore");
        convert(((n / 100000) % 100), "lakh");
        convert(((n / 1000) % 100), "thousand");
        convert(((n / 100) % 10), "hundred");
        convert((n % 100), " ");
        putchar('\n');
    }
    return(0);
}

void convert(long n, char ch[])
{
    (n > 19) ? printf("%s %s ", ten[n / 10], one[n % 10]) : printf("%s ", one[n]);
    if (n)
        printf("%s ", ch);
}
