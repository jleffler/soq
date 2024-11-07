/* SO Staging Ground 7916-4500 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int val = 0, neg;
    long double sum = 0.0, x, prev = 0.0, curr, factorial = 1.0;
    printf("Type X:\n");
    scanf("%Lf", &x);
    curr = x;
    while (fabs(curr- prev) >= 0.000001){
        val++;
 
        prev = curr;
        factorial *= (2*val) * (2*val+1);

        curr = (pow(x, 2*val+1))/factorial;
 
        if (val % 2 == 1)
            neg = -1;
        else
            neg = 1;
        sum += neg*curr;     
    }
    printf("Taylor series sinx: %Lf\n", sum);
    printf("math library sinx:  %lf\n", sin(x));
    return 0;
}
