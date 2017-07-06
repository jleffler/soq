/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        CPD Client for SO 4479-2794
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "cpd.h"
#include "stderr.h"
#include "unpv13e.h"
//#include <arpa/inet.h>
#include <assert.h>
#include <ftw.h>
#include <errno.h>
//#include <limits.h>
//#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/socket.h>
#include <sys/stat.h>
//#include <sys/types.h>
#include <unistd.h>

static const char optstr[] = "hvVl:s:p:S:T:";
static const char usestr[] = "[-hvV][-l log][-s host][-p port][-S source][-T target]";
static const char hlpstr[] = 
    "  -h         Print this help message and exit\n"
    "  -l log     Record errors in log file\n"
    "  -p port    Connect to cpd-server on this port (default 30991)\n"
    "  -s host    Connect to cpd-server on this host (default localhost)\n"
    "  -v         Set verbose mode\n"
    "  -S source  Source directory (default .)\n"
    "  -T target  Target directory (default - realpath for .)\n"
    "  -V         Print version information and exit\n"
    ;

static const char default_source[] = ".";
static const char default_target[] = ".";
static const char default_server[] = "localhost";
static const char default_logger[] = "/dev/null";

#define EVALUATE_STRING(x)    #x
#define STRINGIZE(x)    EVALUATE_STRING(x)

static const char default_port[] = STRINGIZE(CPD_DEFAULT_PORT);

static const char *source = default_source;
static const char *target = default_target;
static const char *server = default_server;
static const char *logger = default_logger;
static const char *port   = default_port;

static int cpd_fd = -1;
static int verbose = 0;

static void cpd_client(void);

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_cpd_client_c[];
const char jlss_id_cpd_client_c[] = "@(#)$Id$";
#endif /* lint */

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 's':
            server = optarg;
            break;
        case 'S':
            source = optarg;
            break;
        case 'T':
            target = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'l':
            logger = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'V':
            err_version("CPD-CLIENT", &"@(#)$Revision$ ($Date$)"[4]);
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

    cpd_client();

    if (log_fp != stderr)
        fclose(log_fp);

    return 0;
}

static int ftw_callback(const char *file, const struct stat *ptr, int flag)
{
    assert(file != 0);
    assert(ptr != 0);
    assert(flag == flag);   /* tautology */
    return 0;
}

static void cpd_send_target(const char *target)
{
    assert(target != 0);
}

static void cpd_send_finished(void)
{
}

static void cpd_client(void)
{
    /* tcp_connect() does not return if it fails to connect */
    cpd_fd = tcp_connect(server, port);
    cpd_send_target(target);
    if (verbose)
        err_remark("The directory being copied is: %s\n", source);
    if (ftw(source, ftw_callback, 10) != 0)
        err_error("failed to traverse directory tree\n");
    cpd_send_finished();
    if (close(cpd_fd) != 0)
        err_syserr("failed to close socket: ");
    if (verbose)
        err_remark("Directory %s has been copied\n", source);
}

