/*
@(#)File:           $RCSfile: bm.c,v $
@(#)Version:        $Revision: 1.6 $
@(#)Last changed:   $Date: 2011/11/27 20:42:33 $
@(#)Purpose:        Boyer-Moore String Search Algorithm
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005,2009,2011
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/*
** Original code from:
** Christian Charras - Thierry Lecroq
** Laboratoire d'Informatique de Rouen
** Universit<C3><A9> de Rouen
** Facult<C3><A9> des Sciences et des Techniques
** 76821 Mont-Saint-Aignan Cedex
** FRANCE
** e-mails: {Christian.Charras, Thierry.Lecroq}@laposte.net
** http://www-igm.univ-mlv.fr/~lecroq/string/node14.html
**
** JL notes: The original code is not suitable for general use.
*/

#include <stdlib.h> /* malloc, free */
#include "bm.h"

#undef MAX
#define MAX(a,b)    (((a)>(b))?(a):(b))

enum { ASIZE = 256 };   /* Alphabet size */

static bm_malloc use_malloc = malloc;
static bm_free   use_free   = free;

struct bm_control
{
    const char *search;             /* String to be searched for */
    size_t      schlen;             /* Length of said string */
    const char *target;             /* String to scanned */
    size_t      tgtlen;             /* Length of scanned string */
    int        *bmGs;               /* Skip table */
    int        *bmBc;               /* Skip table */
    int         posn;               /* Search resume location */
};

static const bm_control bm_empty = { 0 };

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
const char jlss_id__[] = "@(#)$Id: bm.c,v 1.6 2011/11/27 20:42:33 jleffler Exp $";
#endif /* lint */

void bm_release(bm_control *ctrl)
{
    (*use_free)(ctrl);
}

void bm_setalloc(bm_malloc mem_alloc, bm_free mem_free)
{
    use_malloc = mem_alloc;
    use_free   = mem_free;
}

static void preBmBc(const char *x, int m, int bmBc[])
{
    int i;

    for (i = 0; i < ASIZE; ++i)
        bmBc[i] = m;
    for (i = 0; i < m - 1; ++i)
        bmBc[(unsigned char)x[i]] = m - i - 1;
}

static void suffixes(const char *x, int m, int *suff)
{
    int f = 333333333;
    int g, i;

    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i)
    {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else
        {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

static int preBmGs(const char *x, int m, int bmGs[])
{
    int i;
    int j;
    int *suff = (*use_malloc)(sizeof(int) * m);

    if (suff == 0)
        return -1;

    suffixes(x, m, suff);

    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    j = 0;
    for (i = m - 1; i >= -1; --i)
    {
        if (i == -1 || suff[i] == i + 1)
        {
            for (; j < m - 1 - i; ++j)
            {
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
            }
        }
    }
    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;

    (*use_free)(suff);
    return 0;
}

/* Initialize BM Search for string search of length schlen */
bm_control *bm_setsearch(const char *search, size_t schlen)
{
    void *space = (*use_malloc)(sizeof(bm_control) + (ASIZE + schlen) * sizeof(int));
    if (space != 0)
    {
        bm_control *ctrl = space;
        int *bmBc = (int *)((char *)space + sizeof(bm_control));
        int *bmGs = (int *)((char *)space + sizeof(bm_control) + ASIZE * sizeof(int));

        *ctrl = bm_empty;
        ctrl->search = search;
        ctrl->schlen = schlen;
        ctrl->bmBc = bmBc;
        ctrl->bmGs = bmGs;

        if (preBmGs(search, schlen, bmGs) != 0)
        {
            (*use_free)(space);
            space = 0;
        }
        else
            preBmBc(search, schlen, bmBc);
    }
    return space;
}

/* Initialize BM Search to scan target string of length tgtlen */
void bm_settarget(bm_control *ctrl, const char *target, size_t tgtlen)
{
    ctrl->posn = 0;
    ctrl->target = target;
    ctrl->tgtlen = tgtlen;
}

const char *bm_search(bm_control *ctrl)
{
    int j = ctrl->posn;
    int *bmGs = ctrl->bmGs;
    int *bmBc = ctrl->bmBc;
    const char *x = ctrl->search;
    const char *y = ctrl->target;
    int m = ctrl->schlen;
    int n = ctrl->tgtlen;

    while (j <= n - m)
    {
        int i;
        for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i)
            ;
        if (i < 0)
        {
            const char *rv = &y[j];
            /* OUTPUT(j); */
            j += bmGs[0];
            ctrl->posn = j;
            return rv;
        }
        else
            j += MAX(bmGs[i], bmBc[(unsigned char)y[i + j]] - m + 1 + i);
    }
    return 0;
}

#ifdef TEST

#include <stdio.h>
#include <string.h>

enum { MAXBUFFER = 1024 };

/*
** Encapsulated BM String Search Algorithm
** Search for string x of length m in string y of length n.
*/
static void bm_simple(const char *x, int m, const char *y, int n)
{
    bm_control *ctrl = bm_setsearch(x, m);
    if (ctrl != 0)
    {
        const char *found;
        bm_settarget(ctrl, y, n);

        /* Searching */
        while ((found = bm_search(ctrl)) != 0)
        {
            printf("found <%.*s> at offset %td (...%c<%.*s>%c...)\n",
                    m, x, found - y, (found > y) ? *(found-1) : ' ',
                    m, found, (found + m) < (y + n) ? *(found + m) : ' ');
        }
        bm_release(ctrl);
    }
    else
        printf("bm_simple(): bm_setsearch() failed!\n");
}

static void bm_test(const char *search, size_t schlen)
{
    bm_control *ctrl = bm_setsearch(search, schlen);
    if (ctrl != 0)
    {
        const char *found;
        char buffer[MAXBUFFER];

        /* Searching */
        fputs("String? ", stdout);
        while (fgets(buffer, sizeof(buffer), stdin) != 0)
        {
            size_t buflen = strlen(buffer);
            if (buflen <= 1)
                continue;
            bm_settarget(ctrl, buffer, buflen - 1);
            while ((found = bm_search(ctrl)) != 0)
            {
                printf("found <%.*s> at offset %td (...%c<%.*s>%c...)\n",
                        (int)schlen, search, found - buffer, (found > buffer) ? *(found-1) : ' ',
                        (int)schlen, found, (found + schlen) < (buffer + buflen - 1) ? *(found + schlen) : ' ');
            }
            fputs("String? ", stdout);
        }
        putchar('\n');
        bm_release(ctrl);
    }
    else
        printf("bm_test(): bm_setsearch() failed!\n");
}

int main(void)
{
    static const char search[] = "abcdefbba";
    static const char target[] = "AAAabcdefbbabcdefbbabcdefbbbAAA";

    printf("searching for <%s>\n", search);
    printf("searching in  <%s>\n", target);
    bm_simple(search, strlen(search), target, strlen(target));
    printf("searching for <%s>\n", target);
    printf("searching in  <%s>\n", search);
    bm_simple(target, strlen(target), search, strlen(search));

    bm_test(search, strlen(search));

    return 0;
}

#endif /* TEST */
