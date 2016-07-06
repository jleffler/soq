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
**
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
** 10,000,000.
**
** The value of c will clearly be much smaller; the maximum number of
** distinct prime factors in a value up to 10M is 8 (based on the value
** 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 = 9,699,690).  Indeed, 8 is also
** the maximum for 100M as the first number with 9 unique prime factors
** is 223,092,870; the first with 10 is 6,469,693,230; and the first
** with 11 is 200,560,490,130.
**
** ********************************************************************
**
** Solution:
**
** Generate a list of primes and a list of the number of prime factors.
** Assume 10 MiB memory is not a problem (don't assume it fits on the
** stack though).
**
** The Sieve of Eratosthenes allows you to calculate the number of
** unique prime factors on the fly.  As you mark multiples, increment
** the value (because it's a new prime number you're marking with).
*/

#include <cstdint>
#include <iostream>
using namespace std;

namespace {

//const int MAX_NUMBER = 10000000;
// Up to 1E8 - 10 times the maximum stated in the specification.
const int MAX_NUMBER = 100000000;

uint8_t factors[MAX_NUMBER+1];

inline void mark_multiples(int n)
{
    for (int i = n; i <= MAX_NUMBER; i += n)
    {
        factors[i]++;
    }
}

void build_tables()
{
    factors[0] = 0;
    factors[1] = 1;
    for (int i = 2; i <= MAX_NUMBER; ++i)
    {
        if (factors[i] == 0)
            mark_multiples(i);
    }
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
