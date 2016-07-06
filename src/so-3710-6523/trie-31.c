/* SO 37106523 */
/*
** Code amended from what's posted by adding the free_trie() function,
** and this comment, and so on.  That means the word count from running
** on this file isn't the same as in the answer.  Of course, 'tis
** possible t'add t'comments with the extra apostrophes - so it doesn't
** have to be as boring as the old version was.  Ain't'cha glad I've
** done all this??
*/
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    bool wordBool;
    int  wordCount;
    struct node *next[27]; // 26 letters and one space for the apostrophe
} node;

static const char trie_map[] = "'abcdefghijklmnopqrstuvwxyz";
static int numWords = 0;

static void oom(void)
{
    fprintf(stderr, "Out of memory\n");
    exit(EXIT_FAILURE);
}

static int trie_index(char c)
{
    char *p = strchr(trie_map, tolower(c));
    if (p == 0)
        return -1;
    else
        return (p - trie_map);
}

static node *load(const char *dictionary)
{
    FILE *dictionaryf = fopen(dictionary, "r"); // the file to read
    if (dictionaryf == 0)
        return NULL;

    node *base = calloc(sizeof(node), 1);

    node *currNode = base;

    int n;

    while ((n = fgetc(dictionaryf)) != EOF)
    {
        n = trie_index(n);
        if (n >= 0)
        {
            if (currNode->next[n] == NULL)
            {
                currNode->next[n] = calloc(sizeof(node), 1);
                if (currNode->next[n] == NULL)
                    oom();
            }
            currNode = currNode->next[n];
        }
        else if (currNode != base)
        {
            if (!currNode->wordBool)
            {
                currNode->wordBool = true;
                numWords++;
            }
            currNode->wordCount++;
            currNode = base;
        }
        /* else: consecutive non-letters, non-apostrophes */
    }

    if (currNode != base && !currNode->wordBool)
    {
        currNode->wordBool = true;
        numWords++;
    }
    printf("%i distinct words\n", numWords);
    fclose(dictionaryf);
    return base;
}

static void print_trie(node *trie, char *buffer, size_t buflen)
{
    if (trie != 0)
    {
        if (trie->wordBool)
            printf("Word: %3d [%s]\n", trie->wordCount, buffer);
        size_t len = strlen(buffer);
        if (len >= buflen - 2)
        {
            fprintf(stderr, "Word too long!\n[%s]\n", buffer);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 27; i++)
        {
            if (trie->next[i] != 0)
            {
                buffer[len] = trie_map[i];
                buffer[len+1] = '\0';
                print_trie(trie->next[i], buffer, buflen);
            }
        }
    }
}

static void free_trie(node *trie)
{
    if (trie != NULL)
    {
        for (int i = 0; i < 27; i++)
        {
            if (trie->next[i] != 0)
                free_trie(trie->next[i]);
        }
        free(trie);
    }
}

int main(int argc, char **argv)
{
    node *base;
    const char *data = "data";
    if (argc == 2)
        data = argv[1];
    if ((base = load(data)) != NULL)
    {
        printf("Loaded file '%s' OK\n", data);
        char buffer[256] = "";
        print_trie(base, buffer, sizeof(buffer));
        free_trie(base);
    }
    else
        printf("Load of file '%s' failed!\n", data);

    return 0;
}
