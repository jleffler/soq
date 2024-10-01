#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stderr.h"

int main(void)
{
    err_setarg0("tester");
    alarm(20);
    pid_t server = fork();
    if (server < 0)
        err_syserr("failed to fork for server: ");
    if (server == 0)
    {
        char *args[] = { "./server", 0 };
        execv(args[0], args);
        err_syserr("failed to exec server: ");
    }
    printf("Server PID: %d\n", server);
    fflush(stdout);

    pid_t client = fork();
    if (client < 0)
        err_syserr("failed to fork for client: ");
    if (client == 0)
    {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%d", server);
        char *argc[] = { "./client", buffer, 0 };
        execv(argc[0], argc);
        err_syserr("failed to exec client: ");
    }
    printf("Client PID: %d\n", client);
    fflush(stdout);

    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
    {
        printf("Child %d exited with status 0x%.4X\n", corpse, status);
        fflush(stdout);
    }

    return 0;
}
