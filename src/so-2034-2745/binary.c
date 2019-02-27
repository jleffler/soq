#include <stdio.h>

static
void print_binary8(unsigned char x)
{
    for (int b = 128; b != 0; b /= 2)
    {
        printf("%d", (b & x) != 0);
        x &= ~b;
    }
}

static
void format_binary8(unsigned char x, char buffer[static 9])
{
    for (int b = 128; b != 0; b /= 2)
    {
        *buffer++ = ((b & x) != 0) ? '1' : '0';
        x &= ~b;
    }
    *buffer = '\0';
}

static unsigned char scan_binary8(char const *binary)
{
    unsigned char u = 0;
    char c;
    while ((c = *binary++) != '\0')
    {
        /* GIGO: if it isn't a '0' or a '1', you get what you deserve! */
        u = (u << 1) | (c - '0');
    }
    return u;
}

static void print_binary16(unsigned short x)
{
    for (int b = 32768; b != 0; b /= 2)
    {
        printf("%d", (b & x) != 0);
        x &= ~b;
    }
}

static
void format_binary16(unsigned short x, char buffer[static 17])
{
    for (int b = 32768; b != 0; b /= 2)
    {
        *buffer++ = ((b & x) != 0) ? '1' : '0';
        x &= ~b;
    }
    *buffer = '\0';
}

static unsigned short scan_binary16(char const *binary)
{
    unsigned short u = 0;
    char c;
    while ((c = *binary++) != '\0')
    {
        /* GIGO: if it isn't a '0' or a '1', you get what you deserve! */
        u = (u << 1) | (c - '0');
    }
    return u;
}

int main(void)
{
    /* SO 2034-2745 - weird calculation */
    /* Working in hex - simpler */
    int p = 0x15C;
    for (int i = 0; i < 16; i++)
    {
        if ((p & (1 << i)) == 0x04)
            printf("Shift %d yields 0x%.4X from 0x%.4X and 0x%.4X\n",
                   i, (p & (1 << i)), p, (1 << i));
    }

    /* Working in binary - harder */
    char b1[] = "101011100";
    char b2[] = "100";
    unsigned u1 = scan_binary16(b1);
    unsigned u2 = scan_binary16(b2);

    /* Force use of print_binary16() and format_binary16() */
    /* Demonstrates fixed bug in prior version of code */
    printf("~u2 = 0b");
    print_binary16(~u1);
    putchar('\n');
    char buffer[17];
    format_binary16(~u2, buffer);
    printf("~u2 = 0b%s\n", buffer);

    for (int i = 0; i < 16; i++)
    {
        if ((u1 & (1 << i)) == u2)
        {
            char str[17];
            printf("Shift %d yields ", i);
            print_binary16(p & (1 << i));
            printf(" from ");
            print_binary16(u1);
            format_binary16(1 << i, str);
            printf(" and %s\n", str);
        }
    }

    for (int i = 0; i < 256; i++)
    {
        char str[9];
        printf("%3d = ", i);
        print_binary8(i);
        putchar(' ');
        printf("%3d = ", i);
        format_binary8(i, str);
        printf("%s", str);
        printf(" 0x%.2X", scan_binary8(str));
        putchar(((i % 2) == 1) ? '\n' : ' ');
    }
    return 0;
}
