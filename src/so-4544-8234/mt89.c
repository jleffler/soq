/* SO 4544-8234 Daily temperatures */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_VALID_TEMP -100.0
#define MAX_VALID_TEMP +300.0

float max(int ndays, float temp[]);
float min(int ndays, float temp[]);
float avg(int ndays, float temp[]);
int   cnt(int ndays, float temp[]);

int main(void)
{
    float temp[12][31];
    char buff[1000];

    for (int j = 0; fgets(buff, 300, stdin) != NULL; j++)
    {
        int year, month;
        int nf = sscanf(buff, "%d%d%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f",
                   &year, &month,
                   &temp[j][ 0], &temp[j][ 1], &temp[j][ 2], &temp[j][ 3],
                   &temp[j][ 4], &temp[j][ 5], &temp[j][ 6], &temp[j][ 7],
                   &temp[j][ 8], &temp[j][ 9], &temp[j][10], &temp[j][11],
                   &temp[j][12], &temp[j][13], &temp[j][14], &temp[j][15],
                   &temp[j][16], &temp[j][17], &temp[j][18], &temp[j][19],
                   &temp[j][20], &temp[j][21], &temp[j][22], &temp[j][23],
                   &temp[j][24], &temp[j][25], &temp[j][26], &temp[j][27],
                   &temp[j][28], &temp[j][29], &temp[j][30]);

        assert(nf >= 28 + 2 && nf <= 31 + 2);   // 28-31 days, plus year plus month
        int ndays = nf - 2;
        float maxt = max(ndays, temp[j]);
        float mint = min(ndays, temp[j]);
        float avgt = avg(ndays, temp[j]);
        int count  = cnt(ndays, temp[j]);
        printf("%.4d-%.2d: days = %d, min = %6.2f, avg = %6.2f, max = %6.2f\n", year, month, count, mint, avgt, maxt);
    }
    return 0;
}

float max(int ndays, float temp[])
{
    float maxt = temp[0];
    assert(maxt > MIN_VALID_TEMP && maxt < MAX_VALID_TEMP);
    for (int i = 1; i < ndays; i++)
    {
        if (temp[i] > MIN_VALID_TEMP && temp[i] < MAX_VALID_TEMP)
        {
            if (temp[i] > maxt)
                maxt = temp[i];
        }
    }
    return maxt;
}

float min(int ndays, float temp[])
{
    float mint = temp[0];
    assert(mint > MIN_VALID_TEMP && mint < MAX_VALID_TEMP);
    for (int i = 1; i < ndays; i++)
    {
        if (temp[i] > MIN_VALID_TEMP && temp[i] < MAX_VALID_TEMP)
        {
            if (temp[i] < mint)
                mint = temp[i];
        }
    }
    return mint;
}

float avg(int ndays, float temp[])
{
    float sum = 0;
    int count = 0;
    for (int i = 0; i < ndays; i++)
    {
        if (temp[i] > MIN_VALID_TEMP && temp[i] < MAX_VALID_TEMP)
        {
            count++;
            sum += temp[i];
        }
    }
    return sum / ndays;
}

int cnt(int ndays, float temp[])
{
    int count = 0;
    for (int i = 0; i < ndays; i++)
    {
        if (temp[i] > MIN_VALID_TEMP && temp[i] < MAX_VALID_TEMP)
            count++;
    }
    return count;
}
