/* SO 7183-1526 */
/* Test code for generating results */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stderr.h"

static int bin_char_to_number(const char *str)
{
    int result = 0;
    for (int i = 0; i < 4; i++)
    {
        if (str[i] == '1')
            result = (result << 1) | 1;
        else if (str[i] == '0')
            result = (result << 1) | 0;
        else
            err_error("Invalid data (not 0 or 1) in string '%.4s'\n", str);
    }
    return result;
}


static void print_hex(const char *str)
{
    if (strlen(str) % 4 != 0)
    {
        err_error("String length %zu is not a multiple of 4 ('%s')\n",
                  strlen(str), str);
    }

    printf("0x");
    for (int i = 0; str[i] != '\0'; i += 4)
    {
        int number = bin_char_to_number(&str[i]);
        printf("%X", number);
    }
}

static void rotate(char *dst, const char *src, size_t rot)
{
    assert(rot < 64);
    memmove(dst, &src[rot], 64 - rot);
    memmove(&dst[64 - rot], src, rot);
    dst[64] = '\0';
}

int main(void)
{
    char data[] =
    {
        /* 0x101010100505A0A0 */
        "00010000000100000001000000010000"
        "00000101000001011010000010100000"
    };
    assert(sizeof(data) == 65);

    printf("input: ");
    print_hex(data);
    printf(" %s\n", data);
    printf("%2s %2s  %-18s %s\n", "L", "R", "Hex", "Binary");
    for (size_t i = 0; i < 64; i++)
    {
        printf("%2zu %2zu: ", i, 64 - i);
        char info[65];
        rotate(info, data, i);
        print_hex(info);
        printf(" %s\n", info);
    }
    return 0;
}

