/* SO 4859-9507 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int rv;

    int to_ext_program_pipe[2];
    int to_my_program_pipe[2];

    if (pipe(to_ext_program_pipe))
    {
        fprintf(stderr, "Pipe error!\n");
        exit(1);
    }
    if (pipe(to_my_program_pipe))
    {
        fprintf(stderr, "Pipe error!\n");
        exit(1);
    }

    if ((pid = fork()) == -1)
    {
        fprintf(stderr, "Fork error. Exiting.\n");
        exit(1);
    }

    if (pid)
    {
        close(to_my_program_pipe[1]);
        close(to_ext_program_pipe[0]);
        char string_to_write[] = "this is the string to write";

        write(to_ext_program_pipe[1], string_to_write, sizeof(string_to_write) - 1);
        close(to_ext_program_pipe[1]);

        char ch[1024];
        size_t len = 0;
        char *string_to_read =  0;
        ssize_t nbytes;

        while ((nbytes = read(to_my_program_pipe[0], ch, sizeof(ch))) > 0)
        {
            char *new_space = realloc(string_to_read, len + nbytes + 1);
            if (new_space == 0)
            {
                fprintf(stderr, "Error while allocating %zu bytes memory\n", len);
                exit(1);
            }
            string_to_read = new_space;
            memmove(&string_to_read[len], ch, nbytes);
            len += nbytes;
            string_to_read[len] = '\0';
        }
        close(to_my_program_pipe[0]);
        printf("Output: %zu (%zu) [%s]\n", len, strlen(string_to_read), string_to_read);
        free(string_to_read);

        wait(&rv);
        if (rv != 0)
        {
            fprintf(stderr, "%s %d\n", "phantomjs exit status ", rv);
            exit(1);
        }
    }
    else
    {
        dup2(to_ext_program_pipe[0], 0);
        dup2(to_my_program_pipe[1], 1);
        close(to_ext_program_pipe[0]);
        close(to_ext_program_pipe[1]);
        close(to_my_program_pipe[0]);
        close(to_my_program_pipe[1]);

        execlp("ext_program", "ext_program", "/dev/stdin", NULL);
        fprintf(stderr, "execlp Error!\n");
        exit(1);
    }

    return 0;
}
