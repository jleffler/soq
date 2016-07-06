#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    const char fifo[] = "FIFO";
    mkfifo(fifo, 0600);
    int fd = open(fifo, O_RDWR|O_NONBLOCK);
    char buffer[17] = "ABCDEFGHIJKLMNOP";
    size_t bufsiz = 16;
    size_t nbytes = 0;
    while (write(fd, buffer, bufsiz) == (ssize_t)bufsiz)
        nbytes += bufsiz;
    printf("FIFO buffer size: %zu bytes\n", nbytes);
    close(fd);
    unlink(fifo);
    return 0;
}
