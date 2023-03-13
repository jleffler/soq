/*
@(#)File:           filterio.c
@(#)Purpose:        Perform standardized I/O error check for filter programs
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2003-2019
@(#)Derivation:     filterio.c 2019.2 2019/08/16 05:47:20
*/

/*TABSTOP=4*/

#include "filter.h"
#include "stderr.h"

static int numfiles = 0;

/* filter_numfiles() - return number of files to be processed */
int filter_numfiles(void)
{
    return numfiles;
}

/* filter_setnumfiles() - set number of files to be processed */
/*
** Only set number of files if not overridden by prior
** filter_setnumfiles(1) or filter_setnumfiles(2)
*/
void filter_setnumfiles(int num)
{
    if (numfiles == 0)
        numfiles = num;
}

/* filter_io_check() - did an input or output error occur? */
int filter_io_check(FILE *ifp, const char *ifn, FILE *ofp)
{
    int rc = 0;
    if (ferror(ifp))
    {
        err_sysrem("read error on file %s\n", ifn);
        rc = -1;
    }
    if (ferror(ofp))
    {
        err_sysrem("write error on output file\n");
        rc = -1;
    }
    return(rc);
}

#ifdef TEST

#include <stdlib.h>

static int cat(FILE *ifp, const char *ifn, FILE *ofp)
{
    char buffer[4096];
    size_t nbytes;

    while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), ifp)) != 0)
    {
        if (fwrite(buffer, sizeof(char), nbytes, ofp) != nbytes)
        {
            err_syserr("write failed: ");
            /*NOTREACHED*/
        }
    }
    return(filter_io_check(ifp, ifn, ofp));
}

int main(int argc, char **argv)
{
    int rc = EXIT_SUCCESS;
    err_setarg0(argv[0]);
    if (filter_output(argc, argv, 1, cat) != 0)
        rc = EXIT_FAILURE;
    return(rc);
}

#endif /* TEST */
