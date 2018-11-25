/* SO 1487-8356: Efficiently calculate leap days */
/*
** I'm using the following function to calculate the number of leap days
** between two years:
**
** static int CountLeapDays(int startYear, int endYear)
** {
**     int Days = 0;
**
**     while (true)
**     {
**         if ((startYear % 4 == 0 && startYear % 100 != 0) || startYear % 400 == 0)
**             Days++;
**         if (startYear + 1 == endYear) break;
**         startYear++;
**     }
**
**     return Days;
** }
**
** Is there another way to write this so it doesn't need to loop?
**
************************************************************************
**
** Q: Supposing the inputs are 2000 and 2012; there were 4 leap years in
**    that period (2000, 2004, 2008, 2012).  Is that the answer you
**    want?  It treats things as though the first date is 1st Jan
**    [start] and the last 31st Dec [end], as a sweeping generality.
**    OTOH, between 1999 and 2011, there were only 3 leap years, even
**    though there was a gap of 12 years, just the same.  And between
**    1997 and 2015, there were 4 leap years.
**
** A: It should only count the leap days in between the two years, so
**    first date is 31st Dec [start] and last date is 1st Jan [end].
**
** Q: So if the first year is the same as the last year, the answer is
**    zero.  If the first year is after that last year, should that be
**    an error, zero, or something else?
**
** A: Correct!  And it doesnt need to give an error, I handle input
**    validation at a higher level.
*/

/*
** Count the number of   4-year     leap years.
** Count the number of 100-year non-leap years.
** Count the number of 400-year     leap years.
**
** Switchover between 20th and 21st centuries: 2000 was a leap year.
** Early        Later year
**       1996 1997 1998 1999 2000 2001 2002 2003 2004 2005 2006 2007 2008 2009
** 1996    0     0    0    0    0    1    1    1    1    2    2    2    2    3
** 1997    -     0    0    0    0    1    1    1    1    2    2    2    2    3
** 1998    -     -    0    0    0    1    1    1    1    2    2    2    2    3
** 1999    -     -    -    0    0    1    1    1    1    2    2    2    2    3
** 2000    -     -    -    -    0    0    0    0    0    1    1    1    1    2
** 2001    -     -    -    -    -    0    0    0    0    1    1    1    1    2
** 2002    -     -    -    -    -    -    0    0    0    1    1    1    1    2
** 2003    -     -    -    -    -    -    -    0    0    1    1    1    1    2
** 2004    -     -    -    -    -    -    -    -    0    0    0    0    0    1
** 2005    -     -    -    -    -    -    -    -    -    0    0    0    0    1
** 2006    -     -    -    -    -    -    -    -    -    -    0    0    0    1
** 2007    -     -    -    -    -    -    -    -    -    -    -    0    0    1
** 2008    -     -    -    -    -    -    -    -    -    -    -    -    0    0
**
** Switchover between 19th and 20th centuries: 1900 was not a leap year.
** Early        Later year
**       1896 1897 1898 1899 1900 1901 1902 1903 1904 1905 1906 1907 1908 1909
** 1896    0     0    0    0    0   *0   *0   *0   *0   *1   *1   *1   *1   *2
** 1897    -     0    0    0    0   *0   *0   *0   *0   *1   *1   *1   *1   *2
** 1898    -     -    0    0    0   *0   *0   *0   *0   *1   *1   *1   *1   *2
** 1899    -     -    -    0    0   *0   *0   *0   *0   *1   *1   *1   *1   *2
** 1900    -     -    -    -    0    0    0    0    0    1    1    1    1    2
** 1901    -     -    -    -    -    0    0    0    0    1    1    1    1    2
** 1902    -     -    -    -    -    -    0    0    0    1    1    1    1    2
** 1903    -     -    -    -    -    -    -    0    0    1    1    1    1    2
** 1904    -     -    -    -    -    -    -    -    0    0    0    0    0    1
** 1905    -     -    -    -    -    -    -    -    -    0    0    0    0    1
** 1906    -     -    -    -    -    -    -    -    -    -    0    0    0    1
** 1907    -     -    -    -    -    -    -    -    -    -    -    0    0    1
** 1908    -     -    -    -    -    -    -    -    -    -    -    -    0    0
**
** The dashes can be returned as zero as a special case (invalid input).
** The leading diagonal (zeros) are a special case.
**
** The starred values are 'exceptional', because the (end year - 1) is
** in a different century from the start year.
** Note that the corresponding positions in the other table are doubly
** exceptional because they could be calculated as (end year - 1) is in
** a different century from the start year (one smaller) and (end year -
** 1) is in a different quad-century (one larger) for a net change of
** zero.  This matters if the date ranges get bigger (1890..2130, for
** example).
*/

#include <assert.h>

static int nleap(int lo, int hi)
{
    assert(lo >= 1800);
    assert(hi <= 9999);
    assert(lo <= hi);

    /* Covers wild inputs */
    /* Beware: 1600 was not a leap year under the Julian calendar then in effect */
    if (lo > hi || lo < 1800 || hi > 9999)
        return 0;

    /* Leading diagonal */
    if (lo == hi)
        return 0;

    /* Regular leap years */
    int lo_4 = (lo - 0) / 4;    /* 500 */
    int hi_4 = (hi - 1) / 4;    /* 502 */
    int diff = hi_4 - lo_4;     /*   2 */

    /* Century years are not leap years */
    int lo_c = (lo - 0) / 100;
    int hi_c = (hi - 1) / 100;
    diff -= hi_c - lo_c;

    /* Quad-century years are leap years */
    int lo_q = (lo - 0) / 400;
    int hi_q = (hi - 1) / 400;
    diff += hi_q - lo_q;

    return(diff);
}

#include <stdbool.h>

static int CountLeapDays(int startYear, int endYear)
{
    int Days = 0;

    if (startYear >= endYear)
        return 0;
    while (true)
    {
        if ((startYear % 4 == 0 && startYear % 100 != 0) || startYear % 400 == 0)
            Days++;
        if (startYear + 1 == endYear)
            break;
        startYear++;
    }

    return Days;
}

#include <stdio.h>

static struct test
{
    int lo;
    int hi;
    int num;
} tests[] =
{
    { 1996, 1996, 0 },
    { 1996, 1997, 0 },
    { 1996, 1998, 0 },
    { 1996, 1999, 0 },
    { 1996, 2000, 0 },
    { 1996, 2001, 1 },
    { 1996, 2002, 1 },
    { 1996, 2003, 1 },
    { 1996, 2004, 1 },
    { 1996, 2005, 2 },
    { 1996, 2006, 2 },
    { 1996, 2007, 2 },
    { 1996, 2008, 2 },
    { 1996, 2009, 3 },
    { 1997, 1997, 0 },
    { 1997, 1998, 0 },
    { 1997, 1999, 0 },
    { 1997, 2000, 0 },
    { 1997, 2001, 1 },
    { 1997, 2002, 1 },
    { 1997, 2003, 1 },
    { 1997, 2004, 1 },
    { 1997, 2005, 2 },
    { 1997, 2006, 2 },
    { 1997, 2007, 2 },
    { 1997, 2008, 2 },
    { 1997, 2009, 3 },
    { 1998, 1998, 0 },
    { 1998, 1999, 0 },
    { 1998, 2000, 0 },
    { 1998, 2001, 1 },
    { 1998, 2002, 1 },
    { 1998, 2003, 1 },
    { 1998, 2004, 1 },
    { 1998, 2005, 2 },
    { 1998, 2006, 2 },
    { 1998, 2007, 2 },
    { 1998, 2008, 2 },
    { 1998, 2009, 3 },
    { 1999, 1999, 0 },
    { 1999, 2000, 0 },
    { 1999, 2001, 1 },
    { 1999, 2002, 1 },
    { 1999, 2003, 1 },
    { 1999, 2004, 1 },
    { 1999, 2005, 2 },
    { 1999, 2006, 2 },
    { 1999, 2007, 2 },
    { 1999, 2008, 2 },
    { 1999, 2009, 3 },
    { 2000, 2000, 0 },
    { 2000, 2001, 0 },
    { 2000, 2002, 0 },
    { 2000, 2003, 0 },
    { 2000, 2004, 0 },
    { 2000, 2005, 1 },
    { 2000, 2006, 1 },
    { 2000, 2007, 1 },
    { 2000, 2008, 1 },
    { 2000, 2009, 2 },
    { 2001, 2001, 0 },
    { 2001, 2002, 0 },
    { 2001, 2003, 0 },
    { 2001, 2004, 0 },
    { 2001, 2005, 1 },
    { 2001, 2006, 1 },
    { 2001, 2007, 1 },
    { 2001, 2008, 1 },
    { 2001, 2009, 2 },
    { 2002, 2002, 0 },
    { 2002, 2003, 0 },
    { 2002, 2004, 0 },
    { 2002, 2005, 1 },
    { 2002, 2006, 1 },
    { 2002, 2007, 1 },
    { 2002, 2008, 1 },
    { 2002, 2009, 2 },
    { 2003, 2003, 0 },
    { 2003, 2004, 0 },
    { 2003, 2005, 1 },
    { 2003, 2006, 1 },
    { 2003, 2007, 1 },
    { 2003, 2008, 1 },
    { 2003, 2009, 2 },
    { 2004, 2004, 0 },
    { 2004, 2005, 0 },
    { 2004, 2006, 0 },
    { 2004, 2007, 0 },
    { 2004, 2008, 0 },
    { 2004, 2009, 1 },
    { 2005, 2005, 0 },
    { 2005, 2006, 0 },
    { 2005, 2007, 0 },
    { 2005, 2008, 0 },
    { 2005, 2009, 1 },
    { 2006, 2006, 0 },
    { 2006, 2007, 0 },
    { 2006, 2008, 0 },
    { 2006, 2009, 1 },
    { 2007, 2007, 0 },
    { 2007, 2008, 0 },
    { 2007, 2009, 1 },
    { 2008, 2008, 0 },
    { 2008, 2009, 0 },
    { 1896, 1896, 0 },
    { 1896, 1897, 0 },
    { 1896, 1898, 0 },
    { 1896, 1899, 0 },
    { 1896, 1900, 0 },
    { 1896, 1901, 0 },
    { 1896, 1902, 0 },
    { 1896, 1903, 0 },
    { 1896, 1904, 0 },
    { 1896, 1905, 1 },
    { 1896, 1906, 1 },
    { 1896, 1907, 1 },
    { 1896, 1908, 1 },
    { 1896, 1909, 2 },
    { 1897, 1897, 0 },
    { 1897, 1898, 0 },
    { 1897, 1899, 0 },
    { 1897, 1900, 0 },
    { 1897, 1901, 0 },
    { 1897, 1902, 0 },
    { 1897, 1903, 0 },
    { 1897, 1904, 0 },
    { 1897, 1905, 1 },
    { 1897, 1906, 1 },
    { 1897, 1907, 1 },
    { 1897, 1908, 1 },
    { 1897, 1909, 2 },
    { 1898, 1898, 0 },
    { 1898, 1899, 0 },
    { 1898, 1900, 0 },
    { 1898, 1901, 0 },
    { 1898, 1902, 0 },
    { 1898, 1903, 0 },
    { 1898, 1904, 0 },
    { 1898, 1905, 1 },
    { 1898, 1906, 1 },
    { 1898, 1907, 1 },
    { 1898, 1908, 1 },
    { 1898, 1909, 2 },
    { 1899, 1899, 0 },
    { 1899, 1900, 0 },
    { 1899, 1901, 0 },
    { 1899, 1902, 0 },
    { 1899, 1903, 0 },
    { 1899, 1904, 0 },
    { 1899, 1905, 1 },
    { 1899, 1906, 1 },
    { 1899, 1907, 1 },
    { 1899, 1908, 1 },
    { 1899, 1909, 2 },
    { 1900, 1900, 0 },
    { 1900, 1901, 0 },
    { 1900, 1902, 0 },
    { 1900, 1903, 0 },
    { 1900, 1904, 0 },
    { 1900, 1905, 1 },
    { 1900, 1906, 1 },
    { 1900, 1907, 1 },
    { 1900, 1908, 1 },
    { 1900, 1909, 2 },
    { 1901, 1901, 0 },
    { 1901, 1902, 0 },
    { 1901, 1903, 0 },
    { 1901, 1904, 0 },
    { 1901, 1905, 1 },
    { 1901, 1906, 1 },
    { 1901, 1907, 1 },
    { 1901, 1908, 1 },
    { 1901, 1909, 2 },
    { 1902, 1902, 0 },
    { 1902, 1903, 0 },
    { 1902, 1904, 0 },
    { 1902, 1905, 1 },
    { 1902, 1906, 1 },
    { 1902, 1907, 1 },
    { 1902, 1908, 1 },
    { 1902, 1909, 2 },
    { 1903, 1903, 0 },
    { 1903, 1904, 0 },
    { 1903, 1905, 1 },
    { 1903, 1906, 1 },
    { 1903, 1907, 1 },
    { 1903, 1908, 1 },
    { 1903, 1909, 2 },
    { 1904, 1904, 0 },
    { 1904, 1905, 0 },
    { 1904, 1906, 0 },
    { 1904, 1907, 0 },
    { 1904, 1908, 0 },
    { 1904, 1909, 1 },
    { 1905, 1905, 0 },
    { 1905, 1906, 0 },
    { 1905, 1907, 0 },
    { 1905, 1908, 0 },
    { 1905, 1909, 1 },
    { 1906, 1906, 0 },
    { 1906, 1907, 0 },
    { 1906, 1908, 0 },
    { 1906, 1909, 1 },
    { 1907, 1907, 0 },
    { 1907, 1908, 0 },
    { 1907, 1909, 1 },
    { 1908, 1908, 0 },
    { 1908, 1909, 0 },
};
enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };

static void test_data(const char *tag, int (*function)(int, int))
{
    int pass = 0;
    int fail = 0;

    printf("%s:\n", tag);
    for (int i = 0; i < NUM_TESTS; i++)
    {
        int res = (*function)(tests[i].lo, tests[i].hi);
        if (res != tests[i].num)
        {
            printf("!! FAIL !! %4d..%4d wanted %d actual %d\n", tests[i].lo, tests[i].hi, tests[i].num, res);
            fail++;
        }
        else
        {
            printf("== PASS == %4d..%4d = %d\n", tests[i].lo, tests[i].hi, tests[i].num);
            pass++;
        }
    }
    if (fail == 0)
        printf("== PASS == %d tests passed\n", pass);
    else
        printf("!! FAIL !! %d tests out of %d failed\n", fail, pass+fail);
}

static void test_range(int min, int max)
{
    for (int lo = min; lo < max; lo++)
    {
        for (int hi = lo; hi < max; hi++)
        {
            printf("%d..%d = %d leap days\n", lo, hi, nleap(lo, hi));
        }
    }
}

int main(void)
{
    test_data("CountLeapDays", CountLeapDays);
    test_data("nleap", nleap);
    test_range(1997, 2016);
    test_range(1891, 1909);
    return(0);
}
