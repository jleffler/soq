/*
@(#)File:           $RCSfile: dbmalloc.c,v $
@(#)Version:        $Revision: 4.2 $
@(#)Last changed:   $Date: 2016/01/10 06:10:55 $
@(#)Purpose:        Yet another implementation of MALLOC(3)
@(#)Algorithm:      From K&R, augmented with safety checking
@(#)Author:         J Leffler
@(#)Product:        :PRODUCT:
@(#)Copyright:      (C) JLSS 1990-92,1997-2000,2002-05,2008,2013,2016
*/

/*TABSTOP=4*/

/*
**  When compiled non-PARANOID, this behaves pretty much as the
**  version of MALLOC and FREE in K&R (2nd Edition) does, with the
**  additions of CALLOC, REALLOC, and BFREE (an exercise in K&R).
**
**  This version is believed to conform to the ANSI C standard.
**  This means that:
**  -- if free() is passed a null pointer, no damage occurs.
**  -- if realloc() is passed a null pointer, it behaves like malloc()
**  ANSI C specifies that the behaviour of malloc() and realloc()
**  when asked for zero bytes is implementation defined.
**  -- if realloc() is asked for zero bytes, you get a unique pointer
**  -- if malloc() is asked for zero bytes, you get a unique pointer
**
**  When compiled PARANOID, this version also keeps a record of all
**  allocations and complains bitterly (by aborting) if it is made to
**  free (or reallocate) any data which was not previously allocated.
**  It also keeps a record of the hash sums of the header records in
**  the free list and the used list, and also a hash sum of the data in
**  the free list.  If these change when they shouldn't, it complains
**  and aborts.  This will detect overwriting errors at the front of
**  the memory blocks (and some gross overwriting beyond the end of the
**  allocated data), and will also detect writing on previously
**  released blocks of data (dangling pointers).  Finally, when
**  compiled PARANOID, it writes a record of all the memory
**  transactions in a file called "malloc.log".  If it cannot create
**  this file, it will waste time trying to create it every time one of
**  the routines is called.  NB: it uses a statically allocated buffer
**  for the file channel to avoid problems with STDIO calling MALLOC to
**  get memory for the file, and MALLOC calling STDIO to open the
**  channel and then getting some more memory and so on.
**
**  CAVEAT: BFREE(3) has not been tested yet.  It is derived from the
**  answer given in `The C Answer Book' (2nd Edition), but has been
**  modified to take account of the fact that you need 2 units of data
**  to be of any use, and the pointer handed in may be misaligned and
**  consequently need to be moved up memory (with consequential
**  decrease in available memory).
**
**  CAVEAT: this package assumes you are using my STDERR package of
**  error handling routines.  If you are not, you should either obtain
**  them or simulate them.  The err_abort() function prints the message
**  and calls abort().  The err_remark() function is similar to printf()
**  but writes to standard error.  The err_report() function is a
**  varargs routine; ERR_ABT means print a message using the format
**  string and other arguments as supplied and then do abort().  The
**  ERR_STAT value is conventionally 1 and is ignored in any case when
**  the routine does an abort.  In my version, the err_*() functions all
**  end up calling err_report().  There is also a routine err_setarg0()
**  which is called in a main program that sets a static string to the
**  basename of the name of the program.  This is printed in from of all
**  the messages above.  Finally, there is a function err_usage() which
**  prints `Usage: prog string' where string is the argument it is
**  passed.  I find these immensely useful and most of my programs use
**  them.  The header "stderr.h" defines ERR_ABT and ERR_STAT and
**  declares the routines and so on.
**
**  Note that the Malloc structure stores the size of chunk of data in
**  units of sizeof(Header), not in bytes.  The header nodes in the free
**  and used lists have a size of zero.
**
**  ToDo: optionally add barrier data before and after allocated space.
**        Requires exact requested space as well as allocated units.
*/

#include "posixver.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "dbmalloc.h"
#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stderr.h"

/* Minimum space (units of sizeof(Header) bytes) retrieved from sbrk(2) */
enum { NALLOC = 1024 };

#define NIL(x)  ((x)0)

#ifdef PARANOID
#define MALLOC_FREE_SPACE       0xDEADBEEF      /* Freed space */
#define MALLOC_INIT_SPACE       0x8D8D8D8D      /* Uninitialized allocated memory */
#define ENTER_PARANOID(x)       chk_entry(x)
#define EXIT_PARANOID(x)        chk_exit(x)
#define PRINT_PARANOID(s,t,n,p)   log_print(s, t, (size_t)(n), (uintptr_t)(p))
#define INITIALIZE()    if (freep == NIL(Header *)) { \
    fbase.s.ptr = freep = &fbase; \
    ubase.s.ptr = usedp = &ubase; \
    ubase.s.size = fbase.s.size = 0; \
    atexit(db_dump_malloc); }
#else
#define ENTER_PARANOID(x)
#define EXIT_PARANOID(x)
#define PRINT_PARANOID(s,t,n,p)
#define INITIALIZE()    if (freep == NIL(Header *)) { \
    fbase.s.ptr = freep = &fbase; \
    fbase.s.size = 0; }
#endif  /* PARANOID */

typedef long double     Align;
typedef union Header    Header;
typedef struct Malloc   Malloc;

struct Malloc
{
    Header *ptr;        /* Next block on free or used list */
    size_t  size;       /* Size of block (in units of sizeof(Header) bytes, including Header itself) */
};

union Header
{
    Malloc  s;
    Align   x;
};

/* -- Not defined in POSIX; sometimes present in unistd.h */
extern void *sbrk(int);

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_dbmalloc_c[];
const char jlss_id_dbmalloc_c[] = "@(#)$Id: dbmalloc.c,v 4.2 2016/01/10 06:10:55 jleffler Exp $";
#endif /* lint */

static Header   fbase;                  /* Empty free list */
static Header  *freep = NIL(Header *);  /* Start of free list */

#ifdef DBMALLOC_IMPLEMENT_STDC
/* Implement the standard C memory allocation functions in terms of the DB-Malloc functions */
/* Avoid compilation problems if DBMALLOC_MAP_STDC also defined */
void *(malloc)(size_t size)             { return db_malloc(size); }
void *(realloc)(void *ptr, size_t size) { return db_realloc(ptr, size); }
void *(calloc)(size_t num, size_t size) { return db_calloc(num, size); }
void  (free)(void *ptr)                 { db_free(ptr); }
#endif /* DBMÅLLOC_IMPLEMENT_STDC */

#ifdef PARANOID
static Header   ubase;                  /* Empty used list */
static Header  *usedp = NIL(Header *);  /* Start of used list */

static const char *entry_point = NIL(char *);  /* Name of user called function */

static size_t hash_1 = 0; /* Hash of free list */
static size_t hash_2 = 0; /* Hash of used list */
static size_t hash_3 = 0; /* Hash of free space */

static FILE  *fp = NIL(FILE *);
static char   fpbuff[BUFSIZ]; /* To prevent STDIO using malloc */

/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_dbmalloc_paranoia[];
const char jlss_id_dbmalloc_paranoia[] = "@(#)*** PARANOID MALLOC ***";

/* Write a use record to log file */
static void log_print(const char *s, const char *t, size_t n, uintptr_t p)
{
    if (fp != NIL(FILE *))
    {
        fprintf(fp, "%8s%s: %5zu at 0x%08" PRIXPTR "\n", s, t, n, p);
        fflush(fp);
    }
}

/* Calculate hash value for list */
static size_t lst_hash(Header *listp)
{
    size_t  u;
    Header *hp;

    u = 0;
    if (listp != NIL(Header *))
    {
        for (hp = listp; hp->s.ptr != listp; hp = hp->s.ptr)
            u ^= (size_t)hp->s.ptr ^ (size_t)hp->s.size;
    }
    return(u);
}

/* Calculate hash values for free list, used list and free data */
/* h1 - Out: Free list hash value */
/* h2 - Out: Used list hash value */
/* h3 - Out: Free data hash value */
/*
** A simpler scheme simply sets all the free data to a known value
** and checks for any deviation.  That error could then be reported.
*/
static void set_hash(size_t *h1, size_t *h2, size_t *h3)
{
    size_t  u;
    size_t *up;
    size_t *ep;
    Header *hp;

    *h1 = lst_hash(freep);
    *h2 = lst_hash(usedp);

    u = 0;
    if (freep != NIL(Header *))
    {
        for (hp = freep; hp->s.ptr != freep; hp = hp->s.ptr)
        {
            up = (size_t *)(hp + 1);
            ep = up + ((hp->s.size - 1) * sizeof(Header)) / sizeof(size_t);
            while (up < ep)
            {
                if (*up != MALLOC_FREE_SPACE)
                {
                    log_print("*corrupt", "", *up, (size_t)up);
                    u = 1;
                }
                up++;
            }
        }
    }
    *h3 = u;
}

/* Recalculate hashes and check that they have not changed */
static void chk_hash(void)
{
    size_t h1;
    size_t h2;
    size_t h3;
    int    estat = 0;

    set_hash(&h1, &h2, &h3);

    if (h1 != hash_1)
    {
        err_remark("%s %s\n", entry_point, "corrupted free list");
        estat = 1;
    }

    if (h2 != hash_2)
    {
        err_remark("%s %s\n", entry_point, "corrupted used list");
        estat = 1;
    }

    if (h3 != hash_3)
    {
        err_remark("%s %s\n", entry_point, "corrupted free data");
        estat = 1;
    }

    if (estat != 0)
        err_abort("aborting");
}

/* Routine to open log file */
static void chk_file(void)
{
    static int do_fopen = 0;
    if (fp == NIL(FILE *))
    {
        /* Some versions of fopen() - eg GNU C Library 2.1.1 - use malloc */
        if (do_fopen == 0)
        {
            do_fopen++;
            if ((fp = fopen("malloc.log", "w")) != NIL(FILE *))
                setbuf(fp, fpbuff);
            do_fopen--;
        }
        /* Calling err_logmsg() triggers a flurry of malloc()s */
        /* It regrettably causes more confusion than it's worth */
        /* err_logmsg(fp, ERR_LOG, ERR_EXIT, "started\n");     */
    }
}

/* Record routine called by program; open log file; check hash values */
static void chk_entry(const char *x)
{
    chk_file();
    if (entry_point == NIL(char *))
    {
        entry_point = x;
        if (fp != NIL(FILE *))
        {
            fprintf(fp, "-->> %s\n", entry_point);
            fflush(fp);
        }
        chk_hash();
    }
}

/* Record when routine called by program exits; set new hash values */
static void chk_exit(const char *x)
{
    if (strcmp(entry_point, x) == 0)
    {
        set_hash(&hash_1, &hash_2, &hash_3);
        if (fp != NIL(FILE *))
        {
            fprintf(fp, "<<-- %s\n", entry_point);
            fflush(fp);
        }
        entry_point = NIL(char *);
    }
}

/* Print one item on list */
static size_t prt_item(Header *hp)
{
    size_t nb = 0;
    if (hp->s.size > 0)
    {
        nb = (hp->s.size - 1) * sizeof(Header);
        log_print(__func__, "", nb, (size_t)(char *)(hp + 1));
    }
    return(nb);
}

/* Print pointers on one list */
static void prt_hash(Header *listp)
{
    Header *hp;
    size_t  size;

    if (fp != NIL(FILE *))
    {
        size = 0;
        fprintf(fp, "%s: 0x%08" PRIXPTR "\n", __func__, (uintptr_t)listp);
        if (listp != NIL(Header *))
        {
            for (hp = listp; hp->s.ptr != listp; hp = hp->s.ptr)
                size += prt_item(hp);
            size += prt_item(hp);
        }
        fprintf(fp, "%s: Total size = %zu\n", __func__, size);
        fflush(fp);
    }
}

/* Print pointers in used list and free list */
static void prt_list(void)
{
    if (fp != NIL(FILE *))
    {
        fprintf(fp, "Used list\n");
        prt_hash(usedp);
        fprintf(fp, "Free list\n");
        prt_hash(freep);
    }
}

/* Print used and free lists before aborting with suitable message */
static void do_abort(const char *s, uintptr_t p)
{
    db_prt_note("!!!Aborting!!!");
    db_prt_note("%s: %s 0x%08" PRIXPTR, entry_point, s, (uintptr_t)p);
    prt_list();
    db_prt_note("!!!Dump Complete!!!");
    err_report(ERR_ABT, ERR_STAT, "%s: %s 0x%08" PRIXPTR "\n", entry_point, s, (uintptr_t)p);
}

static void prt_header(Header *p)
{
    if (fp != NIL(FILE *) && p != NIL(Header *))
    {
        char *s = (char *)(p + 1);
        char *e = (char *)(p + 1 + (p->s.size > 0 ? p->s.size - 1 : 0));
        fprintf(fp, "%8s: addr = 0x%08" PRIXPTR ", size = %5lu, next = 0x%08" PRIXPTR
                    ", base = 0x%08" PRIXPTR ", end = 0x%08" PRIXPTR "\n",
                "=header=", (uintptr_t)p, (unsigned long)(p->s.size * sizeof(Header)),
                (uintptr_t)p->s.ptr, (uintptr_t)s, (uintptr_t)e);
        fflush(fp);
    }
}

/*
** Set all the non-control memory to MALLOC_FREE_SPACE.
** Note: Header structure is followed by p->s.size bytes of data.
*/
static void set_free(Header *p)
{
    size_t *up;
    size_t *ep;

    prt_header(p);

    up = (size_t *)(p + 1);
    ep = up + (((p->s.size - 1) * sizeof(Header)) / sizeof(size_t));
    while (up < ep)
        *up++ = MALLOC_FREE_SPACE;
}

#endif  /* PARANOID */

/* Print a note into the malloc log */
/* Always available, not always operative */
void db_prt_note(const char *fmt, ...)
{
    assert(fmt != 0);       /* Use fmt even when not paranoid */
#ifdef PARANOID
    chk_file();
    if (fp != NIL(FILE *))
    {
        va_list args;
        fprintf(fp, "\nprt_note: ");
        va_start(args, fmt);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
        vfprintf(fp, fmt, args);
#pragma GCC diagnostic pop
        va_end(args);
        fprintf(fp, "\n");
        fflush(fp);
    }
#endif  /* PARANOID */
}

/* Round address up to next multiple of alignment */
static void *mem_align(void *ptr, size_t alignment)
{
    assert((alignment & (alignment - 1)) == 0); /* Power of two */
    uintptr_t base = (uintptr_t)ptr;
    return (void *)((base + alignment - 1) & ~(alignment - 1));
}

/* Print a note into the malloc log */
/* Always available, not always operative */
FILE *db_malloc_fp(void)
{
    FILE *rv;
#ifdef PARANOID
    chk_file();
    rv = fp;
#else
    rv = stderr;
#endif  /* PARANOID */
    return(rv);
}

/* Print malloc data */
/* Always available, not always operative */
void db_dump_malloc(void)
{
#ifdef PARANOID
    chk_file();
    if (fp != NIL(FILE *))
    {
        fprintf(fp, "\n*** MEMORY DUMP ***\n");
        prt_list();
        fprintf(fp, "*** END OF MEMORY DUMP ***\n\n");
        chk_hash();
    }
#endif  /* PARANOID */
}

/* Internal (unchecked) version of free */
static void do_free(char *ap)
{
    Header         *bp;
    Header         *p;
#ifdef PARANOID
    int             set = 0;
#endif  /* PARANOID */

    bp = (Header *)mem_align(ap, sizeof(Header)) - 1;    /* Pointer to block header */

    PRINT_PARANOID(__func__, "", (bp->s.size - 1) * sizeof(Header), ap);

    /* Locate where block should go in free list */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;              /* Freed block at start or end of arena */
    }

    if (bp + bp->s.size == p->s.ptr)
    {
        /* Join to upper neighbour */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
#ifdef PARANOID
        set_free(bp);
        set = 1;
#endif  /* PARANOID */
    }
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp)
    {
        /* Join to lower neighbour */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
#ifdef PARANOID
        set_free(p);
        set = 1;
#endif  /* PARANOID */
    }
    else
        p->s.ptr = bp;

#ifdef PARANOID
    if (set == 0)
        set_free(bp);
#endif  /* PARANOID */

    freep = p;
}

/* Release memory into free list */
void db_free(void *vp)
{
    char           *ap = vp;

    INITIALIZE();
    ENTER_PARANOID(__func__);

    if (ap == NIL(char *))
        PRINT_PARANOID(__func__, "", 0, ap);
    else
    {
#ifdef PARANOID
        Header *hp;
        Header *bp = (Header *)mem_align(ap, sizeof(Header)) - 1;
        PRINT_PARANOID(__func__, "", (bp->s.size - 1) * sizeof(Header), ap);
        for (hp = usedp; hp->s.ptr != usedp; hp = hp->s.ptr)
        {
            if (hp->s.ptr == bp)
                break;
        }
        if (hp->s.ptr != bp)
        {
            /* Check whether it is known on the free list */
            for (hp = freep; hp->s.ptr != freep; hp = hp->s.ptr)
            {
                if (ap >= (char *)hp->s.ptr && ap < (char *)(hp->s.ptr + hp->s.size))
                    do_abort("double free", (uintptr_t)ap);
            }
            do_abort("freeing never allocated space", (uintptr_t)ap);
        }
        else
            usedp = hp->s.ptr = bp->s.ptr;  /* Disconnect from used list */
#endif  /* PARANOID */
        do_free(ap);
    }

    EXIT_PARANOID(__func__);
}

/* Get memory from system */
static Header *morecore(size_t nu)
{
    char           *cp;
    Header         *up;

    nu = ((nu + NALLOC - 1) / NALLOC) * NALLOC;
    assert(nu * sizeof(Header) < INT_MAX);
    cp = sbrk((int)(nu * sizeof(Header)));
    if (cp == (char *) -1)
        return(NIL(Header *));
    up = (Header *)mem_align(cp, sizeof(Header));
    up->s.size = nu;
    PRINT_PARANOID(__func__, "", nu * sizeof(Header), up);
    do_free((char *)(up + 1));
    return(freep);
}

/* Internal (unchecked) version of malloc */
static char *do_alloc(size_t nbytes)
{
    size_t  nunits = ((nbytes + sizeof(Header) - 1) / sizeof(Header)) + 1;
    Header *prevp = freep;
    void *vp = NIL(char *);
    Header *p;

    for (p = prevp->s.ptr; vp == NIL(char *); prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {                       /* Big enough */
            if (p->s.size == nunits)
            {
                prevp->s.ptr = p->s.ptr;
            }
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            vp = (void *)(p + 1);
            break;
        }
        if (p == freep)
        {
            /* Wrapped around free list -- nothing big enough */
            if ((p = morecore(nunits)) == NIL(Header *))
                break;
        }
    }

#ifdef PARANOID
    if (p != NIL(Header *))
    {
        size_t *up = (size_t *)vp;
        size_t *ep = up + ((nunits - 1) * sizeof(Header) / sizeof(size_t));
        while (up < ep)
            *up++ = MALLOC_INIT_SPACE;
        p->s.ptr = usedp->s.ptr;
        usedp->s.ptr = p;
        usedp = p;
        prt_header(p);
    }
    log_print(__func__, "", (nunits - 1) * sizeof(Header), (size_t)vp);
#endif  /* PARANOID */

    return(vp);
}

/* Collect pointer to some memory */
void *db_malloc(size_t nbytes)
{
    INITIALIZE();
    ENTER_PARANOID(__func__);

    void *vp = do_alloc(nbytes);

    PRINT_PARANOID(__func__, "", nbytes, vp);
    EXIT_PARANOID(__func__);

    return(vp);
}

/* Collect pointer to some zeroed memory */
void *db_calloc(size_t n, size_t s)
{
    INITIALIZE();
    ENTER_PARANOID(__func__);

    size_t  u = n * s;
    void   *vp;
    if ((vp = do_alloc(u)) != NIL(char *))
    {
        int *ip = (int *)vp;
        int *ep = ip + ((u + sizeof(int) - 1) / sizeof(int));
        while (ip < ep)
            *ip++ = 0;
    }

    PRINT_PARANOID(__func__, "", u, vp);
    EXIT_PARANOID(__func__);

    return(vp);
}

/*
**  Reallocate memory previously allocated; if new size is larger than
**  old, move old data into new block.  NB: this version does not try
**  to check the free list to determine if there is a free block
**  immediately beyond its own data block.  It does release spare
**  memory if the program request that the memory is shrunk.
*/
void *db_realloc(void *vp, size_t n)
{
    Header         *bp;
    Header         *xp;
    void           *rp;
    size_t          nunits;

    INITIALIZE();
    ENTER_PARANOID(__func__);

    if (vp == NIL(void *))
    {
        rp = db_malloc(n);
        PRINT_PARANOID(__func__, "0", n, vp);
    }
    else
    {
        bp = (Header *)mem_align(vp, sizeof(Header)) - 1;
        PRINT_PARANOID(__func__, "1", (bp->s.size - 1) * sizeof(Header), vp);
#ifdef PARANOID
        {
        Header         *hp;
        for (hp = usedp; hp->s.ptr != usedp; hp = hp->s.ptr)
        {
            if (hp->s.ptr == bp)
                break;
        }
        if (hp->s.ptr != bp)
            do_abort("reallocating unallocated space", (uintptr_t)vp);
        }
#endif  /* PARANOID */

        nunits = (n + sizeof(Header) - 1) / sizeof(Header) + 1;

        if (nunits <= bp->s.size)
        {
            if (nunits <= bp->s.size - 2)
            {
                /* Partition current block */
                xp = bp + nunits;
                xp->s.size = bp->s.size - nunits;
                do_free((char *)(xp + 1));
                bp->s.size = nunits;
            }
            rp = vp;
        }
        else if ((rp = db_malloc(n)) != NIL(char *))
        {
#ifdef PARANOID
            Header         *hp;
            /* Must relocate previous pointer because malloc() alters list */
            /* It took a lot of work to track this bug down! */
            for (hp = usedp; hp->s.ptr != usedp; hp = hp->s.ptr)
            {
                if (hp->s.ptr == bp)
                    break;
            }
            usedp = hp->s.ptr = bp->s.ptr;  /* Disconnect from used list */
#endif  /* PARANOID */
            memcpy(rp, vp, (bp->s.size - 1) * sizeof(Header));
            do_free(vp);
        }

        PRINT_PARANOID(__func__, "2", n, rp);
    }
    EXIT_PARANOID(__func__);

    return(rp);
}

/*
**  @(#)CAVEAT: BFREE(3)has not been tested yet.
**  Release a block of memory acquired from outside the MALLOC system
**  into the MALLOC arena for use by MALLOC.  Potential uses: allocate
**  a static or external (global) array to contain an initial quantity
**  of data.  When this allocation runs out, use MALLOC to acquire a
**  new chunk of data, copy the old into the new and then use BFREE to
**  release the original array.  This should help mimimise the memory
**  used by the program, and saves worrying about complicated overflow
**  schemes.  NB: it would be a ghastly error to use BFREE on some
**  data acquired from MALLOC where the original pointer supplied by
**  MALLOC was also subsequently freed because the same memory would
**  have two different uses at once -- not a happy situation.
**  Likewise, do not free stack-based memory (local arrays) into the
**  MALLOC arena using BFREE.  Note that the user could hand us a char
**  pointer to some horribly aligned piece of data.  The addition of
**  (sizeof(Align) - 1) to the pointer supplied rounds the pointer up
**  to the next suitable boundary.
*/
void db_bfree(void *vp, size_t n)
{
    Header         *hp;
    char    *p = (char *)vp;

    INITIALIZE();
    ENTER_PARANOID(__func__);

    hp = (Header *)mem_align((p + sizeof(Align) - 1), sizeof(Header));
    assert((char *)hp - p > 0);     /* ptrdiff_t */
    n -= (size_t)((char *)hp - p);
    if (n >= 2 * sizeof(Header))
    {
        hp->s.size = n / sizeof(Header);
        PRINT_PARANOID(__func__, "", n, hp);
        do_free((char *)(hp + 1));
    }

    EXIT_PARANOID(__func__);
}

#if defined(TEST)

#define MIN_BLOCKS      4
#define MAX_BLOCKS      1024
#define MUL_BLOCKS      8
#define MIN_BLOCK_SIZE  16
#define MAX_BLOCK_SIZE  2048
#define MUL_BLOCK_SIZE  8

static void mem_free(int n_blocks, int incr, char **blocks)
{
    int i;
    int j = 0;

    for (i = 0; i < n_blocks; i ++)
    {
        j = (j + incr) % n_blocks;
        if (blocks[j] != (char *)0)
        {
            db_free(blocks[j]);
            blocks[j] = (char *)0;
        }
    }
    db_dump_malloc();
}

static void mem_alloc(size_t blk_size, int n_blocks, int incr, char **blocks)
{
    int i;
    int j = 0;

    /* Allocate memory */
    for (i = 0; i < n_blocks; i++)
    {
        j = (j + incr) % n_blocks;
        blocks[j] = db_malloc(blk_size);
    }
    db_dump_malloc();
}

static int gcd(int x, int y)
{
    int             r;

    while ((r = x % y) != 0)
    {
        x = y;
        y = r;
    }
    return(y);
}

static void test_malloc(int n_blocks, size_t blk_size)
{
    char           *blocks[MAX_BLOCKS];
    char            str[BUFSIZ];

    sprintf(str, "No. blocks = %5d, Block size = %5zu\n", n_blocks, blk_size);
    printf("%s", str);
    db_prt_note("%s", str);

    mem_alloc(blk_size, n_blocks, 1, blocks);
    db_prt_note("Release in reverse order of allocation\n");
    mem_free(n_blocks, n_blocks - 1, blocks);
    db_prt_note("All memory should be free");

    if (n_blocks > 1)
    {
        mem_alloc(blk_size, n_blocks, 1, blocks);
        db_prt_note("Release in order of allocation\n");
        mem_free(n_blocks, 1, blocks);
        db_prt_note("All memory should be free");
    }

    if (n_blocks > 7)
    {
        int pf = 3;
        while (pf < n_blocks - 1 && gcd(n_blocks, pf) != 1)
            pf += 2;
        mem_alloc(blk_size, n_blocks, pf, blocks);
        db_prt_note("Release in pseudo-random order\n");
        pf += 2;
        while (pf < n_blocks - 1 && gcd(n_blocks, pf) != 1)
            pf += 2;
        mem_free(n_blocks, pf, blocks);
        db_prt_note("All memory should be free");
    }
}

/*
** Test basic malloc/free capability.
**
** More exhaustive testing would use realloc() and calloc() too, and it
** would also allocate space, then free some of it, then allocate some
** more, then free some more, using varying size chunks with some of
** them larger than the minimum block size requested in morecore.  Truly
** thorough testing of PARANOID mode would also trigger all the possible
** failures (writing before/after allocated space, freeing unallocated
** space), with code to handle the recovery from deliberate abuses.
*/
int main(void)
{
    int    n_blocks;
    size_t blk_size;

    db_dump_malloc();

    test_malloc(1, 512);
    test_malloc(2, 777);

    for (n_blocks = MIN_BLOCKS; n_blocks < MAX_BLOCKS; n_blocks *= MUL_BLOCKS)
    {
        for (blk_size = MIN_BLOCK_SIZE; blk_size <= MAX_BLOCK_SIZE; blk_size *= MUL_BLOCK_SIZE)
        {
            test_malloc(n_blocks, blk_size);
        }
    }

    puts("OK\n");
    return(0);
}

#endif  /* TEST */
