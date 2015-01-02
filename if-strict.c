/*
 * if.c - original source code for the Sixth Edition (V6) UNIX
 *    conditional command
 *
 *  From: Sixth Edition (V6) UNIX /usr/source/s1/if.c
 *
 *  NOTE: The first 44 lines of this file have been added by
 *        Jeffrey Allen Neitzel <jan (at) v6shell (dot) org>
 *        in order to comply with the license.  The file is
 *        otherwise unmodified.
 */
/*-
 * Copyright (C) Caldera International Inc.  2001-2002.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code and documentation must retain the above
 *    copyright notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed or owned by Caldera
 *      International, Inc.
 * 4. Neither the name of Caldera International, Inc. nor the names of other
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE LIABLE FOR ANY DIRECT,
 * INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* On Mac OS X, #include <stdlib.h> manages to #include <sys/wait.h> too! */
#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* write(), lseek(), execv(), close(), fork() */
#include <fcntl.h>      /* open() */
#include <sys/wait.h>   /* wait() */

static inline int seek(int fd, int offset, int whence) { return lseek(fd, offset, whence); }

/* if command */

static int ap;
static int ac;
static char **av;

static char *nxtarg(void);
static int doex(int earg);
static int e1(void);
static int e2(void);
static int e3(void);
static int eq(const char *a, const char *b);
static int expr(void);
static int tcreat(const char *a);
static int tio(const char *a, int f);

int main(int argc, char **argv)
{
    argv[argc] = 0; /* Pointless in modern C */
    ac = argc;
    av = argv;
    ap = 1;
    if (argc < 2)
        return 1;
    if (expr())
    {
        if (doex(0))
        {
            write(1, "no command\n", 11);
            seek(0, 0, 2);
        }
    }
    return 0;
}

char *nxtarg(void)
{
    if (ap > ac)
        return(ap++, (char *)0);
    return(av[ap++]);
}

int expr(void)
{
    int p1;

    p1 = e1();
    if (eq(nxtarg(), "-o"))
        return(p1 | expr());
    ap--;
    return(p1);
}

int e1(void)
{
    int p1;

    p1 = e2();
    if (eq(nxtarg(), "-a"))
        return(p1 & e1());
    ap--;
    return(p1);
}

int e2(void)
{
    if (eq(nxtarg(), "!"))
        return(!e3());
    ap--;
    return(e3());
}

int e3(void)
{
    int p1, ccode;
    register char *a;
    register char *b;

    ccode = 0;
    if ((a = nxtarg()) == 0)
        goto err;
    if (eq(a, "("))
    {
        p1 = expr();
        if (!eq(nxtarg(), ")"))
            goto err;
        return(p1);
    }

    if (eq(a, "-r"))
        return(tio(nxtarg(), 0));

    if (eq(a, "-w"))
        return(tio(nxtarg(), 1));

    if (eq(a, "-c"))
        return(tcreat(nxtarg()));

    if (eq(a, "{"))  /* execute a command for exit code */
    {
        if (fork()) /*parent*/
            wait(&ccode);
        else   /*child*/
        {
            doex(1);
            goto err;
        }
        while ((a = nxtarg()) && (!eq(a, "}")))
            ;
        return(ccode ? 0 : 1);
    }

    b = nxtarg();
    if (b == 0)
        goto err;
    if (eq(b, "="))
        return(eq(a, nxtarg()));

    if (eq(b, "!="))
        return(!eq(a, nxtarg()));
err:
    write(1, "if error\n", 9);
    exit(9);
}

int tio(const char *a, int f)
{
    int fd = open(a, f);
    if (fd >= 0)
    {
        close(fd);
        return(1);
    }
    return(0);
}

int tcreat(const char *a)
{
    return(a != 0);
}

int eq(const char *a, const char *b)
{
    register int i;

    i = 0;
l:
    if (a[i] != b[i])
        return(0);
    if (a[i++] == '\0')
        return(1);
    goto l;
}

int doex(int earg)
{
    register int np, i, c;
    char *nargv[50], *na;

    np = 0;
    while ((na = nxtarg()) != 0)
    {
        if (earg && eq(na, "}"))
            break;
        nargv[np++] = na;
    }
    if (earg && (!eq(na, "}")))
        return(9);
    nargv[np] = 0;
    if (np == 0)
        return(earg);
    execv(nargv[0], nargv);
    i = 0;
    char ncom[] = "/usr/bin/xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    while ((c = nargv[0][i]) != '\0')
    {
        ncom[9 + i++] = c;
    }
    ncom[9 + i] = '\0';
    execv(ncom + 4, nargv);
    execv(ncom, nargv);
    return(1);
}
