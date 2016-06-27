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
    return o - dec;
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
    return o - dec;
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
        tester("ishex", url, decode_1);
    }

    return 0;
}
