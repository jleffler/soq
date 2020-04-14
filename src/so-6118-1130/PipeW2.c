#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    err_setlogopts(ERR_PID | ERR_MILLI);

    if (argc != 2)
        err_usage("fd");

    int fd = atoi(argv[1]);
    if (fd < 3)
        err_error("Unexpected result converting [%s] to integer\n", argv[1]);

    /* Process C writes 6 characters 500 times = 3000 characters */
    for (int i = 0; i < 400; i++)
    {
        char writeB[16];
        int length = snprintf(writeB, sizeof(writeB), "bbb%.4d-", i + 2345);
        write(fd, writeB, length);
        if ((i + 1) % 50 == 0)
            usleep(150000);
    }
    close(fd);
    return(2);
}
