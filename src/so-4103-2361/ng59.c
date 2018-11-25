/* SO 4103-2621 */
/* Variant 1 - factored into functions */
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* UDN = Unique Digit Number (a base 10 number with no leading zeros and no repeated digit) */
extern bool generate_next_UDN(size_t buflen, char buffer[buflen]);
extern void set_next_UDN(int next);

enum { MAX_ITERATION = 10000000 };

static bool duplicate_digits_1(int value, size_t buflen, char buffer[buflen])
{
    snprintf(buffer, buflen, "%d", value);
    char digits[10] = { 0 };
    char *ptr = buffer;
    char c;
    while ((c = *ptr++) != '\0')
    {
        if (++digits[c - '0'] > 1)
            return true;
    }
    return false;
}

static int next_UDN = 0;

extern void set_next_UDN(int next)
{
    if (next >= 0 && next < MAX_ITERATION)
        next_UDN = next;
    assert(next_UDN >= 0 && next_UDN < MAX_ITERATION);
}

bool generate_next_UDN(size_t buflen, char buffer[buflen])
{
    if (next_UDN >= MAX_ITERATION)
        next_UDN = 0;
    while (duplicate_digits_1(next_UDN++, buflen, buffer))
    {
        if (next_UDN >= MAX_ITERATION)
        {
            next_UDN = 0;
            return false;
        }
    }
    return true;
}

int main(void)
{
    int count = 0;
    const char *pad = "";
    char buffer[12];
    set_next_UDN(0);
    while (generate_next_UDN(sizeof(buffer), buffer))
    {
        count += printf("%s%s", pad, buffer);
        pad = " ";
        if (count > 72)
        {
            putchar('\n');
            count = 0;
            pad = "";
        }
    }
    putchar('\n');
    return 0;
}
