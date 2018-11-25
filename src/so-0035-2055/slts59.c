/* SO 0035-2055 */
/*
** Delving back into the dim distant reaches of antiquity!
** -- Function stripLeadingAndTrailingSpaces() is the accepted answer.
**    It has memory abuse problems and doesn't do the specified job.
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
** The Linux code referenced is the function strstrip(); see slts61.c
** for test code using that.
*/
#include "posixver.h"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static void stripLeadingAndTrailingSpaces(char* string){

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

}

static void str_strip(char *string)
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
}

static void chk_stripper(const char *str)
{
    char *copy1 = strdup(str);
    printf("V1 Before: [%s]\n", copy1);
    stripLeadingAndTrailingSpaces(copy1);
    printf("V1 After:  [%s]\n", copy1);
    free(copy1);
    fflush(stdout);

    char *copy2 = strdup(str);
    printf("V2 Before: [%s]\n", copy2);
    str_strip(copy2);
    printf("V2 After:  [%s]\n", copy2);
    free(copy2);
    fflush(stdout);
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
