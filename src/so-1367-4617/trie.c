/* SO 1367-4617 Adding word to trie structure dictionary */

#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

typedef struct tNode_t tNode;
extern void trie_add_word(tNode *trie, char const *word);
extern char const *trie_find_word(tNode *trie, char const *word);
extern void trie_print(tNode *trie);
extern tNode *trie_new(void);
extern void trie_free(tNode *trie);

#endif /* TRIE_H_INCLUDED */

#include "posixver.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct tNode_t
{
    struct tNode_t **l;
    char            *w;
};

static void db_print(char const *fmt, ...);

tNode *trie_new(void)
{
    tNode *trie = malloc(sizeof(tNode));
    assert(trie != 0);      // Abysmal way to validate memory allocation
    trie->w = 0;
    trie->l = (tNode **)calloc(27, sizeof(tNode *));
    assert(trie->l != 0);   // Abysmal way to validate memory allocation
    return(trie);
}

void trie_free(tNode *trie)
{
    assert(trie != 0);
    assert(trie->l != 0);
    for (size_t i = 0; i < 27; i++)
    {
        if (trie->l[i] != 0)
            trie_free(trie->l[i]);
    }
    free(trie->l);
    free(trie->w);
    free(trie);
}

static void add_word_suffix(tNode *trie, char const *word, char const *suffix)
{
    int c;
    assert(trie != 0);
    assert(trie->l != 0);
    db_print("-->> %s: word [%s], suffix [%s]\n", __func__, word, suffix);
    while ((c = *suffix++) != '\0')
    {
        if (isalpha(c))
        {
            db_print("---- %s: letter %c (index %d)\n", __func__, c, c - 'a' + 1);
            c = tolower(c) - 'a' + 1;
            assert(trie->l != 0);
            if (trie->l[c] == 0)
                trie->l[c] = trie_new();
            db_print("---- %s: recurse: [%s]/[%s]\n", __func__, word, suffix);
            add_word_suffix(trie->l[c], word, suffix);
            db_print("<<-- %s\n", __func__);
            return;
        }
    }
    if (trie->w != 0)
    {
        db_print("---- %s: trie already contains word [%s] at [%s]\n", __func__, word, trie->w);
        return;
    }
    trie->w = strdup(word);
    db_print("<<-- %s: inserted word [%s]\n", __func__, trie->w);
}

void trie_add_word(tNode *trie, char const *word)
{
    add_word_suffix(trie, word, word);
}

static char const *find_word_suffix(tNode *trie, char const *word, char const *suffix)
{
    int c;
    db_print("-->> %s: word [%s] suffix[%s]\n", __func__, word, suffix);
    for ( ; (c = *suffix) != '\0'; suffix++)
    {
        if (isalpha(c))
        {
            db_print("---- %s: letter %c\n", __func__, c);
            c = tolower(c) - 'a' + 1;
            if (trie->l[c] == 0)
                return(0);
            char const *rv = find_word_suffix(trie->l[c], word, suffix+1);
            if (rv == 0)
            {
                db_print("<<-- %s: missing [%s]/[%s]\n", __func__, word, suffix);
                return 0;
            }
            db_print("<<-- %s: found [%s] for [%s]/[%s]\n", __func__, rv, word, suffix);
            return rv;
        }
    }
    if (trie->w == 0)
    {
        db_print("<<-- %s: missing [%s]/[%s]\n", __func__, word, suffix);
        return 0;
    }
    db_print("<<-- %s: found [%s] for [%s]/[%s]\n", __func__, trie->w, word, suffix);
    return(trie->w);
}

char const *trie_find_word(tNode *trie, char const *word)
{
    return find_word_suffix(trie, word, word);
}

void trie_print(tNode *trie)
{
    assert(trie != 0);
    assert(trie->l != 0);
    if (trie->w != 0)
        printf("%s\n", trie->w);
    for (size_t i = 0; i < 27; i++)
    {
        if (trie->l[i] != 0)
            trie_print(trie->l[i]);
    }
}

static int debug = 0;

static void db_print(char const *fmt, ...)
{
    if (debug > 0)
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

int main(int argc, char **argv)
{
    tNode *trie = trie_new();

    /* Set debugging - and use argv */
    if (argc > 1 && argv[argc] == 0)
        debug = 1;

    /* First test */
    char const *word = "cab";
    trie_add_word(trie, word);
    char const *leaf = trie_find_word(trie, word);
    printf("Leaf word = %s\n", leaf);
    trie_free(trie);

    /* Second, more comprehensive test */
    static char const *words[] =
    {
        "cabal",         "cabbie",
        "cab",           "centre",
        "cinema",        "cold",
        "culminate",     "culmination",
        "duck",          "cabs",
        "amniocentesis", "amniocentesis",
        "amniocentesis", "cam",
        "cab",           "cab",
        "zulu",          "alpha",
        "bravo",         "Charlie",
        "delta",         "echo",
        "foxtrot",       "golf",
        "hotel",         "India",
        "Juliet",        "kilo",
        "Lima",          "Mike",
        "November",      "Oscar",
        "Papa",          "Quebec",
        "Romeo",         "Sierra",
        "Tango",         "uMBRelLA",
        "Victor",        "Whisky",
        "X-ray",         "Yankee",
        "Zulu",          "Aquarius",
    };
    size_t num_words = sizeof(words) / sizeof(words[0]);
    size_t counter = 0;

    /* First time, add every other word; second time, every word */
    for (size_t mod = 2; mod > 0; mod--)
    {
        trie = trie_new();
        printf("\nTest %zu\n", ++counter);
        for (size_t i = 0; i < num_words; i++)
        {
            if (i % mod == 0)
                trie_add_word(trie, words[i]);
            char const *leaf = trie_find_word(trie, words[i]);
            if (leaf == 0)
                printf("Word [%s] is missing\n", words[i]);
            else
                printf("Word [%s] for [%s]\n", leaf, words[i]);
        }
        printf("\nTrie:\n");
        trie_print(trie);
        trie_free(trie);
    }

    return(0);
}
