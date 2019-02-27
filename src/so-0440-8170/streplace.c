/* SO 4408170 */
/* Code by https://stackoverflow.com/users/1691280/brandin */

#include <stdio.h>      /* XXX: temporary while debugging */
#include <stdbool.h>
#include <string.h>

// str_replace(haystack, haystacksize, oldneedle, newneedle) --
//  Search haystack and replace all occurrences of oldneedle with newneedle.
//  Resulting haystack contains no more than haystacksize characters (including the '\0').
//  If haystacksize is too small to make the replacements, do not modify haystack at all.
//  If the oldneedle is empty, no substitutions are performed (successfully).
//
// RETURN VALUES
// str_replace() returns haystack on success and NULL on failure.
// Failure means there was not enough room to replace all occurrences of oldneedle.
// Success is returned otherwise, even if no replacement is made.
char *str_replace(char *haystack, size_t haystacksize,
                  const char *oldneedle, const char *newneedle);

// ------------------------------------------------------------------
// Implementation of function
// ------------------------------------------------------------------
#define SUCCESS haystack
#define FAILURE NULL

static bool
locate_forward(char **needle_ptr, char *read_ptr,
               const char *needle, const char *needle_last);
static bool
locate_backward(char **needle_ptr, char *read_ptr,
                const char *needle, const char *needle_last);

char *str_replace(char *haystack, size_t haystacksize,
                    const char *oldneedle, const char *newneedle)
{
    size_t oldneedle_len = strlen(oldneedle);
    size_t newneedle_len = strlen(newneedle);
    char *oldneedle_ptr;    // locates occurrences of oldneedle
    char *read_ptr;         // where to read in the haystack
    char *write_ptr;        // where to write in the haystack
                            // the last character in oldneedle
    const char *oldneedle_last = oldneedle + oldneedle_len - 1;

    // Case 0: oldneedle is empty
    if (oldneedle_len == 0)
        return SUCCESS;     // nothing to do; define as success

    // Case 1: newneedle is not longer than oldneedle
    if (newneedle_len <= oldneedle_len) {
        // Pass 1: Perform copy/replace using read_ptr and write_ptr
        for (oldneedle_ptr = (char *)oldneedle,
            read_ptr = haystack, write_ptr = haystack;
            *read_ptr != '\0';
            read_ptr++, write_ptr++)
        {
            *write_ptr = *read_ptr;
            bool found = locate_forward(&oldneedle_ptr, read_ptr,
                        oldneedle, oldneedle_last);
            if (found)  {
                // then perform update
                write_ptr -= oldneedle_len;
                memcpy(write_ptr+1, newneedle, newneedle_len);
                write_ptr += newneedle_len;
            }
        }
        *write_ptr = '\0';
        return SUCCESS;
    }

    // Case 2: newneedle is longer than oldneedle
    else {
        size_t diff_len =       // the amount of extra space needed
            newneedle_len -     // to replace oldneedle with newneedle
            oldneedle_len;      // in the expanded haystack

        // Pass 1: Perform forward scan, updating write_ptr along the way
        /* JL: bug fix testing write_ptr too */
        for (oldneedle_ptr = (char *)oldneedle,
            read_ptr = haystack, write_ptr = haystack;
            *read_ptr != '\0' && write_ptr < haystack + haystacksize;
            read_ptr++, write_ptr++)
        {
            bool found = locate_forward(&oldneedle_ptr, read_ptr,
                        oldneedle, oldneedle_last);
            if (found) {
                // then advance write_ptr
                write_ptr += diff_len;
            }
        }
        /* JL: bug fix handling write_ptr */
        if (write_ptr >= haystack + haystacksize)
            return FAILURE; // no more room in haystack

        // Pass 2: Walk backwards through haystack, performing copy/replace
        for (oldneedle_ptr = (char *)oldneedle_last;
            write_ptr >= haystack;
            write_ptr--, read_ptr--)
        {
            *write_ptr = *read_ptr;
            bool found = locate_backward(&oldneedle_ptr, read_ptr,
                        oldneedle, oldneedle_last);
            if (found) {
                // then perform replacement
                write_ptr -= diff_len;
                memcpy(write_ptr, newneedle, newneedle_len);
            }
        }
        return SUCCESS;
    }
}

// locate_forward: compare needle_ptr and read_ptr to see if a match occurred
// needle_ptr is updated as appropriate for the next call
// return true if match occurred, false otherwise
static inline bool
locate_forward(char **needle_ptr, char *read_ptr,
        const char *needle, const char *needle_last)
{
    if (**needle_ptr == *read_ptr) {
        (*needle_ptr)++;
        if (*needle_ptr > needle_last) {
            *needle_ptr = (char *)needle;
            return true;
        }
    }
    else
        *needle_ptr = (char *)needle;
    return false;
}

// locate_backward: compare needle_ptr and read_ptr to see if a match occurred
// needle_ptr is updated as appropriate for the next call
// return true if match occurred, false otherwise
static inline bool
locate_backward(char **needle_ptr, char *read_ptr,
        const char *needle, const char *needle_last)
{
    if (**needle_ptr == *read_ptr) {
        (*needle_ptr)--;
        if (*needle_ptr < needle) {
            *needle_ptr = (char *)needle_last;
            return true;
        }
    }
    else
        *needle_ptr = (char *)needle_last;
    return false;
}

#ifdef TEST

#include <stdio.h>
#include <assert.h>

#define BUF 30
char message[BUF] = "Your name is $USERNAME.";
const char username[] = "admin";
const char username_toolong[] = "System Administrator";
const char reference[] = "Your name is $USERNAME.";
const char substitute[] = "$USERNAME";

const char repetition[] = "If $USERNAME is a user name, $USERNAME may not be a group name";

static void test_str_replace(const char *input, size_t buflen, const char *oldneedle,
                             const char *newneedle, const char *output)
{
    size_t inplen = strlen(input);
    assert(inplen < buflen);
    char buffer[buflen+4];
    memset(buffer, '\0', buflen+4);
    buffer[0] = '\0';
    buffer[1] = 'X';
    buffer[buflen+2] = 'X';
    buffer[buflen+3] = '\0';
    memmove(buffer+2, input, inplen);
    char *result = str_replace(buffer+2, buflen, oldneedle, newneedle);
    if (result == 0)
    {
        printf("Not enough room to replace <<%s>> with <<%s>> in <<%s>>\n", oldneedle, newneedle, input);
    }
    else if (buffer[0] != '\0' || buffer[1] != 'X' || buffer[buflen+2] != 'X' || buffer[buflen+3] != '\0')
    {
        puts("FAIL: str_replace() trampled out of bounds!");
        if (buffer[0] != '\0')
            printf("----  buffer[0] != '\\0' (%d found)\n", buffer[0]);
        if (buffer[1] != 'X')
            printf("----  buffer[1] != 'X' (%d found)\n", buffer[1]);
        if (buffer[buflen+2] != 'X')
            printf("----  buffer[%zu] != 'X' (%d found)\n", buflen+2, buffer[buflen+2]);
        if (buffer[buflen+3] != '\0')
            printf("----  buffer[%zu] != '\\0' (%d found)\n", buflen+3, buffer[buflen+3]);
    }
    else if (strcmp(buffer+2, output) != 0)
        printf("FAIL:\nWanted: <<%s>>\nActual: <<%s>>\n", output, buffer+2);
    else
        printf("PASS: replacing <<%s>> with <<%s>> in <<%s>> gave <<%s>>\n", oldneedle, newneedle, input, buffer+2);
}

int main(void)
{
    char *retval1 = str_replace(message, BUF, "$USERNAME", username_toolong);
    char *retval2 = str_replace(message, BUF, "$USERNAME", username);
    if (!retval1)
        printf("Not enough room to replace $USERNAME with `%s'\n", username_toolong);
    if (!retval2)
        printf("Not enough room to replace $USERNAME with `%s'\n", username);
    printf("%s\n\n", message);

    test_str_replace(reference, BUF, substitute, username_toolong, reference);
    test_str_replace(reference, BUF, substitute, username, "Your name is admin.");
    test_str_replace(reference, BUF, "", username, "Your name is $USERNAME.");
    test_str_replace(reference, BUF, "", username_toolong, reference);

    test_str_replace(repetition, 85, substitute, username_toolong,
        "If System Administrator is a user name, "
        "System Administrator may not be a group name");
    test_str_replace(repetition, 84, substitute, username_toolong,
        "If System Administrator is a user name, "
        "System Administrator may not be a group name");

    test_str_replace(repetition, 90, substitute, "($USERNAME, $USERNAME)",
        "If ($USERNAME, $USERNAME) is a user name, "
        "($USERNAME, $USERNAME) may not be a group name");

    return 0;
}

#endif /* TEST */
