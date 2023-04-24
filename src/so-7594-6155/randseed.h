/*
@(#)File:           randseed.h
@(#)Purpose:        Generate pseudo-random seeds
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018-2019
@(#)Derivation:     randseed.h 1.3 2019/01/20 08:44:42
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_RANDSEED_H
#define JLSS_ID_RANDSEED_H

#include <stddef.h>
#include <stdint.h>

extern void random_seed_bytes(size_t nbytes, void *bytes);

#ifdef RS4_NO_INLINE_FUNCTIONS

/* Convenience interfaces */
extern uint32_t random_seed_uint32(void);
extern  int32_t random_seed_sint32(void);
extern uint64_t random_seed_uint64(void);
extern  int64_t random_seed_sint64(void);

#else

static inline int32_t random_seed_sint32(void)
{
    int32_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

static inline uint32_t random_seed_uint32(void)
{
    uint32_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

static inline int64_t random_seed_sint64(void)
{
    int64_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

static inline uint64_t random_seed_uint64(void)
{
    uint64_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

#endif /* RS4_NO_INLINE_FUNCTIONS */

#endif /* JLSS_ID_RANDSEED_H */
