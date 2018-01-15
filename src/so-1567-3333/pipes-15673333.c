#include "posixver.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

extern int  makeargv(char *line, char *seps, char ***args);
extern void err_sys(const char *msg);
static void dump_argv(char **argv);
static void dump_fds(void);

int main(void)
{
    char buf[80];

    printf("            <(^_^)> \nHello \n I am your console and I am here to help you\n");
    printf("    If you don't need me anymore just say \"bye\"\n");
    fflush(stdout);
    dump_fds();
    printf("(>^_^)> ");
    while (fgets(buf, sizeof(buf), stdin) != 0 && strcmp(buf, "bye\n") != 0)
    {
        pid_t pid;
        char **argp;
        int fdleft[2]  = { -1, -1 };
        int fdright[2] = { -1, -1 };
        int pnum = 0;
        int ploc[16];
        int j = makeargv(buf, " \n", &argp);

        ploc[0] = 0;
        if (j > 16)
            j = 16;
        for (int i = 0; i < j; i++)
        {
            if (strcmp(argp[i], "|") == 0)
            {
                argp[i] = NULL;
                ploc[++pnum] = i+1;
            }
        }

        printf("pnum = %d\n", pnum);
        for (int k = 0; k < pnum+1; k++)
            printf("ploc[%d] = %d\n", k, ploc[k]);

        for (int i = 0; i < pnum+1; i++)
        {
            if (i != pnum)
            {
                if (pnum > 0)
                {
                    if (pipe(fdright) != 0)
                        err_sys("pipe");
                    //printf("%d: fdright = { %d, %d }\n", i, fdright[0], fdright[1]);
                    //dump_fds();
                }
            }

            if ((pid = fork()) < 0)
                err_sys("fork failed");
            else if (pid == 0)
            {
                /* Child */
                int targ;
                //dump_fds();
                if (i != pnum)
                {
                    dup2(fdright[1], 1);
                    close(fdright[0]);
                    close(fdright[1]);
                }
                if (i != 0)
                {
                    dup2(fdleft[0], 0);
                    close(fdleft[0]);
                    close(fdleft[1]);
                }
                targ = ploc[i];
                dump_argv(&argp[targ]);
                dump_fds();
                execvp(argp[targ], &argp[targ]);
                fprintf(stderr, "(-_-) I'm sorry the exec failed\n");
                exit(1);
            }

            if (i != 0)
            {
                //dump_fds();
                //printf("%d: fdleft = { %d, %d }\n", i, fdleft[0], fdleft[1]);
                assert(fdleft[0] != -1 && fdleft[1] != -1);
                close(fdleft[0]);
                close(fdleft[1]);
                //dump_fds();
            }

            printf("PID %d launched\n", pid);
            fdleft[0] = fdright[0];
            fdleft[1] = fdright[1];
        }

        //dump_fds();
        //printf("%d: fdleft = { %d, %d }\n", -1, fdleft[0], fdleft[1]);
        close(fdleft[0]);
        close(fdleft[1]);
        free(argp);
        //dump_fds();

        int corpse;
        int status;
        while ((corpse = waitpid(0, &status, 0)) > 0)
            printf(":-( PID %d status 0x%.4X\n", corpse, status);

        printf("\n(>^_^)> ");
    }
    printf("  v(^o^)^ BYE BYE!\n");
}

static void dump_argv(char **argv)
{
    int n = 0;
    char **args;
    args = argv;
    while (*args++ != 0)
        n++;
    fprintf(stderr, "%d: %d args\n", getpid(), n);
    args = argv;
    while (*args != 0)
        fprintf(stderr, "[%s]\n", *args++);
    fprintf(stderr, "EOA\n");
}

/* Report on open file descriptors (0..19) in process */
static void dump_fds(void)
{
    struct stat b;
    char buffer[32];
    sprintf(buffer, "%d: ", getpid());
    char *str = buffer + strlen(buffer);
    for (int i = 0; i < 20; i++)
        *str++ = (fstat(i, &b) == 0) ? 'o' : '-';
    *str++ = '\n';
    *str = '\0';
    fputs(buffer, stderr);
}

int makeargv(char *line, char *seps, char ***args)
{
    enum { MAX_ARGS = 32 };
    char **argv = malloc(32 * sizeof(char *));  // Lazy!
    if (argv == 0)
        err_sys("out of memory in makeargv()");
    int n;
    char **argp = argv;
    char  *str = line;
    for (n = 0; n < MAX_ARGS - 1; n++)
    {
        str += strspn(str, seps);
        if (*str == '\0')
            break;
        *argp++ = str;
        int len = strcspn(str, seps);
        if (len == 0)
            break;
        str[len] = '\0';
        str += len + 1;
    }
    *argp = 0;
    dump_argv(argv);
    *args = argv;
    return(n);
}

void err_sys(const char *msg)
{
    int errnum = errno;
    char *errmsg = strerror(errnum);
    fprintf(stderr, "%s (%d: %s)\n", msg, errnum, errmsg);
    exit(1);
}
