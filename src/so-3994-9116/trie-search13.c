/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Trie-based word searching
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018
*/

/*TABSTOP=4*/

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
#include "posixver.h"
#include "stderr.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* This doesn't really work with Git - which is actually a reason for not using Git */
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_trie_search17_c[];
const char jlss_id_trie_search17_c[] = "@(#)$Id$";
#endif /* lint */

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

    char *word = 0;
    size_t wordsize = 0;
    while (getline(&word, &wordsize, dic) != 0)
    {
        word[strcspn(word, "\r\n")] = '\0';
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

static void load_dictionary(const char *dictionary)
{
    if (load(dictionary))
    {
        printf("Nominal dictionary size: %d\n", dictionary_size);
        print_trie(root);
    }
    else
        err_remark("failed to load dictionary file %s\n", dictionary);
}

static size_t find_prefix_word(const char *word, const node *trie)
{
    assert(islower((unsigned char)word[0]) || word[0] == '\0');
    if (word[0] == '\0')
        return 1;
    else
    {
        int code = word[0] - 'a';
        if (trie->children[code] == 0)
            return 0;
        return find_prefix_word(&word[1], trie->children[code]);
    }
}

static void check_word(const char *word)
{
    size_t wordlen = strlen(word);
    size_t max_word = find_prefix_word(word, root);
    assert(max_word <= wordlen);
    if (wordlen == max_word)
        printf("[%s] is a word\n", word);
    else if (max_word == 0)
        printf("[%s] does not start with a known word\n", word);
    else
        printf("[%s] starts with word [%.*s]\n", word, (int)max_word, word);
}

static const char optstr[] = "hVd:w:";
static const char usestr[] = "[-hV] -d dictionary [-d another]... [-w wordlist] [word ...] ";
static const char hlpstr[] =
    "  -d dictionary  Load words from the dictionary\n"
    "  -h             Print this help message and exit\n"
    "  -w wordlist    Find words from the file containing a list of words\n"
    "  -V             Print version information and exit\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            load_dictionary(optarg);
            break;
        //case 'w':
        //    check_words_from_file(optarg);
        //    break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    for (int i = optind; i < argc; i++)
    {
        check_word(argv[i]);
    }

    free_trie(root);
    return 0;
}
