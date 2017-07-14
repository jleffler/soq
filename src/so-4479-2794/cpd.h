/* SO 4479-2794 - Copy directory hierarchy over network */

/*
** Packets from client (source) to server (target).
**
** CPD_TARGETDIR:
**   2-bytes name length (absolute path name including null byte)
**   length bytes of data
**   -- server creates directory if it can
**   -- server rejects request if directory doesn't exist and cannot be created
**   -- future: mode, uid, gid
** CPD_REGULAR:
**   2 bytes name length (including null byte) - path relative to target directory
**   name length bytes of data (file name)
**   2 bytes file mode (permissions)
**   8 bytes file length
**   file length bytes of data (file body)
**   -- server creates regular file if it can
**   -- server rejects request if the file cannot be created
**   -- future: uid, gid
** CPD_DIRECTORY:
**   2 bytes name length (including null byte) - path relative to target directory
**   name length bytes of data (file name)
**   -- server creates directory if it does not exist
**   -- server rejects request if directory doesn't exist and cannot be created
**   -- future: mode, uid, gid
** CPD_SYMLINK: unimplemented
** CPD_BLOCKDEV: unimplemented
** CPD_CHARDEV: unimplemented
** CPD_SOCKET: unimplemented
** CPD_FIFO: unimplemented
**
** CPD_FINISHED:
**   -- No more work for the current target directory.
**   -- Next operation must be CPD_TARGETDIR or CPD_EXIT
** CPD_EXIT:
**   -- Server process should exit
**
** Packets from server (target) to client (source).
**
** CPD_STATUS:
**   2 bytes error number
**   2 bytes information length (including null byte)
**   length bytes of string information
**   -- Number might be errno or other number.
**   -- Message should report fully with path relative to current target directory
** CPD_EXIT:
**   2 bytes status number
**   -- Server process is exiting with status given.
**
** EINVAL and other appropriate error codes will be reported by server when client
** abuses protocol.
**
** Note that lengths are sent in big-endian order (hence st_uint16(),
** st_uint32(), ld_uint16(), ld_uint32()).
*/

#ifndef CPD_H_INCLUDED
#define CPD_H_INCLUDED

#include <stdint.h>

typedef unsigned char Byte;

enum CPD_OpCode
{
    CPD_TARGETDIR = 23,
    CPD_REGULAR,
    CPD_DIRECTORY,
    CPD_FINISHED,
    CPD_EXIT,
    CPD_STATUS,
};

/* This can't be an enum — the value needs to be stringized by the preprocessor */
#define CPD_DEFAULT_PORT 30991

#define EVALUATE_STRING(x)    #x
#define STRINGIZE(x)    EVALUATE_STRING(x)

/* Functions managing big-endian byte order for data transmission */
static inline void st_uint16(Byte buffer[static sizeof(uint16_t)], uint16_t data)
{
    buffer[0] = (data >> 8) & 0xFF;
    buffer[1] = (data >> 0) & 0xFF;
}

static inline void st_uint32(Byte buffer[static sizeof(uint32_t)], uint32_t data)
{
    buffer[0] = (data >> 24) & 0xFF;
    buffer[1] = (data >> 16) & 0xFF;
    buffer[2] = (data >>  8) & 0xFF;
    buffer[3] = (data >>  0) & 0xFF;
}

static inline void st_uint64(Byte buffer[static sizeof(uint64_t)], uint64_t data)
{
    buffer[0] = (data >> 56) & 0xFF;
    buffer[1] = (data >> 48) & 0xFF;
    buffer[2] = (data >> 40) & 0xFF;
    buffer[3] = (data >> 32) & 0xFF;
    buffer[4] = (data >> 24) & 0xFF;
    buffer[5] = (data >> 16) & 0xFF;
    buffer[6] = (data >>  8) & 0xFF;
    buffer[7] = (data >>  0) & 0xFF;
}

static inline uint16_t ld_uint16(Byte buffer[static sizeof(uint16_t)])
{
    uint16_t data;
    data = (buffer[0] << 8) |
           (buffer[1] << 0);
    return data;
}

static inline uint32_t ld_uint32(Byte buffer[static sizeof(uint32_t)])
{
    uint32_t data;
    data = (buffer[0] << 24) |
           (buffer[1] << 16) |
           (buffer[2] <<  8) |
           (buffer[3] <<  0);
    return data;
}

static inline uint64_t ld_uint64(Byte buffer[static sizeof(uint64_t)])
{
    uint64_t data;
    data = ((uint64_t)buffer[0] << 56) |
           ((uint64_t)buffer[1] << 48) |
           ((uint64_t)buffer[2] << 40) |
           ((uint64_t)buffer[3] << 32) |
           ((uint64_t)buffer[4] << 24) |
           ((uint64_t)buffer[5] << 16) |
           ((uint64_t)buffer[6] <<  8) |
           ((uint64_t)buffer[7] <<  0);
    return data;
}

#endif /* CPD_H_INCLUDED */
