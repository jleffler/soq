/* SO 4859-9507 */
#include <stdio.h>

int main(int argc, char **argv)
{
    int rc = 1;
    FILE *fp;
    if (argc != 2)
        fprintf(stderr, "Usage: %s file\n", argv[0]);
    else if ((fp = fopen(argv[1], "r")) == 0)
        fprintf(stderr, "%s: failed to open file %s for reading\n", argv[0], argv[1]);
    else
    {
        fprintf(stderr, "%s: working\n", argv[0]);
        char buffer[1024];
        size_t nbytes;
        while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), fp)) != 0)
        {
            for (int i = 0; i < 100; i++)
                printf("%s: iter %d - %zu [%.*s]\n", argv[0], i, nbytes, (int)nbytes, buffer);
        }
        fclose(fp);
        rc = 0;
        fprintf(stderr, "%s: exiting\n", argv[0]);
    }
    return rc;
}
