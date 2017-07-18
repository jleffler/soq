/* SO 4489-4213 */
#include "timer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Q: https://stackoverflow.com/q/779875
// A: https://stackoverflow.com/a/779960
static char *replace1(const char *orig, const char *rep, const char *with)
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
static char *replace2(const char *original, const char *pattern, const char *replacement)
{
    size_t replen = strlen(replacement);
    size_t patlen = strlen(pattern);
    size_t orilen = strlen(original);
    size_t patcnt = 0;
    const char *oriptr;
    const char *patloc;

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
static char* replace3(const char* s, const char* term, const char* new_term)
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

static char *replace4(const char *string, const char *oldpiece, const char *newpiece)
{
    int str_index, newstr_index, oldpiece_index, end,
        new_len, old_len, cpy_len;
    char *c;
    if ((c = (char *)strstr(string, oldpiece)) == NULL)
        return strdup(string);

    char *newstring = malloc(10000);
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

static char *replace5(const char *orig, const char *rep, const char *with)
{
    char *result;
    const char *ins;
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

#if 0
/*
** As with replace4(), if there's no match, this code leaks horribly.
** Also, if there's no match, it is not clear that it is safe to free
** the return value.  Yet normally, the return value should be freed.
**
** replace6() only replaces one occurrence of the pattern, not all.
** That explains why it is so fast!
*/
static char *replace6(const char *st, const char *orig, const char *repl)
{
    char *ch;
    if (!(ch = strstr(st, orig)))
        return strdup(st);
    char *buffer = malloc(4000);
    strncpy(buffer, st, ch - st);
    buffer[ch - st] = 0;
    sprintf(buffer + (ch - st), "%s%s", repl, ch + strlen(orig));
    return buffer;
}
#endif

static char *replace7(const char *orig, const char *rep, const char *with)
{
    char *result;
    const char *ins;
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

static char *replace8(const char *str, const char *old, const char *new)
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

enum { MAX_RESIDUE = 64 };

static int debug = 0;

static inline size_t max_size(size_t x, size_t y) { return (x > y) ? x : y; }

static char *str_gsub_matchnull(const char *haystack, const char *new_needle)
{
    size_t h_len = strlen(haystack);
    size_t n_len = strlen(new_needle);

    size_t r_len = (h_len + 1) * (n_len + 1);
    char *result = malloc(r_len);
    if (result == 0)
        return 0;
    char *dst = result;
    const char *src = haystack;
    const char *end = haystack + h_len;
    while (src <= end)
    {
        memmove(dst, new_needle, n_len);
        dst += n_len;
        *dst++ = *src++;
    }
    return result;
}

static char *replace9(const char *haystack, const char *old_needle, const char *new_needle)
{
    if (*old_needle == '\0')
        return str_gsub_matchnull(haystack, new_needle);
    size_t h_len = strlen(haystack);
    size_t o_len = strlen(old_needle);
    size_t n_len = strlen(new_needle);

    size_t r_len = max_size(h_len, (h_len / o_len + 1) * n_len) + 1;
    if (debug)
        printf("h_len = %zu; o_len = %zu; n_len = %zu; r_len = %zu\n", h_len, o_len, n_len, r_len);
    char *result = malloc(r_len);
    if (result == 0)
        return 0;
    char *dst = result;
    const char *src = haystack;
    const char *end = haystack + h_len;
    char *rep;
    if (debug)
        printf("src = [%s]\n", src);
    while (src < end && (rep = strstr(src, old_needle)) != 0)
    {
        size_t p_len = rep - src;
        memmove(dst, src, p_len);
        dst += p_len;
        memmove(dst, new_needle, n_len);
        dst += n_len;
        src = rep + o_len;
        if (debug)
            printf("src = [%s]\n", src);
    }
    size_t t_len = h_len - (src - haystack) + 1;
    if (debug)
        printf("src = %zu [%s]\n", strlen(src), src);
    memmove(dst, src, t_len);
    dst += t_len;
    size_t x_len = dst - result + 1;

    if (r_len > MAX_RESIDUE && x_len < r_len - MAX_RESIDUE)
    {
        if (debug)
            printf("r_len = %zu; x_len = %zu; saving = %zu\n", r_len, x_len, r_len - x_len);
        char *trunc = realloc(result, x_len);
        if (trunc != 0)
            result = trunc;
    }

    return result;
}

static char data[] =
    "A 2345678901234567890123456789012345678901234567890 "
    "B 2345678901234567890123456789012345678901234567890 "
    "C 2345678901234567890123456789012345678901234567890 "
    "D 2345678901234567890123456789012345678901234567890 "
    "E 2345678901234567890123456789012345678901234567890 "
    "F 2345678901234567890123456789012345678901234567890 "
    "G 2345678901234567890123456789012345678901234567890 "
    "H 2345678901234567890123456789012345678901234567890 "
    "I 2345678901234567890123456789012345678901234567890 "
    "J 2345678901234567890123456789012345678901234567890 "
    "K 2345678901234567890123456789012345678901234567890 "
    "L 2345678901234567890123456789012345678901234567890 "
    "M 2345678901234567890123456789012345678901234567890 "
    "N 2345678901234567890123456789012345678901234567890 "
    "O 2345678901234567890123456789012345678901234567890 "
    "P 2345678901234567890123456789012345678901234567890 "
    "Q 2345678901234567890123456789012345678901234567890 "
    "R 2345678901234567890123456789012345678901234567890 "
    "S 2345678901234567890123456789012345678901234567890 "
    "T 2345678901234567890123456789012345678901234567890 "
    "U 2345678901234567890123456789012345678901234567890 "
    "V 2345678901234567890123456789012345678901234567890 "
    "W 2345678901234567890123456789012345678901234567890 "
    "X 2345678901234567890123456789012345678901234567890 "
    "Y 2345678901234567890123456789012345678901234567890 "
    "Z 2345678901234567890123456789012345678901234567890 "
    ;

enum { MAX_COUNT = 80000 };

typedef char *(Replace)(const char *haystack, const char *needle, const char *thread);

static void test_replace(const char *tag, Replace replace, unsigned seed)
{
    srand(seed);
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
    unsigned seed = time(0);

    test_replace("replace1", replace1, seed);
    test_replace("replace2", replace2, seed);
#if 0
    test_replace("replace3", replace3, seed);
#endif
    test_replace("replace4", replace4, seed);
    test_replace("replace5", replace5, seed);
#if 0
    test_replace("replace6", replace6, seed);
#endif
    test_replace("replace7", replace7, seed);
    test_replace("replace8", replace8, seed);
    test_replace("replace9", replace9, seed);

    return 0;
}
