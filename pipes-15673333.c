#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern int  makeargv(char *line, char *seps, char ***args);
extern void err_sys(const char *msg);

int main(void)  
{
    char **argp;
    int i, j;
    char buf[80];
    pid_t pid;
    int pnum;   
        //pipe number
    int ploc[16];   
        //pipe location 
        //(this has a max of 12 possible pipes)
    int targ;
    int fdleft[2], fdright[2];

    printf("            <(^_^)> \nHello \n I am your console and I am here to help you \n");
    printf("    If you dont need me anymore just say \"bye\" ");
    fflush(stdout);
    write(1, "\n(>^_^)> ", 8);
    while (strcmp(fgets(buf, 80, stdin), "bye\n")!=0)
    {        
        j=makeargv(buf, " \n", &argp); //this breaks the line up and returns the number of commands 
        pnum = 0;
        ploc[0] = 0;
        if (j > 16) j = 16;
        for (i=0;i<j;i++)
        {
            if ( strcmp(argp[i], "|") == 0)
            {
                argp[i]= NULL;
                ploc[pnum+1] = (i+1);
                pnum++;
            }
        } 

        for (i = 0; i < (pnum+1); i++) 
        {   
            pipe(fdright);
            if (i != 0)
            {   
                dup2(fdright[1], fdleft[0]);            
            }
            pid = fork();


            switch (pid)
            {
                case -1:
                    err_sys("fork failed");
                    break;
                case 0: // child
                    if (i != pnum)
                    {
                        dup2(fdright[1], 1);
                    }
                    if (i != 0)
                    {
                        dup2(fdright[0], 0); 
                    }
                    //printf("(^o^) running pipe[%i]\n" , i);
                    targ =(ploc[i]) ;
                    execvp(argp[targ], &argp[targ]);
                    fprintf(stderr, "(-_-) I'm sorry the exec failed\n");
                    exit(1);
                default:
                    dup2(fdleft[1], fdright[1]);
                    waitpid(pid, NULL, 0);
                    close(fdright[0]);
                    close(fdright[1]);
                    //waitpid(pid, NULL, 0);
            }
        }   
        //waitpid(pid, NULL, 0);
        write(1, "\n(>^_^)> ", 8);
    }
    printf("  v(^o^)^ BYE BYE!\n");
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
    { printf("%d args:\n", n); for (char **a = argv; *a != 0; a++) printf("[%s]\n", *a); printf("EOA\n"); fflush(0); }
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
