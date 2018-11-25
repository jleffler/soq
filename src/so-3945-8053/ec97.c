/* SO 3945-8053 Caesar Cipher - Encryption/Decryption */

#include "posixver.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// #include "stderr.h"
void err_setarg0(const char *argv0);
void err_usage(const char *usestr);
void err_error(const char *errmsg);

int main(int argc, char **argv)
{
    char  *buffer = 0;
    size_t buflen = 0;

    err_setarg0(argv[0]);
    if (argc != 2)
        err_usage("offset");
    int offset = atoi(argv[1]) % 26;
    if (offset < 0)
        err_error("Offset should be a positive number 1..25\n");

    while (getline(&buffer, &buflen, stdin) != -1)
    {
        char *ptr = buffer;
        unsigned char u;
        while ((u = (unsigned char)*ptr++) != '\0')
        {
            if (isupper(u))
                u = (u - 'A' + offset) % 26 + 'A';
            else if (islower(u))
                u = (u - 'a' + offset) % 26 + 'a';
            putchar(u);
        }
    }

    free(buffer);
    return 0;
}

// Minimal stderr.c code
static const char *arg0 = "unknown";
void err_setarg0(const char *argv0)
{
    arg0 = argv0;
}
void err_usage(const char *usestr)
{
    fprintf(stderr, "Usage: %s %s\n", arg0, usestr);
    exit(EXIT_FAILURE);
}
void err_error(const char *errmsg)
{
    fprintf(stderr, "%s: %s\n", arg0, errmsg);
    exit(EXIT_FAILURE);
}
