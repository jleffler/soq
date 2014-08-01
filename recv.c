#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>  /* inet_ntoa() */

#define WRAPPED_HEADER "stderr.h"
#include "wraphead.h"

static void receiveFile(int sock, int port, const char *filename)
{
    //Keep reading data from the socket
    FILE *fp = fopen(filename, "ab");
    if (fp == 0)
        err_syserr("failed to open file %s", filename);

    printf("\nWaiting for data on port %d\n", port);
    while (1)
    {
        char recvData[BUFSIZ]; // Buffer to store received data
        struct sockaddr_storage addr;
        struct sockaddr_in *client_addr = (struct sockaddr_in *)&addr;
        memset(recvData, 0, sizeof(recvData));
        socklen_t addr_len = sizeof (struct sockaddr_storage);
        int bytesRead = recvfrom(sock, recvData, sizeof(recvData), 0,
                (struct sockaddr *) &client_addr, &addr_len);
        if (bytesRead < 0)
            err_syserr("Failed to read from socket");
        err_remark("Read %d bytes\n", bytesRead);
        for (int x = 0; x < bytesRead; x++)
        {
            fputc(recvData[x], fp);
        }
        fflush(fp);

        // Print out who we're receiving from and what we're receiving
        //char *rem_host = inet_ntoa(client_addr->sin_addr);
        //int   rem_port = ntohs(client_addr->sin_port);
        //printf("Receiving %d bytes from %s:%d\n", bytesRead, rem_host ? rem_host : "<unknown>", rem_port);
    }
    fclose(fp);
}

int main(int argc, char **argv)
{
    int fd;
    struct sockaddr_storage addr;
    struct sockaddr_in *server_addr = (struct sockaddr_in *)&addr;

    memset(&addr, 0, sizeof(addr));
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr->sin_port = htons(5190);

    err_setarg0(argv[0]);
    if (argc > 1)
        err_usage("");
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        err_syserr("Failed to open DGRAM socket");
    if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0)
        err_syserr("Failed to bind DGRAM socket");
    receiveFile(fd, 5190, "dummy.text");

    return(0);
}

