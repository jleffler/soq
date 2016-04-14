#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define SIZE 40

int main(void)
{
    wchar_t buf[SIZE + 1];
    wchar_t *pat = L"привет мир\n";
    wchar_t str[SIZE + 2] = L"";

    setlocale(LC_ALL, "");

    FILE *f1 = fopen("вход", "r");
    FILE *f2 = fopen("выход", "w");
    if (f1 == 0 || f2 == 0)
    {
        fprintf(stderr, "Failed to open one or both files\n");
        return(1);
    }
    fwide(f1, 1);
    fwide(f2, 1);

    if (fgetws(buf, SIZE, f1) != 0)
    {
        if (wcscmp(buf, pat) == 0)
        {
            buf[wcscspn(buf, L"\n")] = L'\0';
            swprintf(str, sizeof(str)/sizeof(str[0]), L"[%ls]\n", buf);
            fputws(str, f2);
            wprintf(L"buffer and pattern are equal: [%ls]\n", buf);
        }
        else
        {
            fprintf(stderr, "wcscmp() failed\n");
            int len = wcslen(pat);
            printf("pat:");
            for (int i = 0; i < len; i++)
                printf(" %.4X", pat[i]);
            putchar('\n');
            len = wcslen(buf);
            printf("buf:");
            for (int i = 0; i < len; i++)
                printf(" %.4X", buf[i]);
            putchar('\n');
        }
    }
    else
        fprintf(stderr, "fgetws() failed\n");

    fclose(f1);
    fclose(f2);

    return(0);
}
