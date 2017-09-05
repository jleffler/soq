/*
@(#)File:           strupper.c
@(#)Purpose:        Convert string to upper case
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1992,1997-98,2005,2007-08,2015
@(#)Derivation:     strupper.c 2.6 2015/05/25 06:57:00
*/

/*TABSTOP=4*/

#include "jlss.h"
#include <ctype.h>

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_strupper_c[];
const char jlss_id_strupper_c[] = "@(#)$Id: strupper.c,v 2.6 2015/05/25 06:57:00 jleffler Exp $";
#endif /* lint */

/* Case-convert string to upper case; return pointer to terminating null */
char *strupper(char *s)
{
    char    *t = s;
    char     c;

    while ((c = *t) != '\0')
        *t++ = (char)toupper(c);
    return(t);
}

#if defined(TEST)

static const char * const list[] =
{
    "all lower case or non-alpha _0123456789~`!@#$%^&*()-=+[]{}|\\\"':;/?.,<>",
    "ALL UPPER CASE",
    "mIxEd CaSe",
    (char *)0
};

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char * const *s;
    char     *end;
    char     *src;
    char      buffer[128];

    for (s = list; *s != (char *)0; s++)
    {
        strcpy(buffer, *s);
        printf("Before: %s\n", buffer);
        end = strupper(buffer);
        assert(*end == '\0');
        for (src = buffer; src < end; src++)
        {
            char c = *src;
            assert(!isalpha(c) || isupper(c));
        }
        printf("After:  %s\n", buffer);
    }
    return(0);
}

#endif /* TEST */
