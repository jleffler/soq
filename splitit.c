/* SO 32428769 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char  str[] = "(I) 44like22 .cookies. ,This, /is\\ ?tricky?"
        "\nBut (as he said, \"Isn't it delicous fun!\"), he vanished.";
    const char *s = str;

    char   out[2 * sizeof(str)];
    char  *ptr[sizeof(str)];
    char **p = ptr;
    char  *o = out;
    int    n = 0;
    int    c;

    printf("Whole string: <<%s>>\n", str);

    while ((c = (unsigned char)*s++) != '\0')
    {
        int (*ctype)(int c) = 0;
        if (isdigit(c))
            ctype = isdigit;
        else if (isalpha(c))
            ctype = isalpha;
        else if (ispunct(c))
            ctype = ispunct;
        else if (isspace(c))
            continue;
        else
        {
            printf("Hmmm: don't know how to classify %d (%c)\n", c, c);
            continue;
        }
        *p++ = o;
        *o++ = c;
        while ((*ctype)((unsigned char)*s))
            *o++ = *s++;
        *o++ = '\0';
        n++;
    }

    for (int i = 0; i < n; i++)
        printf("Fragment[%2d] = %s\n", i, ptr[i]);

    return 0;
}
