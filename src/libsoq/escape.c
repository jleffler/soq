/*
@(#)File:           escape.c
@(#)Purpose:        Return escaped argument for passing to eval etc.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2018
@(#)Derivation:     escape.c 1.13 2018/08/18 17:27:36
*/

/*TABSTOP=4*/

#include "escape.h"
#include <stdlib.h>
#include <string.h>

static char    bstr[256];
static char   *sstr = bstr;
static size_t  slen = sizeof(bstr);

char *escape(const char *s)
{
    char   *p;
    char    c;
    size_t  l = 4 * strlen(s) + 3;
    if (l > slen)
    {
        if (sstr != bstr)
            free(sstr);
        if ((sstr = (char *)malloc(l)) == 0)  /*=C++=*/
        {
            sstr = bstr;
            slen = sizeof(bstr);
            return(0);
        }
        slen = l;
    }

    p = sstr;
    *p++ = '\'';
    while ((c = *s++) != '\0')
    {
        if (c == '\'')
        {
            *p++ = '\'';
            *p++ = '\\';
            *p++ = '\'';
        }
        *p++ = c;
    }
    *p++ = '\'';
    *p   = '\0';

    return(sstr);
}

size_t escape_chosen(const char *src, const char *ok, char *buffer, size_t buflen)
{
    size_t span = strspn(src, ok);
    size_t len;
    if (src[span] != '\0')
    {
        /* Need to escape it */
        char *end = buffer + buflen - 2;
        char *dst = buffer;
        char  c;
        *dst++ = '\'';
        while ((c = *src++) != '\0' && dst < end)
        {
            if (c == '\'')
            {
                if (dst > end - 4)
                    break;
                *dst++ = '\'';
                *dst++ = '\\';
                *dst++ = '\'';
            }
            *dst++ = c;
        }
        if (c != '\0')
        {
            /* Insufficient space - how much more is needed */
            while ((c = *src++) != '\0')
            {
                if (c == '\'')
                    dst += 3;
                dst++;
            }
            dst += 2;
        }
        else
        {
            *dst++ = '\'';
            *dst = '\0';
        }
        len = (size_t)(dst - buffer);
    }
    else
    {
        len = strlen(src);
        if (len < buflen - 1)
            strcpy(buffer, src);
    }
    return(len);
}

const char escape_ok[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789-+=_.,/";

size_t escape_always(const char *src, char *buffer, size_t buflen)
{
    return escape_chosen(src, "", buffer, buflen);
}

size_t escape_simple(const char *src, char *buffer, size_t buflen)
{
    return escape_chosen(src, escape_ok, buffer, buflen);
}

#if defined(TEST)

#include <stdio.h>

int main(void)
{
    char  buffer[BUFSIZ];
    char *esc;
    char  escbuff[4*BUFSIZ+3];
    const char chosen[] = "abcABC123";

    printf("Testing escape functions.  Enter a string.\n"
           "Note that in this test, escape_chosen() escapes any string containing\n"
           "characters other than: %s\n", chosen);
    printf("Enter string to be escaped: ");
    while (fgets(buffer, sizeof(buffer), stdin) != 0)
    {
        buffer[strlen(buffer) - 1] = '\0';  /* Zap newline */
        esc = escape(buffer);
        printf("Input  : %s\n", buffer);
        printf("Escaped: %s\n", esc);
        if (escape_always(buffer, escbuff, sizeof(escbuff)) > sizeof(escbuff))
            printf("escape_always: buffer overflow!\n");
        else
            printf("escape_always: <<%s>>\n", escbuff);
        if (escape_simple(buffer, escbuff, sizeof(escbuff)) > sizeof(escbuff))
            printf("escape_simple: buffer overflow!\n");
        else
            printf("escape_simple: <<%s>>\n", escbuff);
        if (escape_chosen(buffer, "abcABC123", escbuff, sizeof(escbuff)) > sizeof(escbuff))
            printf("escape_chosen: buffer overflow!\n");
        else
            printf("escape_chosen: <<%s>>\n", escbuff);
        printf("Enter string to be escaped: ");
    }
    putchar('\n');
    return(0);
}

#endif /* TEST */
