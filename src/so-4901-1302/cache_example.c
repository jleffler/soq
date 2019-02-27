#include "cache_reader.h"
#include <stdio.h>

int main(void)
{
    cr_file *f = cr_open("text", 20);
    if (f != 0)
    {
        int c;
        while ((c = cr_read_byte(f)) != EOF)
            putchar(c);
        cr_close(f);
    }
    return 0;
}
