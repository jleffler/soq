### Stack Overflow Question 7438-4793

[SO 7438-4793](https://stackoverflow.com/q/74384793) &mdash;
How to read imaginary data from text file, with C

### Answer

Here's a simple solution using `scanf()` and the format shown in the
examples.  It writes the values in the same format that it reads them;
the output can be scanned by the program as input.

```c
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
```

Sample input:

```none
0.2e-3+0.3*I   0.1+0.1*I
0.3+0.1*I      0.1+0.4*I
-1.2-3.6*I     -6.02214076e23-6.62607015E-34*I
```

Output from sample input:

```none
0.0002+0.3*I
0.1+0.1*I
0.3+0.1*I
0.1+0.4*I
-1.2-3.6*I
-6.02214e+23-6.62607e-34*I
```

The numbers at the end with large exponents are Avogadro's Number and
the Planck Constant.

The format is about as stringent are you can make it with `scanf()`,
but, although it requires a sign (`+` or `-`) between the real and
imaginary parts and requires the `*` and `I` to be immediately after the
imaginary part (and the conversion will fail if the `*I` is missing),
and accepts either `i` or `I` to indicate the imaginary value:

* It doesn't stop the imaginary number having a second sign (so it will
  read a value such as "`-6+-4*I`").
* It doesn't stop there being white space after the mandatory sign (so
  it will read a value such as "`-6+ 24*I`".
* It doesn't stop the real part being on one line and the imaginary part
  on the next line.
* It won't handle either a pure-real number or a pure-imaginary number
  properly.

The `scanf()` functions are very flexible about white space, and it is
very hard to prevent them from accepting white space.  It would require
a custom parser to prevent unwanted spaces.  You could do that by
reading the numbers and the markers separately, as strings, and then
verifying that there's no space and so on.  That might be the best way
to handle it.  You'd use `sscanf()` to convert the string read after
ensuring there's no embedded white space yet the format is correct.

<hr>

> I do not know which IDE you are using for C, so I do not understand
> this `./testprog <test.data`.

I have yet to find an IDE that does not drive me bonkers.  I use a Unix
shell running in a terminal window.  Assuming that your program name is
`testprog` and the data file is `test.data`, typing `./testprog <
test.data` runs the program and feeds the contents of `test.data` as its
standard input.  On Windows, this would be a command window (and I think
PowerShell would work much the same way).


> I used `fgets` to read each line of the text file.  Though I know the
> functionality of `sscanf`, I do not know how to parse an entire line,
> which has about 23 elements per line.  If the number of elements in a
> line are few, I know how to parse it.  Could you help me about it?

As I noted in a comment, the SO Q&A [How to use `sscanf()` in
loops?](https://stackoverflow.com/questions/3975236/how-to-use-sscanf-in-loops)
explains how to use `sscanf()` to read multiple entries from a line.  In
this case, you will need to read multiple complex numbers from a single
line.  Here is some code that shows it at work.  It uses the POSIX
[`getline()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html)
function to read arbitrarily long lines.  If it isn't available to you,
you can use `fgets()` instead, but you'll need to preallocate a big
enough line buffer.

```
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
```

Here is a data file with 8 lines with 10 complex numbers per line):

```none
-1.95+11.00*I +21.72+64.12*I -95.16-1.81*I +64.23+64.55*I +28.42-29.29*I -49.25+7.87*I +44.98+79.62*I +69.80-1.24*I +61.99+37.01*I +72.43+56.88*I
-9.15+31.41*I +63.84-15.82*I -0.77-76.80*I -85.59+74.86*I +93.00-35.10*I -93.82+52.80*I +85.45+82.42*I +0.67-55.77*I -58.32+72.63*I -27.66-81.15*I
+87.97+9.03*I +7.05-74.91*I +27.60+65.89*I +49.81+25.08*I +44.33+77.00*I +93.27-7.74*I +61.62-5.01*I +99.33-82.80*I +8.83+62.96*I +7.45+73.70*I
+40.99-12.44*I +53.34+21.74*I +75.77-62.56*I +54.16-26.97*I -37.02-31.93*I +78.20-20.91*I +79.64+74.71*I +67.95-40.73*I +58.19+61.25*I +62.29-22.43*I
+47.36-16.19*I +68.48-15.00*I +6.85+61.50*I -6.62+55.18*I +34.95-69.81*I -88.62-81.15*I +75.92-74.65*I +85.17-3.84*I -37.20-96.98*I +74.97+78.88*I
+56.80+63.63*I +92.83-16.18*I -11.47+8.81*I +90.74+42.86*I +19.11-56.70*I -77.93-70.47*I +6.73+86.12*I +2.70-57.93*I +57.87+29.44*I +6.65-63.09*I
-35.35-70.67*I +8.08-21.82*I +86.72-93.82*I -28.96-24.69*I +68.73-15.36*I +52.85+94.65*I +85.07-84.04*I +9.98+29.56*I -78.01-81.23*I -10.67+13.68*I
+83.10-33.86*I +56.87+30.23*I -78.56+3.73*I +31.41+10.30*I +91.98+29.04*I -9.20+24.59*I +70.82-19.41*I +29.21+84.74*I +56.62+92.29*I +70.66-48.35*I
```

The output of the program is:

```none
Line: 1 [[-1.95+11.00*I +21.72+64.12*I -95.16-1.81*I +64.23+64.55*I +28.42-29.29*I -49.25+7.87*I +44.98+79.62*I +69.80-1.24*I +61.99+37.01*I +72.43+56.88*I]]
-1.95+11*I
21.72+64.12*I
-95.16-1.81*I
64.23+64.55*I
28.42-29.29*I
-49.25+7.87*I
44.98+79.62*I
69.8-1.24*I
61.99+37.01*I
72.43+56.88*I
Line: 2 [[-9.15+31.41*I +63.84-15.82*I -0.77-76.80*I -85.59+74.86*I +93.00-35.10*I -93.82+52.80*I +85.45+82.42*I +0.67-55.77*I -58.32+72.63*I -27.66-81.15*I]]
-9.15+31.41*I
63.84-15.82*I
-0.77-76.8*I
-85.59+74.86*I
93-35.1*I
-93.82+52.8*I
85.45+82.42*I
0.67-55.77*I
-58.32+72.63*I
-27.66-81.15*I
Line: 3 [[+87.97+9.03*I +7.05-74.91*I +27.60+65.89*I +49.81+25.08*I +44.33+77.00*I +93.27-7.74*I +61.62-5.01*I +99.33-82.80*I +8.83+62.96*I +7.45+73.70*I]]
87.97+9.03*I
7.05-74.91*I
27.6+65.89*I
49.81+25.08*I
44.33+77*I
93.27-7.74*I
61.62-5.01*I
99.33-82.8*I
8.83+62.96*I
7.45+73.7*I
Line: 4 [[+40.99-12.44*I +53.34+21.74*I +75.77-62.56*I +54.16-26.97*I -37.02-31.93*I +78.20-20.91*I +79.64+74.71*I +67.95-40.73*I +58.19+61.25*I +62.29-22.43*I]]
40.99-12.44*I
53.34+21.74*I
75.77-62.56*I
54.16-26.97*I
-37.02-31.93*I
78.2-20.91*I
79.64+74.71*I
67.95-40.73*I
58.19+61.25*I
62.29-22.43*I
Line: 5 [[+47.36-16.19*I +68.48-15.00*I +6.85+61.50*I -6.62+55.18*I +34.95-69.81*I -88.62-81.15*I +75.92-74.65*I +85.17-3.84*I -37.20-96.98*I +74.97+78.88*I]]
47.36-16.19*I
68.48-15*I
6.85+61.5*I
-6.62+55.18*I
34.95-69.81*I
-88.62-81.15*I
75.92-74.65*I
85.17-3.84*I
-37.2-96.98*I
74.97+78.88*I
Line: 6 [[+56.80+63.63*I +92.83-16.18*I -11.47+8.81*I +90.74+42.86*I +19.11-56.70*I -77.93-70.47*I +6.73+86.12*I +2.70-57.93*I +57.87+29.44*I +6.65-63.09*I]]
56.8+63.63*I
92.83-16.18*I
-11.47+8.81*I
90.74+42.86*I
19.11-56.7*I
-77.93-70.47*I
6.73+86.12*I
2.7-57.93*I
57.87+29.44*I
6.65-63.09*I
Line: 7 [[-35.35-70.67*I +8.08-21.82*I +86.72-93.82*I -28.96-24.69*I +68.73-15.36*I +52.85+94.65*I +85.07-84.04*I +9.98+29.56*I -78.01-81.23*I -10.67+13.68*I]]
-35.35-70.67*I
8.08-21.82*I
86.72-93.82*I
-28.96-24.69*I
68.73-15.36*I
52.85+94.65*I
85.07-84.04*I
9.98+29.56*I
-78.01-81.23*I
-10.67+13.68*I
Line: 8 [[+83.10-33.86*I +56.87+30.23*I -78.56+3.73*I +31.41+10.30*I +91.98+29.04*I -9.20+24.59*I +70.82-19.41*I +29.21+84.74*I +56.62+92.29*I +70.66-48.35*I]]
83.1-33.86*I
56.87+30.23*I
-78.56+3.73*I
31.41+10.3*I
91.98+29.04*I
-9.2+24.59*I
70.82-19.41*I
29.21+84.74*I
56.62+92.29*I
70.66-48.35*I
All done:
-1.95+11*I
21.72+64.12*I
-95.16-1.81*I
64.23+64.55*I
28.42-29.29*I
-49.25+7.87*I
44.98+79.62*I
69.8-1.24*I
61.99+37.01*I
72.43+56.88*I
-9.15+31.41*I
63.84-15.82*I
-0.77-76.8*I
-85.59+74.86*I
93-35.1*I
-93.82+52.8*I
85.45+82.42*I
0.67-55.77*I
-58.32+72.63*I
-27.66-81.15*I
87.97+9.03*I
7.05-74.91*I
27.6+65.89*I
49.81+25.08*I
44.33+77*I
93.27-7.74*I
61.62-5.01*I
99.33-82.8*I
8.83+62.96*I
7.45+73.7*I
40.99-12.44*I
53.34+21.74*I
75.77-62.56*I
54.16-26.97*I
-37.02-31.93*I
78.2-20.91*I
79.64+74.71*I
67.95-40.73*I
58.19+61.25*I
62.29-22.43*I
47.36-16.19*I
68.48-15*I
6.85+61.5*I
-6.62+55.18*I
34.95-69.81*I
-88.62-81.15*I
75.92-74.65*I
85.17-3.84*I
-37.2-96.98*I
74.97+78.88*I
56.8+63.63*I
92.83-16.18*I
-11.47+8.81*I
90.74+42.86*I
19.11-56.7*I
-77.93-70.47*I
6.73+86.12*I
2.7-57.93*I
57.87+29.44*I
6.65-63.09*I
-35.35-70.67*I
8.08-21.82*I
86.72-93.82*I
-28.96-24.69*I
68.73-15.36*I
52.85+94.65*I
85.07-84.04*I
9.98+29.56*I
-78.01-81.23*I
-10.67+13.68*I
83.1-33.86*I
56.87+30.23*I
-78.56+3.73*I
31.41+10.3*I
91.98+29.04*I
-9.2+24.59*I
70.82-19.41*I
29.21+84.74*I
56.62+92.29*I
70.66-48.35*I
```

The code would handle lines with any number of entries on a line (up to
128 in total because of the limit on the size of the array of complex
numbers — but that can be fixed too.
