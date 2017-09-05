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
#include "emalloc.h"
#include "cpd.h"
#include "mkpath.h"
#include "stderr.h"
#include "unpv13e.h"

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
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
                err_version("CPD-Server", &"@(#)$Revision$ ($Date$)"[4]);
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

    if (d_flag)
    {
        /*
        ** Beware - daemonize() does chdir("/").  It also connects
        ** stdin, stdout, stderr to /dev/null, and closes other file
        ** descriptors.  And it sets the error reporting system so it
        ** reports via syslog and not via file streams.  May need a
        ** mechanism to force printing to specified file stream instead
        ** of following configuration.
        */
        daemonize(err_getarg0(), 0);
    }

    const char logfile[] = "/tmp/cpd-server.log";                           // DEBUG
    FILE *fp = fopen(logfile, "w");                                         // DEBUG
    if (fp == 0)                                                            // DEBUG
        err_syserr("failed to open file '%s' for writing: ", logfile);      // DEBUG
    setvbuf(fp, 0, _IOLBF, 0);                                              // DEBUG
    err_logmsg(fp, ERR_PID|ERR_MILLI, 0, "Log file opened OK\n");           // DEBUG

    err_setlogopts(ERR_MILLI | ERR_PID);
    FILE *log_fp = stderr;
    if (logger != default_logger)
    {
        fprintf(fp, "opening log file '%s'\n", logger);                     // DEBUG
        err_logmsg(fp, ERR_MILLI|ERR_PID, 0, "opening log file '%s'\n", logger);                     // DEBUG
        if ((log_fp = fopen(logger, "a")) == 0)
            fprintf(fp, "failed to open log file '%s': ", logger),          // DEBUG
            err_syserr("failed to open log file '%s': ", logger);
        setvbuf(log_fp, 0, _IOLBF, 0);
        fprintf(fp, "opened log file '%s' OK\n", logger);                   // DEBUG
        fprintf(fp, "log file stream %p\n", (void *)log_fp);                // DEBUG
        FILE *old_log = err_stderr(log_fp);
        err_logmsg(log_fp, ERR_PID|ERR_MILLI, 0,
                   "old log stream = %p; stderr = %p\n", (void *)old_log, (void *)stderr);
        err_logmsg(fp, ERR_PID|ERR_MILLI, 0,
                   "old log stream = %p; stderr = %p\n", (void *)old_log, (void *)stderr);
        err_remark("started log file '%s' OK\n", logger);                   // DEBUG
    }
    else                                                                    // DEBUG
        err_logmsg(fp, ERR_PID|ERR_MILLI, 0,                                // DEBUG
                   "No log file specified - logging to '%s'\n",             // DEBUG
                   default_logger);                                         // DEBUG

    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
        err_syserr("failed to ignore SIGCHLD: ");

    fclose(fp);                                                             // DEBUG

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

static void cpd_send_status(int fd, int errnum, char *msgtxt)
{
    assert(msgtxt != 0);
    assert(errnum >= 0 && errnum < UINT16_MAX);
    //err_remark("Sending status %d [%s]\n", errnum, msgtxt);
    size_t len0 = 1;
    size_t len1 = 2;
    size_t len2 = 2;
    size_t len3 = strlen(msgtxt) + (msgtxt[0] != '\0');
    Byte opcode[1] = { CPD_STATUS };
    Byte ercode[2];
    st_uint16(ercode, errnum);
    Byte msglen[2];
    st_uint16(msglen, len3);
    assert(len3 <= UINT16_MAX);
    ssize_t explen = len0 + len1 + len2 + len3;
    struct iovec iov[4] =
    {
        { .iov_len = len0, .iov_base = (char *)opcode },
        { .iov_len = len1, .iov_base = (char *)ercode },
        { .iov_len = len2, .iov_base = (char *)msglen },
        { .iov_len = len3, .iov_base = (char *)msgtxt },
    };
    ssize_t actlen = writev(fd, iov, 4);
    if (actlen != explen)
        err_syserr("write error to server (wanted: %zu bytes, actual: %zd): ",
                len0 + len1 + len2, actlen);
    err_remark("Status %d [%s] sent\n", errnum, msgtxt);
}

static uint16_t cpd_recv_uint16(int fd)
{
    Byte buffer[2];
    if (read(fd, buffer, sizeof(buffer)) != sizeof(buffer))
        err_sysrem("failed to read %zu bytes\n", sizeof(buffer));
    uint16_t value = ld_uint16(buffer);
    return value;
}

static uint64_t cpd_recv_uint64(int fd)
{
    Byte buffer[8];
    if (read(fd, buffer, sizeof(buffer)) != sizeof(buffer))
        err_sysrem("failed to read %zu bytes\n", sizeof(buffer));
    uint64_t value = ld_uint64(buffer);
    return value;
}

static void cpd_recv_name(int fd, char **name, size_t *length)
{
    *length = cpd_recv_uint16(fd);
    *name = MALLOC(*length);
    if (read(fd, *name, *length) != (ssize_t)*length)
        err_sysrem("failed to read %zu bytes\n", *length);
    //err_remark("Name (%zu) [%s]\n", *length, *name);
    assert((*name)[*length-1] == '\0');
}

static inline mode_t cpd_recv_mode(int fd)
{
    return cpd_recv_uint16(fd);
}

static void cpd_set_status(int *status, char *buffer, size_t buflen, int errnum, const char *fmt, ...)
{
    *status = errnum;
    va_list args;
    va_start(args, fmt);
    size_t nbytes = vsnprintf(buffer, buflen, fmt, args);
    va_end(args);
    if (errnum != 0 && nbytes < buflen - sizeof(": 1234567890"))
    {
        buffer += nbytes;
        buflen -= nbytes;
        nbytes = snprintf(buffer, buflen, ": %d %s", errnum, strerror(errnum));
        if (nbytes < buflen - 2)
            strcpy(buffer + nbytes, "\n");
    }
}

/* Receive directory name, create it, and chdir into it */
static void cpd_recv_targetdir(int fd)
{
    char   *buffer;
    size_t  length;
    cpd_recv_name(fd, &buffer, &length);

    err_remark("Target Directory (%zu) [%s]\n", length, buffer);
    /* Do things like create the directory */
    /* Should probably be in a separate function */
    int status = 0;
    char msg[2048] = "";
    if (mkpath(buffer, 0755) != 0)
        cpd_set_status(&status, msg, sizeof(msg), errno, "failed to create path %s", buffer);
    else if (chdir(buffer) != 0)
    {
        char cwd[1024];
        status = errno;
        if (getcwd(cwd, sizeof(cwd)) == 0)
            strcpy(cwd, "[getcwd() failed]");
        cpd_set_status(&status, msg, sizeof(msg), status,
                       "failed to change directory to %s\nfrom directory %s\n",
                       buffer, cwd);
    }
    else
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == 0)
            strcpy(cwd, "[getcwd() failed]");
        err_remark("Changed directory to %s\n", cwd);
    }
    cpd_send_status(fd, status, msg);
    free(buffer);
}

static void cpd_set_mode(const char *name, mode_t mode, int *status, char *buffer, size_t buflen)
{
    if (chmod(name, mode) != 0)
       cpd_set_status(status, buffer, buflen, errno, "failed to set permission on '%s'", name);
}

/* Receive directory name and permissions and create it */
static void cpd_recv_directory(int fd)
{
    char *directory;
    size_t length;

    cpd_recv_name(fd, &directory, &length);
    err_remark("Receiving directory %zu [%s]\n", length, directory);
    mode_t mode = cpd_recv_mode(fd);
    int status = 0;
    char msg[2048] = "";
    if (mkpath(directory, mode) != 0)
        cpd_set_status(&status, msg, sizeof(msg), errno, "failed to create path %s", directory);
    else
        cpd_set_mode(directory, mode, &status, msg, sizeof(msg));
    cpd_send_status(fd, status, msg);
    free(directory);
}

static inline size_t min_size(size_t x, size_t y) { return x < y ? x : y; }

static void cpd_recv_regular(int fd)
{
    char  *file;
    size_t length;

    cpd_recv_name(fd, &file, &length);
    mode_t mode = cpd_recv_mode(fd);
    size_t size = cpd_recv_uint64(fd);

    char *eop = strrchr(file, '/');
    if (eop != 0)
    {
        size_t dirlen = eop - file + 1;
        char buffer[dirlen];
        memmove(buffer, file, dirlen);
        buffer[dirlen-1] = '\0';
        if (mkpath(buffer, 0755) != 0)
            err_syserr("failed to create directory %s for file %s", buffer, eop+1);
    }

    int o_fd = open(file, O_WRONLY|O_EXCL|O_CREAT, mode);
    if (o_fd < 0)
        err_syserr("failed to create file '%s' for writing: ", file);
    err_remark("Receiving regular file (%zu) [%s]\n", size, file);
    char buffer[65536];
    size_t t_bytes = 0;
    size_t r_bytes = min_size(sizeof(buffer), size);
    ssize_t n_bytes = 0;
    //err_remark("size    = %6zu; t_bytes = %6zu; r_bytes = %6zu\n", size, t_bytes, r_bytes);
    while (r_bytes > 0 && (n_bytes = read(fd, buffer, r_bytes)) > 0)
    {
        //err_remark("n_bytes = %6zu\n", n_bytes);
        if (write(o_fd, buffer, n_bytes) != n_bytes)
            err_syserr("short write for file '%s': ", file);
        t_bytes += n_bytes;
        r_bytes = min_size(sizeof(buffer), size - t_bytes);
        //err_remark("size    = %6zu; t_bytes = %6zu; r_bytes = %6zu\n", size, t_bytes, r_bytes);
    }
    if (n_bytes < 0)
        err_syserr("failed to write to file '%s'\n", file);
    err_remark("File [%s] received\n", file);
    cpd_send_status(fd, 0, "");
    free(file);
    close(o_fd);
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
        {
            cpd_send_status(fd, 0, "");
            break;
        }
        switch (opcode)
        {
        case CPD_TARGETDIR:
            cpd_recv_targetdir(fd);
            break;
        case CPD_REGULAR:
            cpd_recv_regular(fd);
            break;
        case CPD_DIRECTORY:
            cpd_recv_directory(fd);
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
