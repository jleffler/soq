/* SO 27679013 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BinarySearchTree_t
{
    char *word, *def;
    struct BinarySearchTree_t *left;
    struct BinarySearchTree_t *right;
};
typedef struct BinarySearchTree_t BinarySearchTree;

static void freeTree(BinarySearchTree *root);
static void dump_tree(BinarySearchTree *root);
extern char *insertWord(BinarySearchTree **ptree, const char *word, const char *definition);

char *insertWord(BinarySearchTree **ptree, const char *word, const char *definition)
{
    if (*ptree == NULL)
    {
        BinarySearchTree *tmp = malloc(sizeof(*tmp));
        tmp->word = strdup(word);
        tmp->def = strdup(definition);
        tmp->left = NULL;
        tmp->right = NULL;
        *ptree = tmp;
        return tmp->def;
    }
    else
    {
        BinarySearchTree *tree = *ptree;
        int r = strcmp(tree->word, word);
        if (r == 0)
        {
            free(tree->def);
            tree->def = strdup(definition);
            return tree->def;
        }
        else if (r < 0)
            return insertWord(&tree->right, word, definition);
        else
            return insertWord(&tree->left, word, definition);
    }
}

int main(void)
{
    const char *word_defs[][2] =
    {
        { "cat", "feline" },
        { "dog", "canine" },
        { "box", "carton" },
        { "cat", "purring critter" },
    };
    BinarySearchTree *root = 0;

    for (size_t i = 0; i < sizeof(word_defs) / sizeof(word_defs[0]); i++)
    {
        printf("%zu: Add %s => %s\n", i, word_defs[i][0], word_defs[i][1]);
        char *def = insertWord(&root, word_defs[i][0], word_defs[i][1]);
        dump_tree(root);
        printf("New definition: %s\n", def);
    }

    freeTree(root);

    return 0;
}

static void freeTree(BinarySearchTree *root)
{
    if (root != 0)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root->word);
        free(root->def);
        free(root);
    }
}

static void dump_tree(BinarySearchTree *root)
{
    if (root->left != 0)
        dump_tree(root->left);
    printf("%p: %s => %s\n", (void *)root, root->word, root->def);
    if (root->right != 0)
        dump_tree(root->right);
}
