/* SO 7483-2964 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int userInput() {
    int a = 0;
    printf_s("Input your number: ");
    scanf_s("%d", &a);
    return a;
}

//allocate a 2D array
int** allocate2D(int rows, int cols)
{
    int** arr2D;
    int i;

    arr2D = (int**)malloc(rows * sizeof(int*));
    for (i = 0; i < rows; i++)
    {
        arr2D[i] = (int*)malloc(cols * sizeof(int));
    }
    return arr2D;
}
void deallocate2D(int** arr2D, int rows)
{
    int i;

    for (i = 0; i < rows; i++)
    {
        free(arr2D[i]);
    }

    free(arr2D);
}


int** array1Creator(int** array1, int row, int col) {
    srand(time(NULL));
    printf_s("first: \n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            array1[i][j] = rand() % 100;
            printf_s("%d ", array1[i][j]);

        }
        printf_s("\n");
    }
    return array1;
}

int** array2Creator(int** array2, int row, int col) {
    srand(time(NULL));
    printf_s("second: \n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            array2[i][j] = rand() % 101;
            printf_s("%d ", array2[i][j]);

        }
        printf_s("\n");
    }
    return array2;
}

void arrayMultiply(int** arr1, int** arr2, int** arr3, int c1, int r1, int c2, int r2) {
    printf_s("third: \n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            arr3[i][j] = 0;
        for (int a = 0; a < c1; a++) {
                arr3[i][j] += arr1[i][a] * arr2[a][j];
            }
            printf_s("%d ", arr3[i][j]);
        }
        printf_s("\n");
    }

}


int main()
{
    int r1 = userInput();
    int c1 = userInput();
    int r2 = userInput();
    int c2 = userInput();

    int** array1 = allocate2D(r1, c1);
    int** array2 = allocate2D(r2, c2);
    int** array3 = allocate2D(r1, c1);

    if (r1 == c2) {
        arrayMultiply(array1Creator(array1, r1, c1), array2Creator(array2, r2, c2), array3, c1, r1, c2, r2);
    }
    else
        printf_s("wrong values of rows or columns");


    deallocate2D(array1, r1);
    deallocate2D(array2, r2);
    deallocate2D(array3, r1);

    return 0;
}
