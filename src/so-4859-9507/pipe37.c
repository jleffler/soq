/* SO 4859-9507 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
 pid_t pid;
 int rv;

 int to_ext_program_pipe[2];
 int to_my_program_pipe[2];

 if(pipe(to_ext_program_pipe)) {
    fprintf(stderr,"Pipe error!\n");
    exit(1);
 }
 if(pipe(to_my_program_pipe)) {
    fprintf(stderr,"Pipe error!\n");
    exit(1);
 }

 if( (pid=fork()) == -1) {
    fprintf(stderr,"Fork error. Exiting.\n");
    exit(1);
 }

 if(pid) {
    close(to_my_program_pipe[1]);
    close(to_ext_program_pipe[0]);
    char string_to_write[] = "this is the string to write";

    write(to_ext_program_pipe[1], string_to_write, strlen(string_to_write) + 1);
    close(to_ext_program_pipe[1]);

    wait(&rv);
    if(rv != 0) {
        fprintf(stderr, "%s %d\n", "phantomjs exit status ", rv);
        exit(1);
    }

    char *string_to_read;
    char ch[1];
    size_t len = 0;
    string_to_read = malloc(sizeof(char));
    if(!string_to_read) {

        fprintf(stderr, "%s\n", "Error while allocating memory");

        exit(1);
    }
    while(read(to_my_program_pipe[0], ch, 1) == 1) {
        string_to_read[len]=ch[0];
        len++;
        string_to_read = realloc(string_to_read, len*sizeof(char));
        if(!string_to_read) {
            fprintf(stderr, "%s\n", "Error while allocating memory");
        }
        string_to_read[len] = '\0';
    }
    close(to_my_program_pipe[0]);
    printf("Output: %s\n", string_to_read);
    free(string_to_read);
} else {
    close(to_ext_program_pipe[1]);
    close(to_my_program_pipe[0]);

    dup2(to_ext_program_pipe[0],0);
    dup2(to_my_program_pipe[1],1);

    if(execlp("ext_program", "ext_program", "/dev/stdin" , NULL) == -1) {
        fprintf(stderr,"execlp Error!");
        exit(1);
    }
    close(to_ext_program_pipe[0]);
    close(to_my_program_pipe[1]);
}

 return 0; 
}

