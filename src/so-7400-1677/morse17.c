/* SO 7400-1647 */
/*
** Scan Morse code distinguishing between 1 space separating letters of
** a word and 3 spaces separating words
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void decode_morse(const char *buffer)
{
    char symbol[16];
    char spaces[16];

    printf("Input:  [%s]\n", buffer);
    int offset = 0;
    int nbytes;
    int rc;
    while ((rc = sscanf(buffer + offset, "%15[-.]%15[ ]%n", symbol, spaces, &nbytes)) > 0)
    {
        printf("Symbol: [%s]", symbol);
        if (rc == 2)
        {
            size_t length = strlen(spaces);
            if (length == 3 || buffer[offset + nbytes] == '\0')
                printf(" EOW");
            else if (length != 1)
                printf(" Bogus spacing (length = %zu)", length);
            putchar('\n');
            offset += nbytes;
        }
        else
        {
            if (rc == 1)
                printf(" EOW");
            putchar('\n');
            break;
        }
    }
}

int main(void)
{
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        decode_morse(buffer);
    }

    return 0;
}
