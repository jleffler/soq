/* SO 3982-4536 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Each header line has 1 row label and 30 column labels */
/* Each data line has 1 row label and 30 double values */

#define MAX_VALUES  30
#define MAX_NAMELEN 32
#define MAX_ROWS    50

typedef struct header
{
    char    r_name[MAX_NAMELEN];
    char    c_name[MAX_VALUES][MAX_NAMELEN];
} header;

typedef struct sample
{
    char    r_name[MAX_NAMELEN];
    double  value[MAX_VALUES];
} sample;

static void print_header(const char *tag, const header *hdr);
static void print_sample(int rownum, const sample *data);
static void err_format(const char *tag, const char *buffer);
static void err_error(const char *msg);

static void read_header(header *hdr)
{
    char   *buffer = 0;
    size_t  buflen = 0;
    char    delim[2];
    if (getline(&buffer, &buflen, stdin) == -1)
        err_error("Failed to read header line");
    int offset = 0;
    if (sscanf(buffer + offset, "%31[^\t\n\r]%1[\t\n\r]%n", hdr->r_name, delim, &offset) != 2)
        err_format("header row name", buffer);
    if (strchr("\t\n\r", *delim) == 0)
        err_format("unexpected delimiter", buffer);
    for (int i = 0; i < MAX_VALUES; i++)
    {
        int extra;
        if (sscanf(buffer + offset, "%31[^\t\n\r]%1[\t\n\r]%n", hdr->c_name[i], delim, &extra) != 2)
        {
            fprintf(stderr, "Column %d\n", i);
            err_format("header column name", buffer);
        }
        if (strchr("\t\n\r", *delim) == 0)
            err_format("unexpected delimiter", buffer);
        offset += extra;
    }
    free(buffer);
}

static size_t read_samples(size_t max_rows, sample *data)
{
    char   *buffer = 0;
    size_t  buflen = 0;
    size_t  numrow = 0;

    while (getline(&buffer, &buflen, stdin) != -1 && numrow < max_rows)
    {
        int offset;
        char delim[2];
        if (sscanf(buffer, "%31[^\t\n\r]%1[\t\n\r]%n", data[numrow].r_name, delim, &offset) != 2)
            err_format("row name", buffer);
        for (int i = 0; i < MAX_VALUES; i++)
        {
            int extra;
            if (sscanf(buffer + offset, "%lf%n", &data[numrow].value[i], &extra) != 1)
                err_format("value", buffer);
            if (strchr("\t\n\r", *delim) == 0)
                err_format("unexpected delimiter", buffer);
            assert(extra > 0);
            offset += extra;
        }
        numrow++;
    }
    free(buffer);
    return numrow;
}

int main(void)
{
    header  hdr_1;
    header  hdr_2;

    read_header(&hdr_1);
    read_header(&hdr_2);

    sample data[MAX_ROWS];
    size_t numrows = read_samples(MAX_ROWS, data);

    print_header("H1", &hdr_1);
    print_header("H2", &hdr_2);

    printf("Number of rows: %zu\n", numrows);
    for (size_t i = 0; i < numrows; i++)
        print_sample(i, &data[i]);

    return 0;
}

static void print_header(const char *tag, const header *hdr)
{
    printf("[%s] [%s]", tag, hdr->r_name);
    for (size_t i = 0; i < MAX_VALUES; i++)
        printf(" [%s]", hdr->c_name[i]);
    putchar('\n');
}

static void print_sample(int rownum, const sample *data)
{
    printf("%d [%s]", rownum, data->r_name);
    for (int i = 0; i < MAX_VALUES; i++)
        printf(" [%12.9f]", data->value[i]);
    putchar('\n');
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
