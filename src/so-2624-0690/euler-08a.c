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

static void copy_digits(char dst[N_DIGITS], const char src[N_DIGITS], size_t f_pos, size_t n_digits)
{
    for (size_t i = 0; i < n_digits; i++)
    {
        size_t j = (f_pos + i) % N_DIGITS;
        *dst++ = src[j];
    }
}

int main(void)
{
    int c;
    char buffer[N_DIGITS] = "";
    size_t f_pos = 0;       // Position in buffer
    size_t n_digits = 0;    // Number of digits
    size_t d_count = 0;     // Digits in total
    uint64_t product = 1;   // Current product

    char     max_buf[N_DIGITS] = "";
    size_t   max_len = 0;
    uint64_t max_prd = 0;
    size_t   max_bgn = 0;

    while ((c = getchar()) != EOF)
    {
        if (!isdigit(c))
            continue;

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

            if (product > max_prd)
            {
                max_prd = product;
                max_len = n_digits;
                copy_digits(max_buf, buffer, f_pos, n_digits);
                max_bgn = d_count - max_len + 1;
                printf("New maximum: product = %13" PRIu64 "; start = %4zu; len = %2zu; digits = ",
                       max_prd, max_bgn, max_len);
                print_digits(max_buf, 0, max_len);
                putchar('\n');
            }
        }
    }

    printf("Maximum product = %13" PRIu64 "; start = %4zu; len = %2zu; digits = ",
           max_prd, max_bgn, max_len);
    print_digits(max_buf, 0, max_len);
    putchar('\n');

    return 0;
}
