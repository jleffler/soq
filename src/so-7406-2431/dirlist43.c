/* SO 7406-2431 */
#include <dirent.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef UNIX
#define DIRSEP_STR  "/"
#define DIRSEP_CHR  '/'
#else
#define DIRSEP_STR  "\\"
#define DIRSEP_CHR  '\\'
#endif

#define PATH_LEN    99999

extern void listDir(const char *directoryname);
extern int isDir(const char *name);

int main(void)
{
    setlocale(LC_ALL, "Turkish");
    char pwd[PATH_LEN];
    getcwd(pwd, sizeof(pwd));
    printf("FOLDERMAIN: %s\n", pwd);
    listDir(pwd);
    return 0;
}

int isDir(const char *name)
{
    struct stat fileStat;
    int rc = stat(name, &fileStat) == 0 && S_ISDIR(fileStat.st_mode);
#ifdef DEBUG
    printf("%s(): %d [%s]\n", __func__, rc, name);
#endif /* DEBUG */
    return rc;
}

#ifdef DEBUG
static void chk_pwd(const char *tag)
{
    char pwd[PATH_LEN];
    if (getcwd(pwd, sizeof(pwd)) == 0)
    {
        int errnum = errno;
        fprintf(stderr, "%s(): getcwd() failed: %d %s\n",
                __func__, errnum, strerror(errnum));
        exit(1);
    }
    printf("PWD: %s [%s]\n", tag, pwd);
}
#else
#define chk_pwd(tag)    ((void)0)
#endif /* DEBUG */

static void set_pwd(const char *directoryname)
{
#ifdef DEBUG
    printf("CHDIR 1: [%s]\n", directoryname);
#endif /* DEBUG */
    if (chdir(directoryname) != 0)
    {
        int errnum = errno;
        fprintf(stderr, "%s(): chdir(%s) failed: %d %s\n",
                __func__, directoryname, errnum, strerror(errnum));
        exit(1);
    }
    chk_pwd("CHDIR 1");
}

void listDir(const char *directoryname)
{
#ifdef DEBUG
    static int level = 0;
#endif /* DEBUG */
    static int check = 0;

#ifdef DEBUG
    printf("-->> %s() level %d (%s)\n", __func__, ++level, directoryname);
#endif /* DEBUG */

    DIR *dp = opendir(directoryname);
    if (dp == NULL)
    {
        perror(directoryname);
        return;
    }

    set_pwd(directoryname);

    struct dirent *file;
    while ((file = readdir(dp)) != NULL)
    {
        if (strcmp(file->d_name, "..") == 0 || (strcmp(file->d_name, ".") == 0))
            continue;
        if (isDir(file->d_name))
        {
            printf("CHECK: %d\n", ++check);
            char temppath[PATH_LEN];
            snprintf(temppath, sizeof(temppath), "%s%s%s",
                     directoryname, DIRSEP_STR, file->d_name);
            printf("FOLDER: %s\n", temppath);
            chk_pwd("Before recursion");
            listDir(temppath);
            set_pwd(directoryname);
            chk_pwd("After recursion");
        }
        else
        {
            printf("FILE: %s%s%s\n", directoryname, DIRSEP_STR, file->d_name);
        }
    }
    closedir(dp);

#ifdef DEBUG
    printf("<<-- %s() level %d (%s)\n", __func__, level--, directoryname);
#endif /* DEBUG */
}
