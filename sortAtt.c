#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void isort(int a[], int n)
{
    int i, j, val;
	
    for(i=1; i<n; i++)
    {
        j=i-1;
        val = a[i];
        while(j >= 0 && a[j] > val)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = val;
		
    }
}

void ssort(int a[], int n)
{
    int i, j, small, temp;
	
    for (i = 0; i < n-1; i++)
    {
        small = i;
        for (j = i+1; j < n; j++)
            if (a[j] < a[small])
                small = j;
        temp = a[small];
        a[small] = a[i];
        a[i] = temp;
    }
}


void msort_intR(int a[], int lo, int hi, int scratch[]) {
	int i, j, k, m;
	
	if(lo >= hi)
		return;
	m = (lo + hi)/2;
	msort_intR(a, lo, m, scratch);
	msort_intR(a, m+1, hi, scratch);
	
	i=lo;  // lhs index
	j=m+1; // rhs index
	k=0;   // index into scratch
	
	while(i <= m && j <= hi) {
		if(a[i] < a[j]){
			scratch[k] = a[i];
			i++;
		}
		else{
			scratch[k] = a[j];
			j++;
		}
		k++;
	}
	while(i <= m) {
		scratch[k] = a[i];
		i++;
		k++;
	}
	while(j <= hi) {
		scratch[k] = a[j];
		j++;
		k++;
	}
	for(k=0, i=lo; i<=hi; i++, k++) {
		a[i] = scratch[k];
	}
	
	
	
}
void msort_int(int a[], int n) {
    int *scratch;
    scratch = (int *)malloc(n * sizeof(int));
	
    msort_intR(a, 0, n-1, scratch);
    free(scratch);
}


/** \brief Implementation of merge sort algorithm for sorting generic
 *     data a la qsort library function.
 *
 * \param base is the base address of the array being sorted
 * \param n is the number of elements in the array
 * \param size is the size of an individual
 * \return
 *
 */
//void msort(void *base, size_t n, size_t size,
//int (*cmp)(const void *, const void *)){
//}

//int intcmp(const void *a, const void *b)
//{
//return (*(int*)a - *(int*)b);
//}

//void print_points(int base[], int n){
//int i;

//for(i=0; i<n; i++){
//printf("%f\n", base[i]);
//}
//}



/*void msort (void *base, size_t nmemb, size_t size,
 int (*fcmp) (const void *, const void *))
 {
 void *tmp;
 
 if (nmemb < 2)
 return;
 
 if (!(tmp = malloc (nmemb * size)))
 return;
 
 msort (base, nmemb - 1, size, fcmp);
 
 free (tmp);
 }*/

/*void msort(void *base, size_t n, size_t size,
 int (*cmp)(const void *, const void *)){
 
 void *temp;
 
 temp = malloc(size * n);
 free(temp);
 (void) msort(base, n, size, fcmp);
 
 }*/

int cmp (const void *v1, const void *v2)
{
	int x = *(int*) v1;
	int y = *(int*) v2;
    
    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

/*void msort (
			void *b,
			size_t n,
			size_t s,
			int(*cmp)(const void*,const void*))
{
	void *a;
	void *b;
	
	
}*/


static void msort(void *b, size_t n, size_t s, int (*cmp)(const void *v1, const void *v2) )
{
    if (n <= 1)
        return;     /* Already sorted */
	
    printf("-->> msort(%zu)\n", n);
    void *t = malloc(s*n);
	
    if (t == NULL)
    {
        fprintf(stderr, "Error: No Memory.\n");
        printf("<<-- msort(%zu)\n", n);
        return;
    }
	
    size_t n1 = n / 2;
    size_t n2 = n - n1;
	
    if (n2 <= n1)
    {
        fprintf(stderr, "Oops: %zu <= %zu\n", n2, n1);
        free(t);
        printf("<<-- msort(%zu)\n", n);
        return;
    }
	
    char *b1 = b;
    char *b2 = (char *) b + (n1 * s);
	
    msort(b1, n2, s, cmp);
    msort(b2, n1+1, s, cmp);
	
    char *tmp = t;
	
    while (n1 > 0 && n2 > 0)
    {
        if ((*cmp)(b1, b2) <= 0)
        {
            memcpy(tmp, b1, s);
            tmp += s;
            b1 += s;
            --n1;
        }
        else
        {
            memcpy(tmp, b2, s);
            tmp += s;
            b2 += s;
            --n2;
        }
    }
    if (n1 > 0)
        memcpy(tmp, b1, n1 * s);
    memcpy(b, t, (n - n2) * s);
    free(t);
    printf("<<-- msort(%zu)\n", n);
}

int * gen_int_array(int n, int max_val) {
	int i;
	int *a = malloc(n*sizeof(int));
	for(i=0; i<n; i++){
		a[i] = rand() % max_val;
	}
	return a;
}

int * clone_int_array(int *a, int n){
	int *b = (int *)malloc(n * sizeof(int));
	int i;
	for(i=0; i<n; i++)
		b[i] = a[i];
	return b;
}


void dump_int_array(int *a, int n) {
	int i;
	for(i=0; i<n; i++)
		printf("  %d\n", a[i]);
}

int main()
{
    int n;
    int *a, *b, *c;
	
    printf("enter n: ");
    if(scanf("%d", &n) != 1 || n < 10)
    {
        fprintf(stderr, "bad input.  goodbye\n");
        abort();
    }
	
    printf("sizeof(double) %d\n", sizeof(double) );
	
    printf("running experiments with n=%d\n", n);
	
    a = gen_int_array(n, 5000);
    //b = clone_int_array(a, n);
    //c = clone_int_array(a, n);
	
	d = clone_int_array(a, n);
    //ssort(a, n);
    //isort(b, n);
    //msort_int(c, n);
	
	//msort_int(d, n);
	
	msort (d, n, sizeof(int), cmp );
	//qsort (d, n, sizeof(int), cmp);
    //print_points(c, 5);
	
	if(n<50)
        dump_int_array(d, n);
	
    free(a);
    free(b );
    free(c);
	

	
    //if(n<50)
	//dump_int_array(c, n);
	//if(n<50)
	//dump_int_array(d, n);	
	
}

