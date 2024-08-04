/* SO 7140-4900 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char ***array_to_recordset(size_t nrows, size_t ncols, char *results[])
{
    char ***recordset = malloc((nrows + 1) * sizeof(*recordset));
    size_t count = 0;

    for (size_t i = 0; i < nrows + 1; i++)
    {
        recordset[i] = malloc(ncols * sizeof(recordset[0][0]));
        for (size_t j = 0; j < ncols; j++)
        {
            //recordset[i][j] = strdup(results[count++];
            recordset[i][j] = malloc(strlen(results[count]) + 1);
            strcpy(recordset[i][j], results[count++]);
        }
    }
    return recordset;
}

static void free_recordset(size_t nrows, size_t ncols, char ***recordset)
{
     for (size_t i = 0; i < nrows + 1; i++)
     {
         for (size_t j = 0; j < ncols; j++)
              free(recordset[i][j]);
         free(recordset[i]);
     }
     free(recordset);
}

// Test Harness

static size_t max_string_width(size_t nrows, size_t ncols, char ***recordset)
{
    size_t maxwid = 0;
    for (size_t i = 0; i < nrows + 1; i++)
    {
        for (size_t j = 0; j < ncols; j++)
        {
            size_t length = strlen(recordset[i][j]);
            if (length > maxwid)
                maxwid = length;
        }
    }
    return maxwid;
}

static void dump_recordset(size_t nrows, size_t ncols, char ***recordset)
{
    int maxwid = max_string_width(nrows, ncols, recordset);

    for (size_t i = 0; i < nrows + 1; i++)
    {
        const char *pad = "";
        for (size_t j = 0; j < ncols; j++)
        {
            printf("%s%-*s", pad, maxwid, recordset[i][j]);
            pad = "  ";
        }
        putchar('\n');
    }
}

int main(void)
{
    char *results[] =
    {
        "Name",  "Number",
        /* random -n 4 -T '%W%v%c%v%c %[10:99]d' | commalist -S -q '"' -B 8 */
        "Caqam", "18",
        "Cepay", "38",
        "Jojaj", "43",
        "Tovun", "59",
    };
    enum { NUM_ROWS = 4, NUM_COLS = 2 };

    char ***recordset = array_to_recordset(NUM_ROWS, NUM_COLS, results);
    dump_recordset(NUM_ROWS, NUM_COLS, recordset);
    free_recordset(NUM_ROWS, NUM_COLS, recordset);

    return 0;
}
