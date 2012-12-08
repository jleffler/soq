int main(void)
{
    for (int i = 0; i < commands_num; i++) {   //exec all the commands instants
        if (pcommands[i]._flag_pipe_out == 1) { //creates pipe if necessary
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
                if (dup2(pcommands[i]._fd_in, STDIN) == -1) {
                    perror("Error: \"dup2()\" failed");
                    exit(0);
                }
                close(pcommands[i]._fd_in);
            }

            if (pcommands[i]._flag_pipe_out == 1) { //if there was a pipe from this command
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
    //closing all the open fd's
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
