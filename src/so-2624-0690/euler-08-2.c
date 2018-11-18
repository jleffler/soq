/*SO 26240690 - Euler Project 8 (Largest product in a series) */
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/*
** Find the thirteen adjacent digits in the 1000-digit number that have
** the greatest product.
*/

enum { N_DIGITS = 13 };

static inline void print_buffer(char *buffer, size_t b_pos, size_t num)
{
    for (size_t i = 0; i < num; i++)
        printf("%c", buffer[(i + b_pos) % N_DIGITS]);
}

int main(void)
{
    int c;                  // Current character
    char buffer[N_DIGITS] = "";
    size_t b_pos = 0;       // Position in buffer
    size_t c_count = 0;     // Digits since last 0
    size_t d_count = 0;     // Digits in total
    uint64_t product = 1;

    while ((c = getchar()) != EOF)
    {
        if (!isdigit(c))
            continue;
        d_count++;
        c_count++;
        if (c == '0')
        {
            memset(buffer, 0, sizeof(buffer));
            b_pos = 0;
            c_count = 0;
            product = 1;
            printf("Read: %c - N = %2zu\n", c, d_count);
        }
        else
        {
            char old = buffer[b_pos];
            buffer[b_pos] = c;
            product *= c - '0';
            if (c_count > N_DIGITS)
                product /= old - '0';
            printf("Read: %c - N = %2zu, C = %2zu, B = %2zu; P = %13" PRIu64 "; ", c, d_count, c_count, b_pos, product);
            if (c_count > N_DIGITS)
                printf("D = %c; ", old);
            if (c_count > N_DIGITS)
                print_buffer(buffer, (b_pos + 1) % N_DIGITS, N_DIGITS);
            else
                print_buffer(buffer, 0, c_count);
            putchar('\n');
            if (++b_pos >= N_DIGITS)
                b_pos = 0;
        }
    }

    return 0;
}
