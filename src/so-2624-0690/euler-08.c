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

int main(void)
{
    int c;                  // Current character
    char buffer[N_DIGITS];
    size_t b_pos = 0;       // Position in buffer
    size_t c_count = 0;     // Digits since last 0
    size_t d_count = 0;     // Digits in total
    size_t max_end = 0;     // End position in input of maximum product
    uint64_t product = 1;   // Current product
    uint64_t max_prod = 0;  // Maximum product
    char mpdigits[N_DIGITS+1] = "";

    memset(buffer, 1, sizeof(buffer));
    for (size_t i = 0; i < sizeof(buffer); i++)
        assert(buffer[i] == 1);

    while ((c = getchar()) != EOF)
    {
        if (!isdigit(c))
            continue;

        printf("c = %c (d-count = %4zu, c-count = %4zu, b_pos = %2zu, product = %13" PRIu64,
               c, d_count, c_count, b_pos, product);
        if (max_prod > 0)
        {
            assert(max_end >= N_DIGITS);
            printf(", max = %13" PRIu64 ", bgn = %4zu, end = %4zu",
                   max_prod, max_end - N_DIGITS + 1, max_end);
        }
        printf(")\n");

        d_count++;
        c_count++;
        int digit = c - '0';
        if (digit == 0)
        {
            b_pos = 0;
            buffer[b_pos] = 1;
            product = 1;
            c_count = 0;
        }
        else
        {
            if (c_count >= N_DIGITS)
            {
                if (product > max_prod)
                {
                    max_prod = product;
                    max_end = d_count;
                    for (int i = 0; i < N_DIGITS; i++)
                        mpdigits[i] = buffer[(i + b_pos) % N_DIGITS] + '0';
                    mpdigits[N_DIGITS] = '\0';
                }
                assert(buffer[b_pos] != 0);
                if (product % buffer[b_pos] != 0)
                {
                    printf("assert about to fire: product = %" PRIu64 ", b_pos = %zu, "
                           "buffer[b_pos] = %u, remainder = %" PRIu64 " (digits: ",
                           product, b_pos, buffer[b_pos], product % buffer[b_pos]);
                    for (int i = 0; i < N_DIGITS; i++)
                        printf("%c", buffer[(i + b_pos) % N_DIGITS] + '0');
                    printf(")\n");
                }
                assert(product % buffer[b_pos] == 0);
                product /= buffer[b_pos];
            }
            product *= digit;
            buffer[b_pos++] = digit;
            if (b_pos >= N_DIGITS)
                b_pos = 0;
        }

    }

    if (max_prod > 0)
        printf("Max product is %" PRIu64 " starting at %zu up to %zu (digits: %s)\n",
               max_prod, max_end - N_DIGITS + 1, max_end, mpdigits);
    else
        printf("Did not find a sequence of %d non-zero digits\n", N_DIGITS);

    return 0;
}
