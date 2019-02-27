/* SO 4844-3136 - file descriptors version */
#include <unistd.h>
#include "stderr.h"

static void check_fd(int fd)
{
    char buffer[1024];

    err_remark("About to read from fd = %d\n", fd);
    ssize_t nbytes = read(fd, buffer, sizeof(buffer));
    if (nbytes < 0)
        err_sysrem("Failed to read fd = %d: ", fd);
    else if (nbytes == 0)
        err_remark("Got EOF (0 bytes read) on fd = %d\n", fd);
    else
    {
        err_remark("Got normal read of %d bytes on fd = %d\n", (int)nbytes, fd);
        printf("Data: [%.*s]\n", (int)nbytes - 1, buffer);
    }

    err_remark("About to write to fd = %d\n", fd);
    char message[] = "  'Twas brillig and the the slithy toves\n"
                     "  Did gyre and gimble in the wabe.\n"
                     "  All mimsy were the borogroves,\n"
                     "  And the mome raths outgrabe.\n";
    nbytes = write(fd, message, sizeof(message) - 1);
    if (nbytes < 0)
        err_sysrem("Failed to write to fd = %d: ", fd);
    else if (nbytes == (ssize_t)sizeof(message) - 1)
        err_remark("Successfully wrote %d bytes to fd = %d\n", (int)nbytes, fd);
    else
        err_remark("Got a short write (%d bytes written; %d expected) on fd = %d\n",
                   (int)nbytes, (int)(sizeof(message) - 1), fd);
}

int main(int argc, char **argv)
{
    if (argc != 0)
        err_setarg0(argv[0]);

    check_fd(STDIN_FILENO);
    check_fd(STDOUT_FILENO);
    check_fd(STDERR_FILENO);
    return 0;
}
