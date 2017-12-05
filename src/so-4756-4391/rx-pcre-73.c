/* SO 4756-4391 */
#error This code is known to be completely non-working
#error Will need to choose between PCRE 1 and PCRE 2.
#include <pcre.h>
#include <stdio.h>
#include <string.h>
#include "stderr.h"

int main(void)
{
    char *source = "change@/devices/soc/799999.i2c/i2c-3/3-0015/power_supply/battery";
    // char * regexString = "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";
    size_t maxGroups = 5;
    char *regexString =  "([a-zA-Z]+)@\\/(.*)\\/([a-zA-z]+)\\/([a-zA-z]+)";

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    int rc;
    if ((rc = regcomp(&regexCompiled, regexString, REG_EXTENDED)) != 0)
    {
        char buffer[1024];
        regerror(rc, &regexCompiled, buffer, sizeof(buffer));
        printf("Could not compile regular expression (%d: %s).\n", rc, buffer);
        return 1;
    }
    if ((rc = regexec(&regexCompiled, source, maxGroups, groupArray, 0)) != 0)
    {
        char buffer[1024];
        regerror(rc, &regexCompiled, buffer, sizeof(buffer));
        printf("Could not execute regular expression (%d: %s).\n", rc, buffer);
        return 1;
    }

    printf("Match successful:\n");
    for (size_t i = 0; i < maxGroups; i++)
    {
        int so = groupArray[i].rm_so;
        int eo = groupArray[i].rm_eo;
        printf("%zu: %d..%d [%.*s]\n", i, so, eo, eo - so, &source[so]);
    }

    regfree(&regexCompiled);

    return 0;
}

int main(int argc, char **argv)
{
    const char pattern[] = 
        "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)"
        "\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";
    int options = 0;
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

