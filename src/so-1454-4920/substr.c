/* SO 14544920 */
#include <string.h>

extern void substr(char *buffer, size_t buflen, char const *source, int len);

/*
** Given substr(buffer, sizeof(buffer), "string", len), then the output
** in buffer for different values of len is:
** For positive values of len:
** 0    ""
** 1    "s"
** 2    "st"
** ...
** 6    "string"
** 7    "string"
** ...
** For negative values of len:
** -1   "g"
** -2   "ng"
** ...
** -6   "string"
** -7   "string"
** ...
** Subject to buffer being long enough.
** If buffer is too short, the empty string is set (unless buflen is 0,
** in which case, everything is left untouched).
*/
void substr(char *buffer, size_t buflen, char const *source, int len)
{
    size_t srclen = strlen(source);
    size_t nbytes = 0;
    size_t offset = 0;
    size_t sublen;

    if (buflen == 0)    /* Can't write anything anywhere */
        return;
    if (len > 0)
    {
        sublen = len;
        nbytes = (sublen > srclen) ? srclen : sublen;
        offset = 0;
    }
    else if (len < 0)
    {
        sublen = -len;
        nbytes = (sublen > srclen) ? srclen : sublen;
        offset = srclen - nbytes;
    }
    if (nbytes >= buflen)
        nbytes = 0;
    if (nbytes > 0)
        memmove(buffer, source + offset, nbytes);
    buffer[nbytes] = '\0';
}

#ifdef TEST

#include <stdio.h>

struct test_case
{
    const char *source;
    int         length;
    const char *result;
};

static struct test_case tests[] =
{
    {   "string",  0, ""            },
    {   "string", +1, "s"           },
    {   "string", +2, "st"          },
    {   "string", +3, "str"         },
    {   "string", +4, "stri"        },
    {   "string", +5, "strin"       },
    {   "string", +6, "string"      },
    {   "string", +7, "string"      },
    {   "string", -1, "g"           },
    {   "string", -2, "ng"          },
    {   "string", -3, "ing"         },
    {   "string", -4, "ring"        },
    {   "string", -5, "tring"       },
    {   "string", -6, "string"      },
    {   "string", -7, "string"      },
};
enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };

int main(void)
{
    int pass = 0;
    int fail = 0;

    for (int i = 0; i < NUM_TESTS; i++)
    {
        char buffer[20];
        substr(buffer, sizeof(buffer), tests[i].source, tests[i].length);
        if (strcmp(buffer, tests[i].result) == 0)
        {
            printf("== PASS == %2d: substr(buffer, %zu, \"%s\", %+d) = \"%s\"\n",
                   i, sizeof(buffer), tests[i].source, tests[i].length, buffer);
            pass++;
        }
        else
        {
            printf("!! FAIL !! %2d: substr(buffer, %zu, \"%s\", %+d) wanted \"%s\" actual \"%s\"\n",
                   i, sizeof(buffer), tests[i].source, tests[i].length, tests[i].result, buffer);
            fail++;
        }
    }

    if (fail == 0)
    {
        printf("== PASS == %d tests passed\n", NUM_TESTS);
        return(0);
    }
    else
    {
        printf("!! FAIL !! %d tests out of %d failed\n", fail, NUM_TESTS);
        return(1);
    }
}

#endif /* TEST */
