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

extern void listDir(DIR *dp, char *directoryname);
extern int isDir(const char *name);

int main(void)
{
    setlocale(LC_ALL, "Turkish");
    char test[9999];
    getcwd(test, 9999);
    printf("FOLDERMAIN:%s\n", test);
    DIR *dp = opendir(".");
    listDir(dp, test);
    return 0;
}

int isDir(const char *name)
{
    struct stat fileStat;
    return !stat(name, &fileStat) && S_ISDIR(fileStat.st_mode);
}

void listDir(DIR *dp, char *directoryname)
{
    struct dirent *file;
    char buf[PATH_LEN];
    char *temppath;
    temppath = calloc(PATH_LEN, 1);
    char dirhold[100];
    char *dot;
    static int check = 0;

    if (dp == NULL)
    {
        printf("cant open");
    }

    while ((file = readdir(dp)) != NULL)
    {
        // printf("%s\n",file->d_name);
        if (strcmp(file->d_name, "..") == 0 || (strcmp(file->d_name, ".") == 0))
            continue;
        if (isDir(file->d_name))
        {
            check++;
            printf("\n CHECK: %d\n", check);
            strcpy(temppath, directoryname);
            printf("temp:%s\n", directoryname);
            strcat(directoryname, DIRSEP_STR);
            strcat(directoryname, file->d_name);
            dot = strrchr(directoryname, DIRSEP_CHR);
            strcpy(dirhold, dot);
            printf("DIR: %s\n", dirhold);
            printf("%s FOLDER\n", directoryname);
            chdir(directoryname);
            dp = opendir(directoryname);
            if (dp == NULL)
            {
                printf("2\n");
            }
            strcat(temppath, dirhold);
            listDir(dp, temppath);
        }
        else
        {
            snprintf(buf, PATH_LEN, "%s", directoryname);
            strcat(buf, DIRSEP_STR);
            strcat(buf, file->d_name);
            printf("%s FILE\n", buf);
        }
    }
}
