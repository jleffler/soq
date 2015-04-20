/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Prompt for an integer value
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#define TEST

#include "prompt.h"
#include <assert.h>
#include <stdarg.h>
#include <limits.h>

enum { DEF_RETRIES = 10 };

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_prompt_c[];
const char jlss_id_prompt_c[] = "@(#)$Id$";
#endif /* lint */

/*
** Should this detect terminal vs non-terminal input?
** If so, what should it do when input is not a terminal?
** If so, what should it do when output is not a terminal?
** And when either is a terminal?
*/


int fprompt_for_int(FILE *in, FILE *out, int *retval, int minval, int maxval,
                     int maxtries, const char *prompt, const char *err_range,
                     const char *err_invalid)
{
    assert(minval < maxval);
    assert(retval != 0);
    assert(prompt != 0);
    assert(err_range != 0);
    assert(err_invalid != 0);
    assert(maxtries > 0);
    assert(in != 0);
    assert(out != 0);

    /*
    ** Prompt for value.
    ** Scan a value.
    ** If EOF, return EOF.
    ** If value OK and within range, return success.
    ** If value out of range - print error message and try again.
    ** If no value, print error message, scan to end of line and try again.
    ** NB: Count retries and limit to maxtries, returning EOF.
    */

    int retries = 0;
    while (fprintf(out, "%s: ", prompt) > 0 && fflush(out) == 0)
    {
        int rc = fscanf(in, "%d", retval);
        if (rc < 0)
            return EOF;
        if (rc == 1)
        {
            if (*retval >= minval && *retval <= maxval)
                return 0;
            fprintf(out, "%s\n", err_range);
        }
        else
        {
            assert(rc == 0);
            int c;
            fprintf(out, "%s\n", err_invalid);
            while ((c = getc(in)) != EOF && c != '\n')
                ;
            if (c == EOF)
                return EOF;
        }
        if (++retries >= maxtries)
            return EOF;
    }

    /* fprintf() or fflush() failed - report EOF */
    return EOF;
}

int prompt_for_int(int *retval, int minval, int maxval)
{
    char msg_input[64];
    char err_range[64];
    char err_inval[64];
    snprintf(msg_input, sizeof(msg_input), "Please enter an integer [%d..%d]",
             minval, maxval);
    snprintf(err_range, sizeof(err_range), "That value was not in the range [%d..%d]",
             minval, maxval);
    snprintf(err_inval, sizeof(err_inval), "That was not an integer in the range [%d..%d]",
             minval, maxval);
    int rc = fprompt_for_int(stdin, stdout, retval, minval, maxval,
                             DEF_RETRIES, msg_input, err_range, err_inval);
    return rc;
}

#ifdef TEST

int main(void)
{
    int value;
    int min = -99;
    int max = +99;

    for (int i = 0; i < 7; i++)
    {
        if (prompt_for_int(&value, min, max) == 0)
            printf("Entered value was: %3d\n", value);
        min = min * 10 - 9;
        max = max * 10 + 9;
    }

    return 0;
}

#endif /* TEST */
