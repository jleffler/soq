/* SO 4361132 has related code, but answers a different question */
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FileNameArray
{
    char   **filenames;
    size_t   max_filenames;
    size_t   num_filenames;
    size_t   max_namelen;
} FileNameArray;

static void add_filename(FileNameArray *names, const char *name)
{
    assert(names->num_filenames <= names->max_filenames);
    if (names->num_filenames >= names->max_filenames)
    {
        size_t new_num = names->max_filenames * 2 + 2;
        void *space = realloc(names->filenames, new_num * sizeof(*names->filenames));
        if (space == 0)
        {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        names->filenames = space;
        names->max_filenames = new_num;
    }
    names->filenames[names->num_filenames] = strdup(name);
    size_t namelen = strlen(names->filenames[names->num_filenames]);
    if (namelen > names->max_namelen)
        names->max_namelen = namelen;
    names->num_filenames++;
}

static void free_filenames(FileNameArray *names)
{
    for (size_t i = 0; i < names->num_filenames; i++)
        free(names->filenames[i]);
    free(names->filenames);
    names->filenames = 0;
    names->max_filenames = 0;
    names->num_filenames = 0;
}

static int cmp_strings(const void *vp1, const void *vp2)
{
    const char *n1 = *(char **)vp1;
    const char *n2 = *(char **)vp2;
    return(strcmp(n1, n2));
}

static void sort_filenames(FileNameArray *names)
{
    qsort(names->filenames, names->num_filenames, sizeof(names->filenames[0]), cmp_strings);
}

static void rename_files(const char *dirname, const FileNameArray *names)
{
    size_t maxlen = strlen(dirname) + names->max_namelen + sizeof("/");
    char *source = malloc(maxlen);
    char *target = malloc(maxlen);
    if (source == 0 || target == 0)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    for (size_t i = 0; i < names->num_filenames; i++)
    {
        snprintf(source, maxlen, "%s/%s", dirname, names->filenames[i]);
        snprintf(target, maxlen, "%s/%zu.jpg", dirname, i+1);
        rename(source, target);
    }
}

static void process_directory(const char *dirname)
{
    DIR *dp = opendir(dirname);

    if (dp == 0)
        fprintf(stderr, "Failed to open directory %s\n", dirname);
    else
    {
        FileNameArray names = { 0, 0, 0, 0 };
        struct dirent *entry;
        while ((entry = readdir(dp)) != 0)
        {
            /* Ignore current and parent directory */
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;
            /* Ignore file names that do not end .jpg */
            const char *extn = strstr(entry->d_name, ".jpg");
            if (extn == 0)
                continue;
            if (extn == entry->d_name + strlen(entry->d_name) - (sizeof(".jpg") - 1))
                add_filename(&names, entry->d_name);
        }
        closedir(dp);
        sort_filenames(&names);
        rename_files(dirname, &names);
        free_filenames(&names);
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
        process_directory(".");
    else
    {
        for (int i = 1; i < argc; i++)
            process_directory(argv[i]);
    }
    return(0);
}

