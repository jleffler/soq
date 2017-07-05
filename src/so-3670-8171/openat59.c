/* SO 3670-8171 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    const char *dir_name = "test.dir";
    const char *fil_name = "file.name";
    if (argc > 1)
        dir_name = argv[1];

    struct stat sb;
    if (stat(dir_name, &sb) == 0)
        err_error("Directory %s exists - possibly as a file\n", dir_name);
    if (mkdir(dir_name, 0755) != 0)
        err_syserr("Failed to create directory '%s': ", dir_name);
    int fd_dir = open(dir_name, O_RDONLY);
    if (fd_dir < 0)
        err_syserr("Failed to open directory '%s' for reading: ", dir_name);
    if (rmdir(dir_name) != 0)
        err_syserr("Failed to remove directory '%s': ", dir_name);
    int fd_file = openat(fd_dir, fil_name, O_RDWR | O_CREAT, 0644);
    if (fd_file < 0)
        err_syserr("Failed to create file '%s' in removed directory '%s'\n",
                   fil_name, dir_name);
    /* Would it have been any different with O_SEARCH? Hard to tell on macOS Sierra! */
    close(fd_file);
    close(fd_dir);

    return 0;
}

