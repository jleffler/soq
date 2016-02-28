#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static inline int max(int x, int y) { return (x > y) ? x : y; }

static void fettle_text(char *string)
{
    unsigned char *dst = (unsigned char *)string;
    unsigned char *src = dst;
    /* Leading white space */
    while (isspace(*src))
        src++;
    unsigned char c;
    while ((c = *src++) != '\0')
    {
        if (isspace(c))
        {
            /* All white space sequences become a single blank */
            c = ' ';
            while (isspace(*src))
                src++;
        }
        *dst++ = c;
    }
    /* Trailing white space (already reduced to a single blank) */
    if (dst > (unsigned char *)string && *(dst-1) == ' ')
        dst--;
    *dst = '\0';
}

int main(int argc, char **argv)
{
    struct timespec d = { .tv_sec = 0, .tv_nsec = 100000000 };
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s length 'message'\n", argv[0]);
        return 1;
    }
    int width = atoi(argv[1]);
    if (width <= 0)
    {
        fprintf(stderr, "%s: can't convert %s to positive number\n", argv[0], argv[1]);
        return 1;
    }

    const char padding[] = " ... ";
    char *message = strdup(argv[2]);
    fettle_text(message);
    int s_len = strlen(message);
    if (s_len == 0)
    {
        fprintf(stderr, "%s: argument '%s' contains no data\n", argv[0], argv[2]);
        return 1;
    }
    int t_len = s_len;
    if (t_len < width)
        t_len = width;
    int p_len = sizeof(padding) - 1;
    int m_len = 2 * (t_len + p_len) + 1;
    char *sign = malloc(m_len);
    if (sign == 0)
    {
        fprintf(stderr, "%s: failed to malloc %d bytes\n", argv[0], m_len);
        return 1;
    }

    int offset = 0;
    for (int i = 0; i < 2; i++)
    {
        int p_wid = max(width - s_len, 0);
        offset += sprintf(sign + offset, "%s%s%*.*s", message, padding, p_wid, p_wid, " ");
    }
    sign[offset] = '\0';

    printf("%zu vs %d (%s)\n", strlen(sign), 2 * (t_len + p_len), sign);
    assert(strlen(sign) == (size_t)(2 * (t_len + p_len)));

    for (int i = 0; i < 10; i++)
    {
        for (int l_len = 0; l_len < t_len + p_len; l_len++)
        {
            int r_len = t_len + p_len - l_len;
            putchar('\r');
            /* Rotate to right */
            printf("[%.*s]", width, sign + r_len);
            printf("    ");
            /* Rotate to left */
            printf("[%.*s]", width, sign + l_len);
            fflush(stdout);
            nanosleep(&d, 0);
        }
    }
    putchar('\n');

    free(message);
    free(sign);

    return 0;
}
