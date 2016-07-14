/*
** Stack Overflow question - since deleted.
** Title: "Access Violation error. AVL TREE during insertion"
** Body:
** So I got an AVL tree online for a project, and I am trying to insert
** elements with a loop to see if it works.  Obviously it's not working;
** I am getting an access violation error.
**
** Here is the tree.  The code is long, I know, but I can tell you that
** it's in the insert function not the others.
**
** This is the loop I have.
**
**      MY_TREE pRoot=NULL;
**
**      //pRoot = my_tree_init_default();
**      for (i = 0;  i < 99; i++){
**          number = i;
**          pRoot=pRoot->insert(pRoot, number, pResult);
**          printf("a");
**      }
**
** It's crashing before 1 element is added.  However, when I do the init
** function, 1 element is added before it crashes.  I think it has to do
** with the function pointers.
**
** Traces found at:
** http://vbnetlocal.blogspot.com/2015/06/access-violation-error-avl-tree-during.html
** Also previously found at:
** http://eclipsexina.blogspot.com/2015/06/access-violation-error-avl-tree-during.html
** Still no question number - grrrr!
** The code crashes as advertised.
**
** I've done an indeterminate amount of work done on the code.  The
** function declarations at the top have been cleaned up (duplicate
** removed), and the code overall has been run through 'decrust'.
*/

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct node *MY_TREE;
typedef struct node *Node_ptr;
typedef struct node Node;

MY_TREE deldata(MY_TREE pRoot, int, int *);
MY_TREE delete_node(MY_TREE pRoot, MY_TREE hNode, int *);
MY_TREE insert(MY_TREE hRoot, int data, int *h);
MY_TREE my_tree_init_default(int data);
Node_ptr balleft(Node_ptr pRoot, int *h);
Node_ptr balright(Node_ptr pRoot, int *);
void display(MY_TREE pRoot);
void init_tree_functions(Node_ptr pRoot);
void tree_destroy(MY_TREE pRoot);

struct node
{
    MY_TREE (*deldata)(MY_TREE pRoot, int, int *);
    void (*display)(MY_TREE pRoot);
    void (*tree_destroy)(MY_TREE pRoot);
    MY_TREE (*insert)(MY_TREE hRoot, int data, int *h);

    int data;
    int balfact;
    Node_ptr left;
    Node_ptr right;
};

void init_tree_functions(Node_ptr pRoot)
{
    pRoot->tree_destroy = tree_destroy;
    pRoot->deldata = deldata;
    pRoot->display = display;
    pRoot->insert = insert;
}

MY_TREE my_tree_init_default(int data)
{
    Node_ptr pRoot = (Node_ptr) malloc(sizeof(*pRoot));

    if (pRoot == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    pRoot->left = NULL;
    pRoot->right = NULL;
    pRoot->data = data;
    pRoot->balfact = 0;
    init_tree_functions(pRoot);

    return pRoot;
}

MY_TREE insert(MY_TREE hRoot, int data, int *h)
{
    Node_ptr node1, node2;
    Node_ptr pRoot = hRoot;

    if (pRoot == NULL)
    {
        *h = TRUE;
        return my_tree_init_default(data);
    }

    if (data < pRoot->data)
    {
        pRoot->left = insert((MY_TREE)pRoot->left, data, h);

        if (*h)
        {
            switch (pRoot->balfact)
            {
            case 1:
                node1 = pRoot->left;
                if (node1->balfact == 1)
                {
                    pRoot->left = node1->right;
                    node1->right = pRoot;
                    pRoot->balfact = 0;
                    pRoot = node1;
                }
                else
                {
                    node2 = node1->right;
                    node1->right = node2->left;

                    node2->left = node1;
                    pRoot->left = node2->right;
                    node2->right = pRoot;
                    if (node2->balfact == 1)
                        pRoot->balfact = -1;
                    else
                        pRoot->balfact = 0;
                    if (node2->balfact == -1)
                        node1->balfact = 1;
                    else
                        node1->balfact = 0;
                    pRoot = node2;
                }
                pRoot->balfact = 0;
                *h = FALSE;
                break;

            case 0:
                pRoot->balfact = 1;
                break;

            case -1:
                pRoot->balfact = 0;
                *h = FALSE;
            }
        }
    }

    if (data > pRoot->data)
    {
        pRoot->right = insert((MY_TREE)pRoot->right, data, h);

        if (*h)
        {
            switch (pRoot->balfact)
            {
            case 1:
                pRoot->balfact = 0;
                *h = FALSE;
                break;

            case 0:
                pRoot->balfact = -1;
                break;

            case -1:
                node1 = pRoot->right;
                if (node1->balfact == -1)
                {
                    pRoot->right = node1->left;
                    node1->left = pRoot;
                    pRoot->balfact = 0;
                    pRoot = node1;
                }
                else
                {
                    node2 = node1->left;
                    node1->left = node2->right;
                    node2->right = node1;

                    pRoot->right = node2->left;
                    node2->left = pRoot;

                    if (node2->balfact == -1)
                        pRoot->balfact = 1;
                    else
                        pRoot->balfact = 0;
                    if (node2->balfact == 1)
                        node1->balfact = -1;
                    else
                        node1->balfact = 0;
                    pRoot = node2;
                }
                pRoot->balfact = 0;
                *h = FALSE;
            }
        }
    }

    return((MY_TREE)pRoot);
}

MY_TREE deldata(MY_TREE hRoot, int data, int *h)
{
    Node_ptr pRoot = (Node_ptr)hRoot;
    Node_ptr node;

    if (!pRoot)
    {
        return(pRoot);
    }
    else if (data < pRoot->data)
    {
        pRoot->left = deldata((MY_TREE)pRoot->left, data, h);
        if (*h)
            pRoot = balright(pRoot, h);
    }
    else if (data > pRoot->data)
    {
        pRoot->right = deldata((MY_TREE)pRoot->right, data, h);
        if (*h)
            pRoot = balleft(pRoot, h);
    }
    else
    {
        node = pRoot;
        if (node->right == NULL)
        {
            pRoot = node->left;
            *h = TRUE;
            free(node);
        }
        else if (node->left == NULL)
        {
            pRoot = node->right;
            *h = TRUE;
            free(node);
        }
        else
        {
            node->right = delete_node((MY_TREE)node->right, node, h);
            if (*h)
                pRoot = balleft(pRoot, h);
        }
    }
    return((MY_TREE)pRoot);
}

MY_TREE  delete_node(MY_TREE hSucc, MY_TREE hNode, int *h)
{
    Node_ptr node = (Node_ptr)hNode;
    Node_ptr succ = (Node_ptr)hSucc;

    Node_ptr temp = succ;
    if (succ->left != NULL)
    {
        succ->left = delete_node((MY_TREE)succ->left, node, h);
        if (*h)
            succ = balright(succ, h);
    }
    else
    {
        temp = succ;
        node->data = succ->data;
        succ = succ->right;
        free(temp);
        *h = TRUE;
    }
    return((MY_TREE)succ);
}

Node_ptr balright(Node_ptr pRoot, int *h)
{
    Node_ptr node1, node2;

    switch (pRoot->balfact)
    {
    case 1:
        pRoot->balfact = 0;
        break;

    case 0:
        pRoot->balfact = -1;
        *h = FALSE;
        break;

    case -1:
        node1 = pRoot->right;
        if (node1->balfact <= 0)
        {
            pRoot->right = node1->left;
            node1->left = pRoot;
            if (node1->balfact == 0)
            {
                pRoot->balfact = -1;
                node1->balfact = 1;
                *h = FALSE;
            }
            else
            {
                pRoot->balfact = node1->balfact = 0;
            }
            pRoot = node1;
        }
        else
        {
            node2 = node1->left;
            node1->left = node2->right;
            node2->right = node1;

            pRoot->right = node2->left;
            node2->left = pRoot;

            if (node2->balfact == -1)
                pRoot->balfact = 1;
            else
                pRoot->balfact = 0;
            if (node2->balfact == 1)
                node1->balfact = -1;
            else
                node1->balfact = 0;
            pRoot = node2;
            node2->balfact = 0;
        }
    }
    return(pRoot);
}

Node_ptr  balleft(Node_ptr pRoot, int *h)
{
    Node_ptr node1, node2;

    switch (pRoot->balfact)
    {
    case -1:
        pRoot->balfact = 0;
        break;

    case 0:
        pRoot->balfact = 1;
        *h = FALSE;
        break;

    case 1:
        node1 = pRoot->left;
        if (node1->balfact >= 0)
        {
            pRoot->left = node1->right;
            node1->right = pRoot;
            if (node1->balfact == 0)
            {
                pRoot->balfact = 1;
                node1->balfact = -1;
                *h = FALSE;
            }
            else
            {
                pRoot->balfact = node1->balfact = 0;
            }
            pRoot = node1;
        }
        else
        {
            node2 = node1->right;
            node1->right = node2->left;
            node2->left = node1;

            pRoot->left = node2->right;
            node2->right = pRoot;

            if (node2->balfact == 1)
                pRoot->balfact = -1;
            else
                pRoot->balfact = 0;
            if (node2->balfact == -1)
                node1->balfact = 1;
            else
                node1->balfact = 0;
            pRoot = node2;
            node2->balfact = 0;
        }
    }
    return(pRoot);
}

void display(MY_TREE hRoot)
{
    Node_ptr pRoot = (Node_ptr)hRoot;
    if (pRoot != NULL)
    {
        display(pRoot->left);
        printf("%d\t", pRoot->data);
        display(pRoot->right);
    }
}

void tree_destroy(MY_TREE hRoot)
{
    Node_ptr pRoot = (Node_ptr)hRoot;
    if (pRoot != NULL)
    {
        tree_destroy(pRoot->left);
        tree_destroy(pRoot->right);
    }
    free(pRoot);
}

#include <assert.h>

int main(void)
{
    MY_TREE pRoot = my_tree_init_default(0);

    for (int i = 0; i < 99; i++)
    {
        int number = i;
        int result = 0;
        int *pResult = &result;
        assert(pRoot != 0);
        assert(pRoot->insert != 0);
        pRoot = pRoot->insert(pRoot, number, pResult);
        printf("Inserted %d (result %d)\n", i, result);
    }

    for (int i = 0; i < 99; i += 10)
    {
        int result = 0;
        pRoot = pRoot->deldata(pRoot, i, &result);
        printf("Deleted %d (result %d)\n", i, result);
    }

    pRoot->display(pRoot);
    putchar('\n');

    pRoot->tree_destroy(pRoot);

    return 0;
}
