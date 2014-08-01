#include "posixver.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
    struct addrinfo *result, *rp, hints;
    int error;
    char canonname[32][256];
    int canonnum = 0;
    char ip[32][64];
    int ipnum = 0;
    struct timeval tv;
    uint64_t starttime, endtime;

    if (argc < 2)
    {
        printf("Usage: %s <address>\n", argv[0]);
        return 0;
    }

    /* Record Start time */
    gettimeofday(&tv, NULL);
    starttime = tv.tv_usec;

    memset(&hints, 0, sizeof(hints));
    memset(canonname, 0, 32 * 256 * sizeof(char));
    memset(ip, 0, 32 * 64 * sizeof(char));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    error = getaddrinfo(argv[1], NULL, &hints, &result);
    if (error != 0)
    {
        if (error == EAI_SYSTEM)
            perror("getaddrinfo");
        else
            fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));
        return -1;
    }
    strcpy(canonname[0], "");
    if (result->ai_canonname != NULL)
        strcpy(canonname[0], result->ai_canonname);
    canonnum++;

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        if (rp != result && rp->ai_canonname != NULL)
        {
            if (strcmp(rp->ai_canonname, "") != 0)
            {
                strcpy(canonname[canonnum], rp->ai_canonname);
                canonnum++;
            }
        }
        if (rp->ai_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *inaddr_ptr = (struct sockaddr_in *)rp->ai_addr;
            sprintf(ip[ipnum], "%s\n", inet_ntoa(inaddr_ptr->sin_addr));
            ipnum++;
        }
    }

    /* Gets the end time and prints out the execution time */
    gettimeofday(&tv, NULL);
    endtime = tv.tv_usec;
    printf("Execution time: %" PRIu64 " milliseconds\n", (endtime - starttime) / 100);
    printf("Official name: %s\n", canonname[0]);
    printf("Aliases:\n");
    for (int i = 1; i < canonnum; i++)
        printf("%s\n", canonname[i]);
    printf("Addresses:\n");
    for (int i = 0; i < ipnum; i++)
        printf("%s", ip[i]);
    freeaddrinfo(result);
    return 0;
}

