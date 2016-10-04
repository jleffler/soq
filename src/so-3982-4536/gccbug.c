/* SO 3982-4536 */
#include <stdio.h>

enum { MAX_VALUES = 5 };
enum { MAX_NAMELEN = 32 };

int main(void)
{
    char    c_name[MAX_VALUES][MAX_NAMELEN];
    char   *buffer = 0;
    size_t  buflen = 0;
    char    delim;
    int     length;

    if ((length = getline(&buffer, &buflen, stdin)) == -1)
        return 1;
    buffer[length-1] = '\t';
    int offset = 0;

#ifndef SKIP_FIRST_SSCANF
    if (sscanf(buffer + offset, "%31[^ \t\n\r]%1[ \t\n\r]%n", c_name[0], &delim, &offset) != 2)
        return 1;
    printf("    O[%2d]      N[%s] R[%s]\n", offset, c_name[0], buffer + offset);
#endif

    for (int i = 1; i < MAX_VALUES; i++)
    {
        int extra;
        if (sscanf(buffer + offset, "%31[^ \t\n\r]%1[ \t\n\r]%n", c_name[i], &delim, &extra) != 2)
        {
            fprintf(stderr, "sscanf() failed (field %d, offset %d) at [%s]\n", i, offset, buffer + offset);
            return 1;
        }
        offset += extra;
        printf("%.2d: O[%2d] E[%d] N[%s] R[%s]\n", i, offset, extra, c_name[i], buffer + offset);
    }
    return 0;
}
