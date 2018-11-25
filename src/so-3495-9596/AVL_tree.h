/* SO 3495-9596 */
#if !defined AVL_TREE_H
#define AVL_TREE_H

struct vertex
{
    int data;
    long height;
    struct vertex *l, *r, *p;
};

void insert(struct vertex **root, int data);
void *find(struct vertex *root, int data);
void clear_tree(struct vertex **root);
void print_tree(struct vertex *root);

#endif
