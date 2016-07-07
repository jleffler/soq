/* SO 30493198 - Example code using triple pointer */
#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int fail_after = 0;
static int n_allocs = 0;

static void *f_malloc(size_t nbytes)
{
    if (fail_after > 0 && ++n_allocs > fail_after)
        return 0;
    return malloc(nbytes);
}

static char *f_strdup(const char *str)
{
  size_t len = strlen(str) + 1;
  char *dup = f_malloc(len);
  if (dup != 0)
    memmove(dup, str, len);
  return dup;
}

extern int array_of_strings(int *num_strings, char ***string_data);

static void free_n_lines(int num, char **lines)
{
    for (int i = 0; i < num; i++)
        free(lines[i]);
    free(lines);
}

int array_of_strings(int *num_strings, char ***string_data)
{
    int n = 32;
    char **pointers = f_malloc(n * sizeof(*pointers));
    if (pointers == 0)
        return -1;  // Failure
    char line[256];
    int i;
    for (i = 0; i < n && fgets(line, sizeof(line), stdin) != 0; i++)
    {
        size_t len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        pointers[i] = f_strdup(line);
        if (pointers[i] == 0)
        {
            // Release already allocated resources
            free_n_lines(i, pointers);
            return -1;  // Failure
        }
    }
    *num_strings = i;
    *string_data = pointers;
    return 0;  // Success
}

int main(int argc, char **argv)
{
    char **lines;
    int nlines;
    int opt;

    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            fail_after = atoi(optarg);
            if (fail_after > 0)
                printf("Failing after %d allocations\n", fail_after);
            break;
        default:
            fprintf(stderr, "Usage: %s [-n fail]\n", argv[0]);
            return 1;
        }
    }

    if (array_of_strings(&nlines, &lines) == 0)
    {
        for (int i = 0; i < nlines; i++)
            printf("%d [%s]\n", i, lines[i]);
        free_n_lines(nlines, lines);
    }
    else
        printf("Failed to read data into array of strings\n");
    return 0;
}
