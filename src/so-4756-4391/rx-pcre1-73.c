/* SO 4756-4391 */
#include <pcre.h>
#include <stdio.h>
#include <string.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    if (argc != 0)  // Compiler pacification!
        err_setarg0(argv[0]);

    char *source = "change@/devices/soc/799999.i2c/i2c-3/3-0015/power_supply/battery";
    char *pattern = "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";
    int options = 0;
    const char *errptr;
    int erroffset;

    printf("Matching PCRE: %s\n", pattern);

    /*
    ** pcre *pcre_compile(const char *pattern, int options,
    **                    const char **errptr, int *erroffset,
    **                    const unsigned char *tableptr);
    */
    pcre *rx = pcre_compile(pattern, options, &errptr, &erroffset, 0);
    if (rx == 0)
        err_error("PCRE compilation of <<%s>> failed (offset %d: %s)\n", pattern, erroffset, errptr);

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
    int len = strlen(source);

    printf("Scanning <<%s>>\n", &source[off]);
    while ((rc = pcre_exec(rx, 0, source, len, off, 0, ovec, OVECSIZE)) > 0)
    {
        printf("Found pattern (%d substrings)\n", rc);
        for (int i = 0; i < rc; i++)
        {
            int lo = ovec[i * 2 + 0];
            int hi = ovec[i * 2 + 1];
            printf("Substring %d: (%d:%d) <<%*.*s>>\n", i, lo, hi, (hi - lo), (hi - lo), &source[lo]);
        }
        off = ovec[1];
        printf("Scanning <<%s>>\n", &source[off]);
    }
    if (rc == PCRE_ERROR_NOMATCH)
        err_remark("No more matches for the pattern in that line\n");
    else if (rc < 0)
        err_error("PCRE execution failed (error %d)\n", rc);

    pcre_free(rx);

    return 0;
}

