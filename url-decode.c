#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "timer.h"

static inline int ishex(int x)
{
    return (x >= '0' && x <= '9')  ||
           (x >= 'a' && x <= 'f')  ||
           (x >= 'A' && x <= 'F');
}

static int to_hex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else
        return -1;
}

static int decode_1(const char *s, char *dec)
{
    char *o;
    const char *end = s + strlen(s);
    int c;

    for (o = dec; s <= end; ++o)
    {
        c = *s++;
        if (c == '+')
            c = ' ';
        else if (c == '%' && (!ishex(*s++)  ||
                              !ishex(*s++)    ||
                              !sscanf(s - 2, "%2x", &c)))
            return -1;
        if (dec)
            *o = c;
    }
    return o - dec - 1;
}

static int decode_2(const char *s, char *dec)
{
    char *o;
    const char *end = s + strlen(s);
    int c;

    for (o = dec; s <= end; ++o)
    {
        c = *s++;
        if (c == '+')
            c = ' ';
        else if (c == '%' && (!isxdigit(*s++)  ||
                              !isxdigit(*s++)    ||
                              sscanf(s - 2, "%2x", &c) != 1))
            return -1;
        if (dec)
            *o = c;
    }
    return o - dec - 1;
}

static int decode_3(const char *s, char *dec)
{
    char *o;
    const char *end = s + strlen(s);
    int c;

    for (o = dec; s <= end; ++o)
    {
        int c1;
        int c2 = 0;
        c = *s++;
        if (c == '+')
            c = ' ';
        else if (c == '%')
        {
            if ((c1 = to_hex(*s++)) == -1 ||
                (c2 = to_hex(*s++)) == -1)
                return -1;
            else
                c = c1 * 16 + c2;
        }
        if (dec)
            *o = c;
    }
    return o - dec - 1;
}

static int decode_4(const char *s, char *dec)
{
    char *o;
    int c;

    for (o = dec; (c = *s++) != '\0'; ++o)
    {
        if (c == '+')
            c = ' ';
        else if (c == '%')
        {
            int c1 = to_hex(*s++);
            int c2 = to_hex(*s++);
            if (c1 == -1 || c2 == -1)
                return -1;
            else
                c = c1 * 16 + c2;
        }
        *o = c;
    }
    *o = '\0';
    return o - dec;
}

#define is_hex(c)                                              \
  (((c) >= '0' && (c) <= '9') || ((c) >= 'a' && (c) <= 'f') || \
   ((c) >= 'A' && (c) <= 'F'))
#define hex_val(c) (((c) >= '0' && (c) <= '9') ? ((c)-48) : (((c) | 32) - 87))

static int decode_5(const char *url_data, char *dest)
{
    char *pos = dest;
    for (size_t i = 0; url_data[i] != '\0'; i++)
    {
        if (url_data[i] == '+')  // decode space
            *(pos++) = ' ';
        else if (url_data[i] == '%')
        {
            // decode hex value
            if (is_hex(url_data[i + 1]) && is_hex(url_data[i + 2]))
            {
                // this is a percent encoded value.
                *(pos++) = (hex_val(url_data[i + 1]) << 4) | hex_val(url_data[i + 2]);
                i += 2;
            }
            else
            {
                // there was an error in the URL encoding...
                return -1;
            }
        }
        else
            *(pos++) = url_data[i];
    }
    *pos = '\0';
    return pos - dest;
}

enum { MAX_COUNT = 100000 };

static void tester(const char *tag, char *url, int (*decoder)(const char *, char *))
{
    char out[1024];
    unsigned long totlen = 0;
    Clock c;

    clk_init(&c);
    clk_start(&c);
    for (int i = 0; i < MAX_COUNT; i++)
    {
        url[5] = (i % 8) + '1';
        totlen += (*decoder)(url, out);
    }
    clk_stop(&c);

    char buffer[32];
    printf("%8s: %s (%lu)\n", tag, clk_elapsed_us(&c, buffer, sizeof(buffer)), totlen);
}

int main(void)
{
    char url[] =
        "http%3A%2F%2Fmanifest.googlevideo.com%2Fapi%2Fmanifest"
        "%2Fdash%2Fms%2Fau%2Fmt%2F1466992558%2Fmv%2Fm%2Fsver%2F3"
        "%2Fitag%2F0%2Fsignature%2F9811214A6751583E8AAD1951B992D"
        "8E011C91E5C.5DBFF1BD54C73C370B058B8BE27CB5848CEAF391%2F"
        "key%2Fyt6%2Fmn%2Fsn-ipoxu-un56%2Fas%2Ffmp4";

    for (int i = 0; i < 10; i++)
    {
        url[6] = (i % 6) + 'A';
        tester("isxdigit", url, decode_2);
        url[6] = (i % 6) + 'A';
        tester("ishex",    url, decode_1);
        url[6] = (i % 6) + 'A';
        tester("tohex-A",  url, decode_3);
        url[6] = (i % 6) + 'A';
        tester("tohex-B",  url, decode_4);
        url[6] = (i % 6) + 'A';
        tester("hex_val",  url, decode_5);
    }

    return 0;
}
