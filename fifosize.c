#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    const char fifo[] = "FIFO";
    mkfifo(fifo, 0600);
    int fd = open(fifo, O_RDWR|O_NONBLOCK);
    char buffer[16] = "ABCDEFGHIJKLMNOP";
    size_t nbytes = 0;
    while (write(fd, buffer, sizeof(buffer)) == (ssize_t)sizeof(buffer))
        nbytes += sizeof(buffer);
    printf("FIFO buffer size: %zu bytes\n", nbytes);
    close(fd);
    unlink(fifo);
    return 0;
}
