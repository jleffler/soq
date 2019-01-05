#include <stdio.h>
#include <string.h>

/*
** Demonstrating that strncat() should not be given sizeof(buffer) as
** the size, even if the string is empty to start with.  The use of
** (strncat) inhibits the macro expansion on macOS; the code behaves
** differently when the __strncat_chk function (on High Sierra or
** earlier - it's __builtin__strncat_chk on Mojave) is called instead.
** You get an abort 6 (but no other useful message) when the buffer
** length is too long.
*/

int main(int argc, char **argv)
{
    const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (argc >= 2)
        data = argv[1];
    char spare1[16] = "abc";
    char buffer[16] = "";
    char spare2[16] = "xyz";
    size_t len = (argc == 2) ? sizeof(buffer) : sizeof(buffer) - 1;
    if (argc < 3)
        strncat(buffer, data, len);
    else
        (strncat)(buffer, data, len);
    printf("%p: buffer %2zu: [%s]\n", (void *)buffer, strlen(buffer), buffer);
    printf("%p: spare1 %2zu: [%s]\n", (void *)spare1, strlen(spare1), spare1);
    printf("%p: spare2 %2zu: [%s]\n", (void *)spare2, strlen(spare2), spare2);
    return 0;
}
