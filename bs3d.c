#include <ctype.h>
#include <stdio.h>

static inline void flush_buffer(const char *buffer, int buflen)
{
    for (int i = 0; i < buflen; i++)
        putchar(buffer[i]);
}

int main(void)
{
    char buffer[4];
    int bufpos = 0;
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c != '\\')
            putchar(c);
        else
        {
            buffer[bufpos++] = c;
            while ((c = getchar()) != EOF)
            {
                if (!isdigit(c))
                {
                    flush_buffer(buffer, bufpos);
                    ungetc(c, stdin);
                    bufpos = 0;
                    break;
                }
                else if (bufpos == 3)
                {
                    putchar('\n');
                    flush_buffer(buffer, bufpos);
                    putchar(c);
                    bufpos = 0;
                    break;
                }
                else
                    buffer[bufpos++] = c;
            }
        }
    }
    if (bufpos > 0)
        flush_buffer(buffer, bufpos);
    return 0;
}
