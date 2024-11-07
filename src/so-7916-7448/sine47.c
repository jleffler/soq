/* SO Staging Ground 7916-4500 */
/* SO 7916-7448 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int val = 0, neg;
    long double sum = 0.0, x, prev = 0.0, curr, factorial = 1.0;
    printf("Type X:\n");
    scanf("%Lf", &x);
    curr = x;
    while (fabsl(curr - prev) >= 0.000001)
    {
        val++;

        prev = curr;
        factorial *= (2 * val) * (2 * val + 1);

        curr = (powl(x, 2 * val + 1)) / factorial;

        if (val % 2 == 1)
            neg = -1;
        else
            neg = 1;
        sum += neg * curr;
        printf("val = %2d: neg = %+2d; factorial = %12.0Lf; term = %15.9Le; "
               "old = %15.9Le; new = %15.9Le\n",
               val, neg, factorial, curr, prev, sum);
    }
    printf("Taylor series sinx: %Lf\n", sum);
    printf("math library sinx:  %Lf\n", sinl(x));
    return 0;
}
