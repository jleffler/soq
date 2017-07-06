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
  int sockfd;
  struct sockaddr_in serv_addr;
  size_t fnlen = 0;
  struct dirent *de;
  struct stat t_stat;
  unsigned char buffer[4096];
  int fd;
  char recvbuf[1024];
  char result[1024];


  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  printf("Socket retrieve success\n");

  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(buffer, '0', sizeof(buffer));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

  if(listen(listenfd, 10) == -1)
  {
    printf("Failed to listen\n");
    return -1;
  }

  connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);

  recv(connfd, recvbuf, sizeof recvbuf -1, 0);
  strcpy(result,recvbuf);
  printf("String recieved = %s\n", result);


   int i = 0;
   char *p = strtok (result, ",");
   char *array[3];

   while (p != NULL)
   {
       array[i++] = p;
       p = strtok (NULL, ",");
   }
/*
   for (i = 0; i < 3; ++i){
       printf("%s\n", array[i]);
     }
*/

   char* size = array[0];
   char* filename = array[1];
   char* bytes = array[2];

   printf("The Size of file: %s \n",size);
   printf("The name of the Filename:%s \n",filename);
   printf("The No.of Bytes:%s\n",bytes);


   FILE* fp;




  return 0;
}
