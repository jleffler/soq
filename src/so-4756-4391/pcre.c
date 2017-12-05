#include <pcre.h>
#include <stdio.h>
#include <string.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    const char pattern[] = "CONN ([^ ]+) ([^ ]+) ([^\\)]+) ([0-9\\.]+)";
    int options = PCRE_CASELESS;
    const char *errptr;
    int erroffset;

    if (argc != 0)  // Compiler pacification!
        err_setarg0(argv[0]);

    /*
    ** pcre *pcre_compile(const char *pattern, int options,
    **                    const char **errptr, int *erroffset,
    **                    const unsigned char *tableptr);
    */
    pcre *rx = pcre_compile(pattern, options, &errptr, &erroffset, 0);
    if (rx == 0)
        err_error("PCRE compilation of <<%s>> failed (offset %d: %s)\n", pattern, erroffset, errptr);

    /* pcre_fullinfo()? */

    printf("Matching PCRE: %s\n", pattern);
    char line[4096];
    while (fgets(line, sizeof(line), stdin) != 0)
    {
        /*
        ** int pcre_exec(const pcre *code, const pcre_extra *extra,
        **               const char *subject, int length, int startoffset,
        **               int options, int *ovector, int ovecsize);
        **
        ** ovecsize should be a multiple of 3.
        */
        enum { OVECSIZE = 3 * 14 }; // The Answer to the Question of Life, the Universe, and Everything
        int ovec[OVECSIZE];
        int off = 0;
        int rc;
        int len = strlen(line);
        line[--len] = '\0';

        printf("Scanning <<%s>>\n", &line[off]);
        while ((rc = pcre_exec(rx, 0, line, len, off, 0, ovec, OVECSIZE)) > 0)
        {
            printf("Found pattern (%d substrings)\n", rc);
            for (int i = 0; i < rc; i++)
            {
                int lo = ovec[i * 2 + 0];
                int hi = ovec[i * 2 + 1];
                printf("Substring %d: (%d:%d) <<%*.*s>>\n", i, lo, hi, (hi - lo), (hi - lo), &line[lo]);
            }
            off = ovec[1];
            printf("Scanning <<%s>>\n", &line[off]);
        }
        if (rc == PCRE_ERROR_NOMATCH)
            err_remark("No more matches for the pattern in that line\n");
        else if (rc < 0)
            err_error("PCRE execution failed (error %d)\n", rc);
    }
    return(0);
}

