/* SO 3895-9797 */
#include "posixver.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
** POSIX lists async-signal safe functions.
**
** Curiously, amongst the many omissions, you find that the str*()
** functions are not safe (officially).  It's hard to see how strlen()
** could be a problem, though strxfrm() would be a different matter.
**
** How to format a string for printing with write()?  Messy!
*/

static inline void rev_str(char *bgn, char *end)
{
    while (bgn < end)
    {
        char t = *bgn;
        *bgn++ = *end;
        *end-- = t;
    }
}

static inline char *cpy_str(char *dst, const char *src)
{
    while ((*dst++ = *src++) != '\0')
        ;
    return dst - 1;
}

static inline char *cvt_uns(char *dst, unsigned val)
{
    char *bgn = dst;
    do
    {
        *dst++ = val % 10 + '0';
        val /= 10;
    } while (val != 0);
    rev_str(bgn, dst-1);
    *dst = '\0';
    return dst;
}

static void sigIntHandler(int signum)
{
    char buffer[128];
    char *dst = buffer;
    dst = cpy_str(dst, "Ctrl-C (");
    dst = cvt_uns(dst, (unsigned)signum);
    dst = cpy_str(dst, ")\n");

    /*fprintf(stderr, "Ctrl-C (%d)\n", signum);*/
    if (write(STDERR_FILENO, buffer, dst - buffer) != (dst - buffer))
        exit(EXIT_FAILURE);
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

        int len = strlen(block);
        if (len > 0 && block[len-1] == '\n')
            block[--len] = '\0';
        if (strcmp(block, "exit") == 0)
        {
            fprintf(stderr, "Exiting\n");
            exit(1);
        }
        printf("Read: %d [%.*s]\n", len, len, block);
    }
    return 0;
}
