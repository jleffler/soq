/* SO 4544-8234 Daily temperatures */
#include <stdio.h>
#include <stdlib.h>

float max(int ndays, float temp[]);
float min(int ndays, float temp[]);
float avg(int ndays, float temp[]);

int main(void)
{
    float temp[12][31];
    char buff[1000];

    const char *n1 = "temp_data.txt";
    const char *n2 = "temp_out.txt";
    FILE *f1 = fopen(n1, "r");
    FILE *f2 = fopen(n2, "w");

    if (f1 == NULL)
    {
        fprintf(stderr, "Can't open file '%s'\n", n1);
        return 1;
    }

    if (f2 == NULL)
    {
        fprintf(stderr, "Can't open file '%s'\n", n2);
        return 1;
    }

    for (int j = 0; fgets(buff, 300, f1) != NULL; j++)
    {
        int year, month;
        int nf = sscanf(buff, "%i%i%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f",
                   &year, &month,
                   &temp[j][ 0], &temp[j][ 1], &temp[j][ 2], &temp[j][ 3],
                   &temp[j][ 4], &temp[j][ 5], &temp[j][ 6], &temp[j][ 7],
                   &temp[j][ 8], &temp[j][ 9], &temp[j][10], &temp[j][11],
                   &temp[j][12], &temp[j][13], &temp[j][14], &temp[j][15],
                   &temp[j][16], &temp[j][17], &temp[j][18], &temp[j][19],
                   &temp[j][20], &temp[j][21], &temp[j][22], &temp[j][23],
                   &temp[j][24], &temp[j][25], &temp[j][26], &temp[j][27],
                   &temp[j][28], &temp[j][29], &temp[j][30]);

        int ndays = nf - 2;
        float maxt = max(nf-2, temp[j]);
        float mint = min(nf-2, temp[j]);
        float avgt = avg(nf-2, temp[j]);
        printf("%.4d-%.2d: days = %d, min = %6.2f, avg = %6.2f, max = %6.2f\n", year, month, ndays, mint, avgt, maxt);
    }
    return 0;
}

float max(int ndays, float temp[])
{
    float maxt = temp[0];
    for (int i = 1; i < ndays; i++)
    {
        if (temp[i] > maxt)
            maxt = temp[i];
    }
    return maxt;
}

float min(int ndays, float temp[])
{
    float mint = temp[0];
    for (int i = 1; i < ndays; i++)
    {
        if (temp[i] < mint)
            mint = temp[i];
    }
    return mint;
}

float avg(int ndays, float temp[])
{
    float sum = 0;
    for (int i = 0; i < ndays; i++)
        sum += temp[i];
    return sum / ndays;
}
