#include "osfile.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

typedef struct stat Stat;

/* Destined for osfile.h */
typedef int   (*ifx_fd_FileOpen)(const char *name);
typedef FILE *(*ifx_fp_FileOpen)(const char *name);

/* Destined for osfile.h */
extern int   ifx_fd_reopen_if_file_changed(int   fd, const char *fname, ifx_fd_FileOpen opener);
extern FILE *ifx_fp_reopen_if_file_changed(FILE *fp, const char *fname, ifx_fp_FileOpen opener);

#ifdef TESTMODE
extern void mt_log_printf(const char *format, ...);
#endif /* TESTMODE */

/*
** file_has_changed():
**      Check whether the file descriptor fd points to the current file fname 
**
** The file is different if:
** - The file descriptor is invalid
** - The file cannot be stat'd
** - The number of links on the file descriptor is zero (file removed)
** - The device number hosting the file has changed (symlink involved?)
** - The inode number of the file has changed
*/
static bool file_has_changed(int fd, const char *fname)
{
    bool rc = false;
    Stat sb_fd;
    Stat sb_fn;
    int rv1 = fstat(fd, &sb_fd);
    int rv2 = stat(fname, &sb_fd);
    if (rv1 != 0 || rv2 != 0 || sb_fd.st_nlink == 0 ||
        sb_fd.st_rdev != sb_fn.st_rdev || sb_fd.st_ino != sb_fn.st_ino)
    {
#ifdef TESTMODE
        int errnum = errno;
        static const char msg_prefix[] = "Need to reopen file";
        if (rv1 != 0)
            mt_log_printf("%s %s\nfstat(%d) failed with errno %d (%s)",
                          msg_prefix, fname, fd, errnum, strerror(errno));
        else if (rv2 != 0)
            mt_log_printf("%s %s\nstat() failed with errno %d (%s)",
                          msg_prefix, fname, errnum, strerror(errno));
        else if (sb_fd.st_nlink == 0)
            mt_log_printf("%s %s\nlinks to fd %d dropped to zero",
                          msg_prefix, fname, fd);
        else if (sb_fd.st_rdev != sb_fn.st_rdev)
            mt_log_printf("%s %s\nfile device changed (old %d, new %d)",
                          msg_prefix, fname, sb_fd.st_rdev, sb_fn.st_rdev);
        else
            mt_log_printf("%s %s\nfile inode number changed (old %d, new %d)",
                          msg_prefix, fname, sb_fd.st_ino, sb_fn.st_ino);
#endif /* TESTMODE */
        rc = true;
    }
    return rc;
}

int ifx_fd_reopen_if_file_changed(int fd, const char *fname, ifx_fd_FileOpen opener)
{
    if (file_has_changed(fd, fname))
    {
        /* File has been deleted or moved since fd was opened */
        ifx_fd_close(fd);
        fd = opener(fname);
    }
    return(fd);
}

FILE *ifx_fp_reopen_if_file_changed(FILE *fp, const char *fname, ifx_fp_FileOpen opener)
{
    if (file_has_changed(fileno(fp), fname))
    {
        /* File has been deleted or moved since fp was opened */
        ifx_fp_close(fp);
        fp = opener(fname);
    }
    return(fp);
}
