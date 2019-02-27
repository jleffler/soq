/* SO 3707-5084 */

/*
** Note that the interface to fileSearch() has changed compared to the
** question, because the interface in the question cannot handle all the
** cases it needs to handle.
**
** The question wanted a positive number (the index in the array) when
** an exact match was found (but what about a match at position 0?), and
** a negative number when there were approximate matches.
**
** This code implements "return the number of matches (positive)" or -1
** on no match.  It could be revised to use 0 to indicate an exact
** match, with the index stored in possible[0] (instead of returning 1
** with the index stored in possible[0]).
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int fileSearch(char **files, char *toFind, int *possible,int numOfFiles);
static int bsearchf(char **x, int n, char *t);
static int bsearchl(char **x, int n, char *t);
static void print_results(int found, int *possible, char *needle, char **haystack);

/*
** The search has been completely reworked, using (marginally modified)
** versions of binary search code from the answer to SO 3514-7784
** (https://stackoverflow.com/q/35147784).  It needs to find the first
** element that matches, and potentially needs to find the last element
** that matches too.  If there's an exact match, it will be the low
** point in the range.
**
** Hence:
**    1.  Find lowest possible match (bsearchf())
**    2.  If it's an exact match, we're done.
**    3.  Find highest possible match (bsearchl())
**    4.  Return indexes between min and max in array, though it would
**        be reasonable to return just min and max in two elements since
**        the candidates are all contiguous in the haystack.
**
** Note that the upper-bound search eliminates all earlier elements from
** the search - a small saving.
*/

static int fileSearch(char **files, char *toFind, int *possible, int numOfFiles)
{
    int min = bsearchf(files, numOfFiles, toFind);
    if (min < 0)
        return -1;

    if (strcmp(files[min], toFind) == 0)
    {
        possible[0] = min;
        return 1;
    }

    int max = bsearchl(files + min, numOfFiles - min, toFind) + min;

    for (int i = min; i <= max; i++)
        possible[i-min] = i;
    return (max - min + 1);
}

/*
** From J Bentley "Programming Pearls, 2nd Edition", Section 9.3
** Locate the first occurrence of t in x[0..n-1].
** Assume n >= 0, and the hypothetical elements x[-1] < t and x[n] > t
** without accessing either fictitious element.
** Converted to string prefix matching.
*/
static int bsearchf(char **x, int n, char *t)
{
    int l = -1;
    int u = n;
    size_t tlen = strlen(t);

    assert(n >= 0);
    while (l + 1 != u)
    {
        /* Invariant: x[l] < t && x[u] >= t && l < u */
        int m = (l + u) / 2;
        if (strncmp(x[m], t, tlen) < 0)
            l = m;
        else
            u = m;
    }
    if (u >= n || strncmp(x[u], t, tlen) != 0)
        return -1;
    assert(u >= 0 && u < n);
    return u;
}

/*
** Varying J Bentley "Programming Pearls, 2nd Edition", Section 9.3
** Locate the last occurrence of t in x[0..n-1].
** Assume n >= 0, and the hypothetical elements x[-1] < t and x[n] > t
** without accessing either fictitious element.
** Converted to string prefix matching.
*/
static int bsearchl(char **x, int n, char *t)
{
    int l = -1;
    int u = n;
    size_t tlen = strlen(t);

    assert(n >= 0);
    while (l + 1 != u)
    {
        /* Invariant: x[l] <= t && x[u] > t && l < u */
        int m = (l + u) / 2;
        if (strncmp(x[m], t, tlen) <= 0)
            l = m;
        else
            u = m;
    }
    if (l < 0 || strncmp(x[l], t, tlen) != 0)
        return -1;
    assert(l >= 0 && l < n);
    return l;
}

static void print_results(int found, int *possible, char *needle, char **haystack)
{
    if (found <= 0)
        printf("Looking for [%s] - no match found\n", needle);
    else if (found == 1 && strcmp(needle, haystack[possible[0]]) == 0)
        printf("Looking for [%s] - found 1 exact match %d: [%s]\n",
               needle, possible[0], haystack[possible[0]]);
    else
    {
        printf("Looking for [%s] - found %d possible matches\n", needle, found);
        for (int i = 0; i < found; i++)
            printf("  %d [%s]\n", i+1, haystack[possible[i]]);
    }
}

int main(void)
{
    char *files[] =
    {
        "Abelone", "Basilisk", "Gandalf", "Persistence", "Quad",
        "Quadrangle", "Quadratic", "Quadrilateral", "Quagga",
        "Quasimodo", "Stack Overflow", "Syzygy", "Zeta Quad",
    };
    enum { NUM_FILES = sizeof(files) / sizeof(files[0]) };
    char *words[] =
    {
        "Qua", "Quad", "Antimony", "Basil", "Basilisk",
    };
    enum { NUM_WORDS = sizeof(words) / sizeof(words[0]) };
    int possibles[10];

    for (int i = 0; i < NUM_WORDS; i++)
    {
        int found = fileSearch(files, words[i], possibles, NUM_FILES);
        print_results(found, possibles, words[i], files);
    }

    return 0;
}
