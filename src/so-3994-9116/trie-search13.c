/* SO 4997-3644 */
/* Scan onethousandtwohundredandtwentysix into number words */
/*
** Suggestion is to use trie-based scanning.  Note that, for example,
** seven, seventy, seventeen share a common prefix.  So studying the
** string seventhousand needs to recognize seven and then thousand, and
** not error because seventy and seventeen start sevent.
**
** The question (SO 4997-3644) ws closed and deleted (too broad, abandoned).
** The changes between this code and trie89.c generalize it to handle multiple
** files of words.  It isn't clear yet how strings such as the spaceless
** one at the top will be provided.
*/
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stderr.h"

typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

static node *root = 0;
static int dictionary_size = 0;

static void addWord(char *word, node *trie)
{
    assert(islower((unsigned char)word[0]) || word[0] == '\0');
    if (word[0] == '\0')
        trie->is_word = true;
    else
    {
        int code = word[0] - 'a';
        if (trie->children[code] == 0)
        {
            trie->children[code] = calloc(sizeof(node), 1);
            if (trie->children[code] == 0)
            {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
        }
        addWord(&word[1], trie->children[code]);
    }
}

static
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == 0)
        return false;
    if (root == 0)
    {
        dictionary_size = 0;
        root = calloc(1, sizeof(node));
    }
    if (root == 0)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    char word[47];
    while (fgets(word, sizeof(word), dic) != 0)
    {
        char *pos;
        if ((pos = strchr(word, '\n')) != NULL)
            *pos = '\0';
        dictionary_size++;
        for (int i = 0, len = strlen(word); i < len; i++)
        {
            if (!isalpha((unsigned char)word[i]))
                fprintf(stderr, "Non-alphabetic character in '%s'\n", word);
            else
                word[i] = tolower((unsigned char)word[i]);
        }
        addWord(word, root);
    }
    return true;
}

static void print_subtrie(const char *prefix, char nchar, node *child)
{
    if (child != 0)
    {
        int len = strlen(prefix);
        char buffer[len + 2];
        strcpy(buffer, prefix);
        buffer[len] = nchar;
        buffer[len+1] = '\0';
        if (child->is_word)
            printf("%s\n", buffer);
        for (int i = 0; i < 26; i++)
            print_subtrie(buffer, 'a' + i, child->children[i]);
    }
}

static void print_trie(node *top)
{
    for (int i = 0; i < 26; i++)
        print_subtrie("", 'a' + i, top->children[i]);
}

static void free_trie(node *trie)
{
    if (trie != 0)
    {
        for (int i = 0; i < 27; i++)
        {
            if (trie->children[i] != 0)
                free_trie(trie->children[i]);
        }
        free(trie);
    }
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    for (int i = 1; i < argc; i++)
    {
        if (load(argv[i]))
        {
            printf("Nominal dictionary size: %d\n", dictionary_size);
            print_trie(root);
        }
        else
            err_remark("failed to load dictionary file %s\n", argv[i]);
    }
    free_trie(root);
    return 0;
}
