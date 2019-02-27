/* SO 4418-0272 */
/* Variant 4 - handle long messages (configurable) */
#include "posixver.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stderr.h"
#include "debug.h"

static void wait_for(pid_t pid)
{
    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
    {
        err_remark("PID %d exit status 0x%.4X\n", corpse, status);
        if (corpse == pid)
            break;
    }
}

static void write_log_segment(int fd, size_t lencode, size_t length, const char *msg)
{
    unsigned char byte = lencode;
    assert(lencode == length || (lencode == 0 && length == UCHAR_MAX));

    if (write(fd, &byte, sizeof(byte)) != sizeof(byte) ||
        write(fd, msg, length) != (ssize_t)length)    // avoid signed/unsigned comparison
        err_error("failed to write message to logger\n");
    DB_TRACE(5, "Wrote segment: %zu (code %zu) [%s]\n", length, lencode, msg);
}

static void write_log(int fd, const char *msg)
{
    size_t len = strlen(msg);
    DB_TRACE(3, "Write buffer: %zu [%s]\n", len, msg);
    while (len > 0)
    {
        size_t lencode = (len <= UCHAR_MAX) ? len : 0;
        size_t length  = (len <= UCHAR_MAX) ? len : UCHAR_MAX;
        write_log_segment(fd, lencode, length, msg);
        len -= length;
        msg += length;
    }
    DB_TRACE(3, "Buffer complete\n");
}

/*
** This code could encounter:
** 1.  EOF (or a read error) - return EOF.
** 2.  A regular complete message in a single segment - return message
**     length (1..255).
** 3.  A partial message with more segments to follow - return MSG_SEGMENT.
** Partial segments with more to follow are of length 255, but it is
** possible to have a regular complete message of length 255.
*/
enum { MSG_SEGMENT = -2 };
static_assert(MSG_SEGMENT != EOF, "EOF is not distinct from MSG_SEGMENT");

static int read_log_segment(int fd, size_t buflen, char buffer[buflen])
{
    unsigned char byte;
    if (read(fd, &byte, sizeof(byte)) != sizeof(byte))
    {
        err_remark("EOF on file descriptor %d\n", fd);
        return EOF;
    }
    size_t length = byte;
    if (length == 0)
        length = UCHAR_MAX;
    if (buflen < (size_t)(byte + 1))        // avoid signed/unsigned comparison
        err_syserr("buffer length %zu cannot hold %d bytes\n", buflen, byte + 1);
    if (read(fd, buffer, length) != (ssize_t)length)    // avoid signed/unsigned comparison
        err_error("failed to read %zu bytes from file descriptor %d\n", length, fd);
    buffer[length] = '\0';
    return (byte == 0) ? MSG_SEGMENT : byte;
}

static size_t read_log(int fd, size_t buflen, char buffer[buflen])
{
    DB_TRACE(3, "reading %zu\n", buflen);
    char *msg = buffer;
    size_t len = buflen;
    int nbytes;
    int tbytes = 0;
    while (len > 0 && (nbytes = read_log_segment(fd, len, msg)) != EOF)
    {
        if (nbytes != MSG_SEGMENT)
        {
            tbytes += nbytes;
            break;
        }
        nbytes = UCHAR_MAX;
        DB_TRACE(5, "segment %d [%s] (%zu: %d: %zu)\n", nbytes, msg, buflen, tbytes, len);
        msg += nbytes;
        len -= nbytes;
        tbytes += nbytes;
    }
    /* This disguises a read error or EOF as success when a long message is truncated */
    if (tbytes != 0)
        DB_TRACE(3, "logging %d [%s]\n", tbytes, buffer);
    else
        DB_TRACE(3, "EOF\n");
    return tbytes;
}

static void gen_msg(size_t size, char *buffer)
{
    enum { CHUNK_SIZE = 64 };
    char *obuffer = buffer;     // DEBUG
    size_t osize = size;        // DEBUG
    char c = 'a';
    while (size >= CHUNK_SIZE)
    {
        memset(buffer, c, CHUNK_SIZE - 1);
        buffer[CHUNK_SIZE - 1] = '\n';
        size -= CHUNK_SIZE;
        buffer += CHUNK_SIZE;
        if (++c > 'z')
            c = 'a';
    }
    if (size > 0)
    {
        if (size > 1)
            memset(buffer, '@', size - 1);
        buffer[size - 1] = '\n';
        buffer += size;
    }
    buffer[0] = '\0';
    DB_TRACE(7, "GM: Buffer %zu (%zu) [%s]\n", osize, strlen(obuffer), obuffer);
}

static const char optstr[] = "dhD:";
static const char usestr[] = "[-dh][-D level]";
static const char hlpstr[] =
    "  -d        Set debug level 3\n"
    "  -h        Print this help message and exit\n"
    "  -D level  Set debug level\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    err_setlogopts(ERR_PID|ERR_MILLI);
    db_setoptions(DB_OPT_PID);

    int pipefd[2];
    pid_t pid;
    char szLogtest1[] = "Log Event: Blah blah blah\n";
    char szLogtest2[] = "Log Event: Blah blah 2\n";

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            db_setdebug(3);
            break;
        case 'D':
            db_setdebug(atoi(optarg));
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (pipe(pipefd) != 0)
        exit(1);

    if ((pid = fork()) == -1)
        err_syserr("failed to fork: ");
    else if (pid == 0)
    {
        printf("%d: I am child!\n", (int)getpid());
        close(pipefd[1]);     // close the write end of pipe

        char readbuffer[1200];
        int nbytes;
        while ((nbytes = read_log(pipefd[0], sizeof(readbuffer), readbuffer)) > 0)
        {
            printf("%d: Logging string: %d [%s]\n", (int)getpid(), nbytes, readbuffer);
        }
        close(pipefd[0]);
        printf("%d: EOF on pipe - exiting\n", (int)getpid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("%d: I am parent!\n", (int)getpid());
        close(pipefd[0]);     // close read end of pipe

        write_log(pipefd[1], szLogtest1);
        write_log(pipefd[1], szLogtest2);
        int multiplier = 4;
        for (int i = 64; i <= 1024; i *= multiplier)
        {
            char buffer[1100];
            //for (int j = i - multiplier; j <= i + multiplier; j++)
            for (int j = i - 1; j <= i + 1; j++)
            {
                gen_msg(j, buffer);
                write_log(pipefd[1], buffer);
            }
        }
        close(pipefd[1]);
        wait_for(pid);
    }

    return 0;
}
