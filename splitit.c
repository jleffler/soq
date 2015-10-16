/* SO 32428769 Split string at different types of characters into separate strings */
/* OP not ready for pointers to functions */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

 static void split_string(const char *buffer, size_t buflen)
 {
    const char *s = buffer;
    char   out[2 * buflen];
    char  *ptr[buflen];
    char **p = ptr;
    char  *o = out;
    int    n = 0;
    int c;

    printf("Whole string: <<%s>>\n", buffer);

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
}

int main(void)
{
    const char  str[] = "(I) 44like22 .cookies. ,This, /is\\ ?tricky?";
    split_string(str, sizeof(str));

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), stdin) != 0)
        split_string(buffer, strlen(buffer)+1);

    return 0;
}
