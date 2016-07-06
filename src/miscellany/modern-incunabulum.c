#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long I;
typedef struct
{
    I t;
    I r;
    I d[3];
    I p[2];
} *A;

static I *ma(int n)
{
    return (I*)malloc(n*4);
}

static void mv(I *d, I *s, int n)
{
    for (I i = 0; i < n; i++)
        d[i] = s[i];
}

static I tr(int r, I *d)
{
    I z = 1;
    for (I i = 0; i < r; i++)
        z = z*d[i];
    return z;
}

static A ga(int t, int r, I *d)
{
    A z=(A)ma(5+tr(r, d));
    z->t = t;
    z->r = r;
    mv(z->d, d, r);
    return z;
}

static A iota(A w)
{
    I n=*w->p;
    A z = ga(0, 1, &n);
    for (I i = 0; i < n; i++)
        z->p[i] = i;
    return z;
}

static A plus(A a, A w)
{
    I r = w->r;
    I *d = w->d;
    I n = tr(r, d);
    A z = ga(0, r, d);
    for (I i = 0; i < n; i++)
        z->p[i] = a->p[i]+w->p[i];
    return z;
}

static A from(A a, A w)
{
    I r = w->r-1;
    I *d = w->d+1;
    I n = tr(r, d);
    A z = ga(w->t, r, d);
    mv(z->p, w->p+(n**a->p), n);
    return z;
}

static A box(A w)
{
    A z = ga(1, 0, 0);
    *z->p=(I)w;
    return z;
}

static A cat(A a, A w)
{
    I an = tr(a->r, a->d);
    I wn = tr(w->r, w->d);
    I n = an+wn;
    A z = ga(w->t, 1, &n);
    mv(z->p, a->p, an);
    mv(z->p+an, w->p, wn);
    return z;
}

static A find(A a, A w)
{
    assert(a != 0 && w != 0);
    return 0;
}

static A rsh(A a, A w)
{
    I r = a->r ? *a->d : 1;
    I n = tr(r, a->p);
    I wn = tr(w->r, w->d);
    A z = ga(w->t, r, a->p);
    mv(z->p, w->p, wn = n>wn ? wn : n);
    if (n -= wn)
        mv(z->p+wn, z->p, n);
    return z;
}

static A sha(A w)
{
    A z = ga(0, 1, &w->r);
    mv(z->p, w->d, w->r);
    return z;
}

static A id(A w)
{
    return w;
}

static A size(A w)
{
    A z = ga(0, 0, 0);
    *z->p = w->r ? *w->d : 1;
    return z;
}

static void pi(int i)
{
    printf("%d ", i);
}

static void nl(void)
{
    printf("\n");
}

static void pr(A w)
{
    I r = w->r;
    I *d = w->d;
    I n = tr(r, d);
    for (I i = 0; i < r; i++)
        pi(d[i]);
    nl();
    if (w->t)
    {
        for (I i = 0; i < n; i++)
        {
            printf("< ");
            pr(w->p[i]);
        }
    }
    else
    {
        for (I i = 0; i < n; i++)
            pi(w->p[i]);
    }
    nl();
}

static char vt[]="+{~<#,";
static A (*vd[])(A w, A n) = { 0, plus, from, find, 0,   rsh, cat };
static A (*vm[])(A w)      = { 0, id,   size, iota, box, sha, 0   };
static A st[26];

static int qp(int a)
{
    return a >= 'a' && a <= 'z';
}

static int qv(int a)
{
    return a < 'a';
}

static A ex(I *e)
{
    I a = *e;
    if (qp(a))
    {
        if (e[1] == '=')
            return st[a-'a'] = ex(e+2);
        a = st[a-'a'];
    }
    //return qv(a) ? (*vm[a])(ex(e+1)) : e[1] ? (*vd[e[1]])(a, ex(e+2)) : (A)a;
    if (qv(a))
        return (*vm[a])(ex(e+1));
    else if (e[1])
        return (*vd[e[1]])(a, ex(e+2));
    else
        return (A)a;
}

static A noun(int c)
{
    A z;
    if (c < '0' || c > '9')
        return 0;
    z = ga(0, 0, 0);
    *z->p = c - '0';
    return z;
}

static I verb(int c)
{
    I i = 0;
    while (vt[i])
    {
        if (vt[i++] == c)
            return i;
    }
    return 0;
}

static I *wd(char *s)
{
    I  a;
    I  n = strlen(s);
    I *e = ma(n+1);
    char c;
    for (I i = 0; i < n; i++)
        e[i] = (a = noun(c = s[i])) ? a : (a = verb(c)) ? a : c;
    e[n] = 0;
    return e;
}

int main(void)
{
    char s[99];
    while (fgets(s, sizeof(s), stdin))
    {
        I len = strlen(s);
        if (len > 0)
            s[len-1] = '\0';
        pr(ex(wd(s)));
    }
}
