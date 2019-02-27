%{
/* SO 5008-7213 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int yylex(void);
void yyerror(char *msg);
int append =0;
void insertArg(char *arg, int len);
void insertComm(char *arg, int len);
char *arg_list[20];
int i,count=1;
int len;
char command[20];
%}

%union{
    float f;
    char  *id;
}

%start C
%token <id> WORD
%token  NOTOKEN
%type <id> C A

%%
A:  A   WORD    {printf("R1A: len %d %p [%s]\n", len, $2, $2); $$=$2;insertArg($2,len);count++;}
 |  /*Nothing */
                {printf("R1B: - nothing\n");}
 ;

C:  WORD
    {printf("R2A: len %d %p [%s]\n", len, $1, $1); $$=$1;insertComm($1,len);}
    A  
    {printf("R2B: len %d %p [%s]\n", len, $3, $3);}
 ;

%%

void insertComm(char *c, int len)
{
    printf("Command: %d [%s]\n", len, c);
    for (i = 0; i < len; i++)
    {
        command[i] = c[i];
    }
    arg_list[0] = &command[0];
}

void insertArg(char *arg, int len)
{
    printf("Argument: %d [%s]\n", len, arg);
    // Broken code
    // arg_list[count] = arg;
    // Fixed code (sufficiently fixed to be usable)
    arg_list[count] = strdup(arg);
    for (int i = 0; i <= count; i++)
        printf("list[%d] = %p [%s]\n", i, arg_list[i], arg_list[i]);
}

void yyerror(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int main(void)
{
    yyparse();

    for (i = 0; arg_list[i] != NULL; i++)
    {
        printf("arg_list[%d] = [%s]\n", i, arg_list[i]);
    }
    fflush(stdout);

    execvp(arg_list[0], arg_list);
    fprintf(stderr, "failed to execute '%s' (%d: %s)\n", arg_list[0], errno, strerror(errno));
    return EXIT_FAILURE;
}
