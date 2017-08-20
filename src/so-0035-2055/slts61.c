/* SO 0035-2055 */
/*
** Delving back into the dim distant reaches of antiquity!
** -- Function stripLeadingAndTrailingSpaces() is the accepted answer.
**    It has memory abuse problems and doesn't do the specified job.
**    The author is AlfaZulu.
** I have commented:
**    I have to down-vote this.  As my newly added answer shows, the
**    code on display here (as of 2017-08-09) neither strips the
**    trailing blanks nor properly respects the bounds of the array if
**    the input string is empty — consists of a single null byte '\0'.
**    The necessary changes are simple, but they are necessary.  The
**    Linux code in tuminoid's answer is OK, though the semantics are
**    different.
** -- https://stackoverflow.com/questions/352055/best/45620263#comment78200596_352119
**
** -- str_strip() is a correct implementation of the algorithm that
**    stripLeadingAndTrailingSpaces() attempts to implement.
** -- This code is a test harness that demonstrates the difference.
**
** -- strstrip() - This Linux code is from the kernel; see also
**    slts59.c for alternative code.  The functions here have a
**    different interface from the functions in the other file.
*/
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static
char *stripLeadingAndTrailingSpaces(char* string){

     assert(string);

     /* First remove leading spaces */

     const char* firstNonSpace = string;

     while(*firstNonSpace != '\0' && isspace(*firstNonSpace))
     {
          ++firstNonSpace;
     }

     size_t len = strlen(firstNonSpace)+1;

     memmove(string, firstNonSpace, len);

     /* Now remove trailing spaces */

     char* endOfString = string + len;

     while(string < endOfString  && isspace(*endOfString))
     {
          --endOfString ;
     }

     *endOfString = '\0';

    return string;
}

static char *str_strip(char *string)
{
    assert(string);
    //printf("-->> %s(): [%s]\n", __func__, string);

    /* First remove leading spaces */
    const char *firstNonSpace = string;

    while (isspace((unsigned char)*firstNonSpace))
        ++firstNonSpace;
    //printf("---- %s(): [%s]\n", __func__, firstNonSpace);

    size_t len = strlen(firstNonSpace) + 1;
    memmove(string, firstNonSpace, len);
    //printf("---- %s(): [%s]\n", __func__, string);

    /* Now remove trailing spaces */
    char *endOfString = string + len - 1;
    //printf("---- %s(): EOS [%s]\n", __func__, endOfString);

    while (string < endOfString && isspace((unsigned char)endOfString[-1]))
        --endOfString;
    *endOfString = '\0';
    //printf("<<-- %s(): [%s]\n", __func__, string);
    return string;
}

static 
char *strstrip(char *s)
{
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}

static void chk_one_stripper(const char *tag, const char *str, char *(*function)(char *))
{
    char *copy1 = strdup(str);
    printf("%s Before: [%s]\n", tag, copy1);
    char *data = function(copy1);
    printf("%s After:  [%s]\n", tag, data);
    free(copy1);
    fflush(stdout);
}

static void chk_stripper(const char *str)
{
    chk_one_stripper("AlfaZulu ", str, stripLeadingAndTrailingSpaces);
    chk_one_stripper("str_strip", str, str_strip);
    chk_one_stripper("strstrip ", str, strstrip);
}

int main(void)
{
    char *str[] =
    {
        "    \t    ABC   DEF    \t  ",
        "    \t                 \t  ",
        " ",
        "",
    };
    enum { NUM_STR = sizeof(str) / sizeof(str[0]) };
    for (int i = 0; i < NUM_STR; i++)
        chk_stripper(str[i]);
    return 0;
}
