#include "posixver.h"
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    struct stat statbuf;
    int sockfd;
    //int sockfd, newSocket;
    //int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;
    //char buf[PATH_MAX];
    //size_t fnlen = 0;
    //char *endptr = NULL, *fname = NULL, *p = NULL;
    struct dirent *de;
    //DIR *dr;
    char message[1024];
    char byte[1024];
    unsigned char buffer[4096];
    /* Create a socket first */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    /* Attempt a connection */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    if (argc < 2) /* validate at least 3 arguments, argv[0] is exe name */
    {
        fprintf(stderr, "error: insufficient input.\n");
        return 1;
    }

    char *path = NULL;
    path = argv[1];
    printf("The path of the file is : %s\n", path);

    while (1)
    {
        DIR *dr = opendir(path);

        if (dr == NULL)
        {
            fprintf(stderr, "Could not open current directory.\n");
            return 1; /* returning a positive number indicates error */
        }

        while ((de = readdir(dr)) != NULL)
        {
            char buf[PATH_MAX] = ""; /* buf to hold "path/fname" */

            /* build relative filename (e.g. "path/fname")  */
            strcpy(buf, path);    /* copy path to buf */
            strcat(buf, "/");     /* concat dir sep   */
            strcat(buf, de->d_name); /* concat filename  */

            /* skip dot files */
            if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
                continue;

            stat(de->d_name, &statbuf);

            int size = statbuf.st_size;

            FILE *pf;
            unsigned long fsize;

            pf = fopen(buf, "rb+");
            if (pf == NULL)
            {
                printf("File not found!\n");
                printf("The file is :%s \n", buf);
                return 1;
            }
            else
            {
                printf("Found file: %s\n", buf);
                fseek(pf, 0, SEEK_END);
                fsize = ftell(pf);
                rewind(pf);

                printf("File contains %ld bytes\n", fsize);
                printf("Sending the file.....\n");
            }

            sprintf(message, "%d", size);
            strcat(message, ",");
            strcat(message, de->d_name);
            strcat(message, ",");
            sprintf(byte, "%ld", fsize);
            strcat(message, byte);

            send(sockfd, message, strlen(message), 0);
            printf("the message to be sent is %s \n", message);

            while (1)
            {
                int bytes_read = fread(buffer, sizeof(char), sizeof(buffer), pf);
                if (bytes_read == 0)
                    break;

                if (bytes_read < 0)
                {
                    error("ERROR reading from file");
                }

                void *p = buffer;
                while (bytes_read > 0)
                {
                    int bytes_written = write(sockfd, buffer, bytes_read);
                    if (bytes_written <= 0)
                    {
                        error("ERROR writing to socket\n");
                    }
                    bytes_read -= bytes_written;
                    p += bytes_written;
                }
            }
            fclose(pf);
            printf("The File has been sent\n");
            printf("Closing Connection.\n");
            close(sockfd);
            sockfd = -1;
        }
    }

    return 0;
}
