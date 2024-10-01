/* SO 6511-7221 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define N 2048

float *A[N], *B[N];
int i, j, k, count = 0;

float** matrix_create(int n){
  float** M = malloc(n * sizeof(float*));
  for (i = 0; i < n; i++)
    M[i] = (float*)malloc(n * sizeof(float));
  return M;
}

float** add(float* M1[], float* M2[], int n){
  float** M3 = matrix_create(n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      M3[i][j] = M1[i][j] + M2[i][j];
  return M3;
}

float** sub(float* M1[], float* M2[], int n){
  float** M3 = matrix_create(n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      M3[i][j] = M1[i][j] - M2[i][j];
  return M3;
}

void print(float* M[], int n){
  for (i = 0; i <  n; i++){
    for (j = 0; j < n; j++)
      printf("%f\t", M[i][j] );
    printf("\n");
    }
}

float** strassen_multiply(float* A[], float* B[], int n){
  if(n == 1 ){
    float** C = matrix_create(n);
    C[0][0] = A[0][0] * B[0][0];
    return C;
  }
  count++;
  float** C = matrix_create(n);
  int k = n/2;
  /** Creating sub matrecies**/
  float** A11 = matrix_create(k);
  float** A12 = matrix_create(k);
  float** A21 = matrix_create(k);
  float** A22 = matrix_create(k);
  float** B11 = matrix_create(k);
  float** B12 = matrix_create(k);
  float** B21 = matrix_create(k);
  float** B22 = matrix_create(k);

  /**Dividing the Data Matrecies A & B**/
  for(i = 0; i < k; i++)
      for(j = 0; j < k; j++){
          A11[i][j] = A[i][j];
          A12[i][j] = A[i][k+j];
          A21[i][j] = A[k+i][j];
          A22[i][j] = A[k+i][k+j];
          B11[i][j] = B[i][j];
          B12[i][j] = B[i][k+j];
          B21[i][j] = B[k+i][j];
          B22[i][j] = B[k+i][k+j];
      }

  float** P1 = strassen_multiply(A11, sub(B12, B22, k), k);
  float** P2 = strassen_multiply(add(A11, A12, k), B22, k);
  float** P3 = strassen_multiply(add(A21, A22, k), B11, k);
  float** P4 = strassen_multiply(A22, sub(B21, B11, k), k);
  float** P5 = strassen_multiply(add(A11, A22, k), add(B11, B22, k), k);
  float** P6 = strassen_multiply(sub(A12, A22, k), add(B21, B22, k), k);
  float** P7 = strassen_multiply(sub(A11, A21, k), add(B11, B12, k), k);

  float** C11 = sub(add(add(P5, P4, k), P6, k), P2, k);
  float** C12 = add(P1, P2, k);
  float** C21 = add(P3, P4, k);
  float** C22 = sub(sub(add(P5, P1, k), P3, k), P7, k);

  for(i = 0; i < k; i++)
      for(j = 0; j < k; j++){
          C[i][j] = C11[i][j];
          C[i][j+k] = C12[i][j];
          C[k+i][j] = C21[i][j];
          C[k+i][k+j] = C22[i][j];
      }

      for(i = 0; i < k; i++){
          free( A11[i]);
          free( A12[i]);
          free( A21[i]);
          free( A22[i]);
          free( B11[i]);
          free( B12[i]);
          free( B21[i]);
          free( B22[i]);
          free( P1[i]);
          free( P2[i]);
          free( P3[i]);
          free( P4[i]);
          free( P5[i]);
          free( P6[i]);
          free( P7[i]);
          free( C11[i]);
          free( C12[i]);
          free( C21[i]);
          free( C22[i]);
      }

      free( A11);
      free( A12);
      free( A21);
      free( A22);
      free( B11);
      free( B12);
      free( B21);
      free( B22);
      free( P1);
      free( P2);
      free( P3);
      free( P4);
      free( P5);
      free( P6);
      free( P7);
      free( C11);
      free( C12);
      free( C21);
      free( C22);

      return C;

}


int main(){

  int i,j, k;
  struct timeval begin, end;



  for (i = 0; i < N; i++)
    A[i] = (float*)malloc(N * sizeof(float));
  for (i = 0; i < N; i++)
    B[i] = (float*)malloc(N * sizeof(float));


   for (i = 0; i <  N; i++)
     for (j = 0; j < N; j++){
        A[i][j] = -1+2*((float)rand())/RAND_MAX;
        B[i][j] = -1+2*((float)rand())/RAND_MAX;
        }

    float** C = matrix_create(N);
    gettimeofday(&begin, 0);
    C = strassen_multiply(A, B, N);
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    printf("number of recursion: %d\n\n", count);
    printf("Total wall time: %f\n", elapsed);
}
