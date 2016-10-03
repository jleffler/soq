/* SO 3982-4536 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUES  4
#define MAX_NAMELEN 32

typedef struct header
{
    char    r_name[MAX_NAMELEN];
    char    c_name[MAX_VALUES][MAX_NAMELEN];
} header;

static void err_format(const char *tag, const char *buffer);

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
    if (sscanf(buffer + offset, "%31[^\t\n\r]%1[\t\n\r]%n", hdr.r_name, &delim, &offset) != 2)
        err_format("header row name", buffer);

    printf("    O[%2d]      N[%s] R[%s]\n", offset, hdr.r_name, buffer + offset);
    for (int i = 0; i < MAX_VALUES; i++)
    {
        int extra;
        if (sscanf(buffer + offset, "%31[^\t\n\r]%1[\t\n\r]%n", hdr.c_name[i], &delim, &extra) != 2)
            err_format("header column name", buffer);
        offset += extra;
        printf("%.2d: O[%2d] E[%d] N[%s] R[%s]\n", i, offset, extra, hdr.c_name[i], buffer + offset);
    }
    return 0;
}

static void err_format(const char *tag, const char *buffer)
{
    fprintf(stderr, "Format error for %s in line [%s]\n", tag, buffer);
    exit(1);
}
