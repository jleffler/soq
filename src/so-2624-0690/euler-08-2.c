/* SO 2624-0690 - Euler Project 8 (Largest product in a series) */
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/*
** Find the thirteen adjacent digits in the 1000-digit number that have
** the greatest product.
*/

enum { N_DIGITS = 13 };

static inline size_t min(size_t x, size_t y) { return (x < y) ? x : y; }

static inline void copy_buffer(char *output, const char *buffer, size_t b_pos, size_t num)
{
    for (size_t i = 0; i < num; i++)
        output[i] = buffer[(i + b_pos) % N_DIGITS];
    output[num] = '\0';
}

int main(void)
{
    int      c;                             // Current character
    char     buffer[N_DIGITS] = "";         // Circular buffer of digits
    size_t   b_pos = 0;                     // Position in buffer
    size_t   c_count = 0;                   // Digits since last 0
    size_t   d_count = 0;                   // Digits in total
    uint64_t product = 1;                   // Current product
    uint64_t max_prod = 0;                  // Maximum product
    size_t   max_epos = 0;                  // End position
    size_t   max_bpos = 0;                  // Begin position
    char     mpdigits[N_DIGITS + 1] = "";   // Digits for maximum product

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
            printf("Read: %c - N = %4zu\n", c, d_count);
        }
        else
        {
            char old = buffer[b_pos];
            buffer[b_pos] = c;
            product *= c - '0';
            if (c_count > N_DIGITS)
                product /= old - '0';
            printf("Read: %c - N = %4zu, C = %2zu, B = %2zu; P = %13" PRIu64 "; ", c, d_count, c_count, b_pos, product);
            char output[N_DIGITS + 1];
            if (c_count > N_DIGITS)
                copy_buffer(output, buffer, (b_pos + 1) % N_DIGITS, N_DIGITS);
            else
                copy_buffer(output, buffer, 0, c_count);
            printf("%s", output);
            if (c_count > N_DIGITS)
                printf("; D = %c", old);
            if (product > max_prod)
            {
                max_prod = product;
                max_epos = d_count;
                max_bpos = (max_epos > N_DIGITS) ? max_epos - N_DIGITS + 1 : 1;
                strcpy(mpdigits, output);
                printf("; NewMax = %13" PRIu64 " at [%zu:%zu] - %s",
                       max_prod, max_bpos, max_epos, mpdigits);
            }
            putchar('\n');
            if (++b_pos >= N_DIGITS)
                b_pos = 0;
        }
    }

    if (max_prod > 0)
        printf("Maximum product %" PRIu64 " at positions [%zu:%zu] - digits %s\n",
               max_prod, max_bpos, max_epos, mpdigits);
    else
        printf("No valid maximum product - not enough digits in input (%zu < %d)\n",
               d_count, N_DIGITS);

    return 0;
}
