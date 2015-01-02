/* SO 5125919 */
#define _XOPEN_SOURCE 700
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s directory [...]\n", argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; i++)
    {
        DIR *dp;
        struct dirent *dirp;
        struct stat sb;
        int dfd = open(argv[i], O_RDONLY);
        if (dfd == -1)
        {
            fprintf(stderr, "Failed to open directory %s for reading (%d: %s)\n",
                    argv[i], errno, strerror(errno));
            continue;
        }
        if (fstat(dfd, &sb) != 0 || !S_ISDIR(sb.st_mode))
        {
            errno = ENOTDIR;
            fprintf(stderr, "%s: %d %s\n", argv[i], errno, strerror(errno));
            continue;
        }

        if ((dp = opendir(argv[i]))==NULL)
        {
            perror("can't open dir");
            continue;
        }
        printf("%-20s %s\n", "Directory:", argv[i]);

        while ((dirp = readdir(dp)) != NULL)
        {
            if (fstatat(dfd, dirp->d_name, &sb, 0) == -1) {
                fprintf(stderr, "fstatat(\"%s\") failed (%d: %s)\n",
                        dirp->d_name, errno, strerror(errno));
                continue;
            }   
            printf("%-20s %s\n", "File name:", dirp->d_name);
        }
        closedir(dp);
        close(dfd);
    }
    return 0;
}
