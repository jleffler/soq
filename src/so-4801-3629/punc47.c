/* SO 4801-3629 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int is_alnum(char c) { return isalnum((unsigned char)c); }
static inline int is_space(char c) { return isspace((unsigned char)c); }
static inline int is_punct(char c) { return ispunct((unsigned char)c); }

static const char *skip_space(const char *src)
{
    while (is_space(*src))
        src++;
    return src;
}

static const char *scan_alnum(const char *src)
{
    assert(is_alnum(*src) || *src == '\'');
    while (is_alnum(*src) || (src[0] == '\'' && (is_alnum(src[1]) || is_space(src[1]))))
        src++;
    return src;
}

static const char *scan_punct(const char *src)
{
    assert(is_punct(*src));
    while (is_punct(*src))
        src++;
    return src;
}

#include "aoscopy.h"

static void printer(const char *str, void *ctxt)
{
    int num = ++*(int *)ctxt;
    printf("%d: [%s]\n", num, str);
}

static void test_case(const char *data)
{
    AoS_Copy *tokens = aosc_create(20);

    printf("Test: [%s]\n", data);
    const char *word = data;
    while (*word != '\0')
    {
        const char *eow;
        eow = word = skip_space(word);
        if (is_alnum(*word) || (word[0] == '\'' && is_alnum(word[1])))
            eow = scan_alnum(word);
        else if (is_punct(*word))
            eow = scan_punct(word);
        if (eow == word)
            break;
        aosc_addbytes(tokens, word, eow);
        word = eow;
    }

    int num = 0;
    aosc_apply_ctxt(tokens, 0, aosc_length(tokens), printer, &num);
    putchar('\n');

    aosc_destroy(tokens);
}

int main(void)
{
    test_case("Hello, my name is Sara!");
    test_case("Isn't it true that Padraig O'Malley didn't win (he came in 3rd!)? 'Tain't necessarily so!");
    test_case("'Tain't an Archimedes' Screw");
    return 0;
}

