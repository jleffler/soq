/*
@(#)File:           escape.c
@(#)Purpose:        Return escaped argument for passing to eval etc.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2022
@(#)Derivation:     escape.c 2.15 2022/06/10 20:37:54
*/

/*TABSTOP=4*/

#include "escape.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char    bstr[256];
static char   *sstr = bstr;
static size_t  slen = sizeof(bstr);

/*
** Basic escape()
**
** Start state: S0
** Inputs:
**     - SQ: single quote
**     - NQ: not a single quote
**     - ES: end of string (null byte)
**
** BS: backslash
**
** S0: begin-state
** S1: in-quote
** S2: not-in-quote
** S3: end-state
**
** O:xx - output action
** S:yy - next state
**
** State       SQ      NQ      ES
** S0          O:BS    O:SQ    O:SQ
**             O:SQ    O:NQ    O:SQ
**             S:S2    S:S1    O:ES
**                             S:S3
**
** S1          O:SQ    O:NQ    O:SQ
**             O:BS    S:S1    O:ES
**             O:SQ            S:S3
**             S:S2
**
** S2          O:BS    O:SQ    O:ES
**             O:SQ    O:NQ    S:S3
**             S:S2    S:S1
**
** Input           Required output
**                 ''
** '               \'
** ''              \'\'
** '''             \'\'\'
** 'QQQ'           \''QQQ'\'
** 'QQQ'RRR'       \''QQQ'\''RRR'\'
** 'QQQ''RRR'      \''QQQ'\'\''RRR'\'
** 'QQQ''          \''QQQ'\'\'
*/

enum State { S0_BEGIN, S1_IN_QUOTE, S2_OUTQUOTE, S3_END };

char *escape(const char *s)
{
    size_t  len = (5 * (strlen(s) + 1)) / 2 - 1;
    if (len > slen)
    {
        if (sstr != bstr)
            free(sstr);
        if ((sstr = (char *)malloc(len)) == 0)  /*=C++=*/
        {
            sstr = bstr;
            slen = sizeof(bstr);
            return(0);
        }
        slen = len;
    }

    enum State state = S0_BEGIN;

    char *p = sstr;

    while (state != S3_END)
    {
        char c = *s++;
        if (c == '\0')
        {
            switch (state)
            {
            case S0_BEGIN:
                *p++ = '\'';
                /*FALLTHROUGH*/
            case S1_IN_QUOTE:
                *p++ = '\'';
                /*FALLTHROUGH*/
            case S2_OUTQUOTE:
                *p = '\0';
                state = S3_END;
                break;
            default:    /* Can't happen */
                assert(0);
                return(0);
            }
        }
        else if (c == '\'')
        {
            switch (state)
            {
            case S1_IN_QUOTE:
                *p++ = '\'';
                /*FALLTHROUGH*/
            case S0_BEGIN:
            case S2_OUTQUOTE:
                *p++ = '\\';
                *p++ = '\'';
                state = S2_OUTQUOTE;
                break;
            default:    /* Can't happen */
                assert(0);
                return(0);
            }
        }
        else
        {
            switch (state)
            {
            case S0_BEGIN:
            case S2_OUTQUOTE:
                *p++ = '\'';
                /*FALLTHROUGH*/
            case S1_IN_QUOTE:
                *p++ = c;
                state = S1_IN_QUOTE;
                break;
            default:    /* Can't happen */
                assert(0);
                return(0);
            }
        }
    }

    return(sstr);
}

/*
** Complex escape variants
**
** What about OK characters?  They don't have to be in quotes, but
** perfectly well can be in quotes.  Basically, they don't cause a
** change in quote status.
**
** Start state: S0
** Inputs:
**     - SQ: single quote
**     - OK: character in OK list (excludes single quote)
**     - NK: character not in OK list (and not a single quote)
**     - ES: end of string (null byte)
**
** State       SQ      OK      NK      ES
** S0          O:BS    O:OK    O:SQ    O:SQ
**             O:SQ    S:S2    O:NK    O:SQ
**             S:S2            S:S1    O:ES
**                                     S:S3
**
** S1          O:SQ    O:OK    O:NK    O:SQ
**             O:BS    S:S1    S:S1    O:ES
**             O:SQ                    S:S3
**             S:S2
**
** S2          O:BS    O:OK    O:SQ    O:ES
**             O:SQ    S:S2    O:NK    S:S3
**             S:S2            S:S1
**
** Q, R - OK characters
** @    - Not OK character
**
** Input           Required output
**                 ''
** '               \'
** ''              \'\'
** '''             \'\'\'
** 'QQQ'           \'QQQ\'
** 'QQQ'RRR'       \'QQQ\'RRR\'
** 'QQQ''RRR'      \'QQQ\'\'RRR\'
** 'QQQ''          \'QQQ\'\'
** '@@@'           \''@@@'\'
** '@QQ'           \''@QQ'\'
** @QQ@            '@QQ@'
** QQQQ            QQQQ
*/

static inline void try_add_char(size_t buflen, char *buffer, size_t *offset, char c)
{
    assert(offset != 0);
    assert((buflen != 0 && buffer != 0) || buflen == 0);
    if (*offset < buflen)
        buffer[*offset] = c;
    else if (buffer != 0)
        buffer[0] = '\0';
    (*offset)++;
}

size_t escape_chosen(const char *src, const char *ok, char *buffer, size_t buflen)
{
    assert(src != NULL && ok != NULL);
    assert(buffer != NULL || (buffer == NULL && buflen == 0));
    if (buflen == 0)
        buffer = NULL;
    if (buffer != NULL)
        *buffer = '\0';
    size_t span = strspn(src, ok);
    size_t len = 0;
    if (src[span] != '\0')
    {
        ok = "";        /* Escaping needed - work as 'escape_always()' */
        /* Need to escape source string */
        enum State state = S0_BEGIN;
        while (state != S3_END)
        {
            char c = *src++;
            if (c == '\0')
            {
                switch (state)
                {
                case S0_BEGIN:
                    try_add_char(buflen, buffer, &len, '\'');
                    /*FALLTHROUGH*/
                case S1_IN_QUOTE:
                    try_add_char(buflen, buffer, &len, '\'');
                    /*FALLTHROUGH*/
                case S2_OUTQUOTE:
                    try_add_char(buflen, buffer, &len, '\0');
                    state = S3_END;
                    break;
                default:        /* Can't happen */
                    assert(0);
                    return(0);
                }
            }
            else if (c == '\'')
            {
                switch (state)
                {
                case S1_IN_QUOTE:
                    try_add_char(buflen, buffer, &len, '\'');
                    /*FALLTHROUGH*/
                case S0_BEGIN:
                case S2_OUTQUOTE:
                    try_add_char(buflen, buffer, &len, '\\');
                    try_add_char(buflen, buffer, &len, '\'');
                    state = S2_OUTQUOTE;
                    break;
                default:        /* Can't happen */
                    assert(0);
                    return(0);
                }
            }
            else if (strchr(ok, c) != NULL)
            {
                switch (state)
                {
                case S0_BEGIN:
                case S2_OUTQUOTE:
                    try_add_char(buflen, buffer, &len, c);
                    state = S2_OUTQUOTE;
                    break;
                case S1_IN_QUOTE:
                    try_add_char(buflen, buffer, &len, c);
                    state = S1_IN_QUOTE;
                    break;
                default:        /* Can't happen */
                    assert(0);
                    return(0);
                }
            }
            else
            {
                switch (state)
                {
                case S0_BEGIN:
                case S2_OUTQUOTE:
                    try_add_char(buflen, buffer, &len, '\'');
                    try_add_char(buflen, buffer, &len, c);
                    state = S1_IN_QUOTE;
                    break;
                case S1_IN_QUOTE:
                    try_add_char(buflen, buffer, &len, c);
                    state = S1_IN_QUOTE;
                    break;
                default:        /* Can't happen */
                    assert(0);
                    return(0);
                }
            }
        }
    }
    else if (span == 0)
    {
        len = 3;
        if (buflen >= len)
            strcpy(buffer, "''");
    }
    else
    {
        /* No need to escape anything */
        len = span + 1;
        if (buflen >= len)
            strcpy(buffer, src);
    }
    return(len);
}

const char escape_ok[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
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

/*
** The test buffer size is small enough that it can be overflowed, but
** it's unlikely to happen by accident.  Note that the output buffer is
** the same size as the input buffer - that is deliberate too.
*/
enum { TEST_BUFFER_SIZE = 256 };
static const char chosen[] = "abcABC123";

static void test_escape(char *buffer)
{
    char escbuff[TEST_BUFFER_SIZE];
    char *esc = escape(buffer);
    printf("Input:         (%zu) <<%s>>\n", strlen(buffer) + 1, buffer);
    printf("Basic escape:  (%zu) <<%s>>\n", strlen(esc) + 1, esc);
    size_t reqlen;

    if ((reqlen = escape_always(buffer, escbuff, sizeof(escbuff))) > sizeof(escbuff))
        printf("Always escape: buffer overflow (required %zu, available %zu)!\n",
                reqlen, sizeof(escbuff));
    else
    {
        assert(reqlen == strlen(escbuff) + 1);
        assert(strlen(escbuff) < sizeof(escbuff));
        printf("Always escape: (%zu) <<%s>>\n", strlen(escbuff) + 1, escbuff);
    }

    if ((reqlen = escape_simple(buffer, escbuff, sizeof(escbuff))) > sizeof(escbuff))
        printf("Simple escape: buffer overflow (required %zu, available %zu)!\n",
                reqlen, sizeof(escbuff));
    else
    {
        assert(reqlen == strlen(escbuff) + 1);
        assert(strlen(escbuff) < sizeof(escbuff));
        printf("Simple escape: (%zu) <<%s>>\n", strlen(escbuff) + 1, escbuff);
    }

    if ((reqlen = escape_chosen(buffer, "abcABC123", escbuff, sizeof(escbuff))) > sizeof(escbuff))
        printf("Chosen escape: buffer overflow (required %zu, available %zu)!\n",
                reqlen, sizeof(escbuff));
    else
    {
        assert(reqlen == strlen(escbuff) + 1);
        assert(strlen(escbuff) < sizeof(escbuff));
        printf("Chosen escape: (%zu) <<%s>>\n", strlen(escbuff) + 1, escbuff);
    }

    reqlen = escape_chosen(buffer, "abcABC123", 0, 0);
    printf("Chosen escape: null   buffer - required %zu\n", reqlen);

    for (size_t i = 0; i < 10; i++)
    {
        strcpy(escbuff, "XXXXXXXXXXXX");
        reqlen = escape_chosen(buffer, "abcABC123", escbuff, i);
        printf("Chosen escape: size %zu buffer - required %zu (%s)\n", i, reqlen, escbuff);
    }
}

static inline char *prompt_for_string(size_t buflen, char buffer[buflen])
{
    printf("Enter string to be escaped: ");
    fflush(stdout);
    return fgets(buffer, buflen, stdin);
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            test_escape(argv[i]);
    }
    else
    {
        char buffer[TEST_BUFFER_SIZE];

        printf("Testing escape functions.  Enter a string.\n");
        printf("Note that in this test, escape_chosen() escapes any string containing\n"
               "characters other than: %s\n", chosen);

        while (prompt_for_string(sizeof(buffer), buffer) != 0)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            test_escape(buffer);
        }
        putchar('\n');
    }

    return(0);
}

#endif /* TEST */
