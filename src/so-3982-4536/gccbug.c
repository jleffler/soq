/* SO 3982-4536 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUES  4
#define MAX_NAMELEN 32

typedef struct header
{
    char    r_name[MAX_NAMELEN];
    char    c_name[MAX_VALUES][MAX_NAMELEN];
} header;

static void err_format(const char *tag, const char *buffer);
static void err_error(const char *msg);

static void read_header(header *hdr)
{
    char   *buffer = 0;
    size_t  buflen = 0;
    char    delim;

    if (getline(&buffer, &buflen, stdin) == -1)
        err_error("Failed to read header line");
    int c_index = 0;
    printf("HL[%s]\n", buffer);
    if (sscanf(buffer + c_index, "%31[^\t\n\r]%1[\t\n\r]%n", hdr->r_name, &delim, &c_index) != 2)
        err_format("header row name", buffer);

    assert(c_index > 0);
    printf("O[%d] N[%s] R[%s]\n", c_index, hdr->r_name, buffer + c_index);
    assert(!isspace(buffer[c_index]));
    for (int i = 0; i < MAX_VALUES; i++)
    {
        int extra;
        assert(buffer[c_index] != '\0');
        if (sscanf(buffer + c_index, "%31[^\t\n\r]%1[\t\n\r]%n", hdr->c_name[i], &delim, &extra) != 2)
        {
            fprintf(stderr, "Column %d\n", i);
            err_format("header column name", buffer);
        }

        assert(extra > 0);
        c_index += extra;
        printf("%.2d: O[%d] E[%d] N[%s] R[%s]\n", i, c_index, extra, hdr->c_name[i], buffer + c_index);
        fflush(0);
        assert(!isspace(buffer[c_index]));
    }
    free(buffer);
}

int main(void)
{
    header  hdr_1;
    read_header(&hdr_1);
    return 0;
}

static void err_format(const char *tag, const char *buffer)
{
    fprintf(stderr, "Format error for %s in line [%s]\n", tag, buffer);
    exit(1);
}

static void err_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
