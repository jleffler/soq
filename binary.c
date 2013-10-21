#include <stdio.h>

static
void print_binary(unsigned char x)
{
    for (int b = 128; b != 0; b /= 2)
    {
        printf("%d", (b & x) != 0);
        x &= ~b;
    }
}

static
void format_binary(unsigned char x, char buffer[static 9])
{
    for (int b = 128; b != 0; b /= 2)
    {
        *buffer++ = ((b & x) != 0) ? '1' : '0';
        x &= ~b;
    }
    *buffer = '\0';
}

int main(void)
{
    for (int i = 0; i < 256; i++)
    {
        char str[9];
        printf("%3d = ", i);
        print_binary(i);
        putchar(' ');
        printf("%3d = ", i);
        format_binary(i, str);
        printf("%s", str);
        putchar(((i % 2) == 1) ? '\n' : ' ');
    }
    return 0;
}
