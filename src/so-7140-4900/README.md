### Stack Overflow Question 7140-4900

[SO 7140-4900](https://stackoverflow.com/q/71404900) &mdash;
How to deallocate memory assigned to triple pointer?

In general terms, for each call to `malloc()`, there must be a matching
call `free()`.  You need to free the memory more or less in the reverse
of the order it was allocated (so `free(recordset)` should indeed be
last).

Your memory allocation code is broken.  Your memory freeing code is
similarly broken.

According to a comment, you have `nrows + 1` rows of data, each
containing `ncols` values, each of which is a null-terminated string.
It isn't clear that you have to copy the information from `results`, but
it does ensure that the memory is wholly under your control.

You've not shown most of your variable declarations — that always
makes life unnecessarily hard for those who would help you.

The code below omits checks for memory allocation failures.  You should
not omit those — but freeing up space already allocated when an
allocation fails becomes fiddly.

You should have a function along the lines of:

```c
char ***array_to_recordset(size_t nrows, size_t ncols, char *results[])
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
```
Then your release code becomes:
```c
void free_recordset(size_t nrows, size_t ncols, char ***recordset)
{
     for (size_t i = 0; i < nrows + 1; i++)
     {
         for (size_t j = 0; j < ncols; j++)
              free(recordset[i][j]);
         free(recordset[i]);
     }
     free(recordset);
}
```

<sup>_No compiler was consulted about the validity of this code before
the initial posting.  There could be bugs in it (apart from the absence
of checking memory allocations) — indeed, there were two typo bugs
that stopped it compiling (`counter` vs `count`, and a missing close
parenthesis)._</sup>

### Code in test harness

```c
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
```
**Output**
```none
Name    Number
Caqam   18    
Cepay   38    
Jojaj   43    
Tovun   59 
```
There are no leaks reported by the `leaks` program on macOS, and no memory abuse reported when the macOS `malloc()` code is configured to test for memory abuses.

### Testing for and recovering from allocation failure

This variant of the code includes a function `xmalloc()` which can be
configured to start failing after a given number of allocations.  The
code then tests the failure paths after 1..30 allocations (there are
only 16 allocations anyway).  It too is leak-free and memory abuse-free.

```c
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
```

Note that the code releasing memory after an allocation failure has to
deal with with partially allocated rows, previous fully allocated rows,
and of course the initial allocation.

**Output**
```none
Name    Number
Caqam   18    
Cepay   38    
Jojaj   43    
Tovun   59    
xmalloc() failed (counter = 1, failure = 1)
xmalloc() failed (counter = 2, failure = 2)
xmalloc() failed (counter = 3, failure = 3)
xmalloc() failed (counter = 4, failure = 4)
xmalloc() failed (counter = 5, failure = 5)
xmalloc() failed (counter = 6, failure = 6)
xmalloc() failed (counter = 7, failure = 7)
xmalloc() failed (counter = 8, failure = 8)
xmalloc() failed (counter = 9, failure = 9)
xmalloc() failed (counter = 10, failure = 10)
xmalloc() failed (counter = 11, failure = 11)
xmalloc() failed (counter = 12, failure = 12)
xmalloc() failed (counter = 13, failure = 13)
xmalloc() failed (counter = 14, failure = 14)
xmalloc() failed (counter = 15, failure = 15)
xmalloc() failed (counter = 16, failure = 16)
Name    Number
Caqam   18    
Cepay   38    
Jojaj   43    
Tovun   59    
…
```
The output reappears when the allocation failure doesn't occur because
not enough memory allocations occur.

