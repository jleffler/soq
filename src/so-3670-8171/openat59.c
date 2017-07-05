/* SO 3670-8171 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "stderr.h"

#ifndef O_SEARCH
#define O_SEARCH 0
#endif
#ifndef O_DIRECTORY
#define O_DIRECTORY 0
#endif

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    const char *dir_name = "test.dir";
    const char *fil_name = "file.name";
    if (argc > 1)
        dir_name = argv[1];

    struct stat sb;
    if (stat(dir_name, &sb) == 0)
        err_error("File or directory '%s' exists\n", dir_name);
    if (mkdir(dir_name, 0755) != 0)
        err_syserr("Failed to create directory '%s': ", dir_name);
    printf("Created directory '%s' successfully\n", dir_name);
    printf("Testing %s O_SEARCH\n", (O_SEARCH != 0) ? "with" : "without");
    printf("Testing %s O_DIRECTORY\n", (O_DIRECTORY != 0) ? "with" : "without");
    int fd_dir = open(dir_name, O_RDONLY | O_SEARCH | O_DIRECTORY);
    if (fd_dir < 0)
        err_syserr("Failed to open directory '%s' for reading: ", dir_name);
    printf("Directory '%s' opened successfully\n", dir_name);
    if (rmdir(dir_name) != 0)
        err_syserr("Failed to remove directory '%s': ", dir_name);
    printf("Directory '%s' removed successfully\n", dir_name);
    int fd_file = openat(fd_dir, fil_name, O_RDWR | O_CREAT, 0644);
    if (fd_file < 0)
        err_syserr("Failed to create file '%s' in removed directory '%s'\n",
                   fil_name, dir_name);
    /* Probably never reached */
    printf("Created file '%s/%s' successfully\n", dir_name, fil_name);
    char buffer[strlen(dir_name) + strlen(fil_name) + sizeof("/")];
    sprintf(buffer, "%s/%s", dir_name, fil_name);
    if (stat(buffer, &sb) != 0)
        err_syserr("Unable to access file '%s' by name\n", buffer);
    close(fd_file);
    close(fd_dir);

    return 0;
}

