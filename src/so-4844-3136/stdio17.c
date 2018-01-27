/* SO 4844-3136 - file streams version B */
#include "stderr.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void check_fp(FILE *fp, const char *name)
{
    char buffer[1024];

    err_remark("About to read from %s\n", name);
    if (fgets(buffer, sizeof(buffer), fp) == 0)
        err_sysrem("Failed to read %s: ", name);
    else
    {
        size_t nbytes = strlen(buffer);
        err_remark("Got normal read of %zu bytes on %s\n", nbytes - 1, name);
        printf("Data: [%.*s]\n", (int)nbytes - 1, buffer);
    }

    err_remark("About to write to %s\n", name);
    char message[] = "  'Twas brillig and the the slithy toves\n"
                     "  Did gyre and gimble in the wabe.\n"
                     "  All mimsy were the borogroves,\n"
                     "  And the mome raths outgrabe.\n";
    if (fputs(message, fp) < 0)
        err_sysrem("Failed to write to %s: ", name);
    else
        err_remark("Successfully wrote %zu bytes to %s\n", sizeof(message)-1, name);
}

int main(int argc, char **argv)
{
    if (argc != 0)
        err_setarg0(argv[0]);

    check_fp(stdin,  "stdin");
    check_fp(stdout, "stdout");
    check_fp(stderr, "stderr");
    return 0;
}
