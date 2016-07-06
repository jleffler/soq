/* SO 30294129 */
#include <stdio.h>
#include <string.h>

/*
** Testing re-entrant string-splitting functions:
**  - strtok_r() for the multiple separators case.
**  - strtok_f() for the single separators case.
*/

/* Function pointer for strtok_r, strtok_f */
typedef char *(*Splitter)(char *str, const char *delims, char **ptr);

/* strtok_f - fixed variation of strtok_single */
static char *strtok_f(char *str, char const *delims, char **ptr)
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
        *p  = '\0';
        *ptr = ++p;
    }
    else
        *ptr += strlen(*ptr);

    return ret;
}

/* Raw test of splitter functions */
static void parsePostData1(const char *s, const char *t, Splitter splitter)
{
    char tCpy[512];
    strcpy(tCpy, t);
    char *ptr;
    char *pch = splitter(tCpy, "=&", &ptr);
    while (pch != NULL)
    {
        printf("  [%s]\n", pch);
        if (strcmp(pch, s) == 0)
            printf("matches %s\n", s);
        pch = splitter(NULL, "=&", &ptr);
    }
}

/* Fixed version of parsePostData() from SO 30294129 */
static char *parsePostData2(const char *s, const char *t, Splitter splitter)
{
    char tCpy[512];
    strcpy(tCpy, t);
    char *ptr;
    char *pch = splitter(tCpy, "=&", &ptr);
    while (pch != NULL)
    {
        if (strcmp(pch, s) == 0)
        {
            pch = splitter(NULL, "&", &ptr);
            return pch;
        }
        else
        {
            pch = splitter(NULL, "=&", &ptr);
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

    printf("\nCompare variants on strtok()\n");
    {
        int i = NUM_TAGS - 1;
        printf("strtok_r():\n");
        parsePostData1(tags[i], data, strtok_r);
        printf("strtok_f():\n");
        parsePostData1(tags[i], data, strtok_f);
    }

    printf("\nCompare variants on strtok()\n");
    for (int i = 0; i < NUM_TAGS; i++)
    {
        char *value1 = parsePostData2(tags[i], data, strtok_r);
        printf("strtok_r: [%s] = [%s]\n", tags[i], value1);
        char *value3 = parsePostData2(tags[i], data, strtok_f);
        printf("strtok_f: [%s] = [%s]\n", tags[i], value3);
    }

    return 0;
}

