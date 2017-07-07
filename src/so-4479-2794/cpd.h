/* SO 4479-2794 - Copy directory hierarchy over network */

/*
** Packets from client (source) to server (target).
**
** CPD_TARGETDIR:
**   2-bytes name length (absolute path name including null byte)
**   length bytes of data
**   -- server creates directory if it can
**   -- server rejects request if directory doesn't exist and cannot be created
** CPD_REGNAME:
**   2 bytes name length (including null byte) - path relative to target directory
**   2 bytes file mode (permissions)
**   name length bytes of data (file name)
**   -- server creates regular file if it can
**   -- server rejects request if the file cannot be created
** CPD_DIRNAME:
**   2 bytes name length (including null byte) - path relative to target directory
**   name length bytes of data (file name)
**   -- server creates directory if it does not exist
**   -- server rejects request if directory doesn't exist and cannot be created
** CPD_REGFILE4:
**   4 bytes file length (up to 2^31-1 bytes)
**   file length bytes of data (file body)
** CPD_REGFILE8: unimplemented
** CPD_SYMLINK: unimplemented
** CPD_BLOCKDEV: unimplemented
** CPD_CHARDEV: unimplemented
** CPD_SOCKET: unimplemented
** CPD_FIFO:
**   2 bytes name length (including null byte) - path relative to target directory
**   name length bytes of data (FIFO name)
**   -- server creates FIFO if it does not exist
**   -- server rejects request if FIFO doesn't exist and cannot be created
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
*/

#ifndef CPD_H_INCLUDED
#define CPD_H_INCLUDED

enum CPD_OpCode
{
    CPD_TARGETDIR = 23,
    CPD_REGNAME,
    CPD_DIRNAME,
    CPD_REGFILE4,
    CPD_FIFO,
    CPD_FINISHED,
    CPD_EXIT,
    CPD_STATUS,
};

/* This can't be an enum — the value needs to be stringized by the preprocessor */
#define CPD_DEFAULT_PORT 30991

#define EVALUATE_STRING(x)    #x
#define STRINGIZE(x)    EVALUATE_STRING(x)

#endif /* CPD_H_INCLUDED */
