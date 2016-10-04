/* SO 3982-4536 */
#include <stdio.h>

enum { MAX_VALUES = 4 };
enum { MAX_NAMELEN = 32 };

typedef struct header
{
    char    r_name[MAX_NAMELEN];
    char    c_name[MAX_VALUES][MAX_NAMELEN];
} header;

int main(void)
{
    header  hdr;
    char   *buffer = 0;
    size_t  buflen = 0;
    char    delim;
    int     length;

    if ((length = getline(&buffer, &buflen, stdin)) == -1)
        return 1;
    buffer[length-1] = '\t';
    int offset = 0;

#ifndef SKIP_FIRST_SSCANF
    if (sscanf(buffer + offset, "%31[^\t\n\r]%1[\t\n\r]%n", hdr.r_name, &delim, &offset) != 2)
        return 1;
    printf("    O[%2d]      N[%s] R[%s]\n", offset, hdr.r_name, buffer + offset);
#endif

    for (int i = 0; i < MAX_VALUES; i++)
    {
        int extra;
        if (sscanf(buffer + offset, "%31[^\t\n\r]%1[\t\n\r]%n", hdr.c_name[i], &delim, &extra) != 2)
        {
            fprintf(stderr, "sscanf() failed (field %d, offset %d) at [%s]\n", i, offset, buffer + offset);
            return 1;
        }
        offset += extra;
        printf("%.2d: O[%2d] E[%d] N[%s] R[%s]\n", i, offset, extra, hdr.c_name[i], buffer + offset);
    }
    return 0;
}
