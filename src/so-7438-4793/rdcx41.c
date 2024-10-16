/* SO 7438-4793 */
#include <stdio.h>

static int read_complex(FILE *fp, double *r, double *i)
{
    int offset = 0;
    char sign[2];
    if (fscanf(fp, "%lg%[-+]%lg*%*[iI]%n", r, sign, i, &offset) != 3 || offset == 0)
        return EOF;
    if (sign[0] == '-')
        *i = -*i;
    return 0;
}

int main(void)
{
    double r;
    double i;

    while (read_complex(stdin, &r, &i) == 0)
        printf("%g%+g*I\n", r, i);

    return 0;
}
