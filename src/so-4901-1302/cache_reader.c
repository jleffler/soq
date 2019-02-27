#include "cache_reader.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct cr_file
{
    int   file;     // File being read
    int   bufmax;   // Fixed buffer length
    int   bufpos;   // Current point in the buffer
    int   buflen;   // Amount of data in the buffer
    char *buffer;   // A pointer to a piece of memory
};

static void cr_refill(cr_file *f)
{
    if (f->bufpos >= f->buflen)
    {
        int nbytes = read(f->file, f->buffer, f->bufmax);
        if (nbytes > 0)
        {
            f->buflen = nbytes;
            f->bufpos = 0;
        }
    }
}

void cr_close(cr_file *f)
{
    free(f->buffer);
    close(f->file);
    free(f);
}

cr_file *cr_open(char *filename, int buffersize)
{
    int fd;
    if ((fd = open(filename, O_RDWR)) < 0)
    {
        fprintf(stderr, "cannot open %s for reading and writing (%d: %s)\n",
                filename, errno, strerror(errno));
        return 0;
    }

    cr_file *a = (cr_file *)malloc(sizeof(cr_file));
    char *b = (char *)malloc(sizeof(char) * buffersize);
    if (a == 0 || b == 0)
    {
        free(a);
        free(b);
        close(fd);
        fprintf(stderr, "cannot allocate %zu bytes of memory (%d: %s)\n",
                sizeof(cr_file) + buffersize, errno, strerror(errno));
        return 0;
    }
    a->file = fd;
    a->bufmax = buffersize;
    a->bufpos = 0;
    a->buflen = 0;
    a->buffer = b;
    return a;
}

int cr_read_byte(cr_file *f)
{
    if (f->bufpos >= f->buflen)
        cr_refill(f);
    if (f->bufpos >= f->buflen)
        return EOF;
    return f->buffer[f->bufpos++];
}

