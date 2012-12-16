#include <stdlib.h> 
#include <stdio.h>
#include <sys/types.h> //fork
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> //lock
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "sys/ipc.h"
#include "sys/sem.h"

int child;
int cs[3];
int fd[2];
int t;
int parent;
int child;

void okay(int sign)
{
  t = 0;
}

void rr(int sign)
{
  char b[50];
  while(read(fd[0], &b, 50)<0) sleep(0.5);
  printf("Got this: %s \n", b);
}

void ch(int argc, char** argv)
{
  printf("Mypid: %i\n", getpid());
  close(fd[0]);
  while(t==1) sleep(1);
  srand((unsigned)time(NULL)); // init
  int x,y,z,r,pid;
  x = rand() % 101; y = rand() % 101; z = rand() % 101; r = rand() % 101;
  pid = getpid();
  char b[50];
  sprintf(b, "%i %i %i %i %i", pid, x, y, z, r);
  while(write(fd[1], b, 50)<0) sleep(0.2);
  kill(parent, SIGUSR2);
  close(fd[1]);
}

int main(int argc, char** argv)
{
  if(argc < 4)
  {
    printf("Too few args!\n");
    return 0;
  }
  pipe(fd);
  t = 1;
  parent = getpid();
  signal(SIGUSR1, okay);
  child = fork();
  if(child < 0) perror("FORK");
  if(child > 0)
  {
    cs[0] = child;

    child = fork();
    if(child < 0) perror("FORK");
    if(child > 0)
    {

      cs[1] = child;

      child = fork();
      if(child < 0) perror("FORK");
      if(child > 0)
      {
        cs[2] = child; // MAIN
        printf("%i %i %i\n", cs[0], cs[1], cs[2]);
        close(fd[1]);
        signal(SIGUSR2, rr);
        kill(cs[0], SIGUSR1); kill(cs[1], SIGUSR1); kill(cs[2], SIGUSR1);
        int status;

            waitpid(cs[0], &status, 0);
            waitpid(cs[1], &status, 0);
            waitpid(cs[2], &status, 0);
            close(fd[0]);

      }else
      { // ch 3
        ch(argc, argv);
      }   

    }else
    { // ch 2
      ch(argc, argv);
    }  

  }else
  { // ch 1
    ch(argc, argv);
  }
  return 0;
}
