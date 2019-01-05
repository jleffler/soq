#include "stderr.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
** Demonstrating that strncat() should not be given sizeof(buffer) as
** the size, even if the string is empty to start with.  The use of
** (strncat) inhibits the macro expansion on macOS; the code behaves
** differently when the __strncat_chk function (on High Sierra or
** earlier - it's __builtin__strncat_chk on Mojave) is called instead.
** You get an abort 6 (but no other useful message) when the buffer
** length is too long.
*/

static const char optstr[] = "fhlmsV";
static const char usestr[] = "[-fhlmsV] [string]";
static const char hlpstr[] =
    "  -f  Function is called directly\n"
    "  -h  Print this help message and exit\n"
    "  -l  Long buffer length -- sizeof(buffer)\n"
    "  -m  Macro cover for the function is used (default)\n"
    "  -s  Short buffer length -- sizeof(buffer)-1 (default)\n"
    "  -V  Print version information and exit\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int f_flag = 0;
    int l_flag = 0;
    int opt;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'f':
            f_flag = 1;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'l':
            l_flag = 1;
            break;
        case 'm':
            f_flag = 0;
            break;
        case 's':
            l_flag = 0;
            break;
        case 'V':
            err_version(err_getarg0(), &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (optind < argc - 1)
        err_usage(usestr);

    const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (optind != argc)
        data = argv[optind];
    char spare1[16] = "abc";
    char buffer[16] = "";
    char spare2[16] = "xyz";
    size_t len = l_flag ? sizeof(buffer) : sizeof(buffer) - 1;

    printf("Specified length: %zu\n", len);
    printf("Copied string: [%s]\n", data);
    printf("Copied %s\n", f_flag ? "using strncat() function directly"
                                 : "using strncat() macro");

    if (f_flag)
        (strncat)(buffer, data, len);
    else
        strncat(buffer, data, len);

    printf("%p: buffer %2zu: [%s]\n", (void *)buffer, strlen(buffer), buffer);
    printf("%p: spare1 %2zu: [%s]\n", (void *)spare1, strlen(spare1), spare1);
    printf("%p: spare2 %2zu: [%s]\n", (void *)spare2, strlen(spare2), spare2);
    return 0;
}
