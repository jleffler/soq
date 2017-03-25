/* Basis for C Documentation example on SO */
#include <stdio.h>

#define min(x, y) _Generic((x) + (y), \
                        long double: min_ld, \
                        double: min_d, \
                        float: min_f, \
                        unsigned long long: min_ull, \
                        long long: min_ll, \
                        unsigned long: min_ul, \
                        long: min_l, \
                        unsigned: min_u, \
                        default: min_i \
                        )(x, y)

#define gen_min(suffix, type) \
    static inline type min_##suffix(type x, type y) { printf("%8s: ", __func__); return (x < y) ? x : y; }

gen_min(ld, long double)
gen_min(d, double)
gen_min(f, float)
gen_min(ull, unsigned long long)
gen_min(ll, long long)
gen_min(ul, unsigned long)
gen_min(l, long)
gen_min(u, unsigned)
gen_min(i, int)

int main(void)
{
    unsigned long long ull1 = 50ULL;
    unsigned long long ull2 = 37ULL;
    printf("min(%llu, %llu) = %llu\n", ull1, ull2, min(ull1, ull2));
    long double ld1 = 3.141592653L;
    long double ld2 = 3.141592652L;
    printf("min(%.10Lf, %.10Lf) = %.10Lf\n", ld1, ld2, min(ld1, ld2));
    int i1 = 3141653;
    int i2 = 3141652;
    printf("min(%d, %d) = %d\n", i1, i2, min(i1, i2));
    float f1 = 93141652.0;
    double d2 = 93141652.0;
    printf("min(%f, %f) = %f\n", f1, d2, min(f1, d2));
    printf("min(%f, %f) = %f\n", d2, f1, min(d2, f1));
    return 0;
}
