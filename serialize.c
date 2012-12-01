/* stderr.h */
#ifndef STDERR_H_INCLUDED
#define STDERR_H_INCLUDED

static void err_setarg0(char const *argv0);
static void err_sysexit(char const *fmt, ...);
static void err_syswarn(char const *fmt, ...);

#endif /* STDERR_H_INCLUDED */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum { SAMPLE_SIZE = 20 }; /* 2065 in original */
enum { NUM_PERSON  = 10 }; /*   20 in original */

struct Data
{
    int ID;
    double test_sample[SAMPLE_SIZE][1]; //Why?
    size_t XX_row;
    size_t XX_col;
    double **XX;                        //size=[SAMPLE_SIZE][changing]
    double **alpha_new;                 //size=[changing][1]
    size_t alpha_new_row;
    size_t alpha_new_col;
    double t3;
    double kernel_par;
} person[NUM_PERSON];

typedef struct Data Data;

static void *emalloc(size_t nbytes)
{
    void *space = malloc(nbytes);
    if (space == 0)
        err_sysexit("Out of memory");
    return space;
}

static void free_data(Data *data)
{
    for (size_t i = 0; i < data->XX_row; i++)
        free(data->XX[i]);
    free(data->XX);

    for (size_t i = 0; i < data->alpha_new_row; i++)
        free(data->alpha_new[i]);
    free(data->alpha_new);

    data->ID = 0;
    data->t3 = 0.0;
    data->kernel_par = 0.0;
    data->XX = 0;
    data->XX_row = 0;
    data->XX_col = 0;
    data->alpha_new = 0;
    data->alpha_new_row = 0;
    data->alpha_new_col = 0;
}

static void free_array(Data *data, size_t nentries)
{
    for (size_t i = 0; i < nentries; i++)
        free_data(&data[i]);
}

static double **alloc_2D_double(size_t rows, size_t cols)
{
    double **data = emalloc(rows * sizeof(*data));
    for (size_t i = 0; i < rows; i++)
    {
        data[i] = emalloc(cols * sizeof(*data[i]));
    }
    return data;
}

static void populate_data(Data *data, size_t entry_num)
{
    /* entry_num serves as 'changing' size */
    data->ID = entry_num;
    data->t3 = entry_num *  SAMPLE_SIZE; //atan2(entry_num, SAMPLE_SIZE);
    data->kernel_par = (1.0 * SAMPLE_SIZE) / entry_num; //cos(entry_num) + sin(entry_num);

    for (size_t i = 0; i < SAMPLE_SIZE; i++)
        data->test_sample[i][0] = i + entry_num;

    data->XX_row = SAMPLE_SIZE;
    data->XX_col = entry_num;
    data->XX = alloc_2D_double(data->XX_row, data->XX_col);

    for (size_t i = 0; i < data->XX_row; i++)
    {
        for (size_t j = 0; j < data->XX_col; j++)
            data->XX[i][j] = i * data->XX_col + j;
    }

    data->alpha_new_row = entry_num;
    data->alpha_new_col = 1;
    data->alpha_new = alloc_2D_double(data->alpha_new_row, data->alpha_new_col);

    for (size_t i = 0; i < data->alpha_new_row; i++)
    {
        for (size_t j = 0; j < data->alpha_new_col; j++)
            data->XX[i][j] = i * data->alpha_new_col + j;
    }
}

static void populate_array(Data *data, size_t nentries)
{
    for (size_t i = 0; i < nentries; i++)
        populate_data(&data[i], i+1);
}

static void print_1D_double(FILE *fp, char const *tag, double const *values, size_t nvalues)
{
    char const *pad = "";
    fprintf(fp, "%s: ", tag);
    for (size_t i = 0; i < nvalues; i++)
    {
        fprintf(fp, "%s%e", pad, values[i]);
        pad = ", ";
    }
    putc('\n', fp);
}

static void print_2D_double(FILE *fp, char const *tag, double **values, size_t nrows, size_t ncols)
{
    fprintf(fp, "2D array %s[%zd][%zd]\n", tag, nrows, ncols);
    for (size_t i = 0; i < nrows; i++)
    {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%s[%zd]", tag, i);
        print_1D_double(fp, buffer, values[i], ncols);
    }
}

static void print_data(FILE *fp, char const *tag, const Data *data)
{
    fprintf(fp, "Data: %s\n", tag);
    fprintf(fp, "ID = %d; t3 = %e; kernel_par = %e\n", data->ID, data->t3, data->kernel_par);
    print_1D_double(fp, "test_sample", &data->test_sample[0][0], sizeof(data->test_sample)/sizeof(data->test_sample[0][0]));
    print_2D_double(fp, "XX", data->XX, data->XX_row, data->XX_col);
    print_2D_double(fp, "Alpha New", data->alpha_new, data->alpha_new_row, data->alpha_new_col);
}

static void print_array(FILE *fp, char const *tag, const Data *data, size_t nentries)
{
    fprintf(fp, "Array: %s\n", tag);
    fprintf(fp, "Size: %zd\n", nentries);
    for (size_t i = 0; i < nentries; i++)
    {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Row %zd", i);
        print_data(fp, buffer, &data[i]);
    }
    fprintf(fp, "End Array: %s\n\n", tag);
}

static void set_file_name(char *buffer, size_t buflen, size_t i)
{
    snprintf(buffer, buflen, "exp_data.%.3zd.exp", i);
}

static void export_1D_double(FILE *fp, double *data, size_t ncols)
{
    if (fwrite(&ncols, sizeof(ncols), 1, fp) != 1)
        err_sysexit("Failed to write number of columns");
    if (fwrite(data, sizeof(double), ncols, fp) != ncols)
        err_sysexit("Failed to write array of %zd doubles", ncols);
}

static void export_2D_double(FILE *fp, double **data, size_t nrows, size_t ncols)
{
    if (fwrite(&nrows, sizeof(nrows), 1, fp) != 1)
        err_sysexit("Failed to write number of rows");
    if (fwrite(&ncols, sizeof(ncols), 1, fp) != 1)
        err_sysexit("Failed to write number of columns");
    for (size_t i = 0; i < nrows; i++)
        export_1D_double(fp, data[i], ncols);
}

static void export_int(FILE *fp, int value)
{
    if (fwrite(&value, sizeof(value), 1, fp) != 1)
        err_sysexit("Failed to write int to file");
}

static void export_double(FILE *fp, double value)
{
    if (fwrite(&value, sizeof(value), 1, fp) != 1)
        err_sysexit("Failed to write double to file");
}

static void export_data(FILE *fp, Data *data)
{
    export_int(fp, data->ID);
    export_double(fp, data->t3);
    export_double(fp, data->kernel_par);
    export_1D_double(fp, &data->test_sample[0][0], sizeof(data->test_sample)/sizeof(data->test_sample[0]));
    export_2D_double(fp, data->XX, data->XX_row, data->XX_col);
    export_2D_double(fp, data->alpha_new, data->alpha_new_row, data->alpha_new_col);
}

static void export_array(Data *data, size_t nentries)
{
    for (size_t i = 0; i < nentries; i++)
    {
        char filename[30];
        set_file_name(filename, sizeof(filename), i);
        FILE *fp = fopen(filename, "w");
        if (fp == 0)
            err_sysexit("Failed to open file %s for writing", filename);
        printf("Export %zd to %s\n", i, filename);
        export_data(fp, &data[i]);
        fclose(fp);
    }
}

static int import_int(FILE *fp)
{
    int value;
    if (fread(&value, sizeof(value), 1, fp) != 1)
        err_sysexit("Failed to read int");
    return value;
}

static double import_double(FILE *fp)
{
    double value;
    if (fread(&value, sizeof(value), 1, fp) != 1)
        err_sysexit("Failed to read int");
    return value;
}

static size_t import_size_t(FILE *fp)
{
    size_t value;
    if (fread(&value, sizeof(value), 1, fp) != 1)
        err_sysexit("Failed to read size_t");
    return value;
}

static void import_1D_double(FILE *fp, double *data, size_t nvalues)
{
    size_t size = import_size_t(fp);
    if (size != nvalues)
        err_sysexit("Size mismatch (wanted %zd, actual %zd)\n", nvalues, size);
    if (fread(data, sizeof(data[0]), nvalues, fp) != nvalues)
        err_sysexit("Failed to read %zd doubles");
}

static void import_2D_double(FILE *fp, double ***data, size_t *nrows, size_t *ncols)
{
    *nrows = import_size_t(fp);
    *ncols = import_size_t(fp);
    *data  = alloc_2D_double(*nrows, *ncols);
    for (size_t i = 0; i < *nrows; i++)
        import_1D_double(fp, (*data)[i], *ncols);
}

static void import_data(FILE *fp, Data *data)
{
    data->ID = import_int(fp);
    data->t3 = import_double(fp);
    data->kernel_par = import_double(fp);

    import_1D_double(fp, &data->test_sample[0][0], sizeof(data->test_sample)/sizeof(data->test_sample[0][0]));
    import_2D_double(fp, &data->XX, &data->XX_row, &data->XX_col);
    import_2D_double(fp, &data->alpha_new, &data->alpha_new_row, &data->alpha_new_col);
}

static void import_array(Data *data, size_t nentries)
{
    for (size_t i = 0; i < nentries; i++)
    {
        char filename[30];
        set_file_name(filename, sizeof(filename), i);
        FILE *fp = fopen(filename, "r");
        if (fp == 0)
            err_sysexit("Failed to open file %s for reading", filename);
        printf("Import %zd from %s\n", i, filename);
        import_data(fp, &data[i]);
        fclose(fp);
    }
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1)
        err_syswarn("Ignoring %d irrelevant arguments", argc-1);
    populate_array(person, NUM_PERSON);
    print_array(stdout, "Freshly populated", person, NUM_PERSON);
    export_array(person, NUM_PERSON);
    printf("\n\nEXPORT COMPLETE\n\n");
    free_array(person, NUM_PERSON);
    import_array(person, NUM_PERSON);
    printf("\n\nIMPORT COMPLETE\n\n");
    print_array(stdout, "Freshly imported", person, NUM_PERSON);
    free_array(person, NUM_PERSON);
    return(0);
}

/* stderr.c */
/*#include "stderr.h"*/
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static char const *arg0 = "<undefined>";

static void err_setarg0(char const *argv0)
{
    arg0 = argv0;
}

static void err_vsyswarn(char const *fmt, va_list args)
{
    int errnum = errno;
    fprintf(stderr, "%s: ", arg0);
    vfprintf(stderr, fmt, args);
    if (errnum != 0)
        fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
    putc('\n', stderr);
}

static void err_syswarn(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
}

static void err_sysexit(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
    exit(1);
}
