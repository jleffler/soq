/* SO 37577522 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const double MIN_X = -100.0;
static const double MAX_X = +100.0;
static const double MIN_Y = -100.0;
static const double MAX_Y = +100.0;
static const double CTR_X = (MIN_X + MAX_X) / 2.0;
static const double CTR_Y = (MIN_Y + MAX_Y) / 2.0;

struct Particle
{
    double mass;
    double x_pos;
    double y_pos;
    double x_vel;
    double y_vel;
};

typedef struct node
{
    struct Particle *p;
    double center_x;
    double center_y;
    double width;
    struct node *sw;
    struct node *nw;
    struct node *se;
    struct node *ne;
} node;

static node *quadtree_insert(node *n, struct Particle *p, double center_x, double center_y, double width)
{
    printf("Centre (X,Y) = (%6.2f,%6.2f)\n", center_x, center_y);
    if (n == NULL)
    {
        n = (node *)malloc(sizeof(node));
        n->is_leaf = 1;

        n->p = p;
        n->m = 0.1;

        n->sw = NULL;
        n->se = NULL;
        n->nw = NULL;
        n->ne = NULL;
        if (width < 1e-300)
        {
            n->width = 1e-300;
        }
        else
            n->width    = width;
        return n;
    }
    else
    {
        // n = (node*)malloc(sizeof(node));
        double x;
        double y;
        if (width < 1e-300)
        {
            width = 1e-300;
        }
        if (n->is_leaf == 1) // ! that is, if the node is not a branch
        {
            x = n->p->x_pos;
            y = n->p->y_pos;

            if (x <= center_x && y <= center_y) // ! first quadrant
            {
                printf("(X,Y) = (%6.2f, %6.2f) Recurse SW 1: ", x, y);
                n->sw = quadtree_insert(n->sw, n->p, center_x * 0.5, center_y * 0.5, width * 0.5);
            }
            else if (x <= center_x && y > center_y) // ! second quadrant
            {
                printf("(X,Y) = (%6.2f, %6.2f) Recurse NW 1: ", x, y);
                n->nw = quadtree_insert(n->nw, n->p, center_x * 0.5, center_y * 1.5, width * 0.5);
            }
            else if (x > center_x && y <= center_y) // ! third quadrant
            {
                printf("(X,Y) = (%6.2f, %6.2f) Recurse SE 1: ", x, y);
                n->se = quadtree_insert(n->se, n->p, center_x * 1.5, center_y * 0.5, width * 0.5);
            }
            else // ! fourth quadrant
            {
                printf("(X,Y) = (%6.2f, %6.2f) Recurse NE 1: ", x, y);
                n->ne = quadtree_insert(n->ne, n->p, center_x * 1.5, center_y * 1.5, width * 0.5);
            }

            n->p = NULL; // ! sets branch pointer to nothing...
            n->is_leaf = 0;
        }

        x = p->x_pos;
        y = p->y_pos;

        if (x <= center_x && y <= center_y) // ! first quadrant
        {
            printf("(X,Y) = (%6.2f, %6.2f) Recurse SW 2: ", x, y);
            n->sw = quadtree_insert(n->sw, p, center_x * 0.5, center_y * 0.5, width * 0.5);
        }
        else if (x <= center_x && y > center_y) // ! second quadrant
        {
            printf("(X,Y) = (%6.2f, %6.2f) Recurse NW 2: ", x, y);
            n->nw = quadtree_insert(n->nw, p, center_x * 0.5, center_y * 1.5, width * 0.5);
        }
        else if (x > center_x && y <= center_y) // ! third quadrant
        {
            printf("(X,Y) = (%6.2f, %6.2f) Recurse SE 2: ", x, y);
            n->se = quadtree_insert(n->se, p, center_x * 1.5, center_y * 0.5, width * 0.5);
        }
        else // ! fourth quadrant
        {
            printf("(X,Y) = (%6.2f, %6.2f) Recurse NE 2: ", x, y);
            n->ne = quadtree_insert(n->ne, p, center_x * 1.5, center_y * 1.5, width * 0.5);
        }
        return n;
    }
}

/*
   random -n 10 -T '    { %6:2[1:20]f, %6:2[-100:100]f, %6:2[-100:100]f, %6:2[-100:100]f, %6:2[-100:100]f },'
 */

static struct Particle particles[] =
{
    {  19.99,  96.07,  62.79, -99.46,  19.70 },
    {  12.94,   1.43, -33.45,  31.80, -66.08 },
    {   6.49,  16.99, -20.83,  92.51,  35.98 },
    {  17.01, -28.85, -94.10,  42.82,  -1.30 },
    {  14.27,  85.07,  88.21,  11.22,  16.85 },
    {  15.73, -56.37,  46.85,  27.40, -15.15 },
    {   1.53, -49.44, -64.27, -29.45, -38.25 },
    {   8.03,  92.11, -47.50,  63.77, -29.99 },
    {   8.67, -99.81,  73.19,  18.75,  88.66 },
    {  16.36,  66.33,  14.23,  87.65,  40.01 },
};

enum { nParticles = sizeof(particles) / sizeof(particles[0]) };

int main(void)
{
    node *root = NULL;
    printf("Particle 0: ");
    root = quadtree_insert(root, &particles[0], 0.5, 0.5, 1.0);

    for (int i = 1; i < nParticles; i++)
    {
        printf("Particle %d: ", i);
        quadtree_insert(root, &particles[i], 0.5, 0.5, 1.0);
    }
    return 0;
}
