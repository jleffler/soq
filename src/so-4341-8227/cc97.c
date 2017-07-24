/* SO 4341-8227 */
/* CodeChef: https://www.codechef.com/APRIL17/problems/ROWSOLD */
/* Quadratic solution - exceeds time limit on N = 5000 or bigger */

#include "stderr.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static const char optstr[] = "hv";
static const char usestr[] = "[-hv]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -v  Print verbose information\n"
    ;

static inline int num_char(const char *data, char c)
{
    int count = 0;
    for (int i = 0; data[i] != '\0'; i++)
        if (data[i] == c)
            count++;
    return count;
}

int main(int argc, char **argv)
{
    int verbose = 0;
    int opt;
    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'v':
            verbose = 1;
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    char buffer[10002];
    int d;
    if (fgets(buffer, sizeof(buffer), stdin) == 0)
        return 1;
    if (sscanf(buffer, "%d", &d) != 1)
        return 1;
    if (verbose)
        printf("%d entries\n", d);
    for (int i = 0; i < d; i++)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == 0)
            return 1;
        buffer[strcspn(buffer, "\n")] = '\0';
        int buflen = strlen(buffer);
        int tot_1s = num_char(buffer, '1');
        int tot_0s = num_char(buffer, '0');
        if (tot_1s + tot_0s != buflen)
            return 1;
        int lm1 = 0;
        int count = 0;
        if (verbose)
            printf("Input:  %s (1s = %d, 0s = %d)\n", buffer, tot_1s, tot_0s);
        while (lm1 < buflen - tot_1s)
        {
            if (verbose)
                printf("Before: %s (count = %d; lm1 = %d)\n", buffer, count, lm1);
            while (buffer[lm1] == '0')
                lm1++;
            int lm0 = lm1;
            while (buffer[lm0] == '1')
                lm0++;
            if (lm0 >= buflen)
                break;
            assert(lm0 < buflen);
            count++;    // select time
            buffer[lm0 - 1] = '0';
            while (buffer[lm0] == '0')
            {
                count++;    // move time
                lm0++;
            }
            buffer[lm0 - 1] = '1';
            if (verbose)
                printf("After:  %s (count = %d; lm1 = %d)\n", buffer, count, lm1);
        }
        printf("%d\n", count);
    }
    return 0;
}

