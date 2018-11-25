/* SO 4929-0953 */
#include <stdio.h>

static inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void print_smallest(int num1, int num2, int num3)
{
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
}

int main(void)
{
    int lo = -7;        // +1, -2
    int hi = +6;        // +4, +4
    int jp = +6;        // +1, +2
    for (int i = lo; i < hi; i += jp)
    {
        for (int j = lo; j < hi; j += jp)
        {
            for (int k = lo; k < hi; k += jp)
                print_smallest(i, j, k);
        }
    }
    return 0;
}
