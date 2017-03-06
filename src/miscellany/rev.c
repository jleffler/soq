/* A multitude of string reversal algorithms */
#include <stdio.h>
#include <string.h>

static char *reverse1(char *string)
{
    if (*string != '\0')
    {
        for (int i = 0, j = strlen(string) - 1; i < j; i++, j--)
        {
            char c = string[i];
            string[i] = string[j];
            string[j] = c;
        }
    }
    return string;
}

static char *reverse2(char *string)
{
    char *str = string;
    char *ptr = str + strlen(str);
    while (str < --ptr)
    {
        char c = *str;
        *str++ = *ptr;
        *ptr = c;
    }
    return string;
}

static char *reverse3(char *string)
{
    int i = 0;
    int j = strlen(string);
    while (i < --j)
    {
        char c = string[i];
        string[i++] = string[j];
        string[j] = c;
    }
    return string;
}

static char *reverse4(char *string)
{
    int i;
    int len = strlen(string);
    for (i = 0; i < len / 2; i++)
    {
        char c              = string[i];
        string[i]           = string[len - i - 1];
        string[len - i - 1] = c;
    }
    return string;
}

static void tester(int argc, char **argv, char *(*reverse)(char *str))
{
    for (int i = 0; i < argc; i++)
    {
        if (i != 0)
            putchar(' ');
        printf("[%s]", reverse(argv[i]));
    }
    putchar('\n');
}

int main(int argc, char **argv)
{
    tester(argc, argv, reverse1);
    tester(argc, argv, reverse2);
    tester(argc, argv, reverse3);
    tester(argc, argv, reverse4);
    return 0;
}
