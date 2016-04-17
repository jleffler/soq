#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct {
    char output[50]; // I'd like to use this var to output the expression converted
    int top = -1; // starts as -1 to show as empty  
} stack;

void push(char element);
char pop();

int main()
{
    char exp[50];   
    printf("Enter the postfix expression :");
    scanf("%s", exp);

    for (int i=0;exp[i]!='\0';i++){
        // Reads the expression until the end and push. 

        if(exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/'||exp[i]=='^'){
        // If is an operator then take the last 2 positions of the pile, and concat like this: (op1 operator op2)

        // >> please help me to build the logic here <<< 


        }else{
         // if is not an operator then just push
         push(str[i]);
      }

    }

}

void push(char element){
    // >>>> Please help me here I don't know how to pop out the last two elements
    // and concatenate and put it back
    // example if the last 2 elements are 3 and 4: 
    // (3+4) 
    // then put (3+4) on stack.output at the right position 
}

char pop(){
    // Will use this function to pop out the expresstion that is already in the stack
    char x;
    x = stack.output[stack.top];    
    stack.top--;
    return x;   
}

