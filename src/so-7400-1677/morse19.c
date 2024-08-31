/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Encode ASCII to Morse or Decode Morse to ASCII
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include "posixver.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filter.h"
#include "stderr.h"

/* https://en.wikipedia.org/wiki/Morse_code */

typedef struct
{
    char dotdash[12];
    char meaning[4];
} Morse;

/* Not constant - it gets sorted */
static Morse morse[] =
{
    { ".-",         "A" },
    { "-...",       "B" },
    { "-.-.",       "C" },
    { "-..",        "D" },
    { ".",          "E" },
    { "..-.",       "F" },
    { "--.",        "G" },
    { "....",       "H" },
    { "..",         "I" },
    { ".---",       "J" },
    { "-,-",        "K" },
    { ".-..",       "L" },
    { "--",         "M" },
    { "-.",         "N" },
    { "---",        "O" },
    { ".--.",       "P" },
    { "--.-",       "Q" },
    { ".-.",        "R" },
    { "...",        "S" },
    { "-",          "T" },
    { "..-",        "U" },
    { "...-",       "V" },
    { ".--",        "W" },
    { "-..-",       "X" },
    { "-.--",       "Y" },
    { "--..",       "Z" },
    { ".----",      "1" },
    { "..---",      "2" },
    { "...--",      "3" },
    { "....-",      "4" },
    { ".....",      "5" },
    { "-....",      "6" },
    { "--...",      "7" },
    { "---..",      "8" },
    { "----.",      "9" },
    { "-----",      "0" },
    { ".-.-.-",     "." },
    { "--..--",     "," },
    { "..--..",     "?" },
    { ".----.",     "'" },
    { "-.-.--",     "!" },
    { "-..-.",      "/" },
    { "-.--.",      "(" },
    { "-,--,-",     ")" },
    { ".-...",      "&" },
    { "---...",     ":" },
    { "-.-.-.",     ";" },
    { "-...-",      "=" },
    { ".-.-.",      "+" },
    { "-....-",     "-" },
    { "..--.-",     "_" },
    { ".-..-.",     "\"" },
    { "...-..-",    "$" },
    { ".--.-.",     "@" }
};
enum { NUM_MORSE = sizeof(morse) / sizeof(morse[0]) };

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_morse19_c[];
const char jlss_id_morse19_c[] = "@(#)$Id: skel.c,v 2.11 2017/11/01 19:05:42 jleffler Exp $";
#endif /* lint */

static inline void dump_morse(const Morse *m)
{
    printf("%-8s  %s\n", m->dotdash, m->meaning);
}

static inline void dump_morse_array(const char *tag, size_t n, const Morse *m)
{
    printf("%s (%zu):\n", tag, n);
    for (size_t i = 0; i < n; i++)
        dump_morse(&m[i]);
}

static int cmp_dotdash(const void *v1, const void *v2)
{
    const Morse *m1 = v1;
    const Morse *m2 = v2;
    return strcmp(m1->dotdash, m2->dotdash);
}

static int cmp_meaning(const void *v1, const void *v2)
{
    const Morse *m1 = v1;
    const Morse *m2 = v2;
    return strcmp(m1->meaning, m2->meaning);
}

static const char *morse_encode(const char symbol)
{
    Morse s = { .dotdash = "", .meaning = { symbol, '\0' } };
    const Morse *m = bsearch(&s, morse, NUM_MORSE, sizeof(morse[0]), cmp_meaning);
    if (m == NULL)
        return "........";      /* Error! */
    else
        return m->dotdash;
}

static const char *morse_decode(const char *dotdash)
{
    Morse s = { .dotdash = "", .meaning = "" };
    strcpy(s.dotdash, dotdash);
    const Morse *m = bsearch(&s, morse, NUM_MORSE, sizeof(morse[0]), cmp_dotdash);
    if (m == NULL)
        return "<Error>";      /* Error! */
    else
        return m->meaning;
}

static void encode_ascii_line(const char *buffer)
{
    size_t length = 0;
    char last = '\0';
    for (size_t i = 0; buffer[i] != '\0'; i++)
    {
        unsigned char c = toupper((unsigned char)buffer[i]);
        if (isspace(c) || iscntrl(c))
        {
            if (last != ' ')
                length += printf("  ");   /* End of Word */
            last = ' ';
        }
        else
        {
            if (length >= 72)
            {
                putchar('\n');
                length = 0;
            }
            length += printf("%s ", morse_encode(c));
            last = buffer[i];
        }
    }
    if (length > 0)
        putchar('\n');
}

static void decode_morse_line(const char *buffer)
{
    char symbol[16];
    char spaces[16];

    printf("Input: [%s]\n", buffer);
    int offset = 0;
    int nbytes;
    int rc;
    while ((rc = sscanf(buffer + offset, "%15[-.]%15[ ]%n", symbol, spaces, &nbytes)) > 0)
    {
        printf("Symbol: [%s] meaning [%s]", symbol, morse_decode(symbol));
        if (rc == 2)
        {
            size_t length = strlen(spaces);
            if (length == 3)
                printf("  EOW");
            else if (length != 1)
                printf(" Bogus spacing (length = %zu)", length);
        }
        putchar('\n');
        if (rc != 2)
            break;
        offset += nbytes;
    }
}

static int cvt_ascii_to_morse(FILE *fp, const char *fn)
{
    qsort(morse, NUM_MORSE, sizeof(morse[0]), cmp_meaning);
    /*dump_morse_array("ASCII to Morse", NUM_MORSE, morse);*/

    if (filter_numfiles() > 1)
        printf("%s:\n", fn);

    char *buffer = 0;
    size_t buflen = 0;
    ssize_t linelen;
    while ((linelen = getline(&buffer, &buflen, fp)) > 0)
    {
        buffer[--linelen] = '\0';
        encode_ascii_line(buffer);
    }

    return 0;
}

static int cvt_morse_to_ascii(FILE *fp, const char *fn)
{
    qsort(morse, NUM_MORSE, sizeof(morse[0]), cmp_dotdash);
    /*dump_morse_array("Morse to ASCII", NUM_MORSE, morse);*/

    if (filter_numfiles() > 1)
        printf("%s:\n", fn);

    char *buffer = 0;
    size_t buflen = 0;

    ssize_t linelen;
    while ((linelen = getline(&buffer, &buflen, fp)) > 0)
    {
        buffer[--linelen] = '\0';
        decode_morse_line(buffer);
    }

    return 0;
}

static const char optstr[] = "dehV";
static const char usestr[] = "[-dehV] [file ...]";
static const char hlpstr[] =
    "  -e  Convert from ASCII to Morse\n"
    "  -d  Convert from Morse to ASCII\n"
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

int main(int argc, char **argv)
{
    StdoutFilter converter = 0;
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            converter = cvt_morse_to_ascii;
            break;
        case 'e':
            converter = cvt_ascii_to_morse;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("PROG", &"@(#)$Revision: 2.11 $ ($Date: 2017/11/01 19:05:42 $)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (converter == NULL)
    {
        err_error("You must specify either\n"
                  "-d (decode Morse to ASCII)or\n"
                  "-e (encode ASCII to Morse)\n");
    }

    filter_stdout(argc, argv, optind, converter);

    return 0;
}
