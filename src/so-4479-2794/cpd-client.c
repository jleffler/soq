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
#include <ftw.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
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

static char default_source[] = ".";
static char default_target[] = ".";
static char default_server[] = "localhost";
static char default_logger[] = "/dev/null";
static char default_portno[] = STRINGIZE(CPD_DEFAULT_PORT);

static char *source = default_source;
static char *target = default_target;
static char *server = default_server;
static char *logger = default_logger;
static char *portno = default_portno;

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
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'l':
            logger = optarg;
            break;
        case 'p':
            portno = optarg;
            break;
        case 's':
            server = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'S':
            source = optarg;
            break;
        case 'T':
            target = optarg;
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
    printf("Name [%s]\n", file);
    return 0;
}

static inline void st_int2(char *buffer, uint16_t data)
{
    buffer[0] = (data >> 8) & 0xFF;
    buffer[1] = (data >> 0) & 0xFF;
}

static void cpd_send_target(char *target)
{
    assert(target != 0);
    size_t len0 = 1;
    size_t len1 = 2;
    size_t len2 = strlen(target) + 1;
    char opcode[1] = { CPD_TARGETDIR };
    char tgtlen[2];
    st_int2(tgtlen, len2);
    assert(len2 <= UINT16_MAX);
    ssize_t explen = len0 + len1 + len2;
    struct iovec iov[3] =
    {
        { .iov_len = len0, .iov_base = opcode },
        { .iov_len = len1, .iov_base = tgtlen },
        { .iov_len = len2, .iov_base = target },
    };
    if (writev(cpd_fd, iov, 3) != explen)
        err_syserr("write error to server (%zu bytes): ", len0 + len1 + len2);
}

static void cpd_send_finished(void)
{
    assert(target != 0);
    char opcode[1] = { CPD_FINISHED };
    if (write(cpd_fd, &opcode, sizeof(opcode)) != sizeof(opcode))
        err_syserr("write error to server (%zu bytes): ", sizeof(opcode));
}

static void cpd_client(void)
{
    /* tcp_connect() does not return if it fails to connect */
    cpd_fd = tcp_connect(server, portno);
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

