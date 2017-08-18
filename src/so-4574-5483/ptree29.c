#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

double last;

void new_tree(int);

int main(int narg, char * argv[]){
    int n;

    n = atoi(argv[1]);
    last = pow(2,(n-1));
    new_tree(1);
    return 0;
}

void new_tree(int x){
    char buff[60];
    sprintf(buff, "Im the procces %d with pid %d and ppid %d\n",x,getpid(),getppid());
    write(1,buff,strlen(buff));
    if (x >= last) 
    return;

    if (!fork()){ 
        new_tree(2*x);
        exit(0);
    }

    if(!fork()){ 
        new_tree(2*x+1);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
}

