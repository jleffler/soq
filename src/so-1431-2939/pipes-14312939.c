#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int filedes[2];
    int corpse;
    int status;
    if (pipe(filedes) != 0)
    {
        perror("pipe()");
        exit(1);
    }

    /* Run LS. */
    pid_t pid = fork();
    if (pid == 0)
    {
        /* Set stdout to the input side of the pipe, and run 'ls'. */
        dup2(filedes[1], 1);
        close(filedes[1]);
        close(filedes[0]);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
        fprintf(stderr, "Failed to execute /bin/ls\n");
        exit(1);
    }
    /* Close the input side of the pipe, to prevent it staying open. */
    close(filedes[1]);

    /* Run WC. */
    pid = fork();
    if (pid == 0)
    {
        dup2(filedes[0], 0);
        close(filedes[0]);
        char *argv[] = {"wc", NULL};
        execv("/usr/bin/wc", argv);
        fprintf(stderr, "Failed to execute /usr/bin/wc\n");
        exit(1);
    }

    close(filedes[0]);

    while ((corpse = waitpid(-1, &status, 0)) > 0)
        printf("PID %d died 0x%.4X\n", corpse, status);
    return(0);

}
