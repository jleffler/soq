#include "stderr.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static void check_link(const char *tag, const char *name);

int main(int argc, char **argv)
{
    int rc;
    err_setarg0(argv[0]);
    if (argc != 3)
        err_usage("oldname newname");
    check_link("B1", argv[1]);
    check_link("B2", argv[2]);
    if ((rc = rename(argv[1], argv[2])) != 0)
        err_sysrem("rename(\"%s\", \"%s\") failed: ", argv[1], argv[2]);
    check_link("A1", argv[1]);
    check_link("A2", argv[2]);
    return rc;
}

static void check_link(const char *tag, const char *name)
{
    struct stat sb;
    if (lstat(name, &sb) != 0)
        err_sysrem("lstat(\"%s\") failed: ", name);
    else
    {
        printf("%s: device %llu, inode %llu, mode %#o - %s", tag,
               (unsigned long long)sb.st_dev, (unsigned long long)sb.st_ino,
               sb.st_mode, name);
        if (S_ISLNK(sb.st_mode))
        {
            char link_data[1024];
            int link_len = readlink(name, link_data, sizeof(link_data));
            if (link_len < 0)
                err_sysrem("\nreadlink(\"%s\") failed: ", name);
            else
                printf(" --> %.*s", link_len, link_data);
        }
        putchar('\n');
    }
}
