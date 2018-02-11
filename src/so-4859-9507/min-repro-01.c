/* SO 4859-9507 - Streamined reproduction of PhantomJS bug */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void err_exit(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int main(int argc, char **argv)
{
    pid_t pid;
    int extra = 1;      // Enable bug by default
    int to_child[2];
    int fr_child[2];

    if (argc == 2 && strcmp(argv[1], "fix") == 0)
        extra = 0;      // Disable bug on 'fix' request

    if (pipe(to_child) != 0 || pipe(fr_child) != 0)
        err_exit("Pipe error");
    if ((pid = fork()) == -1)
        err_exit("Fork error");

    if (pid != 0)
    {
        printf("Bug is %sfixed\n", (extra == 0) ? "" : "not ");

        close(fr_child[1]);
        close(to_child[0]);

        char js_program[] =
            "var page=require(\'webpage\').create();page.onInitialized"
            "=function(){page.evaluate(function(){delete window._phantom;"
            "delete window.callPhantom;});};page.onResourceRequested="
            "function(requestData,request){if((/http:\\/\\/.+\?\\\\.css/gi)"
            ".test(requestData[\'url\'])||requestData.headers[\'Content-Type\']"
            "==\'text/css\'){request.abort();}};page.settings.loadImage=false;"
            "page.settings.userAgent=\'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 "
            "(KHTML, like Gecko) Chrome/41.0.2228.0 Safari/537.36\';"
            "page.open(\'https://stackoverflow.com\',function(status){"
            "if(status!==\'success\'){phantom.exit(1);}else{console.log("
            "page.content);phantom.exit();}});";

        // This line writes, or does not write, the null after the JS script
        write(to_child[1], js_program, strlen(js_program) + extra);
        close(to_child[1]);

        char buffer[1024];
        int read_chars;

        while ((read_chars = read(fr_child[0], buffer, sizeof(buffer))) > 0)
            printf("%.*s", read_chars, buffer);
        close(fr_child[0]);
    }
    else
    {
        dup2(to_child[0], 0);
        dup2(fr_child[1], 1);
        close(fr_child[0]);
        close(fr_child[1]);
        close(to_child[0]);
        close(to_child[1]);

        execlp("phantomjs", "phantomjs", "--ssl-protocol=TLSv1", "/dev/stdin", (char *)NULL);
        err_exit("failed to execute phantomjs");
    }

    return 0;
}
