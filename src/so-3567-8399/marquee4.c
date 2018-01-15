/* SO 35678399 */
#include "posixver.h"
#include "stderr.h"
#include "chkstrint.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static inline int max(int x, int y) { return (x > y) ? x : y; }

static void fettle_text(char *string)
{
    unsigned char *dst = (unsigned char *)string;
    unsigned char *src = dst;
    /* Leading white space */
    while (isspace(*src))
        src++;
    unsigned char c;
    while ((c = *src++) != '\0')
    {
        if (isspace(c))
        {
            /* All white space sequences become a single blank */
            c = ' ';
            while (isspace(*src))
                src++;
        }
        *dst++ = c;
    }
    /* Trailing white space (already reduced to a single blank) */
    if (dst > (unsigned char *)string && *(dst-1) == ' ')
        dst--;
    *dst = '\0';
}

static const char optstr[] = "d:hp:w:V";
static const char usestr[] = "[-hV][-d delay][-p pad][-w width] 'message'";
static const char hlpstr[] =
    "  -d delay  Delay between renditions (milliseconds; default 100)\n"
    "  -h        Print this help message and exit\n"
    "  -p pad    Use pad between cycles (default '...')\n"
    "  -w width  Width of display slot (default 15)\n"
    "  -V        Print version information and exit\n"
    ;

int main(int argc, char **argv)
{
    struct timespec delay = { .tv_sec = 0, .tv_nsec = 100000000 };
    const char padding[] = " ... ";
    const char *padstr = padding;
    int width = 15;
    int opt;

    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            {
            int d_val;
            if (!chk_strtoi(optarg, 0, 0, &d_val))
                err_error("Unable to interpret '%s' as an integer\n", optarg);
            if (d_val < 0)
                err_error("Unable to do time travel (%s is a negative delay)\n", optarg);
            delay.tv_nsec = 1000000 * (d_val % 1000);
            delay.tv_sec = d_val / 1000;
            }
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'p':
            {
            char *pad = strdup(optarg);
            if (pad == 0)
                err_error("Failed to duplicate string '%s'\n", optarg);
            fettle_text(pad);
            int p_len = strlen(pad) + 3;
            char *padded = malloc(p_len);
            if (padded == 0)
                err_error("failed to malloc %d bytes\n", p_len);
            sprintf(padded, " %s ", pad);
            padstr = padded;
            }
            break;
        case 'w':
            if (!chk_strtoi(optarg, 0, 0, &width))
                err_error("Unable to interpret '%s' as an integer\n", optarg);
            if (width < 1)
                err_error("Width must be at least 1 (you gave '%s')\n", optarg);
            break;
        case 'V':
            err_version("MARQUEE4", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }
    if (optind == argc)
    {
        err_remark("No message to display\n");
        err_usage(usestr);
    }
    if (optind != argc - 1)
    {
        err_remark("Too many messages to display\n");
        err_usage(usestr);
    }

    char *message = strdup(argv[argc-1]);
    if (message == 0)
        err_error("failed to duplicate string '%s'\n", argv[argc-1]);
    fettle_text(message);
    int s_len = strlen(message);
    if (s_len == 0)
        err_error("argument '%s' contains no data\n", argv[argc-1]);
    int t_len = s_len;
    if (t_len < width)
        t_len = width;
    int p_len = strlen(padstr);
    int m_len = 2 * (t_len + p_len) + 1;
    char *sign = malloc(m_len);
    if (sign == 0)
        err_error("failed to malloc %d bytes\n", m_len);

    int offset = 0;
    for (int i = 0; i < 2; i++)
    {
        int p_wid = max(width - s_len, 0);
        offset += sprintf(sign + offset, "%s%s%*.*s", message, padstr, p_wid, p_wid, " ");
    }
    sign[offset] = '\0';

    printf("%zu vs %d (%s)\n", strlen(sign), 2 * (t_len + p_len), sign);
    assert(strlen(sign) == (size_t)(2 * (t_len + p_len)));

    for (int i = 0; i < 10; i++)
    {
        for (int l_len = 0; l_len < t_len + p_len; l_len++)
        {
            int r_len = t_len + p_len - l_len;
            putchar('\r');
            /* Rotate to right */
            printf("[%.*s]", width, sign + r_len);
            printf("    ");
            /* Rotate to left */
            printf("[%.*s]", width, sign + l_len);
            fflush(stdout);
            nanosleep(&delay, 0);
        }
    }
    putchar('\n');

    free(message);
    free(sign);

    return 0;
}
