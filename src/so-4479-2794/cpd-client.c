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
** header and one function:
**  -  tcp_connect()
*/

#include "posixver.h"
#include "cpd.h"
#include "stderr.h"
#include "unpv13e.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <inttypes.h>
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

static void cpd_send_target(int fd, char *target)
{
    err_remark("Sending target [%s]\n", target);
    assert(target != 0);
    size_t len0 = 1;
    size_t len1 = 2;
    size_t len2 = strlen(target) + 1;
    Byte opcode[1] = { CPD_TARGETDIR };
    Byte tgtlen[2];
    st_uint16(tgtlen, len2);
    assert(len2 <= UINT16_MAX);
    ssize_t explen = len0 + len1 + len2;
    ssize_t actlen;
    struct iovec iov[3] =
    {
        { .iov_len = len0, .iov_base = (char *)opcode },
        { .iov_len = len1, .iov_base = (char *)tgtlen },
        { .iov_len = len2, .iov_base = (char *)target },
    };
    actlen = writev(fd, iov, 3);
    if (actlen != explen)
        err_syserr("write error to server (wanted: %zu bytes, actual: %zd): ",
                   explen, actlen);
    err_remark("Target [%s] sent\n", target);
}

static void cpd_send_directory(int fd, const char *directory, mode_t mode)
{
    err_remark("Sending directory [%s]\n", directory);
    assert(directory != 0);
    size_t len0 = 1;
    size_t len1 = 2;
    size_t len2 = strlen(directory) + 1;
    size_t len3 = 2;
    Byte opcode[1] = { CPD_DIRECTORY };
    Byte dirlen[2];
    st_uint16(dirlen, len2);
    Byte dirmode[2];
    st_uint16(dirmode, mode & (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX));
    assert(len2 <= UINT16_MAX);
    ssize_t explen = len0 + len1 + len2 + len3;
    ssize_t actlen;
    struct iovec iov[] =
    {
        { .iov_len = len0, .iov_base = (char *)opcode    },
        { .iov_len = len1, .iov_base = (char *)dirlen    },
        { .iov_len = len2, .iov_base = (char *)directory },
        { .iov_len = len3, .iov_base = (char *)dirmode   },
    };
    enum { NUM_IOV = sizeof(iov) / sizeof(iov[0]) };
    actlen = writev(fd, iov, NUM_IOV);
    if (actlen != explen)
        err_syserr("write error to server (wanted: %zu bytes, actual: %zd): ",
                   explen, actlen);
    err_remark("Directory [%s] sent\n", directory);
}

static void cpd_send_finished(int fd)
{
    printf("Sending finished\n");
    assert(target != 0);
    Byte opcode[1] = { CPD_FINISHED };
    if (write(fd, &opcode, sizeof(opcode)) != sizeof(opcode))
        err_syserr("write error to server (%zu bytes): ", sizeof(opcode));
}

static void cpd_recv_status(int fd, int *errnum, char **msgtxt)
{
    assert(fd >= 0);
    assert(errnum != 0);
    assert(msgtxt != 0);
    Byte err[2];
    if (read(fd, err, sizeof(err)) != sizeof(err))
        err_syserr("failed to read %zu bytes\n", sizeof(err));
    *errnum = ld_uint16(err);
    Byte len[2];
    if (read(fd, len, sizeof(len)) != sizeof(len))
        err_syserr("failed to read %zu bytes\n", sizeof(err));
    uint16_t msglen = ld_uint16(len);
    if (msglen == 0)
        *msgtxt = 0;
    else
    {
        *msgtxt = malloc(msglen);
        if (*msgtxt == 0)
            err_syserr("failed to allocate %d bytes\n", msglen);
        if (read(fd, *msgtxt, msglen) != msglen)
            err_syserr("failed to read %d bytes\n", msglen);
        assert((*msgtxt)[msglen - 1] == '\0');
    }
    printf("%s: status %d L = %d [%s]\n", __func__, *errnum, msglen, *msgtxt ? *msgtxt : "");
}

static void cpd_recv_message(int fd)
{
    assert(fd >= 0);
    Byte opcode;
    if (read(fd, &opcode, sizeof(opcode)) != sizeof(opcode))
        err_syserr("failed to read any response: ");
    switch (opcode)
    {
    case CPD_STATUS:
        {
        int errnum;
        char *msgtxt;
        cpd_recv_status(fd, &errnum, &msgtxt);
        free(msgtxt);
        }
        break;
    default:
        err_internal(__func__, "Unexpected opcode %d (0x%.2X)\n", opcode, opcode);
        /*NOTREACHED*/
    }
}

static inline ssize_t write_all(int fd, const char *buffer, ssize_t size)
{
    ssize_t w_bytes = size;
    ssize_t n_bytes;
    while (w_bytes > 0 && (n_bytes = write(fd, buffer, w_bytes)) > 0)
        w_bytes -= n_bytes;
    return size - w_bytes;
}

static void cpd_send_regular(int fd, const char *file, mode_t mode, off_t size)
{
    /* assume off_t is equivalent to signed 64-bit integer; OK for macOS Sierra */
    assert(fd >= 0);
    assert(file != 0);
    assert(size == size);   /* tautology */
    assert(S_ISREG(mode));
    int i_fd = open(file, O_RDONLY);
    if (i_fd < 0)
        err_syserr("failed to open file '%s' for reading: ", file);
    err_remark("Sending regular file [%s]\n", file);
    size_t len0 = 1;    // opcode
    size_t len1 = 2;    // name length
    size_t len2 = strlen(file) + 1;
    size_t len3 = 2;    // mode
    size_t len4 = 8;    // file size
    Byte op_code[1] = { CPD_REGULAR };
    Byte name_len[2];
    st_uint16(name_len, len2);
    assert(len2 <= UINT16_MAX);
    Byte filemode[2];
    st_uint16(filemode, mode & (S_IRWXO|S_IRWXU|S_IRWXG|S_ISUID|S_ISGID|S_ISVTX));
    Byte filesize[8];
    st_uint64(filesize, size);
    ssize_t explen = len0 + len1 + len2 + len3 + len4;
    struct iovec iov[] =
    {
        { .iov_len = len0, .iov_base = (char *)op_code  },
        { .iov_len = len1, .iov_base = (char *)name_len },
        { .iov_len = len2, .iov_base = (char *)file     },
        { .iov_len = len3, .iov_base = (char *)filemode },
        { .iov_len = len4, .iov_base = (char *)filesize },
    };
    enum { NUM_IOV = sizeof(iov) / sizeof(iov[0]) };
    ssize_t actlen = writev(fd, iov, NUM_IOV);
    if (actlen != explen)
        err_syserr("write error to server (wanted: %zu bytes, actual: %zd): ",
                   explen, actlen);
    size_t t_bytes = 0;
    ssize_t n_bytes;
    char buffer[65536];
    while ((n_bytes = read(i_fd, buffer, sizeof(buffer))) > 0)
    {
        if (t_bytes + n_bytes > (size_t)size)
            err_error("file '%s' grew while being copied\n", file);
        else if (write_all(fd, buffer, n_bytes) != n_bytes)
            err_syserr("short write for file '%s': ", file);
    }
    err_remark("File [%s] sent\n", file);
}

static void cpd_xfer_regular(int fd, const char *file, const struct stat *ptr)
{
    assert(fd >= 0);
    assert(file != 0);
    assert(ptr != 0);
    //int errnum = 0;;
    //char *msgtxt = 0;
    cpd_send_regular(fd, file, ptr->st_mode, ptr->st_size);
    cpd_recv_message(fd);
    //cpd_recv_message(fd, &errnum, &msgtxt);
    //if (errnum != 0)
        //err_remark("failed to copy %" PRId64 " bytes for file %s\n", (int64_t)ptr->st_size, file);
    //else
        //printf("Copied %" PRId64 " bytes of %s OK\n", (int64_t)ptr->st_size, file);
}

static void cpd_xfer_directory(int fd, const char *directory, const struct stat *ptr)
{
    assert(fd >= 0);
    assert(directory != 0);
    assert(ptr != 0);
    //int errnum = 0;;
    //char *msgtxt = 0;
    cpd_send_directory(fd, directory, ptr->st_mode);
    cpd_recv_message(fd);
    //cpd_recv_message(fd, &errnum, &msgtxt);
    //if (errnum != 0)
        //err_remark("failed to create directory %s\n", directory);
    //else
        //
   printf("Created directory %s OK\n", directory);
}

static int ftw_callback(const char *file, const struct stat *ptr, int flag)
{
    assert(file != 0);
    assert(ptr != 0);
    printf("FTW-CB: Name [%s]\n", file);
    switch (flag)
    {
    case FTW_F:
        cpd_xfer_regular(cpd_fd, file, ptr);
        break;
    case FTW_D:
        cpd_xfer_directory(cpd_fd, file, ptr);
        break;
    case FTW_DNR:
        err_remark("Cannot read directory %s\n", file);
        break;
    case FTW_DP:
        err_internal(__func__, "post-order directory - cannot happen!\n");
        /*NOTREACHED*/
    case FTW_NS:
        err_remark("Could not get status for file %s\n", file);
        break;
    case FTW_SL:
        err_remark("Ignoring symlink %s pro tem\n", file);
        break;
    case FTW_SLN:
        err_remark("Ignoring broken symlink %s pro tem\n", file);
        break;
    default:
        err_internal(__func__, "unexpected flag value %d received\n", flag);
        /*NOTREACHED*/
    }
    return 0;
}

static void cpd_client(void)
{
    /* tcp_connect() does not return if it fails to connect */
    cpd_fd = tcp_connect(server, portno);
    assert(cpd_fd >= 0);
    cpd_send_target(cpd_fd, target);
    cpd_recv_message(cpd_fd);
    err_remark("Sending request\n");
    if (verbose)
        err_remark("The directory being copied is: %s\n", source);
    if (chdir(source) != 0)
        err_syserr("failed to change directory to '%s'\n", source);
    if (ftw(".", ftw_callback, 10) != 0)
        err_error("failed to traverse directory tree\n");
    cpd_send_finished(cpd_fd);
    cpd_recv_message(cpd_fd);
    if (close(cpd_fd) != 0)
        err_syserr("failed to close socket: ");
    if (verbose)
        err_remark("Directory %s has been copied\n", source);
}

