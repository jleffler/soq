/*
@(#)File:           crc.c
@(#)Purpose:        Cyclic Redundancy Checksums
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1991-2018
@(#)Derivation:     crc.c 1.7 2018/05/07 17:14:09
*/

/*TABSTOP=4*/

/*
**  Extracted from Personal Computer World, March 1991, Subset.
**  The algorithms there are in 80x86 assembler with a p-code
**  preamble, and this code is an implementation in C of the p-code.
*/

#include "crc.h"

#define DIM(x)  (sizeof(x)/sizeof(*(x)))

typedef unsigned short ushort;

static ushort   crc_fwd[256];
static ushort   crc_ftype = 0;
static ushort   crc_rtype = 0;

static void crc_fwdinit(ushort magic)
{
    ushort  a;
    ushort  d;
    ushort  e;
    ushort  j;
    ushort  t;
    ushort *src;
    ushort *end;

    src = crc_fwd;
    end = src + DIM(crc_fwd);
    e = 0;
    while (src < end)
    {
        d = e;
        e += 256;
        a = 0;
        for (j = 0; j < 8; j++)
        {
            t = d ^ a;
            d <<= 1;
            a <<= 1;
            if (t & 0x8000)
                a ^= magic;
        }
        *src++ = a;
    }
    crc_ftype = magic;
}

static void crc_revinit(ushort magic)
{
    ushort  a;
    ushort  d;
    ushort  e;
    ushort  j;
    ushort  t;
    ushort *src;
    ushort *end;

    src = crc_fwd;
    end = src + DIM(crc_fwd);
    e = 0;
    while (src < end)
    {
        d = e;
        e += 2;
        a = 0;
        for (j = 0; j < 8; j++)
        {
            d >>= 1;
            t = d ^ a;
            a >>= 1;
            if (t & 0x0001)
                a ^= magic;
        }
        *src++ = a;
    }
    crc_rtype = magic;
}

int crc_forward(const void *msg, size_t len, ushort magic)
{
    ushort crc;
    const char  *src = msg;
    const char  *end = src + len;

    if (crc_ftype != magic)
        crc_fwdinit(magic);
    crc = 0;
    while (src < end)
        crc = crc_fwd[(crc >> 8) ^ *src++] ^ (crc << 8);
    return (crc);
}

int crc_reverse(const void *msg, size_t len, ushort magic)
{
    ushort crc;
    const char  *src = msg;
    const char  *end = src + len;

    if (crc_rtype != magic)
        crc_revinit(magic);
    crc = 0;
    while (src < end)
        crc = crc_fwd[(crc ^ *src++) & 0xFF] ^ (crc >> 8);
    return (crc);
}

#ifdef TEST

#include <stdio.h>
#include <string.h>

static const char msg[] = "CRC_16 or CRC_CCITT checksum code -- test string";

#define CRC_16F_CKSUM       10591
#define CRC_16R_CKSUM       30153
#define CRC_CCITTF_CKSUM    13211
#define CRC_CCITTR_CKSUM     5068

int main(void)
{
    int             l;

    l = strlen(msg);

    printf("Message   : %s (length %d)\n", msg, l);
    printf("CRC-16    : %05u (expected %05u)\n", crc_forward(msg, l, CRC_16),    CRC_16F_CKSUM);
    printf("CRC-16R   : %05u (expected %05u)\n", crc_reverse(msg, l, CRC_16),    CRC_16R_CKSUM);
    printf("CRC-CCITT : %05u (expected %05u)\n", crc_forward(msg, l, CRC_CCITT), CRC_CCITTF_CKSUM);
    printf("CRC-CCITTR: %05u (expected %05u)\n", crc_reverse(msg, l, CRC_CCITT), CRC_CCITTR_CKSUM);
    return (0);
}

#endif /* TEST */
