/* SO 13693446 Trying to run ls | grep r with execvp */

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

    Command *pcommands = commands;

//    /* Allow valgrind to check memory */
//    Command *pcommands = malloc(commands_num * sizeof(Command));
//    for (int i = 0; i < commands_num; i++)
//        pcommands[i] = commands[i];

    for (int i = 0; i < commands_num; i++) {   //exec all the commands instants
        if (pcommands[i]._flag_pipe_out == 1) { //creates pipe if necessary
            Pipe pipe_fd;
            if (pipe(pipe_fd) == -1) {
                perror("Error: \"pipe()\" failed");
            }
            pcommands[i]._fd_out = pipe_fd[1];
            pcommands[i+1]._fd_in = pipe_fd[0];
        }
        pid_t pid = fork();   //the child exec the commands
        if (pid == -1) {
            perror("Error: \"fork()\" failed");
            break;
        } else if (!pid) { //child process

            if (pcommands[i]._flag_pipe_in == 1) {  //if there was a pipe to this command
                assert(i > 0);
                assert(pcommands[i-1]._flag_pipe_out == 1);
                assert(pcommands[i-1]._fd_out > STDERR);
                if (dup2(pcommands[i]._fd_in, STDIN) == -1) {
                    perror("Error: \"dup2()\" failed");
                    exit(0);
                }
                close(pcommands[i]._fd_in);
            }

            if (pcommands[i]._flag_pipe_out == 1) { //if there was a pipe from this command
                assert(i < commands_num - 1);
                assert(pcommands[i+1]._flag_pipe_in == 1);
                assert(pcommands[i+1]._fd_in > STDERR);
                if (dup2(pcommands[i]._fd_out, STDOUT) == -1) {
                    perror("Error: \"dup2()\" failed");
                    exit(0);
                }
                close(pcommands[i]._fd_out);
            }
            execvp(pcommands[i]._commands[0] , pcommands[i]._commands); //run the command

            perror("Error: \"execvp()\" failed");
            exit(0);
        } else if (pid > 0) { //father process
            waitpid(pid, NULL, WUNTRACED);
        }
    }

    //closing all the open pipe fd's
    for (int i = 0; i < commands_num; i++) {
        if (pcommands[i]._fd_in != STDIN) { //if there was another stdin that is not 0
            close(pcommands[i]._fd_in);
        }
        if (pcommands[i]._fd_out != STDOUT) { //if there was another stdout that is not 1
            close(pcommands[i]._fd_out);
        }
    }
    return(0);
}
