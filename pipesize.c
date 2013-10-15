#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd[2];  /* Output pipe - for parent */

    pipe(fd);
    int p_flags = fcntl(fd[1], F_GETFL);
    p_flags |= O_NONBLOCK;
    fcntl(fd[1], F_SETFL, p_flags);

    char buffer[16] = "ABCDEFGHIJKLMNOP";
    size_t nbytes = 0;
    while (write(fd[1], buffer, sizeof(buffer)) == (ssize_t)sizeof(buffer))
        nbytes += sizeof(buffer);
    printf("PIPE buffer size: %zu bytes\n", nbytes);

    return 0;
}
