#include <stdio.h>
//#include <conio.h>
#include  <stdlib.h>
#include  <string.h>

#define SIZE 30
typedef struct fix_tag
{
    char s[SIZE][SIZE], dest[SIZE] ;
    char t1[2], t2[2] ;
    char ch1[SIZE], ch2[SIZE], ch3[SIZE] ;
    int i, top ;
}postfix ;

/********** Function Declaration begins **********/
void initialization ( postfix * ) ;
void expression ( postfix *, char * ) ;
void push ( postfix *, char * ) ;
void pop ( postfix *, char * ) ;
void trans ( postfix * ) ;
void display ( postfix ) ;
/********** Function Declaration ends **********/

int main(void)
{
    postfix PF ;
    char exp[SIZE] ;
    //clrscr() ;

    initialization ( &PF ) ;

    printf ( "\n\t\t Enter any Postfix expression :\n " ) ;
    gets ( exp ) ;

    expression ( &PF, exp ) ;
    trans ( &PF ) ;

    printf ( "\nThe resultant infix expression is: " ) ;
    display ( PF ) ;

    //getch() ;
}


/********** Initialization of Strucutre variable **********/
/********** Function Definition begins **********/
void initialization ( postfix *p )
{
    p -> i = 0 ;
    p -> top = -1 ;
    strcpy ( p -> dest, "") ;
}
/********** Function Definition ends **********/


/********** String Copy **********/
/********** Function Definition begins **********/
void expression ( postfix *p, char *c )
{
    strcpy ( p -> dest, c ) ;
}
/********** Function Definition ends **********/


/********** Pushing expression **********/
/********** Function Definition begins **********/
void push ( postfix *p, char *str )
{
    if ( p -> top == SIZE - 1 )
    printf ( "\nStack Overflow." ) ;
    else{
        p -> top++ ;
        strcpy ( p -> s[p -> top], str ) ;
    }
}
/********** Function Definition ends **********/


/********** Popping expression **********/
/********** Function Definition begins **********/
void pop ( postfix *p, char *a )
{
    if ( p -> top == -1 )
    printf ( "\nStack is empty." ) ;
    else{
    strcpy ( a, p -> s[p -> top] ) ;
    p -> top-- ;
    }
}
/********** Function Definition ends **********/


/********** Postfix to Infix **********/
/********** Function Definition begins **********/
void trans ( postfix *p ){
    while ( p -> dest[p -> i] ){
        if( p -> dest[p -> i] == ' ' ){
            p -> i++ ;
        }
        if ( p -> dest[p -> i] == '%' || p -> dest[p -> i] == '*' ||
            p -> dest[p -> i] == '-' || p -> dest[p -> i] == '+' ||
            p -> dest[p -> i] == '/' || p -> dest[p -> i] == '$' ){

            pop ( p, p -> ch2 ) ;
            pop ( p, p -> ch3 ) ;

            p -> t1[0] = p -> dest[p -> i] ;
            p -> t1[1] = '\0' ;
            strcpy (p -> ch1, "(");

            strcat ( p -> ch1, p -> ch3 ) ;
            strcat ( p -> ch1, p -> t1 ) ;
            strcat ( p -> ch1, p -> ch2 ) ;

            strcat ( p -> ch1, ")" ) ;

            push ( p, p -> ch1 ) ;
        }else{
            p -> t1[0] = p -> dest[p -> i] ;
            p -> t1[1] = '\0' ;
            strcpy ( p -> t2, p -> t1 ) ;
            push ( p, p -> t2 ) ;
        }
        p -> i++ ;
    }
}
/********** Function Definition ends **********/


/********** Displaying expression **********/
/********** Function Definition begins **********/
void display ( postfix p ){
    char *t ;
    t = p.s[0] ;
    while ( *t ){
        printf ( "%c ", *t ) ;
        t++ ;
    }
}
