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
    struct node *p = r;
    int i = 0;
    int temp;
    while (i != 26)
    {
        if (p->child[i] == NULL)
        {
            i++;
            continue;
        }
        if (p->child[i]->isword == 1 && p->child[i]->leaf == 1)
        {
            word[k] = i + 'a';
            word[k + 1] = '\0';
            fprintf(file, "%s %d %d\n", word, p->child[i]->occurrence, p->child[i]->super);
			i++;
            continue;
        }
        if (p->child[i]->isword == 0)
        {
            word[k] = i + 'a';
            temp = k;
            k++;
            p = p->child[i];
            printResult(file, p);
            k = temp;
            p = p->parent;
        }
        if (p->child[i]->isword == 1 && p->child[i]->leaf == 0)
        {
            word[k] = i + 'a';
            word[k + 1] = '\0';
            temp = k;
            k++;
            p->child[i]->isword = 0;
            fprintf(file, "%s %d %d\n", word, p->child[i]->occurrence, p->child[i]->super);
            p = p->child[i];
            printResult(file, p);
            k = temp;
            p = p->parent;
        }
        i++;
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
// New Node
            struct node *n = (struct node *)malloc(sizeof(struct node));
            n->parent = temp;
            temp->child[index] = n;
            temp->noempty = 1;
        }
// Node Exist
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

    FILE *file;
    char name[1024];
    int num = 0;
    sprintf(name, "man%d.txt", num);
    file = fopen(name, "w");

    printResult(file, root);

    fclose(file);

    return 0;
}
