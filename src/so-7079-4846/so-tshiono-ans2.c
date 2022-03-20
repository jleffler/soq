#include <stdio.h>

int main(void) {

    int mat[100][100];
    int i, j;
    int ii, jj;                         // incremental values for i and j
    int n;
    int u, v, w;                        // variables to walk on edges
    int val;                            // value of the element
    int prev = -1;                      // previous value in one outer edge
    int length;                         // length of the edge

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
    for (u = 0; u < n / 2; u++) {       // from outmost edge to inner
        i = u; j = u;                   // index of the north west corner
        val = mat[u][u];                // initial value to compare
        for (v = 0; v < 4; v++) {       // four sides
            ii = (v & 1) * ((v & 1) - (v & 2));
                                        //  assigned to {0, 1, 0, -1} in order
            jj = ((v + 1) & 1) * (((v + 1) & 1) - ((v + 1) & 2));
                                        //  assigned to {1, 0, -1, 0} in order
            length = n - u * 2 - 1;     // length of the edge
            for (w = 0; w < length; w++) {
                i += ii;                // one step ahead on the edge
                j += jj;                // same as above
                if (mat[i][j] != val || (u > 0 && mat[i][j] <= prev)) {
                                        // if u == 0, skip the comparison with prev
                    printf("No at [%d][%d] (val=%d)\n", i, j, mat[i][j]);
                    return 1;
                }
            }
        }
        prev = mat[i][j];
    }

    // finally examine the center value (if n is odd number)
    if (n % 2) {
        if (mat[u][u] <= prev) {
            printf("No at [%d][%d] (val=%d)\n", u, u, mat[u][u]);
            return 1;
        }
    }

    printf("Yes\n");
    return 0;
}
