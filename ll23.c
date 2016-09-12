#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct datatype_t
{
    char *name;
    char *data;
} datatype_t;

struct BST_node
{
    char *name1;
    char *data1;
    struct BST_node *left;
    struct BST_node *right;
};

struct BST_node *Insert(struct BST_node *rootptr, datatype_t *d);

struct BST_node *Insert(struct BST_node *rootptr, datatype_t *d)
{
    if (rootptr == NULL)
    {
        rootptr = (struct BST_node *)malloc(sizeof(struct BST_node));
        rootptr->name1 = d->name;
        rootptr->data1 = d->data;
        printf("%s 1\n", rootptr->name1);
        rootptr->left = rootptr->right = NULL;
    }
    else if (strcmp(rootptr->name1, d->name) < 0)
    {
        printf("%s left\n", rootptr->name1);
        rootptr->left = Insert(rootptr->left, d);
    }
    else if (strcmp(rootptr->name1, d->name) > 0)
    {
        printf("right\n");
        rootptr->right = Insert(rootptr->right, d);
    }
    else
    {
        assert(strcmp(rootptr->name1, d->name) == 0);
        printf("duplicate\n");
    }
    return rootptr;
}

static void BST_print_inorder(const char *tag, struct BST_node *node)
{
    if (tag != NULL)
        printf("%s:\n", tag);
    if (node != NULL)
    {
        BST_print_inorder(NULL, node->left);
        printf("%s (%s)\n", node->name1, node->data1);
        BST_print_inorder(NULL, node->right);
    }
}

static void BST_free(struct BST_node *node)
{
    if (node != NULL)
    {
        BST_free(node->left);
        BST_free(node->right);
        free(node->name1);
        free(node->data1);
        free(node);
    }
}

datatype_t *read(FILE* fp);
datatype_t *read(FILE* fp)
{
    char name[65];
    char data[1465];
    if (fscanf(fp, " %[^,], %[^\n]", name, data) == 2) {
        datatype_t *d = (datatype_t*)malloc(sizeof(datatype_t));
        d->name = strdup(name);
        d->data = strdup(data);
        return d;
    }
    return NULL;
}

int main(void)
{
    /*
    datatype_t earth[] =
    {
        { "Dave", "Studying at UCLA" },
        { "John", "Works at Google" },
        { "Mike", "School teacher" },
    };
    enum { NUM_LINES = sizeof(earth) / sizeof(earth[0]) };
    */

    datatype_t *earth;
    struct BST_node *root = NULL;
    while ((earth = read(stdin)) != NULL)
    //for (int index = 0; index < NUM_LINES; index++)
    {
        if (root != NULL)
            printf("Root node: %s\n", (root->name1));
        //root = Insert(root, &earth[index]);
        root = Insert(root, earth);
        BST_print_inorder("Insert complete", root);
    }

    BST_free(root);
    return 0;
}
