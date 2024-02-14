#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *prog = "argc37";
    if (argc > 2)
        fprintf(stderr, "Usage: %s [program]\n", argv[0]);
    else
    {
        if (argc == 2)
            prog = argv[1];

        char *args[] = { NULL };
        execv(prog, args);
        fprintf(stderr, "%s: failed to execute '%s' with zero arguments (%d: %s)\n",
                argv[0], prog, errno, strerror(errno));
    }
    return 1;
}
