/*
** Code by Jonathan Leffler
** SO: http://stackoverflow.com/questions/2371292/
** SPOJ: http://www.spoj.pl/problems/INTEST/
** @(#)$Id: mmf.c,v 1.1 2010/03/06 17:49:04 jleffler Exp $
*/

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

static const char *arg0 = "**unset**";
static void error(const char *fmt, ...)
{
    va_list args;
    fprintf(stderr, "%s: ", arg0);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

static unsigned long read_integer(char *src, char **end)
{
    unsigned long v;
    errno = 0;
    v = strtoul(src, end, 0);
    if (v == ULONG_MAX && errno == ERANGE)
        error("integer too big for unsigned long at %.20s", src);
    if (v == 0 && errno == EINVAL)
        error("failed to convert integer at %.20s", src);
    if (**end != '\0' && !isspace((unsigned char)**end))
        error("dubious conversion at %.20s", src);
    return(v);
}

static void *memory_map(int fd)
{
    void *data;
    struct stat sb;
    if (fstat(fd, &sb) != 0)
        error("failed to fstat file descriptor %d (%d: %s)\n", fd, errno, strerror(errno));
    if (!S_ISREG(sb.st_mode))
        error("file descriptor %d is not a regular file (%o)\n", fd, sb.st_mode);
    data = mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fileno(stdin), 0);
    if (data == MAP_FAILED)
        error("failed to memory map file descriptor %d (%d: %s)\n", fd, errno, strerror(errno));
    return(data);
}

int main(int argc, char **argv)
{
    char *data;
    char *src;
    char *end;
    unsigned long k;
    unsigned long n;
    unsigned long answer = 0;
    size_t i;

    arg0 = argv[0];
    data = memory_map(0);

    src = data;

    /* Read control data */
    n = read_integer(src, &end);
    src = end;
    k = read_integer(src, &end);
    src = end;

    for (i = 0; i < n; i++, src = end)
    {
        unsigned long v = read_integer(src, &end);
        if (v % k == 0)
            answer++;
    }

    printf("%lu\n", answer);
    return(0);
}
