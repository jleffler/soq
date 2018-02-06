/* SO 4859-9507 - OP's Second Version Bug Fixed */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int rv;
    int to_phantomjs_pipe[2];
    int to_my_program_pipe[2];

    if (pipe(to_phantomjs_pipe))
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
        close(to_phantomjs_pipe[0]);

        char jsToExecute[] =
            "var page=require(\'webpage\').create();page.onInitialized="
            "function(){page.evaluate(function(){delete window._phantom;"
            "delete window.callPhantom;});};page.onResourceRequested="
            "function(requestData,request){if((/http:\\/\\/.+\?\\\\.css/gi)"
            ".test(requestData[\'url\'])||requestData.headers"
            "[\'Content-Type\']==\'text/css\'){request.abort();}};"
            "page.settings.loadImage=false;page.settings.userAgent="
            "\'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, "
            "like Gecko) Chrome/41.0.2228.0 Safari/537.36\';page.open"
            "(\'https://stackoverflow.com\',function(status){if(status"
            "!==\'success\'){phantom.exit(1);}else{console.log(page."
            "content);phantom.exit();}});";

        write(to_phantomjs_pipe[1], jsToExecute, strlen(jsToExecute));
        close(to_phantomjs_pipe[1]);

        int read_chars;
        int BUFF = 1024;
        char *str;
        char ch[BUFF];
        size_t len = 0;
        str = malloc(sizeof(char));
        if (!str)
        {
            fprintf(stderr, "%s\n", "Error while allocating memory");
            exit(1);
        }
        str[0] = '\0';

        while ((read_chars = read(to_my_program_pipe[0], ch, BUFF)) > 0)
        {
            len += read_chars;
            str = realloc(str, (len + 1) * sizeof(char));
            if (!str)
            {
                fprintf(stderr, "%s\n", "Error while allocating memory");
            }
            strcat(str, ch);
            str[len] = '\0';
            memset(ch, '\0', BUFF * sizeof(ch[0]));
        }
        close(to_my_program_pipe[0]);
        printf("%s\n", str);
        free(str);

        wait(&rv);
        if (rv != 0)
        {
            fprintf(stderr, "%s %d\n", "phantomjs exit status ", rv);
            exit(1);
        }
    }
    else
    {
        dup2(to_phantomjs_pipe[0], 0);
        dup2(to_my_program_pipe[1], 1);

        close(to_phantomjs_pipe[1]);
        close(to_my_program_pipe[0]);
        close(to_phantomjs_pipe[0]);
        close(to_my_program_pipe[1]);

        execlp("phantomjs", "phantomjs", "--ssl-protocol=TLSv1", "/dev/stdin", (char *)NULL);
    }

    return 0;
}
