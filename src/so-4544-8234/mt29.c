/* SO 4544-8234 Daily temperatures */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_VALID_TEMP -100.0
#define MAX_VALID_TEMP +300.0

#if 0
struct Monthly
{
    int year;
    int month;
    float temp[31];
    float min;
    float max;
    float avg;
    float ndays;
};
#endif /* 0 */

float max(int ndays, float temp[]);
float min(int ndays, float temp[]);
float avg(int ndays, float temp[]);
int   cnt(int ndays, float temp[]);

static inline int is_valid_temp(float temp)
{
    return(temp > MIN_VALID_TEMP && temp < MAX_VALID_TEMP);
}

static inline int is_leap_year(int year)
{
    if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))
        return 0;
    return 1;
}

static int days_in_month(int year, int month)
{
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    assert(year > 0 && year <= 9999);
    assert(month > 0 && month <= 12);
    if (month != 2)
        return(days[month - 1]);
    else
        return(days[month - 1] + is_leap_year(year));
}

static int scan_line(const char *buff, float *temp, int *month, int *year)
{
    int offset = 0;
    int nf = sscanf(buff, "%d%d%n", year, month, &offset);
    if (nf != 2)
    {
        printf("nf = %d; year = %d, month = %d\n", nf, *year, *month);
        return -1;
    }
    buff += offset;
    int days = days_in_month(*year, *month);
    for (int i = 0; i < days; i++)
    {
        if (sscanf(buff, "%f%n", &temp[i], &offset) != 1)
        {
            printf("failed: %s\n", buff + offset);
            return -1;
        }
        if (!is_valid_temp(temp[i]))
        {
            printf("invalid: %6.2f\n", temp[i]);
            return -1;
        }
        buff += offset;
    }
    return days;
}

static void dump_data(const char *tag, int n_months, float temp[][31], float d_min[], float d_max[], float d_avg[], int *d_count, int *d_year, int *d_month)
{
    printf("%s: %d months\n", tag, n_months);
    for (int m = 0; m < n_months; m++)
    {
        printf("%.4d-%.2d: days = %d, min = %6.2f, avg = %6.2f, max = %6.2f\n",
               d_year[m], d_month[m], d_count[m], d_min[m], d_avg[m], d_max[m]);
        fputs("    ", stdout);
        for (int d = 0; d < d_count[m]; d++)
            printf("%6.2f", temp[m][d]);
        putchar('\n');
    }
}

int main(void)
{
    float temp[12][31];
    float d_min[12];
    float d_max[12];
    float d_avg[12];
    int   d_count[12];
    int   d_year[12];
    int   d_month[12];
    char buff[1000];
    int n_months = 0;

    for (int j = 0; j < 12 && fgets(buff, 300, stdin) != NULL; j++)
    {
        int year, month;
        int ndays = scan_line(buff, temp[j], &month, &year);
        if (ndays < 0)
            break;
        float maxt = max(ndays, temp[j]);
        float mint = min(ndays, temp[j]);
        float avgt = avg(ndays, temp[j]);
        int count  = cnt(ndays, temp[j]);
        printf("%.4d-%.2d: days = %d, min = %6.2f, avg = %6.2f, max = %6.2f\n", year, month, count, mint, avgt, maxt);
        d_min[j] = mint;
        d_max[j] = maxt;
        d_avg[j] = avgt;
        d_count[j] = count;
        d_year[j] = year;
        d_month[j] = month;
        n_months = j + 1;
    }
    dump_data("Data all read", n_months, temp, d_min, d_max, d_avg, d_count, d_year, d_month);
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
