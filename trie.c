/* SO 13674617/adding-word-to-trie-structure-dictionary */

/*
** I'm trying to create a trie structure which can be inserted words,
** but the struct has to be exactly like this:
*/

typedef struct tNode_t
{
    struct tNode_t **l;
    char            *w;
} tNode;

/*
** The member l is a pointer to an array of 27 pointers to tNodes;
** that's the part I don't understand.
**
** If the array is of pointers to tNodes, how do I insert words into it?
** And since the size of the array is 27 (26 lower case letters a-z and
** the terminating character) how do you know where to input the word
** depending on what the beginning letter is?
*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static tNode *new_node(void)
{
    tNode *tree = malloc(sizeof(tNode));
    assert(tree != 0);
    tree->w = 0;
    tree->l = (tNode **)calloc(27, sizeof(tNode *));
    assert(tree->l != 0);
    return(tree);
}

static void add_word_suffix(tNode *tree, char const *word, char const *suffix)
{
    int c;
    assert(tree != 0);
    assert(tree->l != 0);
    fprintf(stderr, "-->> %s: word [%s], suffix [%s]\n", __func__, word, suffix);
    while ((c = *suffix++) != '\0')
    {
        if (isalpha(c))
        {
            fprintf(stderr, "---- %s: letter %c (index %d)\n", __func__, c, c - 'a' + 1);
            c = tolower(c) - 'a' + 1;
            assert(tree->l != 0);
            if (tree->l[c] == 0)
                tree->l[c] = new_node();
            fprintf(stderr, "---- %s: recurse: [%s]/[%s]\n", __func__, word, suffix);
            add_word_suffix(tree->l[c], word, suffix);
            fprintf(stderr, "<<-- %s\n", __func__);
            return;
        }
    }
    if (tree->w != 0)
    {
        printf("---- %s: tree already contains word [%s] at [%s]\n", __func__, word, tree->w);
        return;
    }
    tree->w = strdup(word);
    fprintf(stderr, "<<-- %s: inserted word [%s]\n", __func__, tree->w);
}

static void add_word(tNode *tree, char const *word)
{
    add_word_suffix(tree, word, word);
}

static tNode *find_word_suffix(tNode *tree, char const *word, char const *suffix)
{
    int c;
    fprintf(stderr, "-->> %s: word [%s] suffix[%s]\n", __func__, word, suffix);
    while ((c = *suffix++) != '\0')
    {
        if (isalpha(c))
        {
            fprintf(stderr, "---- %s: letter %c\n", __func__, c);
            c = tolower(c) - 'a' + 1;
            if (tree->l[c] == 0)
                return(0);
            //if (*suffix == '\0')
            //    break;
            tNode *rv = find_word_suffix(tree->l[c], word, suffix);
            if (rv == 0)
            {
                fprintf(stderr, "<<-- %s: missing [%s]/[%s]\n", __func__, word, suffix);
                return 0;
            }
            fprintf(stderr, "<<-- %s: found [%s] for [%s]/[%s]\n", __func__, rv->w, word, suffix);
            return rv;
        }
    }
    if (tree->w == 0)
    {
        fprintf(stderr, "<<-- %s: missing [%s]/[%s]\n", __func__, word, suffix);
        return 0;
    }
    fprintf(stderr, "<<-- %s: found [%s] for [%s]/[%s]\n", __func__, tree->w, word, suffix);
    return(tree);
}

static tNode *find_word(tNode *tree, char const *word)
{
    return find_word_suffix(tree, word, word);
}

int main(void)
{
    tNode *root = new_node();

    /* First test */
    char const *word = "cab";
    add_word(root, word);
    tNode *leaf = find_word(root, word);
    printf("Leaf word = %s\n", leaf->w);

    /* Second, more comprehensive test */
    static char const *words[] =
    {
        "cabal",
        "cabbie",
        "cab",
        "duck",
        "cabs",
        "amniocentesis",
        "amniocentesis",
        "amniocentesis",
        "cam",
        "cab",
        "zulu",
        "alpha",
        "bravo",
        "Charlie",
        "delta",
        "echo",
        "foxtrot",
        "golf",
        "hotel",
        "India",
        "Juliet",
        "kilo",
        "Lima",
        "Mike",
        "November",
        "Oscar",
        "Papa",
        "Quebec",
        "Romeo",
        "Sierra",
        "Tango",
        "uMBRelLA",
        "Victor",
        "Whisky",
        "X-ray",
        "Yankee",
        "Zulu",
    };
    size_t num_words = sizeof(words) / sizeof(words[0]);

    for (size_t i = 0; i < num_words; i++)
    {
        if (i % 2 == 0)
            add_word(root, words[i]);
        tNode *leaf = find_word(root, words[i]);
        if (leaf == 0)
            printf("Word [%s] is missing\n", words[i]);
        else
            printf("Leaf [%s] for [%s]\n", leaf->w, words[i]);
    }

    return(0);
}
