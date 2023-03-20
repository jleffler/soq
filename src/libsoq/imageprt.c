/*
@(#)File:           imageprt.c
@(#)Purpose:        Print hexadecimal/printable image of memory block
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2023
@(#)Derivation:     imageprt.c 2023.1 2023/03/06 18:28:14
*/

/*TABSTOP=4*/

#include "imageprt.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static inline size_t min_size(size_t a, size_t b)
{
    return (a < b) ? a : b;
}

static void print_count(FILE *fp, size_t count)
{
    if (count > 0)
        fprintf(fp, "* (%zu)\n", count);
}

static void print_offset(FILE *fp, size_t offset, char pad)
{
    fprintf(fp, "0x%04zX:%c", offset, pad);
}

/* Print one line image of record as hex and characters */
static void print_line(FILE *fp, size_t offset, const void *buffer, size_t nbytes)
{
    const char *base = buffer;

    assert(nbytes > 0 && nbytes <= 16);
    print_offset(fp, offset, ' ');
    const char *s = base;
    size_t i;
    for (i = 0; i < nbytes; i++)
        fprintf(fp, "%02X ", *s++ & 0xFF);
    while (i++ < 16)
        fprintf(fp, "   ");
    fprintf(fp, "  ");
    s = base;
    for (i = 0; i++ < nbytes; s++)
        fprintf(fp, "%c", (isprint((unsigned char)*s) ? *s : '.'));
    putc('\n', fp);
}

/*
**  Print image of record as hex and characters
*/
void image_print(FILE *fp, size_t offset, const void *buffer, size_t nbytes)
{
    const char     *base = buffer;
    const char     *end = base + nbytes;

    for (base = buffer; base < end; base += 16)
    {
        size_t chunk_size = min_size(16, end - base);
        print_line(fp, offset, base, chunk_size);
        offset += chunk_size;
    }
    /* Do not print offset at end - it wrecks odx, amongst other programs */
    /*print_offset(fp, offset, '\n');*/
}

/*
**  Print image of record as hex and characters
**  Compress repeated output lines.
*/
void image_print_compressed(FILE *fp, size_t offset, const void *buffer, size_t nbytes)
{
    const char *base = buffer;
    int         mode = 1;
    size_t      count = 0;
    char        obuffer[16];
    const char *end = base + nbytes;

    for (base = buffer; base < end; base += 16)
    {
        size_t chunk_size = min_size(sizeof(obuffer), end - base);
        if (base != buffer && chunk_size == sizeof(obuffer) &&
            memcmp(obuffer, base, chunk_size) == 0)
        {
            if (mode == 1)
                mode = 0;
            count++;
            offset += chunk_size;
        }
        else
        {
            print_count(fp, count);
            count = 0;
            print_line(fp, offset, base, chunk_size);
            memcpy(obuffer, base, chunk_size);
            mode = 1;
            offset += chunk_size;
        }
    }
    print_count(fp, count);
    print_offset(fp, offset, '\n');
}

#ifdef TEST

#error Use separate test program test.imageprt.c

#endif /* TEST */
