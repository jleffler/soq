/* SO 4929-0953 */
#include <stdio.h>

static inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int main(void)
{
    int num1, num2, num3;

    if (scanf("%d%d%d", &num1, &num2, &num3) != 3)
    {
        fprintf(stderr, "failed to read 3 integers\n");
        return 1;
    }

    printf("The sorted order of (%2d, %2d, %2d) is (%2d, %2d, %2d)\n",
           num1, num2, num3,

           (num1 * (num1 <= num2 && num1 <= num3) +     /* Min1 */
            num2 * (num2 <  num1 && num2 <= num3) +     /* Min2 */
            num3 * (num3 <  num1 && num3 <  num2)),     /* Min3 */

           (num1 * (num1 >= num2 && num1 <= num3) +     /* Med1 */
            num2 * (num2 >  num1 && num2 <= num3) +     /* Med2 */
            num3 * (num3 >  num1 && num3 <  num2) -     /* Med3 */
            num1 * (num1 == num2 && num1 == num3) +     /* Med4 */
            num1 * (num1 <= num2 && num1 >= num3) +     /* Med5 */
            num2 * (num2 <  num1 && num2 >= num3) +     /* Med6 */
            num3 * (num3 <  num1 && num3 >  num2)),     /* Med7 */

           (num1 * (num1 >= num2 && num1 >= num3) +     /* Max1 */
            num2 * (num2 >  num1 && num2 >= num3) +     /* Max2 */
            num3 * (num3 >  num1 && num3 >  num2))      /* Max3 */
          );

    return 0;
}
