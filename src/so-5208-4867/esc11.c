/* SO 5246-1162 */
#include <stdio.h>
#include "escape.h"

int main(void)
{
    static const char *words[] =
    {
        "'\"\"TEST\"\"'",
        "\\''\\\"\"\"\\\"TEST1\\\"\"\"\\\"'\\'",
        "'\\'\"\\\"\\\"\"TEST2\"\\\"\\\"\"\\''",
    };
    enum { NUM_WORDS = sizeof(words) / sizeof(words[0]) };

    for (int i = 0; i < NUM_WORDS; i++)
    {
        printf("Word %d: [[%s]]\n", i, words[i]);
        char buffer[256];
        if (escape_simple(words[i], buffer, sizeof(buffer)) >= sizeof(buffer))
            fprintf(stderr, "Escape failed - not enough space!\n");
        else
            printf("Escaped: [[%s]]\n", buffer);
    }

    return 0;
}
