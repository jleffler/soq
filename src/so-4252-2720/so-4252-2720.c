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

static char word[1024];
static int k = 0;

static
void printResult(FILE *file, struct node *r)
{
    int temp;
    for (int i = 0; i < 26; i++)
    {
        struct node *c = r->child[i];
        if (c == NULL)
        {
            continue;
        }
        if (c->isword == 1 && c->leaf == 1)
        {
            word[k] = i + 'a';
            word[k + 1] = '\0';
            fprintf(file, "%s %d %d\n", word, c->occurrence, c->super);
            continue;
        }
        if (c->isword == 0)
        {
            word[k] = i + 'a';
            temp = k;
            k++;
            printResult(file, c);
            k = temp;
        }
        if (c->isword == 1 && c->leaf == 0)
        {
            word[k] = i + 'a';
            word[k + 1] = '\0';
            temp = k;
            k++;
            c->isword = 0;
            fprintf(file, "%s %d %d\n", word, c->occurrence, c->super);
            printResult(file, c);
            c->isword = 1;
            k = temp;
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

    printResult(stdout, root);

    return 0;
}
