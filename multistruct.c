/* SO 34605516 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct a
{
    char name[20];
};

struct b
{
    double x;
    double y;
    struct b *transverse;
};

struct c
{
    int height;
    int width;
    int depth;
    struct c *transverse;
};

enum abctype { TYPE_A, TYPE_B, TYPE_C };

struct foo
{
    struct foo *longitudinal;
    enum abctype type;
    union
    {
        struct a aye;
        struct b bee;
        struct c cee;
    };
};

static struct foo *add_a_long(struct foo *head, const char *name)
{
    struct foo *new_foo = malloc(sizeof(*new_foo));
    if (new_foo != 0)
    {
        strncpy(new_foo->aye.name, name, sizeof(new_foo->aye.name)-1);
        new_foo->aye.name[sizeof(new_foo->aye.name)-1] = '\0';
        new_foo->type = TYPE_A;
        new_foo->longitudinal = head;
    }
    return new_foo;
}

static struct foo *add_b_long(struct foo *head, double x, double y)
{
    struct foo *new_foo = malloc(sizeof(*new_foo));
    if (new_foo != 0)
    {
        new_foo->bee.x = x;
        new_foo->bee.y = y;
        new_foo->bee.transverse = 0;
        new_foo->type = TYPE_B;
        new_foo->longitudinal = head;
    }
    return new_foo;
}

static struct foo *add_c_long(struct foo *head, int height, int width, int depth)
{
    struct foo *new_foo = malloc(sizeof(*new_foo));
    if (new_foo != 0)
    {
        new_foo->cee.height = height;
        new_foo->cee.width = width;
        new_foo->cee.depth = depth;
        new_foo->cee.transverse = 0;
        new_foo->type = TYPE_C;
        new_foo->longitudinal = head;
    }
    return new_foo;
}

static void add_b_trans(struct b *b, double x, double y)
{
    struct b *new_b = malloc(sizeof(*new_b));
    if (new_b != 0)
    {
        new_b->x = x;
        new_b->y = y;
        new_b->transverse = 0;
        b->transverse = new_b;
    }
}

static void add_c_trans(struct c *c, int height, int width, int depth)
{
    struct c *new_c = malloc(sizeof(*new_c));
    if (new_c != 0)
    {
        new_c->height = height;
        new_c->width = width;
        new_c->depth = depth;
        new_c->transverse = 0;
        c->transverse = new_c;
    }
}

static void print_foo(const char *tag, const struct foo *head)
{
    printf("\n%s:\n", tag);
    while (head != 0)
    {
        switch (head->type)
        {
        case TYPE_A:
            printf("A: %s\n", head->aye.name);
            break;
        case TYPE_B:
            {
            const struct b *bp = &head->bee;
            while (bp != 0)
            {
                printf("B: (%f,%f)\n", bp->x, bp->y);
                bp = bp->transverse;
            }
            printf("  End B transverse\n");
            }
            break;
        case TYPE_C:
            {
            const struct c *cp = &head->cee;
            while (cp != 0)
            {
                printf("C: (%d,%d,%d)\n", cp->height, cp->width, cp->depth);
                cp = cp->transverse;
            }
            printf("  End C transverse\n");
            }
            break;
        }
        head = head->longitudinal;
    }
}

int main(void)
{
    struct foo *head = 0;
    head = add_a_long(head, "Caterpillar");
    print_foo("1 item", head);
    head = add_a_long(head, "Ununtrium");
    print_foo("2 items", head);
    head = add_b_long(head, 3.14159, 2.78128);
    print_foo("3 items", head);
    add_b_trans(&head->bee, 1.2345, 2.3456);
    add_b_trans(&head->bee, 9.8765, 6.5432);
    print_foo("3 items, 2 transverse B", head);
    head = add_c_long(head, 3, 4, 5);
    head = add_c_long(head, 5, 12, 13);
    print_foo("5 items", head);
    add_c_trans(&head->cee, 7, 20, 27);
    add_c_trans(&head->cee, 9, 35, 36);
    print_foo("Final", head);
    return 0;
}
