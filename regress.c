#include <assert.h>
#include <stdio.h>
#include <stdlib.h>           
#include <string.h>   

void linear_regression(const float *x, const float *y, const int n,
                       float *beta1, float *beta0);

int main(void)
{
    float pval[]={
        76.26, 68.68, 71.49, 73.08, 72.99, 70.36, 57.82, 58.98,
        69.71, 70.43, 77.53, 80.77, 70.30, 70.50, 70.79, 75.58,
        76.88, 80.20, 77.69, 80.80, 70.50, 85.27, 75.25,
        };
    const int Nhour = 5;
    const int MAX_HOUR = sizeof(pval)/sizeof(pval[0]);
    const int size_hour = 7;
    float ref_avg;
    float sum = 0.0;
    float m;
    float b;
    float calc_y[6];
    float calc_x[6];

    /* Get the average of the first seven elements */
    for (int i = 0; i < size_hour; i++)
        sum += pval[i];
    ref_avg = sum / size_hour; 
    printf("ref avg = %5.2f\n", ref_avg); // JL

    /* perform the regression analysis on 5 hours increment */
    for (int pass = 0; pass <= MAX_HOUR - Nhour; pass++) // JL
    {
        calc_y[0] = ref_avg;
        calc_x[0] = pass + 1;
        printf("pass %d\ncalc_y[0] = %5.2f, calc_x[0] = %5.2f\n",
               pass, calc_y[0], calc_x[0]);
        for (int i = 1; i <= Nhour; i++)  
        {
            int n = pass + i - 1;
            calc_y[i] = pval[n];
            calc_x[i] = pass + i + 1; 
            printf("calc_y[%d] = %5.2f, calc_x[%d] = %5.2f, n = %2d\n",
                   i, calc_y[i], i, calc_x[i], n);
        }

        linear_regression(calc_x, calc_y, Nhour+1, &m, &b);
        printf("Slope= %5.2f, intercept = %5.2f\n", m, b);
    }

    return 0;
}

void linear_regression(const float *x, const float *y, const int n, float *beta1, float *beta0)
{
    float sumx1 = 0.0;
    float sumy1 = 0.0;
    float sumx2 = 0.0;
    float sumxy = 0.0;

    assert(n > 1);

    for (int i = 0; i < n; i++) 
    {
        sumx1 += x[i];
        sumy1 += y[i];
        sumx2 += (x[i] * x[i]);
        sumxy += (x[i] * y[i]);
    }
    float variance = (sumx2 - ((sumx1 * sumx1) / n));
    if (variance != 0.0)
    {
        *beta1 = (sumxy - ((sumx1 * sumy1) / n)) /  variance;
        *beta0 = (sumy1 - ((*beta1) * sumx1)) / n;
    } 
    else  
    {
        *beta1 = 0.0;
        *beta0 = 0.0;
    }
}

