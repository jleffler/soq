#include <stdio.h>

int main(void) {

    int mat[100][100];
    int ii[] = {0, 1, 0, -1};           // incremental numbers of i
    int jj[] = {1, 0, -1, 0};           // incremental numbers of j

    int i, j;
    int n;
    int u, v, w;                        // variables to walk on edges
    int val;                            // value of the element
    int prev = -1;                      // previous value in one outer edge (assuming the matrix values are positive)
    int length;                         // length of the side of the edge

    // read matrix size and values
    printf("Enter the number:\n");
    scanf("%d", &n);

    printf("Enter the matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // loop on the edges
    for (u = 0; u < n / 2; u++) {       // from the outmost edge to inner
        i = u; j = u;                   // index of the north west corner
        val = mat[u][u];                // initial value to compare
        for (v = 0; v < 4; v++) {       // four sides
            length = n - u * 2 - 1;     // length of the side of the edge
            for (w = 0; w < length; w++) {
                i += ii[v];             // one step ahead on the edge
                j += jj[v];             // same as above
                if (mat[i][j] != val || mat[i][j] <= prev) {
                    printf("No at [%d][%d] (val=%d)\n", i, j, mat[i][j]);
                    return 1;
                }
            }
        }
        prev = mat[i][j];
    }

    // finally examine the center value
    if (n % 2 == 1) {
        if (mat[u][u] <= prev) {
            printf("No at [%d][%d] (val=%d)\n", u, u, mat[u][u]);
            return 1;
        }
    }

    printf("Yes\n");
    return 0;
}
