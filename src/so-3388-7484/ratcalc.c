/* Crude calculator (left-to-right evaluation only) for SO 33887484 */
#include "so.33887484.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* Include the library function code - laziness! */
#include "so.33887484.c"

int main(void)
{
    char line[4096];
    printf("Fraction calculator: enter calculations such as:\n"
           "[13/4] + [19/7] * [29/13] / [14/23]\n"
           "which should yield the result [+111389/5096]\n");
    while (fgets(line, sizeof(line), stdin) != 0)
    {
        line[strcspn(line, "\n")] = '\0';
        Fraction lhs;
        Fraction rhs;
        const char *eon;
        const char *str = line;

        if (ri_scn(str, &eon, &lhs) != 0)
        {
            if (eon == str)
                printf("Unrecognizable number: %s", str);
            else
            {
                int len = (int)(eon - str);
                int errnum = errno;
                printf("%*.*s invalid (%d: %s)\n",
                        len, len, str, errnum, strerror(errnum));
            }
            continue;
        }

        eon = skip_space(eon);

        while (*eon != '\0')
        {
            char buffer[32];
            printf("lhs = %s\n", ri_fmt(lhs, buffer, sizeof(buffer)));
            int op = *eon;
            printf("op  = '%c'\n", op);
            eon = skip_space(eon + 1);

            str = eon;
            if (ri_scn(str, &eon, &rhs) != 0)
            {
                if (eon == str)
                    printf("Unrecognizable number: %s", str);
                else
                {
                    int len = (int)(eon - str);
                    int errnum = errno;
                    printf("%*.*s invalid (%d: %s)\n",
                            len, len, str, errnum, strerror(errnum));
                }
                continue;
            }
            printf("rhs = %s\n", ri_fmt(rhs, buffer, sizeof(buffer)));

            Fraction res;
            switch (op)
            {
                case '+':
                    ri_add(&lhs, &rhs, &res);
                    break;
                case '-':
                    ri_sub(&lhs, &rhs, &res);
                    break;
                case '*':
                    ri_mul(&lhs, &rhs, &res);
                    break;
                case '/':
                    ri_div(&lhs, &rhs, &res);
                    break;
                case '%':
                    ri_mod(&lhs, &rhs, &res);
                    break;
                default:
                    printf("Invalid operation %c - try again\n", op);
                    goto next_line;
            }
            printf("res = %s (op = '%c')\n\n", ri_fmt(res, buffer, sizeof(buffer)), op);
            lhs = res;
            eon = skip_space(eon);
        }
next_line:
        putchar('\n');
    }
    return 0;
}
