#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 2


// Sort list "r" using list "mInt"
static
void sort(unsigned int *mInt, double *r, int n){ 
   unsigned int ph0;
   double ph1, ph2;

   for(int i = 1; i <= n-1; i++)
      for(int j = 1; j <= n-i; j++)
         if(mInt[j-1] >= mInt[j])
         {
            // 1
            ph1 = r[DIM*(j-1)+0];
            ph2 = r[DIM*(j-1)+1];
            ph0 = mInt[j-1];

            // 2
            mInt[j-1] = mInt[j];
            r[DIM*(j-1)+0] = r[DIM*j+0];
            r[DIM*(j-1)+1] = r[DIM*j+1];

            // 3
            mInt[j] = ph0;
            r[DIM*j+0] = ph1;
            r[DIM*j+1] = ph2;
         }
}

// Create morton key
static
inline unsigned int mortoncode(unsigned int x, unsigned int y){
    int answer = 0;
    for (unsigned int i = 0; i < (sizeof(unsigned int)* 8)/2; ++i) {
        answer |= (((x & ((unsigned int)1 << i)) << 2*i) | ((y & ((unsigned int)1 << i)) << (2*i + 1)));
    }
    return answer;
}

// Find max / min values
static
double maxValue(double *r, int n, int d){
    double max = r[d];
    for(int k=0; k<n; k++){
        if(max < r[DIM*k+d]){
            max = r[DIM*k+d];
        }
    }
    return max;
}

static
double minValue(double *r, int n, int d){
    double min = r[d];
    for(int k=0; k<n; k++){
        if(min > r[DIM*k+d]){
            min = r[DIM*k+d];
        }
    }
    return min;
}

int main(void){  
    int n = 100;
    double r[n*DIM];

    printf("Initialize data\n");
    double x1 = 0;
    double y1 = 0;
    for(int k=0; k<n; k++){
        r[DIM*k+0] = x1;
        r[DIM*k+1] = y1;
        x1 += 0.1;
        if(k % 10 == 0){
            y1 += 0.1;
            x1 = 0;
        }
        printf("%lf %lf\n", r[DIM*k+0], r[DIM*k+1]);
    }

    // Get max/min values
    double rMin[DIM];
    double rMax[DIM];
    for(int d=0; d<DIM; d++){
        rMin[d] = minValue(r, n, d);
        rMax[d] = maxValue(r, n, d);
    }

    printf("Convert double data to integers\n");
    unsigned int rInt[n];
    for(int k=0; k<n; k++){
        for(int d=0; d<DIM; d++){
            int idx=DIM*k+d;
            double map = floor(((2097151)/(rMax[d]-rMin[d]))*r[idx]-rMin[d]);
            rInt[idx] = (int)map;
        }
        printf("%d %d\n", rInt[DIM*k+0], rInt[DIM*k+1]);
    }

    // Convert rInt[x_1,y_1,x_2,y_2,...] to Morton key
    printf("\n");
    unsigned int rMor[n];
    for(int k=0; k<n; k++){
        int idx = DIM*k;
        rMor[k] = mortoncode(rInt[idx+0], rInt[idx+1]);
    }

    // Sort data 
    sort(rMor, r, n);

    printf("Sorted data\n");
    for(int k=0; k<n; k++)
        printf("%lf %lf\n", r[DIM*k+0], r[DIM*k+1]);

    return 0;
}
