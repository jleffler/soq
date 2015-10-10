#include <assert.h>
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
            assert(bufpos == 0);
            buffer[bufpos++] = c;
            while ((c = getchar()) != EOF)
            {
                buffer[bufpos++] = c;
                if (!isdigit(c))
                {
                    flush_buffer(buffer, bufpos - 1);
                    ungetc(buffer[bufpos-1], stdin);
                    bufpos = 0;
                    break;
                }
                else if (bufpos == 4)
                {
                    putchar('\n');
                    flush_buffer(buffer, bufpos);
                    bufpos = 0;
                    break;
                }
            }
        }
    }
    if (bufpos > 0)
        flush_buffer(buffer, bufpos);
    return 0;
}
