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
    const char *pad = "";
    for (int i = 0; i < MAX_ITERATION; i++)
    {
        if (!duplicate_digits_2(i))
        {
            count += printf("%s%d", pad, i);
            pad = " ";
            if (count > 72)
            {
                putchar('\n');
                count = 0;
                pad = "";
            }
        }
    }
    putchar('\n');
    return 0;
}
