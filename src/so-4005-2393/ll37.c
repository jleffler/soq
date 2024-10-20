/* SO 4005-2393 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct s_node { void *elem; struct s_node *next; struct s_node *prev; };

void* remove_node1(struct s_node** node);
void* remove_node2(struct s_node** node);
void* remove_node3(struct s_node** node);
void* remove_node4(struct s_node** node);

static void prnode(const char *tag, struct s_node *root)
{
    printf("%s  R 0x%.12" PRIXPTR, tag, (uintptr_t)root);
    if (root != NULL)
    {
        printf("; N 0x%.12" PRIXPTR "; P 0x%.12" PRIXPTR "; V 0x%.12" PRIXPTR,
               (uintptr_t)root->next, (uintptr_t)root->prev, (uintptr_t)root->elem);
    }
    putchar('\n');
}

/* OP's code */
void* remove_node1(struct s_node** node){
    if(node != NULL && *node != NULL && (*node)->elem != NULL){
        void* data = (*node)->elem;
        if((*node)->prev == NULL && (*node)->next == NULL){
            free(*node);
        }else if((*node)->prev == NULL){
            (*node)->next->prev = NULL;
            (*node)->next = NULL;
            free(*node);
        }else if((*node)->next == NULL){
            (*node)->prev->next = NULL;
            (*node)->prev = NULL;
            free(*node);
        }else{
            (*node)->prev->next = (*node)->next;
            (*node)->next->prev = (*node)->prev;
            (*node)->prev = NULL;
            (*node)->next = NULL;
            free(*node);
        }
        return data;
    }else{
        return NULL;
    }
}

void *remove_node2(struct s_node **node)
{
    if (node == NULL || *node == NULL || (*node)->elem == NULL)
        return NULL;
    void *data = (*node)->elem;
    struct s_node *curr = *node;
    struct s_node *next = curr->next;
    struct s_node *prev = curr->prev;

    if (prev != NULL || next != NULL)
    {
        if (next != NULL)
            next->prev = prev;
        if (prev != NULL)
            prev->next = next;
    }
    free(*node);
    return data;
}

void *remove_node3(struct s_node **node)
{
    if (node == NULL || *node == NULL) // || (*node)->elem == NULL)
        return NULL;

    printf("remove_node3: %p\n", (void *)*node);

    void *data = (*node)->elem;

//    struct s_node *curr = *node;
//
//    if (curr->prev != NULL || curr->next != NULL)
//    {
//        prnode("curr 1", curr);
//        prnode("next 1", curr->next);
//        prnode("prev 1", curr->prev);
//        if (curr->next != NULL)
//            curr->next->prev = curr->prev;
//        if (curr->prev != NULL)
//            curr->prev->next = curr->next;
//        prnode("curr 2", curr);
//        prnode("next 2", curr->next);
//        prnode("prev 2", curr->prev);
//    }

    if ((*node)->prev != NULL || (*node)->next != NULL)
    {
        prnode("prev 1", (*node)->prev);
        prnode("curr 1", (*node));
        prnode("next 1", (*node)->next);
        if ((*node)->next != NULL)
            (*node)->next->prev = (*node)->prev;
        prnode("prev 2", (*node)->prev);
        prnode("curr 2", (*node));
        prnode("next 2", (*node)->next);
        if ((*node)->prev != NULL)
            (*node)->prev->next = (*node)->next;
        prnode("prev 3", (*node)->prev);
        prnode("curr 3", (*node));
        prnode("next 3", (*node)->next);
    }

#if 0
remove_node3: 0x7f97ffc02820
prev 1  R 0x7F97FFC02800; N 0x7F97FFC02820; P 0x7F97FFC027E0; V 0x000103BBBD96
curr 1  R 0x7F97FFC02820; N 0x7F97FFC02840; P 0x7F97FFC02800; V 0x000103BBBD9C
next 1  R 0x7F97FFC02840; N 0x000000000000; P 0x7F97FFC02820; V 0x000103BBBDA1
prev 2  R 0x7F97FFC02800; N 0x7F97FFC02820; P 0x7F97FFC027E0; V 0x000103BBBD96
curr 2  R 0x7F97FFC02820; N 0x7F97FFC02840; P 0x7F97FFC02800; V 0x000103BBBD9C
next 2  R 0x7F97FFC02840; N 0x000000000000; P 0x7F97FFC02800; V 0x000103BBBDA1
prev 3  R 0x7F97FFC02800; N 0x7F97FFC02840; P 0x7F97FFC027E0; V 0x000103BBBD96
curr 3  R 0x7F97FFC02840; N 0x000000000000; P 0x7F97FFC02800; V 0x000103BBBDA1
next 3  R 0x000000000000
free: 0x7f97ffc02840
#endif

    printf("free: %p\n", (void *)*node);
    free(*node);
    return data;
}

/* chqrlie's answer */
void *remove_node4(struct s_node **node)
{
    if (node != NULL && *node != NULL && (*node)->elem != NULL)
    {
        void *data = (*node)->elem;
        if ((*node)->prev != NULL)
            (*node)->prev->next = (*node)->next;
        if ((*node)->next != NULL)
            (*node)->next->prev = (*node)->prev;
        free(*node);
        *node = NULL;                                      /* safely, cannot hurt */
        return data;
    }
    else
    {
        return NULL;
    }
}

static void prlist(const char *tag, struct s_node *root)
{
    printf("%s:\n", tag);
    while (root != NULL)
    {
        prnode("", root);
        root = root->next;
    }
    printf("%s done:\n", tag);
}

static struct s_node *mklist(void)
{
    struct s_node *n1 = calloc(1, sizeof(*n1));
    struct s_node *n2 = calloc(1, sizeof(*n2));
    struct s_node *n3 = calloc(1, sizeof(*n3));
    struct s_node *n4 = calloc(1, sizeof(*n4));

    n1->elem = "Hello";
    n2->elem = "World";
    n3->elem = "Fare";
    n4->elem = "Well";

    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    n3->next = n4;
    n4->prev = n3;

    prnode("n1", n1);
    prnode("n2", n2);
    prnode("n3", n3);
    prnode("n4", n4);

    return n1;
}

static void rmlist(struct s_node *root)
{
    while (root != NULL)
    {
        struct s_node *next = root->next;
        free(root);
        root = next;
    }
}

static void test_list(int num, void *(*function)(struct s_node **))
{
    printf("List %d:\n", num);
    struct s_node *list = mklist();
    prlist("Before", list);
    struct s_node *node = list->next->next;
    void *data = function(&node);
    assert(data != NULL);
    prlist("After", list);
    rmlist(list);
}

int main(void)
{
    test_list(1, remove_node1);
    test_list(2, remove_node2);
    test_list(3, remove_node3);
    test_list(4, remove_node4);
    return 0;
}
