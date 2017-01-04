#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { LENGTH = 256 };

// Here's the code
typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

unsigned int wsize = 0;
node *root;

static inline int map_char(unsigned char c)
{
    int t;
    if (isalpha(c))
        t = tolower(c) - 'a';
    else
        t = 26;
    return t;
}

static inline node *alloc_node(void)
{
    node *new_node = calloc(1, sizeof(node));
    if (new_node == 0)
    {
        fprintf(stderr, "Memory allocation failed in %s\n", __func__);
        exit(1);
    }
    return new_node;
}

static bool check(const char *word)
{
    node *chrawler = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int t = map_char(word[i]);
        if (chrawler->children[t] == NULL)
            return false;
        else
            chrawler = chrawler->children[t];
    }

    return chrawler->is_word;
}

// Load function
static bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Failed to open file '%s' for reading\n", dictionary);
        return false;
    }

    root = alloc_node();

    char word[LENGTH];
    while (fgets(word, sizeof(word), inptr) != 0)
    {
        word[strcspn(word, "\n")] = '\0';
        printf("[%s]\n", word);
        node *chrawler = root;
        int len = strlen(word);
        for (int i = 0; i < len; i++)
        {
            int t = map_char(word[i]);
            //printf("t = %d (%c)\n", t, word[i]);
            if (chrawler->children[t] == NULL)
                chrawler->children[t] = alloc_node();
            chrawler = chrawler->children[t];
        }
        chrawler->is_word = 1;
        wsize++;
    }
    printf("%d words read from %s\n", wsize, dictionary);
    fclose(inptr);

    return true;
}

int main(void)
{
    const char *wordfile = "words.txt";
    if (load(wordfile))
    {
        char line[4096];
        while (fgets(line, sizeof(line), stdin) != 0)
        {
            line[strcspn(line, "\n")] = '\0';
            if (check(line))
                printf("[%s] is a word\n", line);
            else
                printf("[%s] is unknown\n", line);
        }
    }
    return 0;
}
