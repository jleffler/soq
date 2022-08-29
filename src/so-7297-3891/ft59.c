
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

static char optstr[] = "a:hm:t:V";
static char usestr[] = "[-hV] [-a atime] [-m mtime] [-t time] file ...";
static char hlpstr[] =
    "  -a atime  Use this time for the access time (default: now)\n"
    "  -h        Print this help message and exit\n"
    "  -m mtime  Use this time for the modification time (default: now)\n"
    "  -t time   Use this time value for both access and modification time\n"
    "  -V        Print version information and exit\n"
    ;

static void set_time(const char *file, struct timespec *tvals)
{
	if (utimensat(AT_FDCWD, file, tvals, 0) != 0)
	    err_sysrem("failed to set time on %s: ", file);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    struct timespec tvals[2];
    clock_gettime(CLOCK_REALTIME, &tvals[0]);
    tvals[1] = tvals[0];
    int opt;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'a':
            if (scn_timespec(optarg, &tvals[0]) != 0)
                err_error("failed to parse '%s' as a time\n", optarg);
            break;
        case 'h':
            err_help(usestr, hlpstr);
        /*NOTREACHED*/
        case 'm':
            if (scn_timespec(optarg, &tvals[1]) != 0)
                err_error("failed to parse '%s' as a time\n", optarg);
            break;
        case 'V':
            err_version("FT97", &"@(#)$Revision$ ($Date$)"[4]);
        /*NOTREACHED*/
        case 't':
            if (scn_timespec(optarg, &tvals[0]) != 0)
                err_error("failed to parse '%s' as a time\n", optarg);
            tvals[1] = tvals[0];
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (argc == optind)
        err_usage(usestr);

    for (int i = optind; i < argc; i++)
        set_time(argv[i], tvals);

    return 0;
}
