/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Version information for SO-VLA-ARGS
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
*/

#ifndef SO_VLA_ARGS_VERSION_H_INCLUDED
#define SO_VLA_ARGS_VERSION_H_INCLUDED

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_so_vla_args_version_h[];
const char jlss_id_so_vla_args_version_h[] = "@(#)$Id$";
#endif /* lint */
#endif /* MAIN_PROGRAM */

static const char version_data[] = "@(#)$Version: 0.1.0 $ ($Datetime: 2022-01-24 17:12:21Z $)";
static const char cmdname_data[] = "@(#)SO-VLA-ARGS";
static const char * const version_info = &version_data[4];
static const char * const cmdname_info = &cmdname_data[4];

#endif /* SO_VLA_ARGS_VERSION_H_INCLUDED */

