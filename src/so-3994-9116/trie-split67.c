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
** The question (SO 4997-3644) was closed and deleted (too broad, abandoned).
*/

#include "posixver.h"

#include "aoscopy.h"
#include "debug.h"
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
                err_syserr("memory allocation failed for %zu bytes\n", sizeof(node));
        }
        addWord(&word[1], trie->children[code]);
    }
}

static bool valid_word(char *word)
{
    for (size_t i = 0; word[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)word[i]))
        {
            err_remark("Non-alphabetic character in '%s'\n", word);
            return false;
        }
        else
            word[i] = tolower((unsigned char)word[i]);
    }
    return true;
}

/* Dictionary loading is fussier than the word matching once the dictionary is loaded */
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
        err_syserr("memory allocation failed for %zu bytes\n", sizeof(node));

    char *word = 0;
    size_t wordsize = 0;
    while (getline(&word, &wordsize, dic) != -1)
    {
        word[strcspn(word, "\r\n")] = '\0';
        if (valid_word(word))
        {
            dictionary_size++;
            addWord(word, root);
        }
    }
    free(word);
    return true;
}

static void print_subtrie(FILE *fp, const char *prefix, char nchar, const node *child)
{
    if (child == 0)
        return;
    int len = strlen(prefix);
    char buffer[len + 2];
    strcpy(buffer, prefix);
    buffer[len] = nchar;
    buffer[len+1] = '\0';
    if (child->is_word)
        fprintf(fp, "%s\n", buffer);
    for (int i = 0; i < 26; i++)
        print_subtrie(fp, buffer, 'a' + i, child->children[i]);
}

static void print_trie(FILE *fp, const node *top)
{
    for (int i = 0; i < 26; i++)
        print_subtrie(fp, "", 'a' + i, top->children[i]);
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

static bool load_dictionary(const char *dictionary)
{
    if (load(dictionary))
    {
        printf("Nominal dictionary size: %d\n", dictionary_size);
        print_trie(stdout, root);
        return true;
    }
    err_remark("failed to load dictionary file %s\n", dictionary);
    return false;
}

/*
** Identify a word in the dictionary that is a prefix of the current
** word.  That is, if the word is "onethousand", and "one" is in the
** dictionary, then the returned result should be 3.  Assuming that the
** dictionary only contains number-related words, then if the word is
** "forklift", the result should be 0. If the word is "seventen", then
** the result should be 5; if it was "seventeenwords", then 9.
**
** So much for the specification!  Now the implementation.  At any given
** level, the trie node might contain information about word[0].  There
** are N relevant pieces of information:
** -- word[0] == '\0' - return 0.
** -- word[0] is a letter and the node has no entry for that letter;
**    there is no word that contains this prefix; return 0.
** -- word[0] is a letter and the node has an entry for that letter;
**    call recursively to see whether there's a longer word;
**    if there is (rv > 0), return the returned length plus one;
**    if there is not and the child node shows that it is a word,
**    then we have found a word and should return 1;
**    else there is not a word ending here so return 0.
*/
static size_t find_prefix_word(const char *word, const node *trie)
{
    //assert(isalpha((unsigned char)word[0]) || word[0] == '\0');
    DB_TRACE(5, "-->> %s(): word [%s]\n", __func__, word);
    if (word[0] == '\0')
    {
        DB_TRACE(5, "<<-- %s(): empty word\n", __func__);
        return 0;
    }
    else if (!isalpha((unsigned char)word[0]))
    {
        DB_TRACE(5, "<<-- %s(): non-alpha - not a word\n", __func__);
        return 0;
    }
    else
    {
        int code = tolower((unsigned char)word[0]) - 'a';
        if (trie->children[code] == 0)
        {
            DB_TRACE(5, "<<-- %s(): empty node %d\n", __func__, code);
            return 0;
        }
        else
        {
            size_t rv = find_prefix_word(&word[1], trie->children[code]);
            if (rv > 0)
            {
                DB_TRACE(5, "<<-- %s(): found word (%zu) return %zu\n", __func__, rv, rv+1);
                return rv + 1;
            }
            else if (trie->children[code]->is_word)
            {
                DB_TRACE(5, "<<-- %s(): child node is word return 1\n", __func__);
                return 1;
            }
            DB_TRACE(5, "<<-- %s(): child node is not word return 0\n", __func__);
            return 0;
        }
    }
}

static size_t check_word(char *word)
{
    size_t wordlen = strlen(word);
    size_t max_word = find_prefix_word(word, root);
    assert(max_word <= wordlen);
    if (wordlen == max_word)
        printf("[%s] (%zu) is a word\n", word, wordlen);
    else if (max_word == 0)
        printf("[%s] does not start with a known word\n", word);
    else
        printf("[%s] starts with word [%.*s] (%zu)\n", word, (int)max_word, word, max_word);
    return max_word;
}

static size_t find_non_word_len(char *word)
{
    size_t wordlen = strlen(word);
    for (size_t offset = 0; offset < wordlen; offset++)
    {
        DB_TRACE(4, "Test: [%s]\n", word + offset);
        if (!isalpha((unsigned char)word[offset]))
        {
            DB_TRACE(4, "Early exit 1 (%zu)\n", offset);
            assert(offset != 0);
            return offset;
        }
        size_t max_word = find_prefix_word(word + offset, root);
        assert(offset != 0 || max_word == 0);
        if (max_word != 0)
        {
            DB_TRACE(4, "Early exit 2 (%zu)\n", offset);
            assert(offset != 0);
            return offset;
        }
    }
    DB_TRACE(4, "Final exit (%zu)\n", wordlen);
    return wordlen;
}

typedef struct Context
{
    FILE   *fp;
    size_t  counter;
} Context;

static void aos_callback(const char *str, void *ctxt)
{
    Context *cp = ctxt;
    fprintf(cp->fp, "%zu: [%s]\n", cp->counter++, str);
}

static void dump_words(const char *tag, AoS_Copy *aos)
{
    Context ctxt = { .fp = stdout, .counter = 1 };
    fprintf(ctxt.fp, "%s (%zu words):\n", tag, aosc_length(aos));
    aosc_apply_ctxt(aos, 0, aosc_length(aos), aos_callback, &ctxt);
    fflush(ctxt.fp);
}

static void check_word_sequence(char *word)
{
    AoS_Copy *aos = aosc_create(10);

    while (word[0] != '\0')
    {
        size_t i;
        for (i = 0; word[i] != '\0'; i++)
        {
             if (isalpha((unsigned char)word[i]))
                break;
        }
        if (i > 0)
        {
            printf("Non-alpha: [%.*s]\n", (int)i, word);
            aosc_addbytes(aos, word, word + i);
            word += i;
        }
        else
        {
            size_t wordlen = check_word(word);
            if (wordlen > 0)
            {
                printf("Word: [%.*s]\n", (int)wordlen, word);
                aosc_addbytes(aos, word, word + wordlen);
                word += wordlen;
            }
            else
            {
                wordlen = find_non_word_len(word);
                printf("Non-word: [%.*s]\n", (int)wordlen, word);
                aosc_addbytes(aos, word, word + wordlen);
                word += wordlen;
            }
        }
    }
    dump_words("Extracted words", aos);
    aosc_destroy(aos);
    putchar('\n');
}

static void check_words_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == 0)
        err_sysrem("failed to open file '%s' for reading: ", filename);
    else
    {
        size_t length = 0;
        char  *buffer = 0;
        while (getline(&buffer, &length, fp) != -1)
        {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            check_word_sequence(buffer);
        }
        free(buffer);
        fclose(fp);
    }
}

static const char optstr[] = "hVd:w:D:";
static const char usestr[] = "[-hV][-D debug] -d dictionary [-d another]... [-w wordlist] [word ...] ";
static const char hlpstr[] =
    "  -d dictionary  Load words from the dictionary\n"
    "  -h             Print this help message and exit\n"
    "  -w wordlist    Find words from the file containing a list of words\n"
    "  -D debug       Set debug level (0..9)\n"
    "  -V             Print version information and exit\n"
    ;

int main(int argc, char **argv)
{
    bool loaded = false;
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            if (!load_dictionary(optarg))
                exit(1);
            loaded = true;
            break;
        case 'w':
            if (!loaded)
                err_error("Must load a dictionary before analyzing words\n");
            check_words_from_file(optarg);
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'D':
            db_setdebug(atoi(optarg));
            break;
        case 'V':
            err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (optind < argc && !loaded)
        err_error("Must load a dictionary before analyzing words\n");
    for (int i = optind; i < argc; i++)
    {
        check_word_sequence(argv[i]);
    }

    free_trie(root);
    return 0;
}
