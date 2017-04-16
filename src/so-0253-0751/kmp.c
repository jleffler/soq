/*
@(#)File:           $RCSfile: kmp.c,v $
@(#)Version:        $Revision: 1.7 $
@(#)Last changed:   $Date: 2015/03/09 07:24:35 $
@(#)Purpose:        Knuth-Morris-Pratt String Search Algorithm
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005,2011,2015
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/*
** Original code from:
** Christian Charras - Thierry Lecroq
** Laboratoire d'Informatique de Rouen
** Université de Rouen
** Faculté des Sciences et des Techniques
** 76821 Mont-Saint-Aignan Cedex
** FRANCE
** e-mails: {Christian.Charras, Thierry.Lecroq}@laposte.net
** http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
**
** JL notes: The original code is not suitable for general use.
**
** A better design calls kmp_setsearch() once to initialize the string
** to be searched for.  It then calls kmp_settarget() - possibly many
** times - to specify the string to be scanned for matches.  For each
** call to kmp_settarget(), there will normally be at least one and
** possibly many calls to kmp_search() to find matches of the search
** string in the target string. kmp_search() returns either a null
** pointer (not found) or the pointer to the start of the search string
** in the target string for each match.  This could then be usable for
** MATCHES "*xyz*" type searches with considerable effect.  An
** alternative design uses indexes instead of pointers, the tricky part
** being what to return on no match.
**
** kmp_setsearch() initializes the control structure for the search.  It
** keeps track of the search string, but does not control it -- the
** application is responsible for ensuring that the pointer remains
** valid while in use.
**
** kmp_settarget() resets the control structure to scan a new string.
** Similar strictures about the pointers apply here, too.
**
** kmp_search() finds the next match in the string based on the control
** information.  It assumes that the string being searched is the same
** from iteration to iteration.  It might be better if kmp_settarget()
** took the target string and length and captured those, and then
** kmp_search() only takes the control argument...
**
** A callback on find algorithm is interesting - but designing the
** appropriate callback is hard.  Presumably, the callback should be
** able to indicate whether to continue or not - hence it returns an
** int.  The values needed in the callback could be many - maybe you
** need a void *context to convey extraneous information, plus the
** search string, the target string, their lengths, and the position of
** the current match.
**
** int (*kmp_callback)(const char *search, size_t schlen, const char
**      *target, size_t tgtlen, const char *found, void *context);
**
** Not exactly trivial!  The context might be omitted, but that's
** unlikely to be desirable in production code.
**
** NB: BUG - KMP_NEXTSIZE needs to be as big as the string to be
** searched for.  Means dynamic memory allocation, etc - hence another
** redesign is in order.  It can be completely opaque to user, but
** requires more support code.  Probably kmp_setsearch() returns a void
** pointer - or nonce-based system. kmp_settarget() does not change; nor
** does kmp_search().  But you need kmp_release() to free a search, and
** kmp_copy() to return an independent copy of the control structure,
** and kmp_setmalloc() to configure the memory allocation. -- requires
** pointers to malloc() and free().
*/

#include <stdlib.h>
#include "kmp.h"

enum { KMP_NEXTSIZE = 256 };

static kmp_malloc use_malloc = malloc;
static kmp_free   use_free   = free;

struct kmp_control
{
    const char *search;             /* String to be searched for */
    size_t      schlen;             /* Length of said string */
    const char *target;             /* String to scanned */
    size_t      tgtlen;             /* Length of scanned string */
    int        *nxt;                /* Skip table */
    int         schpos;             /* Search resume location */
    int         tgtpos;             /* Search resume location */
};

static const kmp_control kmp_empty = { 0 };

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_kmp_c[];
const char jlss_id_kmp_c[] = "@(#)$Id: kmp.c,v 1.7 2015/03/09 07:24:35 jleffler Exp $";
#endif /* lint */

void kmp_release(kmp_control *ctrl)
{
    (*use_free)(ctrl);
}

void kmp_setalloc(kmp_malloc mem_alloc, kmp_free mem_free)
{
    use_malloc = mem_alloc;
    use_free   = mem_free;
}

/* Initialize KMP Search for string search of length schlen */
kmp_control *kmp_setsearch(const char *search, size_t schlen)
{
    void *space = (*use_malloc)(sizeof(kmp_control) + (schlen + 1) * sizeof(int));
    if (space != 0)
    {
        kmp_control *ctrl = space;
        size_t i = 0;
        int j = -1;
        int *kmpNext = (int *)((char *)space + sizeof(kmp_control));

        /* Zero initialize all fields */
        *ctrl = kmp_empty;
        ctrl->search = search;
        ctrl->schlen = schlen;
        ctrl->nxt = kmpNext;
        kmpNext[0] = -1;
        while (i < schlen)
        {
            while (j > -1 && search[i] != search[j])
                j = kmpNext[j];
            i++;
            j++;
            if (search[i] == search[j])
                kmpNext[i] = kmpNext[j];
            else
                kmpNext[i] = j;
        }
    }
    return space;
}

/* Initialize KMP Search to scan target string of length tgtlen */
void kmp_settarget(kmp_control *ctrl, const char *target, size_t tgtlen)
{
    ctrl->schpos = ctrl->tgtpos = 0;
    ctrl->target = target;
    ctrl->tgtlen = tgtlen;
}

/*
** KMP String Search Algorithm
** Find specific search string in target string
*/
const char *kmp_search(kmp_control *ctrl)
{
    int i = ctrl->schpos;
    int j = ctrl->tgtpos;
    const int *kmpNext = ctrl->nxt;
    const char *search = ctrl->search;
    int schlen = ctrl->schlen;
    const char *target = ctrl->target;
    size_t tgtlen = ctrl->tgtlen;

    /* Bare minimum of validity checking */
    /* Nonce-based pure opaque type solution? */
    if (target == 0 || search == 0)
        return 0;

    /* Searching */
    while ((size_t)j < tgtlen)
    {
        while (i > -1 && search[i] != target[j])
            i = kmpNext[i];
        i++;
        j++;
        if (i >= schlen)
        {
            ctrl->schpos = kmpNext[i];
            ctrl->tgtpos = j;
            return(&target[j - i]);
        }
    }
    return 0;
}

#ifdef TEST

#include <stdio.h>
#include <string.h>

enum { MAXBUFFER = 1024 };

/*
** Encapsulated KMP String Search Algorithm
** Search for string x of length m in string y of length n.
*/
static void kmp_simple(const char *x, int m, const char *y, int n)
{
    kmp_control *ctrl = kmp_setsearch(x, m);
    if (ctrl != 0)
    {
        const char *found;
        kmp_settarget(ctrl, y, n);

        /* Searching */
        while ((found = kmp_search(ctrl)) != 0)
        {
            printf("found <%.*s> at offset %td (...%c<%.*s>%c...)\n",
                    m, x, found - y, (found > y) ? *(found-1) : ' ',
                    m, found, (found + m) < (y + n) ? *(found + m) : ' ');
        }
        kmp_release(ctrl);
    }
    else
        printf("kmp_simple(): kmp_setsearch() failed!\n");
}

static void kmp_test(const char *search, size_t schlen)
{
    kmp_control *ctrl = kmp_setsearch(search, schlen);
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
            kmp_settarget(ctrl, buffer, buflen - 1);
            while ((found = kmp_search(ctrl)) != 0)
            {
                printf("found <%.*s> at offset %td (...%c<%.*s>%c...)\n",
                        (int)schlen, search, found - buffer, (found > buffer) ? *(found-1) : ' ',
                        (int)schlen, found, (found + schlen) < (buffer + buflen - 1) ? *(found + schlen) : ' ');
            }
            fputs("String? ", stdout);
        }
        putchar('\n');
        kmp_release(ctrl);
    }
    else
        printf("kmp_test(): kmp_setsearch() failed!\n");
}

int main(void)
{
    static const char search[] = "abcdefbba";
    static const char target[] = "AAAabcdefbbabcdefbbabcdefbbbAAA";

    printf("searching for <%s>\n", search);
    printf("searching in  <%s>\n", target);
    kmp_simple(search, strlen(search), target, strlen(target));
    printf("searching for <%s>\n", target);
    printf("searching in  <%s>\n", search);
    kmp_simple(target, strlen(target), search, strlen(search));

    kmp_test(search, strlen(search));

    return 0;
}

#endif /* TEST */
