#include "stderr.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    err_setarg0("pipesize");
    char buffer[1024] = "";
    int fd[2];
    if (pipe(fd) != 0)
        err_syserr("pipe() failed - ");
    int flags = fcntl(fd[1], F_GETFL, NULL);
    if (flags < -1)
        err_syserr("fcntl(F_GETFL) failed - ");
    flags |= O_NONBLOCK;
    if (fcntl(fd[1], F_SETFL, flags) != 0)
        err_syserr("fcntl(F_SETFL) failed - ");
    int count = 0;
    int nbytes;
    while ((nbytes = write(fd[1], buffer, sizeof(buffer))) > 0)
        count += nbytes;
    err_sysrem("write() failed - ");
    printf("Pipe size: %d\n", count);
    return 0;
}

