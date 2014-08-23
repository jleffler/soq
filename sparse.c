/* SO 25354530 */
//#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct col col;
typedef struct row row;
typedef struct matrix matrix;

struct col
{
    int     indiceColumn;
    double  value;
    col    *next;
};

struct row
{
    int  indiceRow;
    col *data;
    row *next;
};

struct matrix
{
    row *rowFirst;
    int  nRows;
    int  nCols;
};

matrix* sp_read(char* path);
col* pushCol(int* column, double* value, col* dataRow);
row* pushRow(col* data, int* rows, matrix* top);

int main(void)
{
    //matrix *tempMatrix = (matrix*)malloc(sizeof(matrix));
    matrix *tempMatrix = sp_read("mat_100x5");
    printf("%p\n", tempMatrix);
    return 0;
}

matrix* sp_read(char* path)
{
    matrix* matrice = (matrix*)malloc(sizeof(matrix));
    matrice->rowFirst = NULL;
    matrice->nRows = 0;
    matrice->nCols = 0;
    row* rows = (row*)malloc(sizeof(row));
    rows->indiceRow = 0;
    rows->data = NULL;
    rows->next = NULL;
    col* cols = (col*)malloc(sizeof(col));
    cols->value = 0;
    cols->indiceColumn = 0;
    cols->next = NULL;

    FILE* file = NULL;
    file = fopen(path, "rb");

    int nRow;
    int nCol;

    fread(&nRow, sizeof(int), 1, file);
    fread(&nCol, sizeof(int), 1, file);
    printf("%d , %d \n", nRow, nCol);

    int i;
    int j;

    double* currentDigit = (double*)malloc(sizeof(double));
    int count;

    for (i = 1; i <= nRow; i++) {
        if (i == 1) { // initialize the matrix
            matrice->nRows = nRow;
            matrice->nCols = nCol;
            matrice->rowFirst = rows;
        }

        rows = pushRow(NULL, &i, matrice);
        count = 0;
        for (j = 1; j <= nCol; j++) {
            fread(currentDigit, sizeof(double), 1, file);

            if (*(currentDigit) != 0.0) {
                count++;
                if (count == 1) { // begin a new column list on the next node of
                                  // the row list
                    cols = NULL;
                    rows->data = cols;
                }
                cols = pushCol(&j, currentDigit, cols);
            }
        }
    }

    fclose(file);
    free(currentDigit);
    return matrice;
}

row* pushRow(col* data, int* rows, matrix* top)
{
    row* f = NULL;
    f = (row*)malloc(sizeof(row));

    if (f == NULL) {
        exit(EXIT_FAILURE);
    }

    f = top->rowFirst;

    if (f->indiceRow == 0) {
        printf("null");
        f->data = data;
        f->indiceRow = *(rows);
        f->next = NULL;
    }
    else {
        while (f->next != NULL) {
            f = f->next;
        }
        row* temp = NULL;
        temp = (row*)malloc(sizeof(row));
        f->next = temp;
        f->next->indiceRow = *(rows);
        f->next->data = data;
        f = f->next;
    }

    return f;
}

col* pushCol(int* column, double* value, col* dataRow) {
    col* f = NULL;
    f = (col*)malloc(sizeof(col));

    if (f == NULL) {
        exit(EXIT_FAILURE);
    }

    f = dataRow;
    if (f->indiceColumn == 0) {
        f->indiceColumn = *(column);
        f->value = *(value);
        dataRow = f;
    }
    else {
        while (f->next != NULL) {
            f = f->next;
        }
        col* temp = NULL;
        temp = (col*)malloc(sizeof(col));
        f->next = temp;
        f->next->indiceColumn = *(column);
        f->next->value = *(value);
        f = f->next;
        dataRow = f;
    }

    return dataRow;
}
