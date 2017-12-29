/* SO 4801-3629 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *skip_space(const char *src)
{
    while (isspace((unsigned char)*src))
        src++;
    return src;
}

static const char *scan_alnum(const char *src)
{
    assert(isalnum((unsigned char)*src));
    while (isalnum((unsigned char)*src))
        src++;
    return src;
}

static const char *scan_punct(const char *src)
{
    assert(ispunct((unsigned char)*src));
    while (ispunct((unsigned char)*src))
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
        if (isalnum((unsigned char)*word))
            eow = scan_alnum(word);
        else if (ispunct((unsigned char)*word))
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
    test_case("Isn't it true that Bill O'Reilly didn't win (he came in 3rd!)? 'Tain't necessarily so!");
    return 0;
}

