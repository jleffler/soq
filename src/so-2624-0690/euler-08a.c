/* SO 26240690 - Euler Project 8 (Largest product in a series) */
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

enum { N_DIGITS = 13 };

static void print_digits(const char buffer[N_DIGITS], size_t f_pos, size_t n_digits)
{
    for (size_t i = 0; i < n_digits; i++)
    {
        size_t j = (f_pos + i) % N_DIGITS;
        printf("%d", buffer[j]);
    }
}

int main(void)
{
    int c;
    char buffer[N_DIGITS];
    size_t f_pos = 0;       // Position in buffer
    size_t n_digits = 0;    // Number of digits
    size_t d_count = 0;     // Digits in total
    uint64_t product = 1;   // Current product

    /*
    size_t max_end = 0;
    size_t max_len = 0;
    uint64_t max_prod = 0;  // Maximum product
    */

    /*
    memset(buffer, 1, sizeof(buffer));
    for (size_t i = 0; i < sizeof(buffer); i++)
        assert(buffer[i] == 1);
    */

    while ((c = getchar()) != EOF)
    {
        if (!isdigit(c))
            continue;

        /*
        printf("c = %c (d-count = %4zu, c-count = %4zu, f_pos = %2zu, old.product = %13" PRIu64,
               c, d_count, n_digits, f_pos, product);
        if (max_prod > 0)
        {
            printf(", max (product = %13" PRIu64 ", bgn = %4zu, end = %4zu)",
                   max_prod, max_end - max_len, max_end);
        }
        printf(")\n");
        */

        d_count++;
        int digit = c - '0';
        assert(digit >= 0 && digit <= 9);
        if (digit == 0)
        {
            printf("Zeroed!\n");
            f_pos = 0;
            product = 1;
            n_digits = 0;
        }
        else
        {
            /*
            if (n_digits >= N_DIGITS)
            {
                assert(n_digits == N_DIGITS);
                printf("max-len: bp = %2zu; B[bp] = %d; product = %13" PRIu64 "; remainder = %13" PRIu64 "\n",
                       f_pos, buffer[f_pos], product, product % buffer[f_pos]);
                assert(f_pos < N_DIGITS);
                assert(buffer[f_pos] != 0);
                if (product % buffer[f_pos] != 0)
                {
                    printf("Numbers: ");
                    print_digits(buffer, f_pos, n_digits);
                    putchar('\n');
                }
                assert(product % buffer[f_pos] == 0);
                product /= buffer[f_pos];
                n_digits--;
            }
            */
            //product *= digit;
            size_t w_pos = (f_pos + n_digits) % N_DIGITS;

            int o_val = buffer[w_pos];
            buffer[w_pos] = digit;
            if (n_digits < N_DIGITS)
            {
                o_val = 0;
                n_digits++;
            }
            else
            {
                assert(o_val > 0 && o_val <= 9);
                assert(product % o_val == 0);
                product /= o_val;
                f_pos = (f_pos + 1) % N_DIGITS;
            }

            product *= digit;

            printf("Digit: %d - d_count = %4zu; n_digits = %2zu; f_pos = %2zu;"
                   " o_val = %d; product = %13" PRIu64 "; digits = ",
                   digit, d_count, n_digits, f_pos, o_val, product);
            print_digits(buffer, f_pos, n_digits);
            putchar('\n');

            /*
            if (product > max_prod)
            {
                max_prod = product;
                max_end = d_count;
                max_len = n_digits;
            }
            */

        }
    }

    /*
    printf("Max product is %" PRIu64 " starting at %zu up to %zu\n",
           max_prod, max_end - max_len, max_end);
    */
    return 0;
}
