#include <string.h>

// str_replace(haystack, haystacksize, oldneedle, newneedle) --
//  Search haystack and replace occurences of oldneedle with newneedle.
//  Write no more than haystacksize characters (including '\0') into haystack.
//
// RETURN VALUES
// str_replace() returns haystack on success and NULL on failure. 
// Failure means there was not sufficient room for all requested replacements.
// Success is returned otherwise, even if no replacement is made.
char *str_replace(char *haystack, size_t haystacksize,
                    const char *needle, const char *newneedle);

// paste(dest, src): copy strlen(src) characters of src into dest
static inline void paste(char *dest, const char *src)
{
    while (*src) {
        *dest = *src;
        dest++, src++;
    }
}

// str_replace() implementation
char *str_replace(char *haystack, size_t haystacksize,
                    const char *oldneedle, const char *newneedle)
{   
    char *success = haystack;
    char *failure = NULL;
    size_t oldneedle_len = strlen(oldneedle);
    size_t newneedle_len = strlen(newneedle);

    // Case 0: oldneedle is empty
    if (oldneedle_len == 0) {
        if (strlen(haystack) == 0) {
            if (newneedle_len <= haystacksize - 1) {
                paste(haystack, newneedle);
                haystack[newneedle_len] = '\0';
                return success;
            }
            return failure; // no room for replacement
        }
        return success;
    }

    // Case 1: newneedle is not longer than oldneedle
    if (newneedle_len <= oldneedle_len) {
        const char *oldneedle_ptr;    // used to find an occurence of oldneedle
        const char *read_ptr;         // where to read in the haystack
        char *write_ptr;        // where to write in the haystack

        // Pass 1: Perform copy/replace using read_ptr and write_ptr
        for (oldneedle_ptr = oldneedle,
            read_ptr = haystack, write_ptr = haystack; 
            *read_ptr != '\0';
            read_ptr++, write_ptr++)
        {
            *write_ptr = *read_ptr;         
            if (*read_ptr == *oldneedle_ptr)
                oldneedle_ptr++;
            if (*oldneedle_ptr == '\0')  {  // then perform update
                oldneedle_ptr = oldneedle;
                write_ptr -= oldneedle_len;
                paste(write_ptr+1, newneedle);
                write_ptr += newneedle_len;
            }               
        } 
        *write_ptr = '\0';
        return success;
    }

    // Case 2: newneedle is longer than oldneedle
    else {
        const char *oldneedle_ptr;    // used to find an occurence of oldneedle
        const char *read_ptr;         // where to read in the haystack
        char *write_ptr;        // where to write in the haystack
        size_t diff_len =       // the amount of extra space needed 
            newneedle_len -     // to replace oldneedle with newneedle
            oldneedle_len;

        // Pass 1: Perform forward scan, updating write_ptr along the way
        for (oldneedle_ptr = oldneedle,
            read_ptr = haystack, write_ptr = haystack;
            *read_ptr != '\0';
            read_ptr++, write_ptr++)
        {
            if (*read_ptr == *oldneedle_ptr)
                oldneedle_ptr++;
            if (*oldneedle_ptr == '\0') {  // then advance write_ptr
                oldneedle_ptr = oldneedle;
                // For each occurence of oldneedle, diff_len additional
                // characters are needed in the expanded haystack
                write_ptr += diff_len;
            }
        }
        if (write_ptr >= haystack+haystacksize)
            return failure; // not enough room

        // Pass 2: Walk backwards through haystack, performing copy/replace
        const char *oldneedle_last =      // points to the last character 
            oldneedle +             // (excluding the '\0') in
            oldneedle_len - 1;      // oldneedle
        for (oldneedle_ptr = oldneedle_last;
            write_ptr >= haystack;
            write_ptr--, read_ptr--)
        {
            *write_ptr = *read_ptr;
            if (*read_ptr == *oldneedle_ptr)
                oldneedle_ptr--;            
            if (oldneedle_ptr < oldneedle) {  // perform replacement
                oldneedle_ptr = oldneedle_last;
                // For each occurence of oldneedle, write_ptr will
                // initially be located too far to the right by a
                // distance of diff_len. This corresponds to the
                // adjustment to write_ptr made in Pass 1.
                write_ptr -= diff_len;
                paste(write_ptr, newneedle);
            }   
        }
        return success;
    }
}

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
        puts("FAIL: str_replace() trampled out of bounds!");
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
    printf("%s\n", message);

    test_str_replace(reference, BUF, substitute, username_toolong, reference);
    test_str_replace(reference, BUF, substitute, username, "Your name is admin.");
    test_str_replace(reference, BUF, "", username, "adminYour name is $USERNAME.");
    test_str_replace(reference, BUF, "", username_toolong, reference);
    test_str_replace(repetition, 85, substitute, username_toolong,
        "If System Administrator is a user name, "
        "System Administrator may not be a group name");
    test_str_replace(repetition, 84, substitute, username_toolong,
        "If System Administrator is a user name, "
        "System Administrator may not be a group name");
    return 0;
}

