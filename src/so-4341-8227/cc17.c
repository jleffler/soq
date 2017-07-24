/* SO 4341-8227 */
/* CodeChef: https://www.codechef.com/APRIL17/problems/ROWSOLD */
/* Linear solution */

/*
** You need to see the slow quadratic solution in cc97.c at work to
** stand much of a chance of understanding this algorithm.  However,
** this is fast because it is linear.  It takes about 15 ms on a 10k
** data sample (and about 10 ms on tiny samples), compared with 13 s
** for the quadratic algorithm on the same data.
**
** The inspiration here is illustrated by the input:
**
**    0011100111000100
**
**    Input:  0011100111000100 (1s = 7, 0s = 9)
**    After:  0011001111000100 (count = 3; lm1 = 2)
**    After:  0010011111000100 (count = 6; lm1 = 2)
**    After:  0000111111000100 (count = 9; lm1 = 2)
**    After:  0000111110001100 (count = 13; lm1 = 4)
**    After:  0000111100011100 (count = 17; lm1 = 4)
**    After:  0000111000111100 (count = 21; lm1 = 4)
**    After:  0000110001111100 (count = 25; lm1 = 4)
**    After:  0000100011111100 (count = 29; lm1 = 4)
**    After:  0000000111111100 (count = 33; lm1 = 4)
**    After:  0000000111111001 (count = 36; lm1 = 7)
**    After:  0000000111110011 (count = 39; lm1 = 7)
**    After:  0000000111100111 (count = 42; lm1 = 7)
**    After:  0000000111001111 (count = 45; lm1 = 7)
**    After:  0000000110011111 (count = 48; lm1 = 7)
**    After:  0000000100111111 (count = 51; lm1 = 7)
**    After:  0000000001111111 (count = 54; lm1 = 7)
**
** The leading zeroes are not material.
**
** There's a group of 3 ones followed by 2 zeroes; the block of ones can
** be moved right 2 places (the length of the group of zeros), which
** takes 3 * (2 + 1) = 9 (cumulative 9) counts according to the rules of
** the question.
**
** There's then a block of 6 ones followed by 3 zeros; the block of ones
** can be moved right 3 places, for an extra count of 6 * (3 + 1) = 24
** (cumulative 33).
**
** There's now a block of 7 ones followed by 2 zeros; the block of ones
** can be moved right by places for an extra count of 7 * (2 + 1) = 21
** (cumulative 54).
**
** In the code: n1 is the number of ones in the new block of ones; b1 is
** the number of ones in the block of ones as a whole; and n0 is the
** number of zeros.
**
** Both cc17 and cc97 agree that the answer is 54.
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

static inline int num_char(const char *data, char c)
{
    int count = 0;
    for (int i = 0; data[i] != '\0'; i++)
        if (data[i] == c)
            count++;
    return count;
}

int main(void)
{
    char buffer[10002];
    int d;
    if (fgets(buffer, sizeof(buffer), stdin) == 0)
        return 1;
    if (sscanf(buffer, "%d", &d) != 1)
        return 1;
    //printf("%d entries\n", d);
    for (int i = 0; i < d; i++)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == 0)
            return 1;
        buffer[strcspn(buffer, "\n")] = '\0';
        int buflen = strlen(buffer);
        int tot_1s = num_char(buffer, '1');
        int tot_0s = num_char(buffer, '0');
        if (tot_1s + tot_0s != buflen)
            return 1;
        //printf("Input:  %s (1s = %d, 0s = %d)\n", buffer, tot_1s, tot_0s);

        int count = 0;
        int i = 0;
        while (buffer[i] == '0')
            i++;
        int b1 = 0;
        while (i < buflen)
        {
            int n1 = 0;
            while (i < buflen && buffer[i] == '1')
            {
                i++;
                n1++;
            }
            int n0 = 0;
            while (i < buflen && buffer[i] == '0')
            {
                i++;
                n0++;
            }
            if (n0 == 0)
                break;
            //int b0 = b1;
            //int c0 = count;
            b1 += n1;
            count += b1 * (n0 + 1);
            //printf("i = %d; old(b1 = %d, count = %d); n1 = %d; n0 = %d; count = %d\n",
            //        i, b0, c0, n1, n0, count);
        }
        printf("%d\n", count);
    }
    return 0;
}

