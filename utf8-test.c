#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 40

int main(void)
{
    char buf[SIZE + 1];
    char *pat = "привет мир";
    char str[SIZE + 2];

    FILE *f1;
    FILE *f2;

    f1 = fopen("вход", "r");
    f2 = fopen("выход", "w");
    if (f1 == 0 || f2 == 0)
    {
        fprintf(stderr, "Failed to open one or both files\n");
        return(1);
    }

    size_t nbytes;
    if ((nbytes = fread(buf, 1, SIZE, f1)) > 0)
    {
        buf[nbytes] = 0;

        if (strncmp(buf, pat, nbytes) == 0)
        {
            sprintf(str, "%.*s\n", (int)nbytes, buf);
            fwrite(str, 1, nbytes, f2);
        }
    }

    fclose(f1);
    fclose(f2);

    return(0);
}
