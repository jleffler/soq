/* SO 19452971 */
/* Macros by http://stackoverflow.com/users/1606345/alter-mann */
/* Can this be combined with _Static_assert()? */
#include <stdio.h>

#define IS_INDEXABLE(arg) (sizeof(arg[0]))
#define IS_ARRAY(arg) (IS_INDEXABLE(arg) && (((void *) &arg) == ((void *) arg)))
#define ARRAYSIZE(arr) (sizeof(arr) / (IS_ARRAY(arr) ? sizeof(arr[0]) : 0))

static char a[1];
static char b[20];
static double c[1];
static double d[20];

#define CHECK_IT(n, t)  printf("AS.%-3s = %3d (%d) - %s\n", #n, (int)ARRAYSIZE(n), (int)IS_ARRAY(n), #t)

int main(void)
{
    char a1[1];
    char a20[20];
    double d1[1];
    double d20[20];
    double d22[2][2];
    int i = 20;
    int j[i];
    //char *cp = a1;
    //double *dp = d1;

    CHECK_IT(a,   char a[1]);
    CHECK_IT(b,   char b[1]);
    CHECK_IT(c,   double c[1]);
    CHECK_IT(d,   double d[1]);
    CHECK_IT(a1,  char a1[1]);
    CHECK_IT(a20, char a20[20]);
    CHECK_IT(d1,  double d1[1]);
    CHECK_IT(d20, double d20[20]);
    CHECK_IT(d22, double d22[2][2]);
    //CHECK_IT(i,   int i);
    CHECK_IT(j,   int j[i]);

    //CHECK_IT(cp,  char cp);
    //CHECK_IT(dp,  char dp);
    //printf("AS.%-3s = %3d\n", "a",   (int)ARRAYSIZE(a));
    //printf("AS.%-3s = %3d\n", "b",   (int)ARRAYSIZE(b));
    //printf("AS.%-3s = %3d\n", "c",   (int)ARRAYSIZE(c));
    //printf("AS.%-3s = %3d\n", "d",   (int)ARRAYSIZE(d));
    //printf("AS.%-3s = %3d\n", "a1",  (int)ARRAYSIZE(a1));
    //printf("AS.%-3s = %3d\n", "a20", (int)ARRAYSIZE(a20));
    //printf("AS.%-3s = %3d\n", "d1",  (int)ARRAYSIZE(a1));
    //printf("AS.%-3s = %3d\n", "d20", (int)ARRAYSIZE(d20));
    //printf("AS.%-3s = %3d\n", "cp",  (int)ARRAYSIZE(cp));
    //printf("AS.%-3s = %3d\n", "dp",  (int)ARRAYSIZE(dp));

    return 0;
}
