#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

static void fileManipulator(FILE *source, FILE *dest);
static void manipulateToken(wint_t token, FILE *dest);

int main(int argc, const char *argv[])
{
    FILE    *source, *dest;
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s input output\n", argv[0]);
        exit(1);
    }

    setlocale(LC_ALL, "");

    source = fopen(argv[1], "r");
    if (source == NULL)
    {
        fprintf(stderr, "could not open source file %s\n", argv[1]);
        exit(1);
    }

    dest = fopen(argv[2], "w+");
    if (dest == NULL)
    {
        fclose(source);
        fprintf(stderr, "could not open dest file %s\n", argv[2]);
        exit(1);
    }

    fwide(source, 1);
    fwide(dest, 1);

    fileManipulator(source, dest);

    fclose(source);
    fclose(dest);

    return 0;
}

static void fileManipulator(FILE *source, FILE *dest)
{
    wint_t token;

    while (WEOF != (token = getwc(source)))
    {
        manipulateToken(token, dest);
    }
}

static void manipulateToken(wint_t token, FILE *dest)
{
    wchar_t *pre = L"- ";
    wchar_t *post = L" -\n";

    if (EOF == fputws(pre, dest))
    {
        fprintf(stderr, "Failed to write prefix string\n");
        exit(1);
    }
    if (WEOF == fputwc(token, dest))
    {
        fprintf(stderr, "Failed to write wide character %d\n", (int)token);
        exit(1);
    }
    if (EOF == fputws(post, dest))
    {
        fprintf(stderr, "Failed to write suffix string\n");
        exit(1);
    }
}
