/*
** Based on Andrew Koenig's article "Comparing an Integer with a
** Floating-Point Number, Part 2: Tactics" dated March 15, 2013.
** http://www.drdobbs.com/cpp/comparing-an-integer-with-a-floating-poi/240150886
*/

#include <assert.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>

typedef long Int;
typedef long unsigned Unsigned;
typedef float Float;

/*
** We're using Int and Float to refer to the integer and floating-point
** types that we're comparing, and Unsigned to refer to the unsigned
** type that corresponds to Int.  We intend to be able to use any
** integer and any floating-point type here, so long as Unsigned is the
** appropriate unsigned type.
**
** Last week, we talked about a magic number B that is a power of 2 with
** the property that integers greater than B cannot always be
** represented exactly as floating-point numbers.  We know that we're
** going to have to compute that number at some point, so let's define a
** function to do so.
**
** This function computes B both as a floating-point value and as an
** unsigned integer.  Depending on the machine, the integer value might
** overflow; we shall signal that case by an unsigned value of zero.
**
** First we define a structure to hold the results:
*/

typedef struct B_t      /* C++ vs C */
{
    Unsigned u;
    Float f;
} B_t;

/* Now we can write the actual function: */

static B_t compute_B(void)
{
    B_t result = { 1, 1.0 };
    while (true)
    {
        Float b = result.f + 1;
        if (b == result.f)
        {
            b = result.f - 1;
            assert (b != result.f);
            return result;
        }
        result.f *= 2;
        result.u *= 2;
    }
    /*NOTREACHED*/
}

/*
** This function returns the smallest power of 2, f, with the property
** that f+1 cannot be distinguished from f, along with the unsigned
** version of the same value (or 0 if that unsigned value overflows).
** Because f is a power of 2, f-1 has one less significant bit than f,
** and therefore f and f-1 should be distinct.  If they're not, the
** floating-point system is doing something beyond our capacity to
** accommodate; hence the assert.
**
** We compare f with f+1 by putting f+1 in a separate variable.
** Otherwise, it is possible that the implementation will compute f+1
** with more precision than a Float variable would have.  If we are
** trying to do precise computations on floating-point numbers, we must
** watch out for well-intentioned but inappropriate optimizations from
** our compilers.
**
** Now we can start defining the comparison function proper:
*/

extern int compare(Float X, Int N);

int compare(Float X, Int N)
{
    /*
    ** We have made the arbitrary decision that the first operand is
    ** floating-point and the second is integer.  Our function will
    ** return an integer that follows the strcmp convention: A negative
    ** value means that X < N, a positive value means that X > N, and
    ** zero means that X == N.  If, for some reason, we want to compare
    ** the operands in the opposite order, we simply swap them and
    ** invert the sign of the result.
    **
    ** Our first job is to deal with the numbers' signs.  We begin by
    ** handling the easy case in which they have opposite signs:
    */

    if (X < 0 && N >= 0)
        return -1;
    if (X >= 0 && N < 0)
        return 1;

    /*
    ** Now we know that both numbers have the same sign.  If that sign
    ** is negative, we'll remember that fact and make both numbers
    ** positive.  Either way, we will wind up with an unsigned version
    ** of |N| in U:
    */

    bool neg = X < 0;
    Unsigned U;
    if (neg)
    {
        X = -X;
        U = -(N + 1);
        ++U;
    }
    else
        U = N;

    /*
    ** The assignments to U are needed because it is possible — and,
    ** on most computers, likely — that the most negative integer has
    ** no signed positive integer that corresponds to it.  Because an
    ** unsigned integer has one more bit than the corresponding signed
    ** integer, an unsigned integer can accommodate the absolute value
    ** of any corresponding signed integer — but it is necessary to
    ** compute that absolute value without directly computing a signed
    ** integer that might overflow.
    **
    ** In the case where N is negative, we solve this problem by first
    ** computing N + 1 — which has an absolute value of |N| - 1 —
    ** and putting the inverse of that value in U.  When we then
    ** increment U, we get |N| without ever having had to compute |N| as
    ** a signed integer.
    **
    ** At this point, the positive versions of the two numbers that we
    ** are comparing are in X and U.  If U is less than B, we can safely
    ** convert U to floating-point for comparison.  In order to find out
    ** whether U is less than B, we must compute B if needed:
    */

    /*static*/ B_t B = compute_B();     /* C++ */

    /*
    ** By saying static in the definition of B, we ensure that we will
    ** execute compute_B only the first time compare is ever called.
    ** Now we can check whether U is less than B; if so, we can do the
    ** comparison in floating-point:
    */

    if (B.u == 0 || U < B.u)
    {
        int result = X > U ? 1 : X < U ? -1 : 0;
        return neg ? -result : result;
    }

    /*
    ** At this point we have handled the case where U can be accurately
    ** converted to floating-point, so we know that U >= B.  If X is
    ** less than the floating-point version of B, we know the result:
    */

    if (X < B.f)
        return neg ? 1 : -1;

    /*
    ** The point is that because we already know that U >= B, we can
    ** avoid comparison entirely if X < B.  If this return statement is
    ** not executed, then we know that X >= B.  In this case, either X
    ** is greater than the largest possible value of type Unsigned, or
    ** we can safely convert X to Unsigned for the comparison.  So:
    */
    const Float Too_big_for_Unsigned = (1 << FLT_MANT_DIG);

    if (X >= Too_big_for_Unsigned)
        return neg? -1 : 1;
    Unsigned Uns_X = X;
    int result = Uns_X > U ? 1 : Uns_X < U ? -1: 0;
    return neg ? -result : result;
}

/*
** There are still three tasks to accomplish in writing this function.
**
** First is the definition of Too_big_for_Unsigned.  It is easy enough
** to compute the largest possible value of type Unsigned by writing
** Unsigned(0)-1, but in order to ensure an accurate comparison in the
** floating-point domain, we would like that value as a floating-point
** number.  Because this number is a power of two, it is not
** particularly hard to compute.
**
** Once we have complete code that we can execute, we need to write test
** cases.  Normally, I would say that we should write the test cases
** first; but in this example, we know that the most interesting test
** cases will be at or near values that depend on the program itself.
** In fact, I will argue that this is one of those odd programs that is
** almost impossible to test thoroughly without knowing how it works.
**
** Finally, there are several places, notably involving the use of neg,
** in which the code can probably be made significantly shorter and
** perhaps even cleaner.  We realized early in the coding that it would
** be useful to fold the possibility of negative values into the code;
** once we see how the whole thing works — but not before then — we
** can probably fold it slightly differently and streamline the code in
** doing so.
**
** I am going to leave these last three tasks — defining that last
** variable; testing the code; and cleaning it up — as exercises.
*/

