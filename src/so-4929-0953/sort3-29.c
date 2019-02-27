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
    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            for (int k = 1; k < 4; k++)
                print_smallest(i, j, k);
        }
    }
    return 0;
}
