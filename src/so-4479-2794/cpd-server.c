#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include<stdlib.h>
#include<limits.h>
#include <sys/stat.h>
#include<dirent.h>
 
int main(int argc, char* argv[])
{
  int listenfd = 0;
  int connfd = 0;
  struct sockaddr_in serv_addr;
  char sendBuff[1025];
  int numrv;
  long tmp = 0;
  size_t fnlen = 0;
  char *endptr = NULL, *fname = NULL, *p = NULL,
  path[PATH_MAX] = "";
  struct dirent *de;
  struct stat t_stat, min_stat;
  int src_fd, dst_fd, c, err;
  unsigned char buffer[4096];
 
 
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
 
  printf("Socket retrieve success\n");
 
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);
 
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
 
  if(listen(listenfd, 10) == -1)
  {
    printf("Failed to listen\n");
    return -1;
  }
 
 
 
  while(1){
 
    int number;
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
 
 
    // Receive  the file, unable to implement.
 
 
 
 
 
 
 
 
 
  }
    return 0;
  }
