/* SO 18579583 Segmentation fault error in 3d array memory allocation */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int ***allocate_3d_array(int no1, int ****a)
{
    *a = (int***)malloc(no1 * sizeof(int**));
    if (*a == 0)
        return 0;

    for (int l = 0; l < no1; l++)
    {
        if (((*a)[l]=(int**)malloc((no1+1)*sizeof(int*))) == 0)
        {
            while (l > 0)
                free((*a)[--l]);
            return 0;
        }
    }

    for (int l = 0; l < no1; l++)
    {
        for (int h = 0; h < no1; h++)
        {
            if (((*a)[l][h]=(int*)malloc(2*sizeof(int))) == 0)
            {
                /* Leak! */
                return 0;
            }
        }
    }

    for (int l = 0; l < no1; l++)
        for (int h = 0; h < no1; h++)
            for (int k = 0; k < 2; k++)
                (*a)[l][h][k] = 10000 * l + 100 * h + k;

    return *a;
}

int main(void)
{
    int no1 = 5;
    int ***a = 0;
    int ***b = allocate_3d_array(no1, &a);
    const char *pad[] = { "  ", "\n" };
    assert(b == a);

    if (a != 0)
    {
        for (int l = 0; l < no1; l++)
            for (int h = 0; h < no1; h++)
                for (int k = 0; k < 2; k++)
                    printf("a[%d][%d][%d] = %.6d%s", l, h, k, a[l][h][k], pad[k]);

        // free memory - added by harpun; reformatted by Jonathan Leffler
        // Would be a function normally — see version 2 code.
        for (int l = 0; l < no1; l++)
        {
            for (int h = 0; h < no1; h++)
                free(a[l][h]);
            free(a[l]);
        }
        free(a);
    }

    return 0;
}
