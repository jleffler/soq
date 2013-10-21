#include <unistd.h>
#include <errno.h>

static
int probe_memory(void *address, size_t length) {
    int result, fd[2];

    pipe(fd);  /* Remember to check for errors! */

    /* Not completely foolproof, just a simple idea to get you started. */
    errno = 0;
    result = write(fd[1], address, length);
    if (result < 0 || (size_t)result != length || errno == EFAULT)
        result = 0;
    else
        result = 1;

    close(fd[0]);
    close(fd[1]);

    return result;
}

#include <stdio.h>

int main(void)
{
    int test;
    if ((test = probe_memory(&test, sizeof(test))) == 1)
        printf("&test is OK\n");
    else
        printf("&test is BAD\n");

    if ((test = probe_memory(NULL, sizeof(test))) == 1)
        printf("NULL is OK\n");
    else
        printf("NULL is BAD\n");
    return 0;
}
