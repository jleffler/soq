/* SO 30294129 */
#include <stdio.h>
#include <string.h>

/* Function pointer for strtok, strtok_single, strtok_fixed */
typedef char *(*Splitter)(char *str, const char *delims);

/* strtok_single - as quoted in SO 30294129 (from SO 8705844) */
static char *strtok_single(char *str, char const *delims)
{
    static char  *src = NULL;
    char  *p,  *ret = 0;

    if (str != NULL)
        src = str;

    if (src == NULL)
        return NULL;

    if ((p = strpbrk(src, delims)) != NULL)
    {
        *p  = 0;
        ret = src;
        src = ++p;
    }

    return ret;
}

/* strtok_fixed - fixed variation of strtok_single */
static char *strtok_fixed(char *str, char const *delims)
{
    static char  *src = NULL;
    char  *p,  *ret = 0;

    if (str != NULL)
        src = str;

    if (src == NULL || *src == '\0')    // Fix 1
        return NULL;

    ret = src;                          // Fix 2
    if ((p = strpbrk(src, delims)) != NULL)
    {
        *p  = 0;
        //ret = src;                    // Unnecessary
        src = ++p;
    }
    else
        src += strlen(src);

    return ret;
}

/* Raw test of splitter functions */
static void parsePostData1(const char *s, const char *t, Splitter splitter)
{
    char tCpy[512];
    strcpy(tCpy, t);
    char *pch = splitter(tCpy, "=&");
    while (pch != NULL)
    {
        printf("  [%s]\n", pch);
        if (strcmp(pch, s) == 0)
            printf("matches %s\n", s);
        pch = splitter(NULL, "=&");
    }
}

/* Fixed version of parsePostData() from SO 30294129 */
static char *parsePostData2(const char *s, const char *t, Splitter splitter)
{
    char tCpy[512];
    strcpy(tCpy, t);
    char *pch = splitter(tCpy, "=&");
    while (pch != NULL)
    {
        if (strcmp(pch, s) == 0)
        {
            pch = splitter(NULL, "&");
            return pch;
        }
        else
        {
            pch = splitter(NULL, "=&");
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
        printf("strtok():\n");
        parsePostData1(tags[i], data, strtok);
        printf("strtok_single():\n");
        parsePostData1(tags[i], data, strtok_single);
        printf("strtok_fixed():\n");
        parsePostData1(tags[i], data, strtok_fixed);
    }

    printf("\nCompare variants on strtok()\n");
    for (int i = 0; i < NUM_TAGS; i++)
    {
        char *value1 = parsePostData2(tags[i], data, strtok);
        printf("strtok: [%s] = [%s]\n", tags[i], value1);
        char *value2 = parsePostData2(tags[i], data, strtok_single);
        printf("single: [%s] = [%s]\n", tags[i], value2);
        char *value3 = parsePostData2(tags[i], data, strtok_fixed);
        printf("fixed:  [%s] = [%s]\n", tags[i], value3);
    }

    return 0;
}

