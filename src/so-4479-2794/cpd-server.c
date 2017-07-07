/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        ?
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/*
** NB: This code uses some of the code from Stevens et al "Unix Network
** Programming, Volume 1, 3rd Edition" (aka UNP, or UNPv13e).
** Specifically, this code uses (a much cut down variant of) the unp.h
** header and four functions:
**  -  tcp_connect()
**  -  tcp_listen()
**  -  daemon_init() - renamed to daemonize() when imported to JLSS
**  -  Accept() - renamed to tcp_accept() when imported to JLSS, and
**     modified to handle SIGCHLD signals, unlike the book's version.
*/

#include "posixver.h"
#include "cpd.h"
#include "stderr.h"
#include "unpv13e.h"
#include <assert.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

static const char optstr[] = "dhvVp:l:";
static const char usestr[] = "[-dhvV][-p port][-l log]";
static const char hlpstr[] =
    "  -d       Daemonize process\n"
    "  -h       Print this help message and exit\n"
    "  -l log   Record errors in log file\n"
    "  -p port  Listen on this port (default 30991 - arbitrary)\n"
    "  -v       Set verbose mode\n"
    "  -V       Print version information and exit\n"
    ;

static char default_logger[] = "/dev/null";
static char default_portno[] = STRINGIZE(CPD_DEFAULT_PORT);

static int verbose = 0;
static char *logger = default_logger;
static char *portno = default_portno;

static void cpd_server(void);

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_cpd_server_c[];
const char jlss_id_cpd_server_c[] = "@(#)$Id$";
#endif /* lint */

int main(int argc, char **argv)
{
    int d_flag = 0;
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
            case 'd':
                d_flag = 1;
                break;
            case 'l':
                logger = optarg;
                break;
            case 'p':
                portno = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                err_help(usestr, hlpstr);
                /*NOTREACHED*/
            case 'V':
                err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
                /*NOTREACHED*/
            default:
                err_usage(usestr);
                /*NOTREACHED*/
        }
    }

    if (optind != argc)
    {
        err_remark("Extraneous arguments, starting with '%s'\n", argv[optind]);
        err_usage(usestr);
    }

    FILE *log_fp = stderr;
    if (logger != default_logger)
    {
        if ((log_fp = fopen(logger, "a")) == 0)
            err_syserr("failed to open log file '%s': ", logger);
        err_stderr(log_fp);
    }

    if (d_flag)
    {
        /* Beware - daemonize() does chdir("/") */
        daemonize(err_getarg0(), 0);
    }

    cpd_server();

    if (log_fp != stderr)
        fclose(log_fp);

    return 0;
}

static void cpd_server(void)
{
}
