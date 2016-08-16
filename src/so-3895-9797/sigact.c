/* SO 3895-9797 */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sigIntHandler(int signum)
{
    fprintf(stderr, "Ctrl-C (%d)\n", signum);
}

int main(void)
{
    struct sigaction signalAction;
    signalAction.sa_handler = sigIntHandler;
    sigemptyset(&signalAction.sa_mask);
    signalAction.sa_flags = 0;      // SA_RESTART;
    sigaction(SIGINT, &signalAction, NULL);

    while (1)
    {
        char block[4096];

        printf("sigAction>");
        fflush(stdout);

        if (fgets(block, 4096, stdin) == 0)
        {
            if (errno == EINTR)
            {
                errno = 0;
                clearerr(stdin);
                fprintf(stderr, "Interrupted!\n");
                continue;
            }
            else
            {
                fprintf(stderr, "EOF spotted\n");
                break;
            }
        }

        if (!strcmp(block, "exit\n"))
        {
            fprintf(stderr, "Exiting\n");
            exit(1);
        }
        printf("Read: [%.*s]\n", (int)(strlen(block) - 1), block);
    }
}
