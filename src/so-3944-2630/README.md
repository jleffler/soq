### Stack Overflow Question 3944-2630

[SO 3944-2630](https://stackoverflow.com/q/39442630) &mdash;
Insert function for BST with strings in C

### Answer

This code works.
The primary change is making sure that you return immediately after
setting the root node.
(Note that in your trace, you get told that the first node you insert is
a 'duplicate' — that's because you don't do the early return.)
I used an `else` on the subsequent `if` statement rather than add an
extra `return rootptr;`, but that would also work.

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

    int main(void)
    {
        datatype_t earth[] =
        {
            { "Dave", "Studying at UCLA" },
            { "John", "Works at Google" },
            { "Mike", "School teacher" },
        };
        enum { NUM_LINES = sizeof(earth) / sizeof(earth[0]) };
        struct BST_node *root = NULL;
        for (int index = 0; index < NUM_LINES; index++)
        {
            if (root != NULL)
                printf("Root node: %s\n", (root->name1));
            root = Insert(root, &earth[index]);
            BST_print_inorder("Insert complete", root);
        }
        return 0;
    }

Sample run:

    Dave 1
    Insert complete:
    Dave (Studying at UCLA)
    Root node: Dave
    Dave left
    John 1
    Insert complete:
    John (Works at Google)
    Dave (Studying at UCLA)
    Root node: Dave
    Dave left
    John left
    Mike 1
    Insert complete:
    Mike (School teacher)
    John (Works at Google)
    Dave (Studying at UCLA)

You can't afford not to have a printing function, and you can't afford
not to call it on each iteration of the inserting loop until you know
everything is working.

Running with [`valgrind`](http://www.valgrind.org/) gives it a clean
bill of health as far as memory access goes.
I've not written the tree-free function.

Note that this code avoids having to worry about how the name and data
values are allocated since they are part of an initialized array.
However, in your 'real' code, you need to ensure that each name and data
value is given its own memory.

<hr>

### Still crashing?

If you are still crashing after this, then you need to look hard at the
`read()` code — or the other supporting code.

Note that `read()` is not a good function name to use on Unix-like
systems; there is a `read()` system call too.
The linker will sort things out for you so that the library code works,
but if any of your code uses `read()` expecting the system call, it will
be surprised to get your function instead.

## Undefined behaviour from `read()`

The `read()` function has been posted as:

    datatype_t *read(FILE* fp)
    {
        char name[65];
        char data[1465];
        if (fscanf(fp, "%[^,] %[^\n]", name, data) == 2) {
            datatype_t *d = (datatype_t*)malloc(sizeof(datatype_t));
            d->name = name;
            d->data = data;
            return d;
        }
        return NULL;
    }

You're returning an allocated data structure, but the two strings
contained in the structure are pointers to the local variables `name`
and `data` and they are no longer valid once the function exits.
You need to duplicate the strings.

Also, the `fscanf()` format is a bit curious.
It doesn't read the comma separately, so the comma is parsed as part of
the second scanset.
The blank in the format means 'skip optional white space', of course.
So, when the first scanset stops at the comma, the blank doesn't change
anything, and then the data up to the newline, starting with the comma,
is read into the `data`.
Also, the second and subsequent names start with a newline.
You need a format string like:

    " %[^,], %[^\n]"

The scansets, `%c` and `%n` conversion specifications are the only ones
that don't skip leading white space.

For example:

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

(Note: trailing space in a `scanf()`-family format string intended for
interactive use is a usability disaster — don't use it, ever.)

Revised main using modified `read()`:

    int main(void)
    {
        datatype_t *earth;
        struct BST_node *root = NULL;
        while ((earth = read(stdin)) != NULL)
        {
            if (root != NULL)
                printf("Root node: %s\n", (root->name1));
            root = Insert(root, earth);
            BST_print_inorder("Insert complete", root);
        }

        BST_free(root);
        return 0;
    }

And `BST_free()` is:

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

<hr>

There was a memory leak in the previous code for `Insert()` —
actually, two of them.
One is for each added node; the `datatype_t` structure is not freed when
it should be (but the members are still in use; they've been transferred
to the tree).
The other is when there's a duplicate found; then the new data members
need to be freed too.

I've also revised `main()` again to simulate what the code in the
question does.

    struct BST_node *Insert(struct BST_node *rootptr, datatype_t *d)
    {
        if (rootptr == NULL)
        {
            rootptr = (struct BST_node *)malloc(sizeof(struct BST_node));
            rootptr->name1 = d->name;
            rootptr->data1 = d->data;
            rootptr->left = rootptr->right = NULL;
            printf("%s 1\n", rootptr->name1);
            free(d);
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
            free(d->name);
            free(d->data);
            free(d);
            printf("duplicate\n");
        }
        return rootptr;
    }

...

    int main(void)
    {
        struct BST_node *root = NULL;

        enum { MAX_NUM_LINE = 1000 };

        datatype_t **earth = (datatype_t **)malloc(MAX_NUM_LINE * sizeof(datatype_t *));
        assert(earth != NULL);

        datatype_t *earth_one;
        size_t index = 0;

        while ((earth_one = read(stdin)) != NULL)
        {
            earth[index] = earth_one;

            if (root != NULL)
                printf("Root node: %s\n", (root->name1));
            root = Insert(root, earth[index]);
            BST_print_inorder("Insert complete", root);
            index++;
            assert(index < MAX_NUM_LINE);
        }
        printf("%zu nodes\n", index);

        BST_free(root);
        free(earth);

        return 0;
    }

This compiles cleanly under GCC 6.1.0 on Mac OS X 10.11.6 using:

    $ gcc -O3 -g -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     -Wold-style-definition ll23.c -o ll23
    $

It runs cleanly under [`valgrind`](http://www.valgrind.org/).

I have used two data files:

`data.1`:

    Dave, Studying at UCLA
    John, Works at Google
    Mike, School teacher

`data.2`:

    Dave, Studying at UCLA
    John, Works at Google
    Mike, School teacher
    Jane, CEO of Humdinger Enterprises
    Anne, Chief Dogsbody
    Beryl, Tech Lead at Apple
    Mina, Doctor at Kaiser Permanente
    Dave, Transfer PhD to UCB

<hr>

Note that the `struct BST_Node` should embed a `datatype_t`.
For consistency, either use `struct datatype_t` thoughout (with no
typedef for `datatype_t`) or introduce `typedef struct BST_Node
BST_Node;`.
