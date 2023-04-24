/*
@(#)File:           grpwd43.c
@(#)Purpose:        Generate random password
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2023
@(#)Derivation:     grpwd43.c 1.2 2023/04/24 06:19:07
*/

/*TABSTOP=4*/

/* Inspired by SO 7594-6155 */
/* https://stackoverflow.com/questions/75946155/random-password-generator-algorithm */
/* Random Password Generator Algorithm */

#include "posixver.h"
#include "grpwd43.h"         /* SSC: Self-sufficiency check */
#include <assert.h>
#include "randseed.h"
#include "prng48.h"

/*
** Tweak this list of alphanumerics plus punctuation to suit.
** For example, list the alphabets twice (or more) to make letters more
** likely than numbers or punctuation.
*/
static const char password[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
    ;
enum { NUM_PASSWORD = sizeof(password) - 1 };

static int initialized = 0;

void gen_random_passwd(size_t length, char buffer[length])
{
    assert(buffer != NULL && length != 0);
    if (buffer == NULL || length == 0)
        return;

    if (initialized == 0)
    {
        unsigned short seed[3];
        random_seed_bytes(sizeof(seed), seed);
        prng48_seed(seed);
        initialized = 1;
    }

    for (size_t i = 0; i < length - 1; i++)
    {
        buffer[i] = password[prng48_rand(0, NUM_PASSWORD - 1)];
    }
    buffer[length - 1] = '\0';
}

#ifdef TEST

#include <stdio.h>

int main(void)
{
    for (int i = 11; i < 31; i++)
    {
        char passwd[i];
        gen_random_passwd(i, passwd);
        printf("%d: %s\n", i - 1, passwd);
    }

    return 0;
}

#endif /* TEST */
