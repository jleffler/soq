#include <stdio.h>

int main(void)
{
    int nRows = 5;
    int nCols = 10;

    fwrite(&nRows, sizeof(nRows), 1, stdout);
    fwrite(&nCols, sizeof(nCols), 1, stdout);
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            double d = (i == j) ? 1.0 : 0.0;
            fwrite(&d, sizeof(d), 1, stdout);
        }
    }
    return 0;
}
