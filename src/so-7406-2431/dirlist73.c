/* SO 7406-2431 */
#include <dirent.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wchar.h>

#ifdef UNIX
#define DIRSEP_STR  "/"
#define DIRSEP_CHR  '/'
#else
#define DIRSEP_STR  "\\"
#define DIRSEP_CHR  '\\'
#endif

#define PATH_LEN    99999

extern void listDir(DIR *dp, const char *directoryname);
extern int isDir(const char *name);

int main(void)
{
    setlocale(LC_ALL, "Turkish");
    char test[9999];
    getcwd(test, 9999);
    printf("FOLDERMAIN:%s\n", test);
    const char *dirname = ".";
    DIR *dp = opendir(dirname);
    if (dp == NULL)
    {
        perror(dirname);
        exit(1);
    }
    listDir(dp, test);
    return 0;
}

int isDir(const char *name)
{
    struct stat fileStat;
    return !stat(name, &fileStat) && S_ISDIR(fileStat.st_mode);
}

void listDir(DIR *dp, const char *directoryname)
{
    struct dirent *file;
    char temppath[PATH_LEN];
    char dirhold[100];
    static int check = 0;

    while ((file = readdir(dp)) != NULL)
    {
        // printf("%s\n",file->d_name);
        if (strcmp(file->d_name, "..") == 0 || (strcmp(file->d_name, ".") == 0))
            continue;
        if (isDir(file->d_name))
        {
            check++;
            printf("CHECK: %d\n", check);
            strcpy(temppath, directoryname);
            printf("temp:%s\n", directoryname);
            strcat(temppath, DIRSEP_STR);
            strcat(temppath, file->d_name);
            char *dot = strrchr(temppath, DIRSEP_CHR);
            strcpy(dirhold, dot);
            printf("DIR: %s\n", dirhold);
            printf("%s FOLDER\n", temppath);
            DIR *dp2 = opendir(temppath);
            if (chdir(temppath) != 0)
            {
                perror("chdir 1");
                exit(1);
            }
            if (dp2 == NULL)
            {
                perror(temppath);
                exit(1);
            }
            //strcat(temppath, dirhold);
            listDir(dp2, temppath);
            if (chdir(directoryname) != 0)
            {
                perror("chdir 2");
                exit(1);
            }
        }
        else
        {
            printf("FILE: %s%s%s\n", directoryname, DIRSEP_STR, file->d_name);
        }
    }
}
