/* SO Staging Ground 7916-4500 */
/* SO 7916-7448 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int val = 0, neg;
    double sum = 0.0, x, prev = 0.0, curr, factorial = 1.0;
    printf("Type X: ");
    scanf("%lf", &x);
    sum = curr = x;
    while (fabs(curr - prev) >= 0.000001)
    {
        val++;

        prev = curr;
        factorial *= (2 * val) * (2 * val + 1);

        curr = (pow(x, 2 * val + 1)) / factorial;

        if (val % 2 == 1)
            neg = -1;
        else
            neg = 1;
        sum += neg * curr;
        printf("val = %2d: neg = %+2d; factorial = %12.0lf; term = %15.9le; "
               "old = %15.9le; new = %15.9le\n",
               val, neg, factorial, curr, prev, sum);
    }
    printf("Taylor series sinx: %lf\n", sum);
    printf("math library sinx:  %lf\n", sin(x));
    return 0;
}
