/* SO 7140-4900 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generate allocation failures */
static size_t counter = 0;
static size_t failure = 0;

static void *xmalloc(size_t size)
{
    if (failure > 0 && ++counter >= failure)
    {
        fprintf(stderr, "%s() failed (counter = %zu, failure = %zu)\n", __func__, counter, failure);
        return NULL;
    }
    return malloc(size);
}

static char ***array_to_recordset(size_t nrows, size_t ncols, char *results[])
{
    char ***recordset = xmalloc((nrows + 1) * sizeof(*recordset));
    if (recordset == NULL)
        return NULL;

    size_t count = 0;
    for (size_t i = 0; i < nrows + 1; i++)
    {
        recordset[i] = xmalloc(ncols * sizeof(recordset[0][0]));
        if (recordset[i] == NULL)
        {
            for (size_t ei = 0; ei < i; ei++)
            {
                for (size_t ej = 0; ej < ncols; ej++)
                    free(recordset[ei][ej]);
                free(recordset[ei]);
            }
            free(recordset);
            return NULL;
        }
        for (size_t j = 0; j < ncols; j++)
        {
            //recordset[i][j] = strdup(results[count++];
            recordset[i][j] = xmalloc(strlen(results[count]) + 1);
            if (recordset[i][j] == NULL)
            {
                for (size_t ej = 0; ej < j; ej++)
                    free(recordset[i][ej]);
                free(recordset[i]);
                for (size_t ei = 0; ei < i; ei++)
                {
                    for (size_t ej = 0; ej < ncols; ej++)
                        free(recordset[ei][ej]);
                    free(recordset[ei]);
                }
                free(recordset);
                return NULL;
            }
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

    for (failure = 0; failure < 30; failure++)
    {
        counter = 0;
        char ***recordset = array_to_recordset(NUM_ROWS, NUM_COLS, results);
        if (recordset != NULL)
        {
            dump_recordset(NUM_ROWS, NUM_COLS, recordset);
            free_recordset(NUM_ROWS, NUM_COLS, recordset);
        }
    }

    return 0;
}
