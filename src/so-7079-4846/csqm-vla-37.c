/* SO 7079-4846 */

/* Is a square matrix a set of concentric shells with values increasing towards the centre? */

#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filter.h"
#include "so-vla-args-version.h"
#include "stderr.h"

enum { MAT_SIZE = 100 };

static int quiet = 0;
static int aflag = 0;

static int err_shell(int r, int c, int a_val, int e_val)
{
    printf("Element M[%d][%d] = %d vs expected value %d\n", r, c, a_val, e_val);
    return 0;
}

static int check_shell(int shell, int n, int matrix[n][n])
{
    int lb = shell;
    int ub = n - shell - 1;
    int val = matrix[lb][lb];

    /* Check the horizontals */
    for (int c = lb; c <= ub; c++)
    {
        if (matrix[lb][c] != val)
            return err_shell(lb, c, matrix[lb][c], val);
        if (matrix[ub][c] != val)
            return err_shell(ub, c, matrix[ub][c], val);
    }

    /* Check the verticals */
    for (int r = lb; r <= ub; r++)
    {
        if (matrix[r][lb] != val)
            return err_shell(r, lb, matrix[r][lb], val);
        if (matrix[r][ub] != val)
            return err_shell(r, ub, matrix[r][ub], val);
    }

    return 1;
}

static int check_matrix(int n, int matrix[n][n])
{
    for (int i = 0; i <= n / 2; i++)
    {
        if (check_shell(i, n, matrix) == 0)
            return 0;
    }

    for (int i = 0; i < (n - 1) / 2; i++)
    {
        if (matrix[i][i] >= matrix[i+1][i+1])
        {
            printf("Shell %d has value %d but inner shell %d has value %d\n",
                   i, matrix[i][i], i+1, matrix[i+1][i+1]);
            return 0;
        }
    }
    return 1;
}

static int read_size(FILE *fp)
{
    int n;
    if (fscanf(fp, "%d", &n) != 1)
        err_error("failed to read an integer\n");
    if (n <= 0 || n > MAT_SIZE)
        err_error("matrix size %d is not in the range 1..%d\n", n, MAT_SIZE);
    return n;
}

static void read_matrix(FILE *fp, int n, int matrix[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1)
                err_error("failed to read M[%d][%d]\n", i, j);
        }
    }
}

static int max_field_width(int n, int matrix[n][n])
{
    int min_val = matrix[0][0];
    int max_val = matrix[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] < min_val)
                min_val = matrix[i][j];
            if (matrix[i][j] > max_val)
                max_val = matrix[i][j];
        }
    }
    int fld_width = snprintf(0, 0, "%d", max_val);
    if (min_val < 0)
    {
        int min_width = snprintf(0, 0, "%d", min_val);
        if (min_width > fld_width)
            fld_width = min_width;
    }
    return fld_width;
}

static void print_matrix(const char *tag, int n, int matrix[n][n])
{
    printf("%s (%d):\n", tag, n);
    int w = max_field_width(n, matrix) + 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%*d", w, matrix[i][j]);
        }
        putchar('\n');
    }
}

static int check_concentric_matrix(FILE *fp, const char *fn)
{
	if (filter_numfiles() > 1)
		printf("%s:\n", fn);
    int n = read_size(fp);
    int matrix[n][n];
    read_matrix(fp, n, matrix);
    if (!quiet)
        print_matrix("Input", n, matrix);
    if (check_matrix(n, matrix))
	{
        printf("YES: Matrix is a valid concentric matrix\n");
		return 0;
	}
    else
	{
        printf("NO: Matrix is not a valid concentric matrix\n");
		return 1;
    }
}

static const char optstr[] = "ahqV";
static const char usestr[] = "[-ahqV] [file ...]";
static const char hlpstr[] =
    "  -a  Print all discrepancies\n"
    "  -h  Print this help message and exit\n"
    "  -q  Quiet mode - do not print matrix or details of discrepancies\n"
    "  -V  Print version information and exit\n"
    ;

/* If the argument handling is any more complex, use getopt() instead */
int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'a':
            aflag = 1;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'q':
            quiet = 1;
            break;
        case 'V':
            err_version(cmdname_info, version_info);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            break;
        }
    }

    return filter_stdout(argc, argv, optind, check_concentric_matrix);
}
