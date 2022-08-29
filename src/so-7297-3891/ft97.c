
/* To get the 64-bit inode structure with struct timespec elements on Mac OS X */
//#ifdef __APPLE__
//#define _DARWIN_USE_64_BIT_INODE
//#endif /* __APPLE__ */

#include "posixver.h"
#include <fcntl.h>           /* AT_FDCWD on macOS Monterey 12.4 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "stderr.h"
#include "timespec_io.h"

static char optstr[] = "ht:V";
static char usestr[] = "[-hV] [-t time] file ...";
static char hlpstr[] =
    "  -t time  Use this time value (default: now)\n"
    "  -h       Print this help message and exit\n"
    "  -V       Print version information and exit\n"
    ;

static void set_time(const char *file, struct timespec *tval)
{
    struct timespec times[2] = { *tval, *tval };

	if (utimensat(AT_FDCWD, file, times, 0) != 0)
	    err_sysrem("failed to set time on %s: ", file);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    struct timespec tval;
    clock_gettime(CLOCK_REALTIME, &tval);
    int opt;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
        /*NOTREACHED*/
        case 'V':
            err_version("FT97", &"@(#)$Revision$ ($Date$)"[4]);
        /*NOTREACHED*/
        case 't':
            scn_timespec(optarg, &tval);
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (argc == optind)
        err_usage(usestr);

    for (int i = optind; i < argc; i++)
        set_time(argv[i], &tval);

    return 0;
}
