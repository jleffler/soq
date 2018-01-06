/*
@(#)File:           microsleep.c
@(#)Purpose:        Implement platform-independent micro_sleep()
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018
*/

/*TABSTOP=4*/

#ifndef MICROSLEEP_H_INCLUDED
#define MICROSLEEP_H_INCLUDED

#include <sys/types.h>

extern int micro_sleep(useconds_t useconds);

#endif /* MICROSLEEP_H_INCLUDED */
