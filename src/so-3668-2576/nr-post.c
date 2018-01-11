/* SO 36682576 */
#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode BSTNode;
struct BSTNode
{
    int      data;
    BSTNode *left;
    BSTNode *right;
};

typedef struct Stack
{
    size_t    size;
    size_t    top;
    BSTNode **stack;
} Stack;

static void err_syserr(const char *fmt, ...)
{
    int errnum = errno;
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (errnum != 0)
        fprintf(stderr, "(%d: %s)\n", errnum, strerror(errnum));
    exit(1);
}

static void push(Stack *sp, BSTNode *np)
{
    assert(sp != 0 && np != 0);
    if (sp->top == sp->size)
    {
        size_t n_size = (sp->size + 2) * 2;
        void  *n_data = realloc(sp->stack, n_size * sizeof(*sp->stack));
        if (n_data == 0)
            err_syserr("Out of memory (%zu bytes requested)\n",
                       n_size * sizeof(*sp->stack));
        sp->stack = n_data;
        sp->size = n_size;
    }
    sp->stack[sp->top++] = np;
}

static bool isEmpty(Stack *sp)
{
    return sp->top == 0;
}

static void pop(Stack *sp)
{
    if (!isEmpty(sp))
        sp->top--;
}

static void init(Stack *sp)
{
    sp->top = 0;
    sp->size = 0;
    sp->stack = 0;
}

static BSTNode *top(Stack *sp)
{
    if (sp->top == 0)
        return 0;
    return sp->stack[sp->top - 1];
}

static void clean(Stack *sp)
{
    while (sp->top > 0)
        free(sp->stack[--sp->top]);
    free(sp->stack);
    init(sp);
}

static BSTNode *new_node(int data)
{
    BSTNode *np = malloc(sizeof(*np));
    if (np == 0)
        err_syserr("Out of memory (%zu bytes requested)\n", sizeof(*np));
    np->data = data;
    np->left = 0;
    np->right = 0;
    return np;
}

static void printPostOrderIterative(BSTNode *root)
{
    if (!root)
        return;

    Stack s;
    Stack output;
    init(&s);
    init(&output);
    push(&s, root);

    while (isEmpty(&s) != 1)
    {
        BSTNode *cur = top(&s);
        push(&output, cur);
        pop(&s);
        if (cur->left)
            push(&s, cur->left);
        if (cur->right)
            push(&s, cur->right);
    }

    while (isEmpty(&output) != 1)
    {
        BSTNode *c = top(&output);
        printf(" %d", c->data);
        pop(&output);
    }
    putchar('\n');

    clean(&s);
    clean(&output);
}

static void printPostOrderRecursive(BSTNode *root)
{
    if (root != 0)
    {
        printPostOrderRecursive(root->left);
        printPostOrderRecursive(root->right);
        printf(" %d", root->data);
    }
}

static void printInOrderRecursive(BSTNode *root)
{
    if (root != 0)
    {
        printInOrderRecursive(root->left);
        printf(" %d", root->data);
        printInOrderRecursive(root->right);
    }
}

static BSTNode *bst_add(BSTNode *root, int data)
{
    if (root == 0)
        root = new_node(data);
    else if (root->data > data)
        root->left = bst_add(root->left, data);
    else
        root->right = bst_add(root->right, data);
    return root;
}

static void bst_destroy(BSTNode *root)
{
    if (root != 0)
    {
        bst_destroy(root->left);
        bst_destroy(root->right);
        free(root);
    }
}

int main(void)
{
    int data[] =
    {
        71, 57,  4, 31, 47, 65, 69, 65, 98, 81,
        54, 58, 17, 37, 48, 64, 64, 93, 40, 22,
        45, 62, 99, 47, 18, 86, 67, 99, 68, 27,
    };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };

    BSTNode *root = 0;
    for (int i = 0; i < NUM_DATA; i++)
    {
        root = bst_add(root, data[i]);
        printInOrderRecursive(root);
        putchar('\n');
    }

    printPostOrderRecursive(root);
    putchar('\n');
    printPostOrderIterative(root);

    bst_destroy(root);
    return 0;
}
