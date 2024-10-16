/* SO 7438-4793 */
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#ifndef CMPLX
#define CMPLX(r, i)     ((double complex)((double)(r) + I * (double)(i)))
#endif

static size_t scan_multi_complex(const char *string, size_t nvalues,
                                 complex double *v, const char **eoc)
{
    size_t nread = 0;
    const char *buffer = string;
    while (nread < nvalues)
    {
        int offset = 0;
        char sign[2];
        double r, i;
        if (sscanf(buffer, "%lg%[-+]%lg*%*[iI]%n", &r, sign, &i, &offset) != 3 || offset == 0)
            break;
        if (sign[0] == '-')
            i = -i;
        v[nread++] = CMPLX(r, i);
        buffer += offset;
    }

    *eoc = buffer;
    return nread;
}

static void dump_complex(size_t nvalues, complex double values[nvalues])
{
    for (size_t i = 0; i < nvalues; i++)
        printf("%g%+g*I\n", creal(values[i]), cimag(values[i]));
}

enum { NUM_VALUES = 128 };

int main(void)
{
    double complex values[NUM_VALUES];
    size_t nvalues = 0;
    char *buffer = 0;
    size_t buflen = 0;
    int length;
    size_t lineno = 0;

    while ((length = getline(&buffer, &buflen, stdin)) > 0 && nvalues < NUM_VALUES)
    {
        const char *eoc;
        printf("Line: %zu [[%.*s]]\n", ++lineno, length - 1, buffer);
        size_t nread = scan_multi_complex(buffer, NUM_VALUES - nvalues, &values[nvalues], &eoc);
        if (*eoc != '\0' && *eoc != '\n')
            printf("EOC:  [[%s]]\n", eoc);
        if (nread == 0)
            break;
        dump_complex(nread, &values[nvalues]);
        nvalues += nread;
    }
    free(buffer);

    printf("All done:\n");
    dump_complex(nvalues, values);

    return 0;
}
