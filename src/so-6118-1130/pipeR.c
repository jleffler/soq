#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	err_setarg0(argv[0]);
	if (argc != 2)
		err_usage("fd");

	int fd = atoi(argv[1]);
	if (fd < 3)
		err_error("Unexpected result from converting [%s] to an integer\n", argv[1]);

    int reads = 0;
	int total = 0;
	int nbytes;
    char charRead[100];
    /* Process D reads 100 characters at a time */
    while ((nbytes = read(fd, charRead, sizeof(charRead))) > 0)
    {
        total += nbytes;
        reads++;
        printf("%.*s\n", nbytes, charRead);
        if (reads % 50 == 0)
            usleep(200000);
    }
    close(fd);
    printf("Total number of read calls: %d\n", reads);
	printf("Number of characters read:  %d\n", total);
    return(4);
}
