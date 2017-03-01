#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length(x) strlen(x)

struct node
{
    struct node *parent;
    int noempty;
    int isword;
    int super;
    int occurrence;
    int leaf;
    struct node *child[26];
};

static
void printResult(FILE *file, struct node *r, char *word, int k)
{
    if (r->isword == 1)
        fprintf(file, "%s %d %d\n", word, r->occurrence, r->super);

    for (int i = 0; i < 26; i++)
    {
        if (r->child[i] != NULL)
        {
            word[k++] = i + 'a';
            word[k] = '\0';
            printResult(file, r->child[i], word, k);
            word[--k] = '\0';
        }
    }
}

static
struct node *insert(struct node *root, char *c)
{
    int i = 0;
    struct node *temp = root;
    int l = length(c);
    while (i != l)
    {
        int index = c[i] - 'a';
        if (temp->child[index] == NULL)
        {
            struct node *n = (struct node *)malloc(sizeof(struct node));
            n->parent = temp;
            temp->child[index] = n;
            temp->noempty = 1;
        }
        if (i != l && temp->leaf == 1)
        {
            temp->leaf = 0;
        }
        temp = temp->child[index];
        i++;
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
