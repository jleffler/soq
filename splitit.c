/* SO 32428769 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char  str[] = "(I) 44like22 .cookies. ,This, /is\\ ?tricky?";
    const char *s = str;

    char   out[2 * sizeof(str)];
    char  *ptr[sizeof(str)];
    char **p = ptr;
    char  *o = out;
    int    n = 0;

    /* ( I ) 44 like 22 . cookies . , This , / is \ ? tricky ? */

    int c;

    printf("Whole string: <<%s>>\n", str);

    while ((c = (unsigned char)*s++) != '\0')
    {
        if (isdigit(c))
        {
            *p++ = o;
            *o++ = c;
            while (isdigit((unsigned char)*s))
                *o++ = *s++;
            *o++ = '\0';
            n++;
        }
        else if (isalpha(c))
        {
            *p++ = o;
            *o++ = c;
            while (isalpha((unsigned char)*s))
                *o++ = *s++;
            *o++ = '\0';
            n++;
        }
        else if (ispunct(c))
        {
            *p++ = o;
            *o++ = c;
            while (ispunct((unsigned char)*s))
                *o++ = *s++;
            *o++ = '\0';
            n++;
        }
        else if (!isspace(c))
        {
            printf("Hmmm: don't know how to classify %d (%c)\n", c, c);
        }
    }

    for (int i = 0; i < n; i++)
        printf("Fragment[%2d] = %s\n", i, ptr[i]);

    return 0;
}
