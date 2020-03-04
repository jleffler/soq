/* SO 0512-5919 */
#define _XOPEN_SOURCE 700   /* POSIX 2008 plus ... */
#include <dirent.h>
#include <errno.h>
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
        const char *name = argv[i];

        DIR *dp = opendir(name);
        if (dp == NULL)
        {
            fprintf(stderr, "failed to open directory %s (%d: %s)\n",
                    name, errno, strerror(errno));
            return -1;
        }

        int dfd = dirfd(dp);    /* Very, very unlikely to fail */

        printf("%-20s %s\n", "Directory:", name);

        struct dirent *dirp;
        while ((dirp = readdir(dp)) != NULL)
        {
            struct stat sb;
            if (fstatat(dfd, dirp->d_name, &sb, 0) == -1) {
                fprintf(stderr, "fstatat(\"%s/%s\") failed (%d: %s)\n",
                        name, dirp->d_name, errno, strerror(errno));
            }
            else
                printf("%-20s %s/%s\n", "File name:", name, dirp->d_name);
        }

        closedir(dp);
    }
    return 0;
}
