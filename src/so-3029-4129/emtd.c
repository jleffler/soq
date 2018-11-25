/* SO 3029-4129 */
#include <stdio.h>
#include <string.h>

/* Function pointer for strtok_ds, strtok_dm */
typedef char *(*Splitter)(char *str, const char *delims, char **ptr, char *sep);

/* strtok_ds - variation of strtok_r */
static char *strtok_ds(char *str, char const *delims, char **ptr, char *sep)
{
    char *p;
    char *ret = 0;

    if (str != NULL)
        *ptr = str;

    if (*ptr == NULL || **ptr == '\0')
        return NULL;

    ret = *ptr;
    if ((p = strpbrk(*ptr, delims)) != NULL)
    {
        if (sep != 0)
            *sep = *p;
        *p  = '\0';
        *ptr = ++p;
    }
    else
    {
        *ptr += strlen(*ptr);
        if (sep != 0)
            *sep = '\0';
    }

    return ret;
}

/* strtok_dm - variation of strtok_r */
static char *strtok_dm(char *str, char const *delims, char **ptr, char *sep)
{
    char *p;
    char *ret = 0;

    if (str != NULL)
        *ptr = str;

    if (*ptr == NULL || **ptr == '\0')
        return NULL;

    ret = *ptr;
    /* Skip leading delimiters */
    ret += strspn(*ptr, delims);
    if ((p = strpbrk(*ptr, delims)) != NULL)
    {
        if (sep != 0)
            *sep = *p;
        *p  = '\0';
        *ptr = ++p;
    }
    else
    {
        *ptr += strlen(*ptr);
        if (sep != 0)
            *sep = '\0';
    }

    return ret;
}

/* Raw test of splitter functions */
static void parsePostData1(const char *s, const char *t, Splitter splitter)
{
    char tCpy[512];
    strcpy(tCpy, t);
    printf("Source: [[%s]]\n", t);
    char *ptr;
    char  sep;
    char *pch = splitter(tCpy, "=&", &ptr, &sep);
    while (pch != NULL)
    {
        printf("  [%s] [0x%.2X = %c]\n", pch, sep, sep);
        if (strcmp(pch, s) == 0)
            printf("matches %s\n", s);
        pch = splitter(NULL, "=&", &ptr, &sep);
    }
}

/* Fixed version of parsePostData() from SO 3029-4129 */
static char *parsePostData2(const char *s, const char *t, Splitter splitter)
{
    char tCpy[512];
    strcpy(tCpy, t);
    printf("Source: [[%s]]\n", t);
    char *ptr;
    char  sep;
    char *pch = splitter(tCpy, "=&", &ptr, &sep);
    while (pch != NULL)
    {
        if (strcmp(pch, s) == 0)
        {
            pch = splitter(NULL, "&", &ptr, &sep);
            return pch;
        }
        else
        {
            pch = splitter(NULL, "=&", &ptr, &sep);
        }
    }
    return NULL;
}

/* Composite test program */
int main(void)
{
    char data[] = "to=myself@gmail.com&cc=youself@gmail.com&title=&content=how are you?&signature=best regards.";
    char *tags[] = { "to", "cc", "title", "content", "signature" };
    enum { NUM_TAGS = sizeof(tags) / sizeof(tags[0]) };

    printf("\nCompare variants on strtok() - 1\n");
    {
        int i = NUM_TAGS - 1;
        printf("strtok_ds():\n");
        parsePostData1(tags[i], data, strtok_ds);
        printf("strtok_dm():\n");
        parsePostData1(tags[i], data, strtok_dm);
    }

    printf("\nCompare variants on strtok() - 2\n");
    for (int i = 0; i < NUM_TAGS; i++)
    {
        char *value1 = parsePostData2(tags[i], data, strtok_ds);
        printf("strtok_ds: [%s] = [%s]\n", tags[i], value1);
        char *value3 = parsePostData2(tags[i], data, strtok_dm);
        printf("strtok_dm: [%s] = [%s]\n", tags[i], value3);
    }

    return 0;
}

