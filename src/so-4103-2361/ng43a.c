/* SO 4103-2621 */
/* Variant 2 - minimal printing */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum { MAX_ITERATION = 10000000 };

static bool duplicate_digits_2(int value)
{
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", value);
    char *ptr = buffer;
    char c;
    while ((c = *ptr++) != '\0')
    {
        if (strchr(ptr, c) != NULL)
            return true;
    }
    return false;
}

int main(void)
{
    int count = 0;
    for (int i = 0; i < MAX_ITERATION; i++)
    {
        if (!duplicate_digits_2(i))
            count++;
    }
    printf("%d\n", count);
    return 0;
}
