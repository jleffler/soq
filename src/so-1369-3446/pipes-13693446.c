/* SO 1369-3446 Trying to run ls | grep r with execvp */

#include "posixver.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct Command Command;
struct Command
{
    int _fd_out;
    int _fd_in;
    int _flag_pipe_in;
    int _flag_pipe_out;
    char **_commands;
};

typedef int Pipe[2];

enum { STDIN = STDIN_FILENO, STDOUT = STDOUT_FILENO, STDERR = STDERR_FILENO };

int main(void)
{
    char *ls_cmd[] = { "ls", 0 };
    char *grep_cmd[] = { "grep", "r", 0 };
    Command commands[] =
    {
        {
            ._fd_in  = 0, ._flag_pipe_in  = 0,
            ._fd_out = 1, ._flag_pipe_out = 1,
            ._commands = ls_cmd,
        },
        {
            ._fd_in  = 0, ._flag_pipe_in  = 1,
            ._fd_out = 1, ._flag_pipe_out = 0,
            ._commands = grep_cmd,
        }
    };
    int commands_num = sizeof(commands) / sizeof(commands[0]);

    /* Allow valgrind to check memory */
    Command *pcommands = malloc(commands_num * sizeof(Command));
    for (int i = 0; i < commands_num; i++)
        pcommands[i] = commands[i];

    for (int i = 0; i < commands_num; i++)
    {
        if (pcommands[i]._flag_pipe_out == 1)
        {
            Pipe pipe_fd;
            if (pipe(pipe_fd) == -1)
            {
                perror("Error: \"pipe()\" failed");
                break;
            }
            pcommands[i]._fd_out = pipe_fd[1];
            pcommands[i+1]._fd_in = pipe_fd[0];
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Error: \"fork()\" failed");
            break;
        }
        else if (pid == 0)
        {
            /* Child - execs command */
            if (pcommands[i]._flag_pipe_in == 1)
            {
                assert(i > 0);
                assert(pcommands[i-1]._flag_pipe_out == 1);
                assert(pcommands[i-1]._fd_out > STDERR);
                if (dup2(pcommands[i]._fd_in, STDIN) == -1)
                {
                    perror("Error: \"dup2()\" failed");
                    exit(1);
                }
                close(pcommands[i]._fd_in);
                close(pcommands[i-1]._fd_out);
            }
            if (pcommands[i]._flag_pipe_out == 1)
            {
                assert(i < commands_num - 1);
                assert(pcommands[i+1]._flag_pipe_in == 1);
                assert(pcommands[i+1]._fd_in > STDERR);
                if (dup2(pcommands[i]._fd_out, STDOUT) == -1)
                {
                    perror("Error: \"dup2()\" failed");
                    exit(1);
                }
                close(pcommands[i]._fd_out);
                close(pcommands[i+1]._fd_in);
            }
            execvp(pcommands[i]._commands[0], pcommands[i]._commands);
            perror("Error: \"execvp()\" failed");
            exit(1);
        }
        else
            printf("Child PID %d running\n", (int)pid);
    }

    for (int i = 0; i < commands_num; i++)
    {
        if (pcommands[i]._fd_in != STDIN)
            close(pcommands[i]._fd_in);
        if (pcommands[i]._fd_out != STDOUT)
            close(pcommands[i]._fd_out);
    }

    int status;
    pid_t corpse;
    while ((corpse = waitpid(-1, &status, 0)) > 0)
        printf("Child PID %d died with status 0x%.4X\n", (int)corpse, status);

    free(pcommands);

    return(0);
}
