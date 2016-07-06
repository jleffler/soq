/* SO 35678399 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    char sign[80];
    struct timespec d = { .tv_sec = 0, .tv_nsec = 100000000 };

    printf("What should I say? ");

    /* Reserve enough space for " ... " */
    if (scanf("%74[^\n]", sign) == 1)
    {
        printf("Sign: [%s]\n\n", sign);
        strcat(sign, " ... ");

        int t_len = strlen(sign);
        for (int i = 0; i < 10; i++)
        {
            for (int l_len = 0; l_len < t_len; l_len++)
            {
                int r_len = t_len - l_len;
                /* Rotate to right */
                putchar('\r');
                printf("[%.*s%.*s]", l_len, sign + r_len, r_len, sign);
                printf("    ");
                /* Rotate to left */
                printf("[%.*s%.*s]", r_len, sign + l_len, l_len, sign);
                fflush(stdout);
                nanosleep(&d, 0);
            }
        }
        putchar('\n');
    }
    return 0;
}
