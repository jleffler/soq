#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s old-name new-name\n", argv[0]);
        return 1;
    }
    if (rename(argv[1], argv[2]) != 0)
    {
        int errnum = errno;
        fprintf(stderr, "%s: failed to rename '%s' to '%s'\n", argv[0], argv[1], argv[2]);
        fprintf(stderr, "%s: errno %d (%s)\n", argv[0], errnum, strerror(errnum));
        return 1;
    }
    return 0;
}
