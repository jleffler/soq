#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ABin_s *ABin;
struct ABin_s
{
    int valor;
    ABin esq;
    ABin dir;
};

ABin somasAcA_OK(ABin a);
int getsums(ABin a);
ABin somasAcA(ABin a);

static ABin newABin(int valor, ABin esq, ABin dir)
{
    ABin ab = malloc(sizeof(*ab));
    if (ab == 0)
    {
        fprintf(stderr, "Failed to malloc %zu bytes\n", sizeof(*ab));
        exit(EXIT_FAILURE);
    }
    ab->valor = valor;
    ab->esq = esq;
    ab->dir = dir;
    return ab;
}

int getsums(ABin a)
{
    if (a == NULL)
        return 0;
    int esq = getsums(a->esq);
    int dir = getsums(a->dir);
    return(a->valor + esq + dir);
}

ABin somasAcA_OK(ABin a)
{
    ABin b, *res;
    res = &b;

    if (a != NULL)
    {
        b = newABin(getsums(a), NULL, NULL);
        b->esq = somasAcA_OK(a->esq);
        b->dir = somasAcA_OK(a->dir);
    }
    if (a == NULL)
        b = NULL;
    return *res;
}

ABin somasAcA(ABin a)
{
    if (a != NULL)
    {
        a->valor = getsums(a);
        a->esq = somasAcA(a->esq);
        a->dir = somasAcA(a->dir);
    }
    return a;
}

static void print_postorder(ABin node)
{
    if (node != 0)
    {
        print_postorder(node->esq);
        print_postorder(node->dir);
        printf("Valor = %d\n", node->valor);
    }
}

static void print_tree(const char *tag, ABin node)
{
    printf("Tree: %s\n", tag);
    print_postorder(node);
}

static void free_tree(ABin node)
{
    if (node != 0)
    {
        free_tree(node->esq);
        free_tree(node->dir);
        free(node);
    }
}

int main(void)
{
    ABin root = newABin(3, 0, 0);
    ABin esq = newABin(1, 0, 0);
    ABin dir = newABin(2, 0, 0);
    root->esq = esq;
    root->dir = dir;

    print_tree("Before", root);

    ABin eval = somasAcA(root);
    assert(eval == root);

    print_tree("After", root);

    eval = somasAcA_OK(root);
    assert(eval != root);

    print_tree("Second time", root);

    free(root);
    free(esq);
    free(dir);
    free_tree(eval);
}
