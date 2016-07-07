/* http://stackoverflow.com/q/18923412 Use strtok() and execute Unix command in background */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LENGTH 1024
#define DELIMS " \t\r\n"
static void run_command(char **argv, int bg_flag);

int main(void)
{
    char line[MAX_LENGTH];
    char *ps1 = "toysh> ";

    while (fputs(ps1, stdout) > 0 && fgets(line, sizeof(line), stdin) != NULL)
    {
        char *cmd[100];
        char *bg = NULL;
        int j = 0;
        char *tokens = line;

        while ((cmd[j++] = strtok(tokens, DELIMS)) != NULL)
            tokens = NULL;

        assert(j < 100);
        /* The line has been tokenized into j-1 tokens */
        /* Print the tokens found */
        for (int i = 0; i < j; i++)
        {
            if (cmd[i] != 0)
                printf("%d: <<%s>>\n", i, cmd[i]);
            else
                printf("%d: NULL pointer\n", i);
        }

        assert(j > 0);
        if (j == 1)
            continue;   // No command

        j--;

        assert(j > 0);
        if (strcmp(cmd[j-1], "&") == 0)
        {
            printf("== Found &\n");
            bg = cmd[j-1];
            cmd[--j] = 0;
            if (j == 0)
            {
                puts("Syntax error: cannot have & on its own");
                continue;
            }
        }

        if (strcmp(cmd[0], "exit") == 0)
        {
            printf("== Found exit command\n");
            if (bg != NULL)
            {
                puts("Can't run exit in background");
                continue;
            }
            break;
        }

        /*
        ** Now you can do your fork, exec, waitpid work.  Note that the
        ** command is already split into words with the null pointer at
        ** the end.  This is what execv(), execve() and execvp() want
        */
        run_command(cmd, (bg != NULL));

    }
    putchar('\n');

    return(0);
}

/* Wait for a specific child to die, collecting any other corpses as we go */
/*
** waitpid() returns 0 with WNOHANG and no children already dead but some
** children to wait for.
*/
static void wait_for_child(int pid, int flags)
{
    int status;
    int corpse;
    while ((corpse = waitpid(-1, &status, flags)) > 0)
    {
        fprintf(stderr, "Process %d exited with status 0x%.4X\n",
                corpse, status);
        if (corpse == pid)
            break;
    }
}

static void run_command(char **argv, int bg_flag)
{
    int pid;

    fflush(0);  // Flush pending output

    if ((pid = fork()) < 0)
        printf("Fork failed\n");
    else if (pid == 0)
    {
        /* Child process */
        execvp(argv[0], argv);
        fprintf(stderr, "%d: failed to execute %s (%d: %s)",
                (int)getpid(), argv[0], errno, strerror(errno));
        exit(1);
    }
    /* Parent shell */
    else if (bg_flag == 0)
    {
        /*
        ** (pid, 0) - wait explicitly for given child to complete,
        ** reporting others that die first too.
        */
        wait_for_child(pid, 0);
        usleep(10000);
    }
    else
    {
        printf("%d: %s running in background\n", pid, argv[0]);
        /*
        ** (-1, WNOHANG) - wait for any background processes that have
        ** died but return when there are no bodies left to collect.
        */
        wait_for_child(-1, WNOHANG);
    }
}

