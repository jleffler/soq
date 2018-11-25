/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        SO 4547-5326 - Copy file using asymmetric buffer sizes
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
*/

/*TABSTOP=4*/

/*
** Create a function that takes the name of two files, and the allowed
** buffer size to read from file1 and allowed buffer size for write to
** file2.  If the buffer size is the same [it is easy], but [...] how to
** move data between the buffers when the sizes are of different?  One
** of the constraints is that [the code must] always fill the write
** buffer before writing it to file.  If file1 is not a multiple of
** file2, we pad the last buffer transfer with zeros.
*/

/*
** Observations by YT (aka JL):
** There are two main cases to consider: (1) the read buffer is bigger
** than the write buffer, and (2) the read buffer is smaller than the
** write buffer.  The other case — same size buffers — doesn't
** present any problems, of course.  It isn't clear whether the sizes
** will be integral multiples of each other (could you have a 6KiB read
** buffer and a 7KiB write buffer?).  You have to process case (1)
** differently from case (2).  In case (1), you read a buffer full, then
** write parts of the big buffer into the write buffer and write it.  If
** the read buffer is smaller, then you do several reads per write.
**
** There are also the edge conditions to worry about — there's part of
** a write buffer full left in the read buffer, or vice versa.  These
** can all be handled if you think about it.  However, as already
** pointed out, this is a rather artificial question — there is lots
** of unnecessary buffer copying in progress unless you're careful.
**
** Are you sure the code for the answer to this question is supposed to
** use fopen() and the stream I/O rather than the lower-level
** POSIX-style file descriptor I/O (open(), close(), read(), write())?
** Using the latter makes the question more nearly sensible.  And back
** in the days of half-inch magnetic tape drives, buffer sizes really
** did matter.
*/

/*
** Proposed solution
** -- The code will work with file descriptor I/O.
** -- The code will (at least initially) use separate functions for
**    three cases.
** Command line arguments:
**
** $ copy_buffer [-h] [-i in-size] [-o out-size] [in-file [out-file]]
**
** Default in-size: 1 KiB
** Default out-size: 4 KiB
** Default input: standard input
** Default output: standard output
**
** Acceptable suffixes are case-insensitive.  They include:
** KiB  = 2^10 = 1024
** MiB  = 2^20 = 1048576
** GiB  = 2^30 = 1073741824
** TiB  = 2^40 = 1099511627776
** PiB  = 2^50 = 1125899906842624
** EiB  = 2^60 = 1152921504606846976
** The i may be dropped, meaning decimal powers (so KB means 1000 bytes).
** The b may be dropped, meaning binary powers.
*/

#include "stderr.h"
#include "unitsize.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char optstr[] = "hi:o:";
static const char usestr[] = "[-h] [-i in-size] [-o out-size] [in-file [out-file]]";
static const char hlpstr[] =
    "  -h           Print this help message and exit\n"
    "  -i in-size   Input buffer size (1 KiB: optional multipliers K, M, G)\n"
    "  -o out-size  Output buffer size (4 KiB: optional multipliers K, M, G)\n"
    ;

enum { DEFAULT_IN_SIZE = 1024, DEFAULT_OUT_SIZE = 4096 };

extern void buffered_copy(FILE *in, FILE *out, uint64_t i_size, uint64_t o_size);

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_fc31_c[];
const char jlss_id_fc31_c[] = "@(#)$Id$";
#endif /* lint */

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    uint64_t i_size = DEFAULT_IN_SIZE;
    uint64_t o_size = DEFAULT_OUT_SIZE;
    int rc;

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'i':
            if ((rc = scn_unitsize(optarg, (char **)0, &i_size)) != 0)
                err_syserr("Failed to convert input size '%s' to number: ", optarg);
            break;
        case 'o':
            if ((rc = scn_unitsize(optarg, (char **)0, &o_size)) != 0)
                err_syserr("Failed to convert output size '%s' to number: ", optarg);
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("FC31", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    FILE *in = stdin;
    FILE *out = stdout;
    /* Check for extra arguments - and file names */
    buffered_copy(in, out, i_size, o_size);

    return 0;
}
