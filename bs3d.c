#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int c0;
    while ((c0 = getchar()) != EOF)
    {
        if (c0 != '\\')
        {
            putchar(c0);
            continue;
        }
        int c1 = getchar();
        if (c1 == EOF)
        {
            putchar(c0);
            break;
        }
        if (!isdigit(c1))
        {
            putchar(c0);
            ungetc(c1, stdin);
            continue;
        }
        int c2 = getchar();
        if (c2 == EOF)
        {
            putchar(c0);
            putchar(c1);
            break;
        }
        if (!isdigit(c2))
        {
            putchar(c0);
            putchar(c1);
            ungetc(c2, stdin);
            continue;
        }
        int c3 = getchar();
        if (c3 == EOF)
        {
            putchar(c0);
            putchar(c1);
            putchar(c2);
            break;
        }
        if (!isdigit(c3))
        {
            putchar(c0);
            putchar(c1);
            putchar(c2);
            ungetc(c3, stdin);
            continue;
        }
        putchar('\n');
        putchar(c0);
        putchar(c1);
        putchar(c2);
        putchar(c3);
    }
    return 0;
}
