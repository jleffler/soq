#include "stderr.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void process_directory(const char *dir)
{
    DIR *dp = opendir(dir);
    if (dp == 0)
    {
        err_sysrem("failed to open directory %s: ", dir);
        return;
    }
    /* dirfd(): POSIX 2008 - OK on BSD, macOS, Linux, AIX, HP-UX, Solaris */
    int fd = dirfd(dp);     /* Risk of failure is very, very small */
    struct dirent *file;
    while ((file = readdir(dp)) != 0)
    {
        struct stat sb;
        /* 0 argument could be AT_SYMLINK_NOFOLLOW */
        if (fstatat(fd, file->d_name, &sb, 0) == 0)
        {
            /* Some of the conversion specifiers may be incorrect for some systems */
            /* Inode number, size, time in particular */
            printf("%10llu  %5d  %5d  %7o  %3d  %9lld  %10ld  %10ld  %10ld  %s/%s\n",
                    sb.st_ino, sb.st_uid, sb.st_gid, sb.st_mode, sb.st_nlink, sb.st_size,
                    sb.st_mtime, sb.st_atime, sb.st_ctime, dir, file->d_name);
        }
        else
            err_sysrem("failed to stat() %s/%s: ", dir, file->d_name);
    }
    closedir(dp);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    for (int i = 1; i < argc; i++)
        process_directory(argv[i]);
    return 0;
}
