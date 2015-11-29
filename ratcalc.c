/* Crude calculator (left-to-right evaluation only) for SO 33887484 */
#include "so.33887484.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "so.33887484.c"

//static inline char *skip_space(char *str) { while (isspace(*str)) str++; return str; }

int main(void)
{
    char line[4096];
    while (fgets(line, sizeof(line), stdin) != 0)
    {
        RationalInt lhs;
        RationalInt rhs;
        char *eon;
        char *str = line;

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
        }

        eon = skip_space(eon);
        char buffer[32];

        while (*eon != '\0')
        {
            printf("lhs = %s\n", ri_fmt(lhs, buffer, sizeof(buffer)));
            int op = *eon;
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
            }
            printf("rhs = %s\n", ri_fmt(rhs, buffer, sizeof(buffer)));

            RationalInt res;
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
                    goto next_line;;
            }
            printf("res = %s (op = '%c')\n\n", ri_fmt(res, buffer, sizeof(buffer)), op);
            lhs = res;
            eon = skip_space(eon + 1);
        }
next_line:
        putchar('\n');
    }
    return 0;
}
