/* SO 3958-2332 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    unsigned char c[4];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *f = fopen(argv[1], "r");

    if (f == 0)
    {
        fprintf(stderr, "%s: failed to open file %s for reading\n",
                argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    size_t nbytes = fread(c, sizeof(char), sizeof(c), f);
    fclose(f);

    if (nbytes == 2)
    {
        /* UTF16 with BOM only? */
        if (c[0] == 0xFE && c[1] == 0xFF)
            printf("UTF-16BE\n");
        else if (c[0] == 0xFF && c[1] == 0xFE)
            printf("UTF-16LE\n");
        else
            printf("Two non-BOM bytes 0x%.2X and 0x%.2X\n", c[0], c[1]);
    }
    else if (nbytes == 4)
    {
        if (memcmp(c, "\xFF\xFE\x00\x00", 4) == 0)
            printf("UTF-32LE (or UTF-16LE followed by U+0000)\n");
        else if (memcmp(c, "\x00\x00\xFE\xFF", 4) == 0)
            printf("UTF-32BE\n");
        else if (memcmp(c, "\xFE\xFF", 2) == 0)
            printf("UTF-16BE\n");
        else if (memcmp(c, "\xFF\xFE", 2) == 0)
            printf("UTF-16LE\n");
        else
            printf("Four non-BOM bytes 0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X\n",
                   c[0], c[1], c[2], c[3]);
    }
    else
    {
        printf("Odd-ball data size %zu (expected 2 or 4) - no diagnosis\n", nbytes);
        return EXIT_FAILURE;
    }

    return 0;
}
