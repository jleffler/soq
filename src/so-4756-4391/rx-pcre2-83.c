/* SO 4756-4391 */
#define  PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    if (argc != 0)  // Compiler pacification!
        err_setarg0(argv[0]);

    unsigned char source[] = "change@/devices/soc/799999.i2c/i2c-3/3-0015/power_supply/battery";
    unsigned char pattern[] = "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";
    uint32_t options = 0;
    PCRE2_SIZE erroroffset;
    int errorcode;

    printf("Matching PCRE: %s\n", pattern);

    pcre2_code *rx = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, options,
                                   &errorcode, &erroroffset, NULL);
    if (rx == 0)
    {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errorcode, buffer, sizeof(buffer));
        err_error("PCRE compilation of <<%s>> failed (offset %d: %s)\n",
                  pattern, (int)erroroffset, buffer);
    }

    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(rx, NULL);

    size_t off = 0;
    size_t len = sizeof(source) - 1;
    int rc;
    printf("Scanning %zu bytes <<%s>>\n", len, &source[off]);
    while ((rc = pcre2_match(rx, source, len, 0, 0, match_data, NULL)) > 0)
    {
        printf("Found pattern (%d substrings)\n", rc);
        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
        for (int i = 0; i < rc; i++)
        {
            int lo = ovector[i * 2 + 0];
            int hi = ovector[i * 2 + 1];
            printf("Substring %d: (%d:%d) <<%*.*s>>\n", i, lo, hi, (hi - lo), (hi - lo), &source[lo]);
        }
        off = ovector[1];
        assert(len >= ovector[1]);
        len = len - ovector[1];
        printf("Scanning %zu bytes <<%s>>\n", len, &source[off]);
    }

    if (rc == PCRE2_ERROR_NOMATCH)
        err_remark("No more matches for the pattern in that line\n");
    else if (rc < 0)
        err_error("PCRE2 matching (error %d)\n", rc);

    pcre2_match_data_free(match_data);
    pcre2_code_free(rx);

    return 0;
}



