### Stack Overflow Question 6511-7221

[SO 6511-7221](https://stackoverflow.com/q/65117221) &mdash;
Bus error/ core dumped When surpassing 1024x1024 matrix in C


## Question

When running this code on N > 1024, I get a bus error/core dumped error.
I am using a remote HPC and gcc/8.1.  This is a matrix multiplication
NxN.  I don't understand where the error comes from.  Specifically why
there's nothing wrong with the smaller Ns.  I had other codes running up
to 2^20 before.

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

<hr>

Sequence of created source files:

* `matmul97.c` - original code
* `matmul47.c`
* `matmul67.c`
* `matmul73.c`
* `matmul89.c`
* `matmul23.c` - simplified code

<hr>


<sup>_Transferring some comments from the [chat](https://chat.stackoverflow.com/rooms/225442/discussion-on-question-by-mahan-agha-zahedi-bus-error-core-dumped-when-surpassi)._</sup>

## Diagnosis

* You're not checking that your memory is allocated successfully.  You
  don't know whether everything worked.

* You start off with two 2048x2048 `float` matrices.  Your
  `strassen_multiply()` function then (1) creates 8 matrices each with
  half the size (in terms of number of rows and columns), loads them,
  and then recurses 7 times in a row.  Each of those recursions also
  creates a load of matrices — I've not sat down and calculated the
  total space required, but it is going to be considerable.  You really
  need to check that your memory allocation is working.  It may be that
  your 64-bit machine has enough space that it isn't a problem (the two
  initial matrices require 32 MiB of data, which may be OK).

* You have calls like

      float** P1 = strassen_multiply(A11, sub(B12, B22, k), k);
      float** P2 = strassen_multiply(add(A11, A12, k), B22, k);

  You have no way to free the matrix returned by the nested calls to
  `sub()` and `add()`.  You can't afford not to free that memory.  So,
  you're leaking large quantities of memory.  You need a function to
  free your matrices — and arguably a matrix structure type that
  records the size of the matrix since you're going to need the size in
  the function to free a matrix.

* You check that memory was allocated by checking for a null pointer
  returned by `malloc()`.  On most systems, that's reliable.  On Linux,
  it has the OOM (Out of Memory) manager and tends to return a non-null
  pointer and later crashes when you try to use the memory that it told
  you was available but actually wasn't.  I regard that as highly
  undesirable behaviour, but … If you fail to allocate one of the
  rows, don't forget to release any previously allocated rows in that
  matrix.

* You can't use global matrices; you have to return matrices from
  functions, and you have recursive functions, so global matrices won't
  work.  You need to convert your matrices (which are all square
  matrices) into a structure such as:

      struct Matrix
      {
          int     size;
          float **data;
      };

  Your existing two global arrays of pointers to `float` should be
  replaced — otherwise, you'll need special code to release the memory
  allocated to them.

* In `main()` you have:

      float** C = matrix_create(N);
      …
      C = strassen_multiply(A, B, N);

   so you're leaking a full-size matrix.

* The functions returning a matrix will return a matrix structure, and
  the ones that take two matrix arguments will be taking two pointers to
  (constant) matrix structures as arguments.  The outlined matrix
  structure is so small there isn't a benefit to returning a pointer to
  a matrix structure.

* In your current code for `main()`, you should have:

      float **A = matrix_create(N);
      float **B = matrix_create(N);

  Your matrix `C` in the main() should be created with:

      float **C = strassen_multiply(A, B, N);

  The matrix `C` never was global.

* Use `matrix_create()` as you do now.  Just remember to free the
  returned value in the function that calls `add()` or `sub()`, which
  also means you'll need to save those intermediate results in local
  variables so that you can free them.

* You're using global variables `i`, `j`, `k` for your array indices.
  All hell is going to break loose.  Array indices must be local
  variables, especially if you use recursion.

* That means you have to declare loop variables in each function. You should write

      for (int i = 0; i < n; i++)

   or equivalent for each loop.  This will be more efficient than using
   global variables; it also gives your code a better chance of being
   correct.  As it stands, you've not got the slightest chance of the
   code being correct.

## Prescription

Putting those points together yields code like this:

    #include <assert.h>
    #include <errno.h>
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/time.h>

    #ifndef N
    #define N 128
    #endif

    typedef struct Matrix
    {
        int    size;
        float **data;
    } Matrix;

    static int count = 0;
    static size_t cnt_create = 0;
    static size_t cnt_destroy = 0;
    static size_t cnt_add = 0;
    static size_t cnt_sub = 0;

    static void err_nomemory(const char *file, const char *func, int line, size_t size)
    {
        fprintf(stderr, "%s:%s():%d: out of memory attempting to allocate %zu bytes "
                "(%d: %s)\n", file, func, line, size, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    static void matrix_destroy(Matrix *M)
    {
        cnt_destroy++;
        for (int i = 0; i < M->size; i++)
            free(M->data[i]);
        free(M->data);
    }

    static Matrix matrix_create(int n)
    {
        cnt_create++;
        Matrix M = { .size = n, .data = malloc(n * sizeof(float *)) };
        if (M.data == NULL)
            err_nomemory(__FILE__, __func__, __LINE__, n * sizeof(float *));
        for (int i = 0; i < n; i++)
        {
            if ((M.data[i] = (float *)malloc(n * sizeof(float))) == NULL)
                err_nomemory(__FILE__, __func__, __LINE__, n * sizeof(float));
        }
        return M;
    }

    static Matrix add(const Matrix *M1, const Matrix *M2)
    {
        cnt_add++;
        assert(M1->size == M2->size);
        Matrix M3 = matrix_create(M1->size);
        for (int i = 0; i < M1->size; i++)
        {
            for (int j = 0; j < M1->size; j++)
                M3.data[i][j] = M1->data[i][j] + M2->data[i][j];
        }

        return M3;
    }

    static Matrix sub(const Matrix *M1, const Matrix *M2)
    {
        cnt_sub++;
        assert(M1->size == M2->size);
        Matrix M3 = matrix_create(M1->size);
        for (int i = 0; i < M1->size; i++)
        {
            for (int j = 0; j < M1->size; j++)
                M3.data[i][j] = M1->data[i][j] - M2->data[i][j];
        }

        return M3;
    }

    static void matrix_print(const char *tag, const Matrix *M)
    {
        printf("%s (%dx%d):\n", tag, M->size, M->size);
        if (M->size > 128)
        {
            printf("Printing suppressed - matrix too large\n");
            return;
        }
        char buffer[32];
        int len = snprintf(buffer, sizeof(buffer), "%d", M->size);
        for (int i = 0; i < M->size; i++)
        {
            printf("[%*d]: ", len, i);
            const char *pad = "";
            for (int j = 0; j < M->size; j++)
            {
                printf("%s%f", pad, M->data[i][j]);
                pad = "\t";
            }
            printf("\n");
        }
    }

    static Matrix strassen_multiply(const Matrix *A, const Matrix *B)
    {
        assert(A->size == B->size);
        if (A->size == 1)
        {
            Matrix C = matrix_create(A->size);
            C.data[0][0] = A->data[0][0] * B->data[0][0];
            return C;
        }
        count++;
        Matrix C = matrix_create(A->size);
        int k = A->size / 2;
        /** Creating sub matrices**/
        Matrix A11 = matrix_create(k);
        Matrix A12 = matrix_create(k);
        Matrix A21 = matrix_create(k);
        Matrix A22 = matrix_create(k);
        Matrix B11 = matrix_create(k);
        Matrix B12 = matrix_create(k);
        Matrix B21 = matrix_create(k);
        Matrix B22 = matrix_create(k);

        /** Dividing the Data Matrices A & B **/
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                A11.data[i][j] = A->data[i + 0][j + 0];
                A12.data[i][j] = A->data[i + 0][k + j];
                A21.data[i][j] = A->data[k + i][j + 0];
                A22.data[i][j] = A->data[k + i][k + j];
                B11.data[i][j] = B->data[i + 0][j + 0];
                B12.data[i][j] = B->data[i + 0][k + j];
                B21.data[i][j] = B->data[k + i][j + 0];
                B22.data[i][j] = B->data[k + i][k + j];
            }
        }

        Matrix T1 = sub(&B12, &B22);
        Matrix P1 = strassen_multiply(&A11, &T1);
        matrix_destroy(&T1);

        Matrix T2 = add(&A11, &A12);
        Matrix P2 = strassen_multiply(&T2, &B22);
        matrix_destroy(&T2);

        Matrix T3 = add(&A21, &A22);
        Matrix P3 = strassen_multiply(&T3, &B11);
        matrix_destroy(&T3);

        Matrix T4 = sub(&B21, &B11);
        Matrix P4 = strassen_multiply(&A22, &T4);
        matrix_destroy(&T4);

        Matrix T5A = add(&A11, &A22);
        Matrix T5B = add(&B11, &B22);
        Matrix P5 = strassen_multiply(&T5A, &T5B);
        matrix_destroy(&T5A);
        matrix_destroy(&T5B);

        Matrix T6A = sub(&A12, &A22);
        Matrix T6B = add(&B21, &B22);
        Matrix P6 = strassen_multiply(&T6A, &T6B);
        matrix_destroy(&T6A);
        matrix_destroy(&T6B);

        Matrix T7A = sub(&A11, &A21);
        Matrix T7B = add(&B11, &B12);
        Matrix P7 = strassen_multiply(&T7A, &T7B);
        matrix_destroy(&T7A);
        matrix_destroy(&T7B);

        matrix_destroy(&A11);
        matrix_destroy(&A12);
        matrix_destroy(&A21);
        matrix_destroy(&A22);
        matrix_destroy(&B11);
        matrix_destroy(&B12);
        matrix_destroy(&B21);
        matrix_destroy(&B22);

        Matrix C1A = add(&P5, &P4);
        Matrix C1B = add(&C1A, &P6);
        Matrix C11 = sub(&C1B, &P2);
        Matrix C12 = add(&P1, &P2);
        Matrix C21 = add(&P3, &P4);
        Matrix C2A = add(&P5, &P1);
        Matrix C2B = sub(&C2A, &P3);
        Matrix C22 = sub(&C2B, &P7);
        matrix_destroy(&C1A);
        matrix_destroy(&C1B);
        matrix_destroy(&C2A);
        matrix_destroy(&C2B);

        matrix_destroy(&P1);
        matrix_destroy(&P2);
        matrix_destroy(&P3);
        matrix_destroy(&P4);
        matrix_destroy(&P5);
        matrix_destroy(&P6);
        matrix_destroy(&P7);

        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                C.data[i + 0][j + 0] = C11.data[i][j];
                C.data[i + 0][j + k] = C12.data[i][j];
                C.data[k + i][j + 0] = C21.data[i][j];
                C.data[k + i][k + j] = C22.data[i][j];
            }
        }

        matrix_destroy(&C11);
        matrix_destroy(&C12);
        matrix_destroy(&C21);
        matrix_destroy(&C22);

        return C;
    }

    int main(void)
    {
        struct timeval begin, end;
        Matrix A = matrix_create(N);
        Matrix B = matrix_create(N);

        for (int i = 0; i <  N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A.data[i][j] = -1.0 + 2.0 * ((double)rand()) / RAND_MAX;
                B.data[i][j] = -1.0 + 2.0 * ((double)rand()) / RAND_MAX;
            }
        }

        gettimeofday(&begin, 0);
        Matrix C = strassen_multiply(&A, &B);
        gettimeofday(&end, 0);

        matrix_print("A", &A);
        matrix_print("B", &B);
        matrix_print("C", &C);

        matrix_destroy(&A);
        matrix_destroy(&B);
        matrix_destroy(&C);

        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds + microseconds * 1e-6;

        printf("Number of non-minimal recursive calls: %d\n", count);
        printf("Number of matrices created:    %zu\n", cnt_create);
        printf("Number of matrices destroyed:  %zu\n", cnt_destroy);
        printf("Number of matrix additions:    %zu\n", cnt_add);
        printf("Number of matrix subtractions: %zu\n", cnt_sub);
        printf("Total wall time: %f\n", elapsed);
        return 0;
    }

This cheats on detecting the memory allocation errors by calling a
function that simply exits, rather than freeing any successfully
allocated memory and returning to the caller.

The code can be compiled with `-DN=256` or any other power of two.  It
isn't clear what would happen if the size is not a power of 2.

## Performance

Some sample times and other statistics for various sizes:

### N=8
``` none
Number of non-minimal recursive calls: 57
Number of matrices created:    1884
Number of matrices destroyed:  1884
Number of matrix additions:    627
Number of matrix subtractions: 399
Total wall time: 0.000480
```
### N=16
``` none
Number of non-minimal recursive calls: 400
Number of matrices created:    13203
Number of matrices destroyed:  13203
Number of matrix additions:    4400
Number of matrix subtractions: 2800
Total wall time: 0.003723
```
### N=32
``` none
Number of non-minimal recursive calls: 2801
Number of matrices created:    92436
Number of matrices destroyed:  92436
Number of matrix additions:    30811
Number of matrix subtractions: 19607
Total wall time: 0.025097
```
### N=64
``` none
Number of non-minimal recursive calls: 19608
Number of matrices created:    647067
Number of matrices destroyed:  647067
Number of matrix additions:    215688
Number of matrix subtractions: 137256
Total wall time: 0.161971
```
### N=128
``` none
Number of non-minimal recursive calls: 137257
Number of matrices created:    4529484
Number of matrices destroyed:  4529484
Number of matrix additions:    1509827
Number of matrix subtractions: 960799
Total wall time: 1.164555
```
### N=256
``` none
Number of non-minimal recursive calls: 960800
Number of matrices created:    31706403
Number of matrices destroyed:  31706403
Number of matrix additions:    10568800
Number of matrix subtractions: 6725600
Total wall time: 7.632881
```
### N=512
``` none
Number of non-minimal recursive calls: 6725601
Number of matrices created:    221944836
Number of matrices destroyed:  221944836
Number of matrix additions:    73981611
Number of matrix subtractions: 47079207
Total wall time: 53.730002
```
### N=1024
``` none
Number of non-minimal recursive calls: 47079208
Number of matrices created:    1553613867
Number of matrices destroyed:  1553613867
Number of matrix additions:    517871288
Number of matrix subtractions: 329554456
Total wall time: 373.596480
```
### N=2048
``` none
Number of non-minimal recursive calls: 329554457
Number of matrices created:    10875297084
Number of matrices destroyed:  10875297084
Number of matrix additions:    3625099027
Number of matrix subtractions: 2306881199
Total wall time: 2737.750096
```

Note that the number of matrices created is the same as the number
destroyed; that's reassuring.  Note too that there are massive numbers
of matrices created and destroyed.

However, doubling the size of the matrices being multiplied is not
giving a cubic time; it is better than O(N³), whereas the naïve
algorithm is O(N³).

## Improving Performance

One way to improve the speed of the code is to special-case 2x2 matrix
multiplication.  When implemented, that gave results like:

### N=16
``` none
Number of large multiplications: 57
Number of 1x1 multiplications:   0
Number of 2x2 multiplications:   343
Number of matrices created:      1884
Number of matrices destroyed:    1884
Number of matrix additions:      627
Number of matrix subtractions:   399
Total wall time: 0.001045
```
### N=32
``` none
Number of large multiplications: 400
Number of 1x1 multiplications:   0
Number of 2x2 multiplications:   2401
Number of matrices created:      13203
Number of matrices destroyed:    13203
Number of matrix additions:      4400
Number of matrix subtractions:   2800
Total wall time: 0.006532
```
### N=64
``` none
Number of large multiplications: 2801
Number of 1x1 multiplications:   0
Number of 2x2 multiplications:   16807
Number of matrices created:      92436
Number of matrices destroyed:    92436
Number of matrix additions:      30811
Number of matrix subtractions:   19607
Total wall time: 0.038640
```
### N=128
``` none
Number of large multiplications: 19608
Number of 1x1 multiplications:   0
Number of 2x2 multiplications:   117649
Number of matrices created:      647067
Number of matrices destroyed:    647067
Number of matrix additions:      215688
Number of matrix subtractions:   137256
Total wall time: 0.263008
```
### N=256
``` none
Number of large multiplications: 137257
Number of 1x1 multiplications:   0
Number of 2x2 multiplications:   823543
Number of matrices created:      4529484
Number of matrices destroyed:    4529484
Number of matrix additions:      1509827
Number of matrix subtractions:   960799
Total wall time: 1.796228
```
### N=512
``` none
Number of large multiplications: 960800
Number of 1x1 multiplications:   0
Number of 2x2 multiplications:   5764801
Number of matrices created:      31706403
Number of matrices destroyed:    31706403
Number of matrix additions:      10568800
Number of matrix subtractions:   6725600
Total wall time: 12.383302
```

For comparison, the number of matrices created and destroyed with the
1x1 and 2x2 special cases is:

      N            1x1           2x2
     16         13,203         1,884
     32         92,436        13,203
     64        647,067        92,436
    128      4,528,484       647,067
    256     31,706,403     4,529,484
    512    221,944,836    31,706,403

Observe that the number of matrices created for with the 1x1 minimum
case for multiplying NxN matrices is the same as for the 2x2 minimum
case with 2Nx2N matrices.  It also provides a fairly dramatic speed-up
(c.f. 53.73 seconds for N=512 with 1x1 versus 12.38 seconds for N=512
with 2x2).  A lot of the original cost is in creating 1x1 matrices to
multiply together.

## Other recommendations

[Unslander Monica](https://chat.stackoverflow.com/users/1329652/unslander-monica) [suggested](https://chat.stackoverflow.com/transcript/message/51068700#51068700):

> Sub-matrices should be copied only when they are used a lot — to
> improve cache locality.  Otherwise, a "sub matrix" is not a variable,
> but a concept.  That means that when you do any matrix operation, you
> should be passing some object that describes the range of indices, and
> the index stride, e.g. to matrix multiplication.  That way you won't
> be creating those sub-matrices.  In general, there's lots to be done
> to make this code reasonable.

This would make the matrix structures more complex, but would also
radically improve performance.  You'd probably end up with
`matrix_create()` returning a `Matrix *`, and the structure would
contain extra elements: `int tl_r; int tl_c; int br_r; int br_c;`
(top-left row and column, bottom-left row and column).  You'd have
another function to split a matrix into 4 quarter matrices, which would
all reference the data of the unsplit matrix but with different values
for the top-left and bottom-right coordinates of the sub-matrix.  If you
continue with the current array of pointers to arrays of floats
organization, you don't need to record the 'stride' (the width of each
row in the original array, which is also the height since this deals
only with square matrices).  You'd have to be careful with the memory
management.  Result arrays would be created afresh.  You won't be
releasing the data from quarter matrices — only from those created
afresh.

[Asteroids With Wings](https://chat.stackoverflow.com/users/4386278/asteroids-with-wings) [commented](https://chat.stackoverflow.com/transcript/message/51068688#51068688):

> Why do you use arrays of pointers for square arrays?  That's a lot of
> overhead for no reason.  Just create an array of N*N floats!  Then you
> can start simplifying all this crazy memory management.

And there is some justice in that, though care would be required.  I
still think you'd be using a structure, but the data element would be
`float *` instead of `float **`, and you'd compute the array indexes
(`row * width + col`) instead of using two subscripts.  If you forego
structures, you might be able to use 'variable length array' (VLA)
notation instead.  Care would be required.  The arrays would still be
dynamically allocated.

## Further experiments and Suggestions

I've experimented with both 4x4 and 8x8 special cases, and both provide
considerable benefit because of the reduced memory management overhead
(many fewer matrix allocations and destructions).  Multiplying 1024x1024
matrices with different minimum sizes gives:

    Size    Time        #Matrices
    1x1   6m 32s    1,553,613,867
    2x2   1m 31s      221,944,836
    4x4      23s       31,706,403
    8x8       7s        4,529,484

I also coded a version that does a straight-forward raw matrix
multiplication (O(N³) algorithm — using the same code as I used for
8x8 multiplication for NxN), and it is quite a bit faster than the
Strassen algorithm, mainly because there's almost no memory management
required.

    Size             Time
    128x128           3ms
    256x256          25ms
    512x512         280ms
    1024x1024     1,802ms
    2048x2048    84,686ms
    4096x4096   850,860ms

Note that the time multiplication between 1.80s at 1024 and 84.7s at
2048 is bigger than a cubic relation (a factor of 8 that more or less
applies otherwise) — I've not investigated the cause.

I think the key to speeding up from here is not copying matrices —
using what Unslander Monica suggested.  I note that you probably don't
need 4 coordinates as I suggested earlier; 2 coordinates and the size
are sufficient (because the matrices are all square).  That reduces the
copying as well as the memory allocation — that will have a major
benefit on performance.

I don't think Strassen is proved a failure yet.  I think it shows that
the naïve memory management you (we) are using is not the way to go.
But I also think that unless your matrices are bigger than 1024x1024, it
is likely that the naïve multiplication algorithm is probably
sufficiently fast.  If you must deal with big arrays, then the Strassen
algorithm may be beneficial.  More coding and testing needed!

