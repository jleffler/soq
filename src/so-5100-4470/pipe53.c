#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 100

static char const *errMsgPipe = "signal handled SIGPIPE\n";
static int errMsgPipeLen;

static void handler(int x)
{
    if (x == SIGPIPE)
        write(2, errMsgPipe, errMsgPipeLen);
}

int main(void)
{
    errMsgPipeLen = strlen(errMsgPipe);
    char bufin[BUFSIZE] = "empty";
    char bufout[] = "hello soner";
    int bytesin;
    pid_t childpid;
    int fd[2];

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = 0;
    sigfillset(&sa.sa_mask);
    sa.sa_handler = handler;
    sigaction(SIGPIPE, &sa, 0);

    if (pipe(fd) == -1)
    {
        perror("Failed to create the pipe");
        return 1;
    }

    close(fd[0]); // <-- it's in order for no process has an open read descriptor

    int val = -999;
    bytesin = strlen(bufin);
    childpid = fork();
    if (childpid == -1)
    {
        perror("Failed to fork");
        return 1;
    }

    /*
     * close(fd[0]); <---- if it were here, we wouldn't get expected error and signal
     *                      since, parent can be reached to write(fd[1], .... ) call
     *                      before the child close(fd[0]); call defined here it.
     *          It means there is by child open read descriptor seen by parent.
     */

    // sleep(1);     <---- we can prove my saying by calling sleep() here

    if (childpid)
    {
        val = write(fd[1], bufout, strlen(bufout) + 1);
        if (val < 0)
        {
            perror("writing process error");
        }
    }
    else
    {
        bytesin = read(fd[0], bufin, BUFSIZE);
    }
    fprintf(stderr, "[%ld]:my bufin is {%.*s}, my bufout is {%s}\n",
            (long)getpid(), bytesin, bufin, bufout);

    return 0;
}
