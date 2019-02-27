/* SO 4844-3136 - file streams version A */
#include <unistd.h>
#include "stderr.h"

static void check_fp(FILE *fp, const char *name)
{
    char buffer[1024];

    err_remark("About to read from %s\n", name);
    size_t nbytes = fread(buffer, sizeof(char), sizeof(buffer), fp);
    if (nbytes <= 0)
        err_sysrem("Failed to read %s: ", name);
    else
    {
        err_remark("Got normal read of %zu bytes on %s\n", nbytes, name);
        printf("Data: [%.*s]\n", (int)nbytes - 1, buffer);
    }

    err_remark("About to write to %s\n", name);
    char message[] = "  'Twas brillig and the the slithy toves\n"
                     "  Did gyre and gimble in the wabe.\n"
                     "  All mimsy were the borogroves,\n"
                     "  And the mome raths outgrabe.\n";
    nbytes = fwrite(message, sizeof(char), sizeof(message) - 1, fp);
    if (nbytes == 0)
        err_sysrem("Failed to write to %s: ", name);
    else if (nbytes == sizeof(message) - 1)
        err_remark("Successfully wrote %d bytes to %s\n", (int)nbytes, name);
    else
        err_remark("Got a short write (%zu bytes written; %zu expected) on %s\n",
                   nbytes, (sizeof(message) - 1), name);
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
