/* PBB - Print balanced brackets */

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const char o_bracket[] = "<[({";
static const char c_bracket[] = ">])}";
static const int debug = 0;

int main(void)
{
    char line[4096];

    while (fgets(line, sizeof(line), stdin) != 0)
    {
        size_t len = strlen(line);
        if (len <= 1)
            continue;
        assert(line[len-1] == '\n');
        line[--len] = '\0';
        printf("Input: %s\n", line);
        char stack[2048];
        int  sp = 0;
        for (size_t i = 0; i < len; i++)
        {
            char c = line[i];
            if (debug)
                printf("%zu: %c\n", i, c);
            char *s;
            if (strchr(o_bracket, c) != 0)
                stack[sp++] = c;
            else if ((s = strchr(c_bracket, c)) != 0)
            {
                if (sp <= 0)
                    printf("Oops: Close bracket '%c' at offset %zu with no matching open\n", c, i);
                else
                {
                    int n = s - c_bracket;
                    if (stack[sp-1] != o_bracket[n])
                    {
                        int cb = strchr(o_bracket, stack[sp-1]) - o_bracket;
                        printf("Oops: unbalanced bracket '%c' at offset %zu (should be '%c')\n",
                               c, i, c_bracket[cb]);
                    }
                    else
                        sp--;
                }
            }
            // else it is a non-bracketing character: ignore
        }
        if (sp > 0)
            printf("Oops: too many open brackets for the close brackets (%d unmatched '%.*s')\n",
                   sp, sp, stack);
        else
            printf("OK: balanced brackets\n");
    }
    return 0;
}

