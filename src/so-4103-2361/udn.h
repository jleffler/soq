/*
@(#)File:           udn.h
@(#)Purpose:        Generate numbers with no repeated base 10 digits
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_UDN_H
#define JLSS_ID_UDN_H

/*
** UDN = Unique Digit Number (a base 10 number with no leading zeros and
**       no repeated digit).
** Assume 32-bit int type.  A 32-bit integer is big enough for up to
** 9-digit numbers; it can't handle 10-digit numbers.
** UDN is not an opaque type so the functions do not need to handle
** memory allocation.
*/

#include <stdbool.h>
#include <stddef.h>

typedef struct UDN
{
    int next_value;
    int max_value;
} UDN;

enum { UDN_BUFLEN = 12 };       // Recommended length for buffer to udn_gen_next()

/* Generate next UDN - report true unless there are no more in current */
/* cycle 0..max_value - or buflen is too small  */
extern bool udn_gen_next(UDN *udn, size_t buflen, char buffer[buflen]);

/* Set or reset next UDN */
extern void udn_set_next(UDN *udn, int next);

/* Initialize UDN structure */
extern void udn_initialize(UDN *udn, int next, int max);

#endif /* JLSS_ID_UDN_H */
