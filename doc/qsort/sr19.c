/* SO 3968-2323 */
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct record
{
    int   key;
    int   data_len;
    char  data[];
};

static int comparator(const void *v1, const void *v2);
static void print_records(const char *tag, int num_recs, struct record **recs);
static void err_syserr(const char *msg, ...);
static void err_setarg0(const char *argv0);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }

    err_setarg0(argv[0]);

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        err_syserr("Failed to open file '%s' for reading\n", argv[1]);

    struct record **records = 0;
    int num_recs = 0;
    int max_recs = 0;
    int key;
    int len;
    while (read(fd, &key, sizeof(key)) == sizeof(key) &&
           read(fd, &len, sizeof(len)) == sizeof(len))
    {
        //printf("rec num %d (key %d, len %d)\n", num_recs, key, len);
        assert(len > 0);
        assert(num_recs <= max_recs);
        if (num_recs == max_recs)
        {
            size_t new_max = 2 * max_recs + 2;
            void *new_recs = realloc(records, new_max * sizeof(*records));
            if (new_recs == 0)
                err_syserr("Failed to realloc() %zu bytes of memory\n", new_max * sizeof(*records));
            records = new_recs;
            max_recs = new_max;
        }
        int rec_size = sizeof(struct record) + len;
        records[num_recs] = malloc(rec_size);
        records[num_recs]->key = key;
        records[num_recs]->data_len = len;
        if (read(fd, records[num_recs]->data, len) != len)
            err_syserr("Short read for record number %d (key %d)\n", num_recs, key);
        records[num_recs]->data[len-1] = '\0';
        //printf("Data: [%s]\n", records[num_recs]->data);
        char blank = 0;
        if (read(fd, &blank, sizeof(blank)) != sizeof(blank))
            err_syserr("Missing record terminator after record number %d (key %d)\n", num_recs, key);
        if (blank != ' ')
            err_syserr("Unexpected EOR code %d for record number %d (key %d)\n", blank, num_recs, key);
        num_recs++;
    }
    close(fd);

    print_records("Before", num_recs, records);
    qsort(records, num_recs, sizeof(struct record *), comparator);
    print_records("After", num_recs, records);

    for (int i = 0; i < num_recs; i++)
        free(records[i]);
    free(records);

    return 0;
}

static int comparator(const void *v1, const void *v2)
{
    int key_1 = (*(struct record **)v1)->key;
    int key_2 = (*(struct record **)v2)->key;
    if (key_1 < key_2)
        return -1;
    else if (key_1 > key_2)
        return +1;
    else
        return 0;
}

static void print_records(const char *tag, int num_recs, struct record **recs)
{
    printf("%s (%d records):\n", tag, num_recs);
    for (int i = 0; i < num_recs; i++)
    {
        struct record *rec = recs[i];
        printf("%6d: %4d: %s\n", rec->key, rec->data_len, rec->data);
    }
}

/* My standard error handling - stderr.h and stderr.c */
static const char *arg0 = "unknown";

static void err_setarg0(const char *argv0)
{
    arg0 = argv0;
}

static void err_syserr(const char *fmt, ...)
{
    va_list args;
    int errnum = errno;
    fprintf(stderr, "%s: ", arg0);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (errnum != 0)
        fprintf(stderr, "(%d: %s)\n", errnum, strerror(errnum));
    exit(EXIT_FAILURE);
}
