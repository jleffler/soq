/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        CPD Server for SO 4479-2794
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
**  -  daemonize() - called daemon_init() in UNP
**  -  tcp_accept() - called Accept() in UNP
**     modified to handle SIGCHLD signals, unlike the book's version.
*/

#include "posixver.h"
#include "cpd.h"
#include "stderr.h"
#include "unpv13e.h"
#include <arpa/inet.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
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
    "  -p port  Listen on this port (default 30991)\n"
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

    err_setlogopts(ERR_MILLI | ERR_PID);
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

static int chk_close(int fd) 
{
    int rc = close(fd);

    if (rc != 0)
        err_sysrem("close error: fd = %d\n", rc);
    return(rc);
}

/* Code ignores the possibility of 16-bit ints */
static void cpd_recv_targetdir(int fd)
{
    assert(fd >= 0);
    Byte len[2];
    if (read(fd, len, sizeof(len)) != sizeof(len))
        err_sysrem("failed to read %zu bytes\n", sizeof(len));
    uint16_t length = ld_int2(len);
    char buffer[length];
    if (read(fd, buffer, length) != length)
        err_sysrem("failed to read %u bytes\n", length);
    assert(buffer[length-1] == '\0');
    printf("Target Directory (%d) [%s]\n", length, buffer);
    /* Do things like create the directory */
}

static noreturn void be_childish(int fd, struct sockaddr_storage *client, socklen_t len)
{
    assert(fd >= 0);
    assert(client != 0);
    assert(len > 0);
    Byte opcode;
    while (read(fd, &opcode, sizeof(opcode)) == sizeof(opcode))
    {
        if (opcode == CPD_FINISHED || opcode == CPD_EXIT)
            break;
        switch (opcode)
        {
        case CPD_TARGETDIR:
            cpd_recv_targetdir(fd);
            break;
        default:
            err_internal(__func__, "Unimplemented opcode %d received\n", opcode);
            /*NOTREACHED*/
        }
    }
    chk_close(fd);
    err_remark("Child %d exiting on EOF\n", (int)getpid());
    exit(0);
}

static void cpd_server(void)
{
    size_t n_connections = 0;
    int lstn_fd = tcp_listen(NULL, portno, NULL);

    while (1)
    {
        struct sockaddr_storage cliaddr;
        socklen_t len = sizeof(cliaddr);
        int conn_fd = tcp_accept(lstn_fd, (struct sockaddr *)&cliaddr, &len);
        n_connections++;
        pid_t pid = fork();

        if (pid < 0)
            err_remark("failed to fork - connection %zu dropped!\n", n_connections);
        else if (pid == 0)
        {
            /* Child */
            chk_close(lstn_fd);
            be_childish(conn_fd, &cliaddr, len);
            /*NOTREACHED*/
        }
        else
            err_remark("Child PID %d started for connection %zu\n", (int)pid, n_connections);
        chk_close(conn_fd);
    }
}
