### Stack Overflow Question 4784-9166

[SO 4784-9166](https://stackoverflow.com/q/47849166) &mdash;
Convert BST to DLL in pre-order (base)

<hr>

Here's some code that seems to work.
The conversion function is quite simple in concept, but requires some
care in handling the details.

For this problem, it seems to me that when you are processing any given
node, you need to get three elements:

* the current node (root)
* the list for the left-child
* the list for the right-child

And the resulting list needs to be:

* current node, followed by
* list for left-child, followed by
* list for right-child.


Given the tree from the question:

          4                               
        /   \       
       2      6    ---------> output of DLL: 4<->2<->1<->3<->6<->5<->7.         
     /  \     / \                         
    1    3   5   7       

The final result is:

* node 4, followed by the list from node 2, followed by the list from node 6.

Of course, the list from node 2 is:

* node 2, followed by the list from node 1, followed by the list from node 3.
* And the lists from node 1 and node 3 are trivial, so the result is:
  * node 2, node 1, node 3
* And similarly the list from node 6 is:
  * node 6, followed by the list from node 5, followed by the list from node 7.
* And the lists from node 5 and node 7 are trivial, so the result is:
  * node 6, node 5, node 7

And hence the final result is:

  * node 4, node 2, node 1, node 3, node 6, node 5, node 7

The lists are doubly-linked and null-terminated.
That means that on return to the invocation processing node 4, the left
list has the organization:

           +--------+     +--------+     +--------+
    0 <----|        |<----|        |<----|        |
           | Node 2 |     | Node 1 |     | Node 3 |
           |        |---->|        |---->|        |----> 0
           +--------+     +--------+     +--------+

The trivial cases return a list with null next and previous pointers.
The right list has a similar organization for Nodes 6, 5, 7 in sequence.
Assembling the final result requires setting the left pointer of Node 4
to null, setting the right pointer of Node 4 to the head of the left
list, setting the left pointer of the head of the left list to Node 4,
finding the end of the list starting from Node 4's right pointer, and
then adding the right list after that and setting the left pointer of
head of the right list to the right pointer of the node pointing at the
right list.

Either the left list or the right list or both can be empty; these
require a modicum of care.

This is the resulting code, complete with a trio of test cases.
The pointer to pointer to node technique for traversing lists is rather
powerful and worth learning.
You can find other SO questions for the technique, such as:

* [What is the double-pointer technique for simplifying the traversal of linked lists?](https://stackoverflow.com/questions/3182733/what-is-the-double-pointer-technique-for-simplifying-the-traversal-of-linked-lis/3182787#3182787)

* [An interesting linked list idiom](https://stackoverflow.com/questions/332441/an-interesting-c-linked-list-idiom)

<!-- -->

    /* SO 4784-9166 */
    #include <inttypes.h>
    #include <stdio.h>

    typedef struct Node Node;
    struct Node
    {
        int   number;
        Node *left;
        Node *right;
    };

    static Node *convertToPreOrder(Node *root)
    {
        if (root == 0)
            return 0;
        Node *l_list = convertToPreOrder(root->left);
        Node *r_list = convertToPreOrder(root->right);
        root->left = 0;
        /* Add left list */
        root->right = l_list;
        if (l_list != 0)
            l_list->left = root;
        /* Find the end */
        Node **pos = &root;
        while ((*pos)->right != 0)
            pos = &(*pos)->right;
        /* Add right list */
        (*pos)->right = r_list;
        if (r_list != 0)
            r_list->left = *pos;
        return root;
    }

    static void print_node(Node *node)
    {
        if (node != 0)
            printf("Node = 0x%.12" PRIXPTR " - Number = %d - "
                   "Left = 0x%.12" PRIXPTR " - Right = 0x%.12" PRIXPTR "\n",
                   (uintptr_t)node, node->number, (uintptr_t)node->left, (uintptr_t)node->right);
    }

    static void print_BST_preorder(Node *root)
    {
        if (root == 0)
            return;
        print_node(root);
        print_BST_preorder(root->left);
        print_BST_preorder(root->right);
    }

    static void print_list(Node *list)
    {
        while (list != 0)
        {
            print_node(list);
            list = list->right;
        }
    }

    static Node *add_bst_node(Node *root, Node *node)
    {
        if (root == 0)
            return node;
        if (node->number >= root->number)
            root->right = add_bst_node(root->right, node);
        else
            root->left = add_bst_node(root->left, node);
        return root;
    }

    static void test_bst_to_list(size_t n_nodes, Node nodes[])
    {
        Node *root = 0;
        for (size_t i = 0; i < n_nodes; i++)
            root = add_bst_node(root, &nodes[i]);
        printf("Print BST in pre-order:\n");
        print_BST_preorder(root);
        printf("Convert to list\n");
        Node *list = convertToPreOrder(root);
        printf("Print list:\n");
        print_list(list);
        putchar('\n');
    }

    int main(void)
    {
        Node array1[] =
        {
            { 4, 0, 0 },
            { 2, 0, 0 },
            { 1, 0, 0 },
            { 3, 0, 0 },
            { 6, 0, 0 },
            { 5, 0, 0 },
            { 7, 0, 0 },
        };
        enum { ARRAY1_SIZE = sizeof(array1) / sizeof(array1[0]) };
        test_bst_to_list(ARRAY1_SIZE, array1);

        Node array2[] =
        {
            { 19, 0, 0 },
            { 21, 0, 0 },
            { 20, 0, 0 },
            { 18, 0, 0 },
            { 22, 0, 0 },
            { 24, 0, 0 },
            { 17, 0, 0 },
            { 16, 0, 0 },
            { 23, 0, 0 },
            { 27, 0, 0 },
            { 26, 0, 0 },
            { 25, 0, 0 },
        };
        enum { ARRAY2_SIZE = sizeof(array2) / sizeof(array2[0]) };
        test_bst_to_list(ARRAY2_SIZE, array2);

        Node array3[] =
        {
            { 16, 0, 0 },
            { 11, 0, 0 },
            { 21, 0, 0 },
            { 10, 0, 0 },
            { 22, 0, 0 },
            { 22, 0, 0 },
            { 21, 0, 0 },
            { 27, 0, 0 },
            { 27, 0, 0 },
            { 20, 0, 0 },
            { 22, 0, 0 },
            { 17, 0, 0 },
            { 12, 0, 0 },
        };
        enum { ARRAY3_SIZE = sizeof(array3) / sizeof(array3[0]) };
        test_bst_to_list(ARRAY3_SIZE, array3);

        return 0;
    }

The `print_node()` function is tuned to running on a Mac (in 64-bit),
where heap allocations typically have leading zeroes in the first 4
nybbles, so 12 hex digits is sufficient to print them.
The stack allocated arrays used in the test have the first 7 nybbles as
zeroes, but if the code used dynamic allocation for the nodes, the
longer address would be needed.

Sample output:

    Print BST in pre-order:
    Node = 0x7FFEE6F5B180 - Number = 4 - Left = 0x7FFEE6F5B198 - Right = 0x7FFEE6F5B1E0
    Node = 0x7FFEE6F5B198 - Number = 2 - Left = 0x7FFEE6F5B1B0 - Right = 0x7FFEE6F5B1C8
    Node = 0x7FFEE6F5B1B0 - Number = 1 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B1C8 - Number = 3 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B1E0 - Number = 6 - Left = 0x7FFEE6F5B1F8 - Right = 0x7FFEE6F5B210
    Node = 0x7FFEE6F5B1F8 - Number = 5 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B210 - Number = 7 - Left = 0x000000000000 - Right = 0x000000000000
    Convert to list
    Print list:
    Node = 0x7FFEE6F5B180 - Number = 4 - Left = 0x000000000000 - Right = 0x7FFEE6F5B198
    Node = 0x7FFEE6F5B198 - Number = 2 - Left = 0x7FFEE6F5B180 - Right = 0x7FFEE6F5B1B0
    Node = 0x7FFEE6F5B1B0 - Number = 1 - Left = 0x7FFEE6F5B198 - Right = 0x7FFEE6F5B1C8
    Node = 0x7FFEE6F5B1C8 - Number = 3 - Left = 0x7FFEE6F5B1B0 - Right = 0x7FFEE6F5B1E0
    Node = 0x7FFEE6F5B1E0 - Number = 6 - Left = 0x7FFEE6F5B1C8 - Right = 0x7FFEE6F5B1F8
    Node = 0x7FFEE6F5B1F8 - Number = 5 - Left = 0x7FFEE6F5B1E0 - Right = 0x7FFEE6F5B210
    Node = 0x7FFEE6F5B210 - Number = 7 - Left = 0x7FFEE6F5B1F8 - Right = 0x000000000000

    Print BST in pre-order:
    Node = 0x7FFEE6F5B230 - Number = 19 - Left = 0x7FFEE6F5B278 - Right = 0x7FFEE6F5B248
    Node = 0x7FFEE6F5B278 - Number = 18 - Left = 0x7FFEE6F5B2C0 - Right = 0x000000000000
    Node = 0x7FFEE6F5B2C0 - Number = 17 - Left = 0x7FFEE6F5B2D8 - Right = 0x000000000000
    Node = 0x7FFEE6F5B2D8 - Number = 16 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B248 - Number = 21 - Left = 0x7FFEE6F5B260 - Right = 0x7FFEE6F5B290
    Node = 0x7FFEE6F5B260 - Number = 20 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B290 - Number = 22 - Left = 0x000000000000 - Right = 0x7FFEE6F5B2A8
    Node = 0x7FFEE6F5B2A8 - Number = 24 - Left = 0x7FFEE6F5B2F0 - Right = 0x7FFEE6F5B308
    Node = 0x7FFEE6F5B2F0 - Number = 23 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B308 - Number = 27 - Left = 0x7FFEE6F5B320 - Right = 0x000000000000
    Node = 0x7FFEE6F5B320 - Number = 26 - Left = 0x7FFEE6F5B338 - Right = 0x000000000000
    Node = 0x7FFEE6F5B338 - Number = 25 - Left = 0x000000000000 - Right = 0x000000000000
    Convert to list
    Print list:
    Node = 0x7FFEE6F5B230 - Number = 19 - Left = 0x000000000000 - Right = 0x7FFEE6F5B278
    Node = 0x7FFEE6F5B278 - Number = 18 - Left = 0x7FFEE6F5B230 - Right = 0x7FFEE6F5B2C0
    Node = 0x7FFEE6F5B2C0 - Number = 17 - Left = 0x7FFEE6F5B278 - Right = 0x7FFEE6F5B2D8
    Node = 0x7FFEE6F5B2D8 - Number = 16 - Left = 0x7FFEE6F5B2C0 - Right = 0x7FFEE6F5B248
    Node = 0x7FFEE6F5B248 - Number = 21 - Left = 0x7FFEE6F5B2D8 - Right = 0x7FFEE6F5B260
    Node = 0x7FFEE6F5B260 - Number = 20 - Left = 0x7FFEE6F5B248 - Right = 0x7FFEE6F5B290
    Node = 0x7FFEE6F5B290 - Number = 22 - Left = 0x7FFEE6F5B260 - Right = 0x7FFEE6F5B2A8
    Node = 0x7FFEE6F5B2A8 - Number = 24 - Left = 0x7FFEE6F5B290 - Right = 0x7FFEE6F5B2F0
    Node = 0x7FFEE6F5B2F0 - Number = 23 - Left = 0x7FFEE6F5B2A8 - Right = 0x7FFEE6F5B308
    Node = 0x7FFEE6F5B308 - Number = 27 - Left = 0x7FFEE6F5B2F0 - Right = 0x7FFEE6F5B320
    Node = 0x7FFEE6F5B320 - Number = 26 - Left = 0x7FFEE6F5B308 - Right = 0x7FFEE6F5B338
    Node = 0x7FFEE6F5B338 - Number = 25 - Left = 0x7FFEE6F5B320 - Right = 0x000000000000

    Print BST in pre-order:
    Node = 0x7FFEE6F5B350 - Number = 16 - Left = 0x7FFEE6F5B368 - Right = 0x7FFEE6F5B380
    Node = 0x7FFEE6F5B368 - Number = 11 - Left = 0x7FFEE6F5B398 - Right = 0x7FFEE6F5B470
    Node = 0x7FFEE6F5B398 - Number = 10 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B470 - Number = 12 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B380 - Number = 21 - Left = 0x7FFEE6F5B428 - Right = 0x7FFEE6F5B3B0
    Node = 0x7FFEE6F5B428 - Number = 20 - Left = 0x7FFEE6F5B458 - Right = 0x000000000000
    Node = 0x7FFEE6F5B458 - Number = 17 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B3B0 - Number = 22 - Left = 0x7FFEE6F5B3E0 - Right = 0x7FFEE6F5B3C8
    Node = 0x7FFEE6F5B3E0 - Number = 21 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B3C8 - Number = 22 - Left = 0x000000000000 - Right = 0x7FFEE6F5B3F8
    Node = 0x7FFEE6F5B3F8 - Number = 27 - Left = 0x7FFEE6F5B440 - Right = 0x7FFEE6F5B410
    Node = 0x7FFEE6F5B440 - Number = 22 - Left = 0x000000000000 - Right = 0x000000000000
    Node = 0x7FFEE6F5B410 - Number = 27 - Left = 0x000000000000 - Right = 0x000000000000
    Convert to list
    Print list:
    Node = 0x7FFEE6F5B350 - Number = 16 - Left = 0x000000000000 - Right = 0x7FFEE6F5B368
    Node = 0x7FFEE6F5B368 - Number = 11 - Left = 0x7FFEE6F5B350 - Right = 0x7FFEE6F5B398
    Node = 0x7FFEE6F5B398 - Number = 10 - Left = 0x7FFEE6F5B368 - Right = 0x7FFEE6F5B470
    Node = 0x7FFEE6F5B470 - Number = 12 - Left = 0x7FFEE6F5B398 - Right = 0x7FFEE6F5B380
    Node = 0x7FFEE6F5B380 - Number = 21 - Left = 0x7FFEE6F5B470 - Right = 0x7FFEE6F5B428
    Node = 0x7FFEE6F5B428 - Number = 20 - Left = 0x7FFEE6F5B380 - Right = 0x7FFEE6F5B458
    Node = 0x7FFEE6F5B458 - Number = 17 - Left = 0x7FFEE6F5B428 - Right = 0x7FFEE6F5B3B0
    Node = 0x7FFEE6F5B3B0 - Number = 22 - Left = 0x7FFEE6F5B458 - Right = 0x7FFEE6F5B3E0
    Node = 0x7FFEE6F5B3E0 - Number = 21 - Left = 0x7FFEE6F5B3B0 - Right = 0x7FFEE6F5B3C8
    Node = 0x7FFEE6F5B3C8 - Number = 22 - Left = 0x7FFEE6F5B3E0 - Right = 0x7FFEE6F5B3F8
    Node = 0x7FFEE6F5B3F8 - Number = 27 - Left = 0x7FFEE6F5B3C8 - Right = 0x7FFEE6F5B440
    Node = 0x7FFEE6F5B440 - Number = 22 - Left = 0x7FFEE6F5B3F8 - Right = 0x7FFEE6F5B410
    Node = 0x7FFEE6F5B410 - Number = 27 - Left = 0x7FFEE6F5B440 - Right = 0x000000000000

The first test case corresponds to the sample tree from the question.
Given the construction of the tree, the nodes are presented in the same
order in both the BST print and the list print.
However, the pointers are quite different.
That test case is a little too simple for comfort.
It doesn't test the cases where a given node in the BST has either an
empty left tree or an empty right tree (but not both — that would be a
leaf node).

