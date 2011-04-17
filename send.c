#include "posixver.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "stderr.h"

#define bzero(b,len) (memset((b), '\0', (len)), (void)0)

enum { DEBUG = 1 };

static void sendFile(int sock, const char *filename, char *address, int port)
{
    // Announce who we're sending data to
    if (DEBUG)
        printf("\nSending %s to %s:%d\n", filename, address, port);

    // Open file
    FILE * file = fopen(filename, "rb");
    if (file == 0)
        err_syserr("Failed to open file %s", filename);

    // Get size of the file
    fseek(file, 0, SEEK_END);
    int filesize = ftell(file);
    rewind(file);

    int curPos = 0;
    int dataSize = 0;

    while (curPos < filesize)
    {
        struct sockaddr_in server_addr; 
        struct hostent *recvr;
        char sendData[BUFSIZ]; // stores message to be sent
        memset(sendData, 0, BUFSIZ);

        int byte, i;
        for (i = 0; i < BUFSIZ; i++){
            if ((filesize - curPos) > 0) {
                byte = fgetc(file);
                sendData[i] = byte;
                curPos++;
                dataSize++;
            }
            else
                break;
        }

        recvr = gethostbyname(address);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr = *((struct in_addr *) recvr->h_addr_list[0]);
        bzero(&(server_addr.sin_zero), 8);

        if(DEBUG) {
            char tempData[1201];
            strncpy(tempData, sendData, 1200);
            tempData[1201] ='\0';
            printf("SEND:\n%s\n\n\n", tempData);
        }

        if (sendto(sock, sendData, dataSize, 0,
                (struct sockaddr *) &server_addr, sizeof (struct sockaddr)) < 0)
            err_syserr("Failed to send %d bytes\n", dataSize);
        dataSize = 0;
    }

    fclose(file);
}

int main(int argc, char **argv)
{
    int fd;

    err_setarg0(argv[0]);
    if (argc > 1)
        err_usage("");
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        err_syserr("Failed to open DGRAM socket");
    sendFile(fd, "/etc/passwd", "localhost", 5190);

    return(0);
}

