#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Q: https://stackoverflow.com/q/779875
// A: https://stackoverflow.com/a/779960
static char *replace1(char *orig, char *rep, char *with)
{
    char *result;
    char *ins;
    char *tmp;
    size_t len_rep;
    size_t len_with;
    size_t len_front;
    int count;

    if (!orig)
        return NULL;
    if (!rep || !(len_rep = strlen(rep)))
        return NULL;
    if (!(ins = strstr(orig, rep)))
        return NULL;
    if (!with)
        with = "";
    len_with = strlen(with);

    for (count = 0; (tmp = strstr(ins, rep)); ++count)
    {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if (!result)
        return NULL;

    while (count--)
    {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}

// Q: https://stackoverflow.com/q/779875
// A: https://stackoverflow.com/a/780024
static char *replace2(char *original, char *pattern, char *replacement)
{
    size_t replen = strlen(replacement);
    size_t patlen = strlen(pattern);
    size_t orilen = strlen(original);
    size_t patcnt = 0;
    char *oriptr;
    char *patloc;

    for (oriptr = original; (patloc = strstr(oriptr, pattern)) != 0; oriptr = patloc + patlen)
    {
        patcnt++;
    }
    {
        size_t retlen = orilen + patcnt * (replen - patlen);
        char *const returned = (char *)malloc(sizeof(char) * (retlen + 1));
        if (returned != NULL)
        {
            char *retptr = returned;
            for (oriptr = original; (patloc = strstr(oriptr, pattern)) != 0; oriptr = patloc + patlen)
            {
                size_t skplen = patloc - oriptr;
                strncpy(retptr, oriptr, skplen);
                retptr += skplen;
                strncpy(retptr, replacement, replen);
                retptr += replen;
            }
            strcpy(retptr, oriptr);
        }
        return returned;
    }
}

#if 0
static char* replace3(char* s, char* term, char* new_term)
{
    //error
    char *nw = NULL, *pos;
    char *cur = s;
    while(pos = strstr(cur, term))
    {
        nw = (char*)realloc(nw, pos - cur + strlen(new_term));
        strncat(nw, cur, pos-cur);
        strcat(nw, new_term);
        cur = pos + strlen(term);
    }
    strcat(nw, cur);
    //free(s);
    return nw;
}
#endif

/*
** If there's no match, this code leaks horribly.  Also, if there's no
** match, it is not clear that it is safe to free the return value.  Yet
** normally, the return value should be freed.
*/
static char *replace4(char *string, char *oldpiece, char *newpiece)
{
    int str_index, newstr_index, oldpiece_index, end,
        new_len, old_len, cpy_len;
    char *c;
    char *newstring = malloc(10000);
    //static char newstring[10000];
    if ((c = (char *)strstr(string, oldpiece)) == NULL)
        return string;
    new_len        = strlen(newpiece);
    old_len        = strlen(oldpiece);
    end            = strlen(string) - old_len;

    oldpiece_index = c - string;
    newstr_index = 0;
    str_index = 0;
    while (str_index <= end && c != NULL)
    {
        cpy_len = oldpiece_index - str_index;
        strncpy(newstring + newstr_index, string + str_index, cpy_len);
        newstr_index += cpy_len;
        str_index    += cpy_len;

        strcpy(newstring + newstr_index, newpiece);
        newstr_index += new_len;
        str_index    += old_len;

        if ((c = (char *)strstr(string + str_index, oldpiece)) != NULL)
            oldpiece_index = c - string;
    }

    strcpy(newstring + newstr_index,
           string + str_index);
    return newstring;
}

static char *replace5(char *orig, char *rep, char *with)
{
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count)
    {
        ins = tmp + len_rep;
    }
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if (!result)
        return NULL;
    while (count--)
    {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}

/*
** As with replace4(), if there's no match, this code leaks horribly.
** Also, if there's no match, it is not clear that it is safe to free
** the return value.  Yet normally, the return value should be freed.
**
** replace6() only replaces one occurrence of the pattern, not all.
** That explains why it is so fast!
*/
static char *replace6(char *st, char *orig, char *repl)
{
    //static char buffer[4000];
    char *buffer = malloc(4000);
    char *ch;
    if (!(ch = strstr(st, orig)))
        return st;
    strncpy(buffer, st, ch - st);
    buffer[ch - st] = 0;
    sprintf(buffer + (ch - st), "%s%s", repl, ch + strlen(orig));
    return buffer;
}

static char *replace7(char *orig, char *rep, char *with)
{
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;
    if (!orig)
    {
        return NULL;
    }
    if (!rep)
    {
        rep = "";
    }
    len_rep = strlen(rep);
    if (!with)
    {
        with = "";
    }
    len_with = strlen(with);

    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)) != 0; ++count)
    {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if (!result)
    {
        return NULL;
    }
    while (count--)
    {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}

static char *replace8(char *str, char *old, char *new)
{
    int i, count = 0;
    int newlen = strlen(new);
    int oldlen = strlen(old);
    for (i = 0; str[i]; ++i)
        if (strstr(&str[i], old) == &str[i])
            ++count, i += oldlen - 1;

    char *ret = (char *)calloc(i + 1 + count * (newlen - oldlen), sizeof(char));
    if (!ret)
        return "";
    i = 0;
    while (*str)
        if (strstr(str, old) == str)
            strcpy(&ret[i], new),
            i += newlen,
            str += oldlen;
        else
            ret[i++] = *str++;

    ret[i] = '\0';
    return ret;
}

static char data[] =
    "A2345678901234567890123456789012345678901234567890"
    "B2345678901234567890123456789012345678901234567890"
    "C2345678901234567890123456789012345678901234567890"
    "D2345678901234567890123456789012345678901234567890"
    "E2345678901234567890123456789012345678901234567890"
    "F2345678901234567890123456789012345678901234567890"
    "G2345678901234567890123456789012345678901234567890"
    "H2345678901234567890123456789012345678901234567890"
    "I2345678901234567890123456789012345678901234567890"
    "J2345678901234567890123456789012345678901234567890"
    "K2345678901234567890123456789012345678901234567890"
    "L2345678901234567890123456789012345678901234567890"
    "M2345678901234567890123456789012345678901234567890"
    "N2345678901234567890123456789012345678901234567890"
    "O2345678901234567890123456789012345678901234567890"
    "P2345678901234567890123456789012345678901234567890"
    "Q2345678901234567890123456789012345678901234567890"
    "R2345678901234567890123456789012345678901234567890"
    "S2345678901234567890123456789012345678901234567890"
    "T2345678901234567890123456789012345678901234567890"
    "U2345678901234567890123456789012345678901234567890"
    "V2345678901234567890123456789012345678901234567890"
    "W2345678901234567890123456789012345678901234567890"
    "X2345678901234567890123456789012345678901234567890"
    "Y2345678901234567890123456789012345678901234567890"
    "Z2345678901234567890123456789012345678901234567890"
    ;

enum { MAX_COUNT = 80000 };

static void test_replace(const char *tag, char *(*replace)(char *data, char *find, char *repl))
{
    int len = strlen(data);
    char *source = strdup(data);
    Clock clk;
    clk_init(&clk);
    clk_start(&clk);
    for (int current = 0; current < MAX_COUNT; current++)
    {
        strcpy(source, data);
        for (int i = 0; i < 20; i++)
            source[rand() % len] = (rand() % 10) + '0';
        char find[2] = { (rand() % 10) + '0', '\0' };
        char *temp = replace(source, find, "black");
        free(temp);
    }
    clk_stop(&clk);
    char buffer[32];
    printf("%-10s %12s\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)));
    free(source);
}

int main(void)
{
    srand(time(0));

    test_replace("replace1", replace1);
    test_replace("replace2", replace2);
#if 0
    test_replace("replace3", replace3);
#endif
    test_replace("replace4", replace4);
    test_replace("replace5", replace5);
    test_replace("replace6", replace6);
    test_replace("replace7", replace7);
    test_replace("replace8", replace8);

    return 0;
}
