/* Derived from code in SO 18863184 */
/* Original answer by https://stackoverflow.com/users/703016/kretab-chabawenizc */
#include "memprobe.h"
#include <assert.h>
#include <errno.h>
#include <unistd.h>

enum { MAX_PROBE_SIZE = 512 };
static int fd[2] = { -1, -1 };

int probe_init(void)
{
    if (fd[0] == -1) 
    {
        assert(fd[1] == -1);
        if (pipe(fd) != 0)
        {
            assert(fd[0] == -1 && fd[1] == -1);
            return -1;
        }
    }
    return 0;
}

void probe_finish(void)
{
    if (fd[0] != -1)
        close(fd[0]);
    if (fd[1] != -1)
        close(fd[1]);
    fd[0] = fd[1] = -1;
}

int probe_memory_ro(const void *address, size_t length)
{
    int result;

    if (probe_init() != 0)
        return -1;

    /*
    ** Do not allow over-long lengths.
    **
    ** Could be more sophisticated, such as writing at the start and end
    ** of a large segment, or writing every 4 KiB along a very large
    ** segment.
    */
    if (length > MAX_PROBE_SIZE)
        length = MAX_PROBE_SIZE;

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

int probe_memory_rw(void *address, size_t length)
{
    int result;

    if (probe_init() != 0)
        return -1;

    /*
    ** Do not allow over-long lengths.
    **
    ** Could be more sophisticated, such as writing at the start and end
    ** of a large segment, or writing every 4 KiB along a very large
    ** segment.
    */
    if (length > MAX_PROBE_SIZE)
        length = MAX_PROBE_SIZE;

    /* Save errno */
    int errnum = errno;
    errno = 0;
    int io_len = write(fd[1], address, length);
    if (io_len < 0 || (size_t)io_len != length || errno == EFAULT)
        result = 0;
    else
        result = 1;

    /*
    ** Read what was written - checking writability of address and
    ** ensuring that the pipe doesn't fill and block
    */
    if (result == 1)
    {
        if ((io_len = read(fd[0], address, length)) < 0 || (size_t)io_len != length || errno == EFAULT)
            result = 0;

    }

    /* Reinstate errno */
    if (errno == 0)
        errno = errnum;

    return result;
}

/* ---------------------------------------------------------------------- */

#ifdef TEST

#include <stdio.h>
#include <string.h>

static void test_ro(const void *address, size_t length, const char *tag)
{
    if (probe_memory_ro(address, length) == 1)
        printf("%s is readable\n", tag);
    else
        printf("%s is BAD (%d: %s)\n", tag, errno, strerror(errno));
}

static void test_rw(void *address, size_t length, const char *tag)
{
    if (probe_memory_rw(address, length) == 1)
        printf("%s is writeable\n", tag);
    else
        printf("%s is BAD (%d: %s)\n", tag, errno, strerror(errno));
}

int main(void)
{
    int matrix[4] = { 0, 1, 2, 3 };
    int *dne = (int *)0x820011114444;

    printf("Readability:\n");
    test_ro(matrix, sizeof(matrix), "matrix");
    test_ro(NULL, sizeof(matrix), "NULL");
    test_ro(dne, sizeof(matrix), "Non-existent address");
    test_ro(probe_memory_ro, sizeof(matrix), "Function probe_memory_ro()");

    printf("\nWriteability:\n");
    test_rw(matrix, sizeof(matrix), "matrix");
    test_rw(NULL, sizeof(matrix), "NULL");
    test_rw(dne, sizeof(matrix), "Non-existent address");
    test_rw(probe_memory_ro, sizeof(matrix), "Function probe_memory_ro()");

    probe_finish();
    return 0;
}

#endif /* TEST */
