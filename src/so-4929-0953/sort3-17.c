/* SO 4929-0953 */
#include <stdio.h>

static void print_smallest(int num1, int num2, int num3)
{
    printf("The smallest number of (%d, %d, %d) is %d\n",
           num1, num2, num3,
           (num1 * (num1 <= num2 && num1 <= num3) +
            num2 * (num2 <  num1 && num2 <= num3) +
            num3 * (num3 <  num2 && num3 <  num1)));
}

int main(void)
{
    int lo = -2;
    int hi = +4;
    int inc = +2;
    for (int i = lo; i < hi; i += inc)
    {
        for (int j = lo; j < hi; j += inc)
        {
            for (int k = lo; k < hi; k += inc)
                print_smallest(i, j, k);
        }
    }
    return 0;
}
