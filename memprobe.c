#include <unistd.h>
#include <errno.h>

//#include "memprobe.h"
#ifndef MEMPROBE_H_INCLUDED
#define MEMPROBE_H_INCLUDED

#include <stddef.h>
extern int probe_memory(void *address, size_t length);
extern void probe_finish(void);
extern int probe_init(void);

#endif /* MEMPROBE_H_INCLUDED */

static int fd[2] = { -1, -1 };

int probe_init(void)
{
    if (fd[0] == -1) 
    {
        if (pipe(fd) != 0)
            return -1;
    }
    return 0;
}

void probe_finish(void)
{
    if (fd[0] != -1)
        close(fd[0]);
    if (fd[1] != -1)
        close(fd[1]);
}

int probe_memory(void *address, size_t length)
{
    int result;

    if (probe_init() != 0)
        return -1;

    /*
    ** Do not allow over-long lengths.
    **
    ** Could be more sophisticated, such as writing at start and end of
    ** segment long segment, or writing every 4 KiB along segment.
    */
    if (length > 512)
        length = 512;

    /* Save errno */
    int errnum = errno;
    errno = 0;
    result = write(fd[1], address, length);
    if (result < 0 || (size_t)result != length || errno == EFAULT)
        result = 0;
    else
        result = 1;

    /* Read what was written - so the pipe doesn't fill and block */
    if (result == 1)
    {
        char buffer[length];
        read(fd[0], buffer, length);
    }

    /* Reinstate errno */
    if (errno == 0)
        errno = errnum;

    return result;
}

#include <stdio.h>

int main(void)
{
    int matrix[4] = { 0, 1, 2, 3 };

    if (probe_memory(matrix, sizeof(matrix)) == 1)
        printf("matrix is readable\n");
    else
        printf("matrix is BAD (%d)\n", errno);

    if (probe_memory(NULL, sizeof(matrix)) == 1)
        printf("NULL is readable\n");
    else
        printf("NULL is BAD (%d)\n", errno);

    int *dne = (int *)0x820011114444;
    if (probe_memory(dne, sizeof(matrix)) == 1)
        printf("dne is readable\n");
    else
        printf("dne is BAD (%d)\n", errno);

    if (probe_memory(probe_memory, sizeof(matrix)) == 1)
        printf("probe_memory is readable\n");
    else
        printf("probe_memory is BAD (%d)\n", errno);

    probe_finish();
    return 0;
}
