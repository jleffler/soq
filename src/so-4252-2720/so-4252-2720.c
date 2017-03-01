#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    struct node *parent;
    int noempty;        // Redundant with leaf
    int isword;
    int super;          // Essentially unused
    int occurrence;     // Essentially unused
    int leaf;           // Redundant with noempty
    struct node *child[26];
};

static
void printResult(FILE *file, struct node *r, char *word, int k)
{
    assert((r->leaf == 0 && r->noempty != 0) ||
           (r->leaf != 0 && r->noempty == 0));
    if (r->isword == 1)
        fprintf(file, "%s %d %d\n", word, r->occurrence, r->super);

    if (r->leaf == 1)
        return;

    assert(r->noempty > 0);
    word[k+1] = '\0';
    for (int i = 0; i < 26; i++)
    {
        if (r->child[i] != NULL)
        {
            word[k] = i + 'a';
            printResult(file, r->child[i], word, k+1);
        }
    }
    word[k] = '\0';
}

static
struct node *insert(struct node *root, char *c)
{
    struct node *temp = root;
    int l = strlen(c);
    for (int i = 0; i < l; i++)
    {
        if (!isalpha((unsigned char)c[i]))
            break;
        c[i] = tolower((unsigned char)c[i]);
        int index = c[i] - 'a';
        if (temp->child[index] == NULL)
        {
            struct node *n = (struct node *)malloc(sizeof(struct node));
            assert(n != 0);
            memset(n, '\0', sizeof(*n));
            n->parent = temp;
            temp->child[index] = n;
            temp->noempty = 1;
        }
        if (i != l && temp->leaf == 1)
        {
            temp->leaf = 0;
        }
        temp = temp->child[index];
    }
    if (temp->noempty == 0)
    {
        temp->leaf = 1;
    }
    temp->isword = 1;
    return root;
}

int main(void)
{
    struct node *root = (struct node *)malloc(sizeof(struct node));
    assert(root != 0);
    memset(root, '\0', sizeof(*root));

    char line[1024];

    while (fgets(line, sizeof(line), stdin) != 0)
    {
        line[strcspn(line, "\n")] = '\0';
        printf("[%s]\n", line);
        root = insert(root, line);
    }

    char word[1024] = "";
    printResult(stdout, root, word, 0);

    return 0;
}
