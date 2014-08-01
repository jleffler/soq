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

    char buffer[17] = "ABCDEFGHIJKLMNOP";   /*=C++=*/
    size_t bufsiz = sizeof(buffer) - 1;     /*=C++=*/
    size_t nbytes = 0;
    while (write(fd[1], buffer, bufsiz) == (ssize_t)bufsiz)
        nbytes += bufsiz;
    printf("PIPE buffer size: %zu bytes\n", nbytes);

    return 0;
}
