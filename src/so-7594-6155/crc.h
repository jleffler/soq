/*
@(#)File:           crc.h
@(#)Purpose:        Cyclic Redundancy Checksums
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1991-2018
@(#)Derivation:     crc.h 1.6 2018/05/07 17:14:09
*/

#ifndef CRC_H
#define CRC_H

#include <stddef.h>

/* Recommended (standard) values for magic */
#define CRC_16      0x8005
#define CRC_CCITT   0x1021

/* Return values are 16-bit values, always positive unless sizeof(int) == 2 */
extern int crc_forward(const void *msg, size_t len, unsigned short magic);
extern int crc_reverse(const void *msg, size_t len, unsigned short magic);

#endif /* CRC_H */
