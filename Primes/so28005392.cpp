/*
** SO 28005392
**
** Given a file such as:
** 3
** 5 15 2
** 2 10 1
** 24 42 3
**
** the output should be like this
**
** 5
** 7
** 2
**
** The first number is the number of entries to process.
** Each entry is on a single line.  It consists of a triple a, b, c.
** The output should be the count of the numbers in the inclusive range
** [a, b] that have c distinct prime factors.
**
** For the first row, 5 has 1, 6 has 2, 7 has 1, 8 has 1, 9 has 1, 10
** has 2, 11 has 1, 12 has 2, 13 has 1, 14 has 2, 15 has 2, so {6, 10,
** 12, 14, 15} are the numbers, and the count is 5.
**
** For the second row, 2 has 1, 3 has 1, 4 has 1, 5 has 1, 6 has 2, 7
** has 1, 8 has 1, 9 has 1, 10 has 2, so the matching numbers are {2, 3,
** 4, 5, 7, 8, 9} for a count of 7.
**
** Similarly, for the third row, 30 and 42 both have 3; everything else
** has fewer, so the output is 2.
**
** The constraints are the the values in a, b will be in the range 2 to
** 10,000,000.  The value of c will clearly be much smaller; the maximum
** number of distinct prime factors in a value up to 10M is 2 * 3 * 5 *
** 7 * 11 * 13 * 17 * 19 = 9,699,690
**
** ********************************************************************
**
** Solution:
**
** Generate a list of primes and a list of the number of prime factors.
** Assume 20 MiB memory is not a problem (don't assume it fits on the stack though).
**
*/

#include <cassert>
#include <cstdint>
#include <iostream>
using namespace std;

namespace {

const int MAX_NUMBER = 10000000;
const int MAX_PRIMES = 670000;

static uint8_t factors[MAX_NUMBER+1];
static uint8_t sieve[MAX_NUMBER+1];
uint32_t primes[MAX_PRIMES];
int n_primes = 0;

#if 0
int num_unique_prime_factors(int n)
{
    int count = 0;
    //cout << "-->> " << __func__ << ": n = " << n << "\n";
    for (int i = 0; n > 1 && i < n_primes; i++)
    {
        //cout << __func__ << ": p[" << i << "] = " << primes[i] << ", n = " << n << "\n";
        if (n % primes[i] == 0)
        {
            count++;
            do {
                n /= primes[i];
            } while (n % primes[i] == 0);
        }
        //cout << __func__ << ": count = " << count << ", n = " << n << "\n";
    }
    //cout << "<<-- " << __func__ << ": count = " << count << "\n";
    return count;
}
#endif

static inline void mark_multiples(int n)
{
    for (int i = n + n; i <= MAX_NUMBER; i += n)
    {
        sieve[i] = 1;
        factors[i]++;
    }
}

void build_tables()
{
    factors[0] = 0;
    factors[1] = 1;
    for (int i = 2; i <= MAX_NUMBER; ++i)
    {
        if (i % 100000 == 0) cerr << "." << flush;
        if (i % 1000000 == 0) cerr << "\n";
        if (sieve[i] == 0)
        {
            primes[n_primes++] = i;
            mark_multiples(i);
            factors[i] = 1;
        }
        #if 0
        else
            factors[i] = num_unique_prime_factors(i);
        #endif
    }
    assert(n_primes < MAX_PRIMES);
}

int factor_count(int a, int b, int c)
{
    int count = 0;
    for (int i = a; i <= b; i++)
    {
        if (factors[i] == c)
            count++;
    }
    return count;
}

} // Anonymous namespace

int main()
{
    build_tables();
    int n_triples;
    cin >> n_triples;
    for (int i = 0; i < n_triples; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a < 0 || a > MAX_NUMBER || b < 0 || b > MAX_NUMBER || c < 0 || c > MAX_NUMBER)
        {
            cerr << "Bogus triple: (" << a << "," << b << "," << c << ")\n";
            return 1;
        }
        cout << "(" << a << "," << b << "," << c << ") = " << factor_count(a, b, c) << "\n";
    }

    return 0;
}
