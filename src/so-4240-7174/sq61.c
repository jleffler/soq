/* SO 4240-7174 Is point P inside square identified by BL and TR corners? */
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "reldiff.h"

extern double area_triangle(double xa, double ya, double xb, double yb, double xc, double yc);
extern void inside_square(double x1, double y1, double x2, double y2, double px, double py);

/* This computation is ridiculous! */

static int verbose = 1;

static inline double fmin3(double a, double b, double c)
{
    double     r = a;
    if (b < r) r = b;
    if (c < r) r = c;
    return r;
}

static inline double fmax3(double a, double b, double c)
{
    double     r = a;
    if (b > r) r = b;
    if (c > r) r = c;
    return r;
}

static inline bool point_on_boundary(double xp, double yp, double xmin, double xmax, double ymin, double ymax)
{
    return (xp == xmin || xp == xmax || yp == ymin || yp == ymax);
}

static inline double simplex_area_triangle(double xa, double ya, double xb, double yb, double xc, double yc)
{
    double xmax = fmax3(xa, xb, xc);
    double xmin = fmin3(xa, xb, xc);
    double ymax = fmax3(ya, yb, yc);
    double ymin = fmin3(ya, yb, yc);
    /*
    ** Each of the points A, B, C touches the bounding rectangle
    ** (that is, if each of points A, B, C has at least one coordinate
    ** equal to the corresponding minimum or maximum) then the simple
    ** formula here applies.
    */
    {
        double area_sq = (xmax - xmin) * (ymax - ymin);
        double area_ab = fabs((xa - xb) * (ya - yb)) / 2.0;
        double area_bc = fabs((xb - xc) * (yb - yc)) / 2.0;
        double area_ca = fabs((xc - xa) * (yc - ya)) / 2.0;
        double result  = area_sq - area_ab - area_bc - area_ca;
        if (verbose)
            printf("ATS: (%g,%g) (%g,%g) (%g,%g): %g - %g - %g - %g = %g\n",
                    xa, ya, xb, yb, xc, yc, area_sq, area_ab, area_bc, area_ca, result);
        return result;
    }
}

static inline double complex_area_triangle(double xa, double ya, double xb, double yb, double xc, double yc)
{
    double area = fabs(xa - xb) * fabs(ya - yb) / 2;
    double d1 = (xa - xc) * (xa - xc) + (yb - yc) * (yb - yc);
    double d2 = (xb - xc) * (xb - xc) + (ya - yc) * (ya - yc);
    if (d1 < d2)
    {
        area -= simplex_area_triangle(xa, ya, xc, yc, xa, yb);
        area -= simplex_area_triangle(xb, yb, xc, yc, xa, yb);
    }
    else
    {
        area -= simplex_area_triangle(xa, ya, xc, yc, xb, ya);
        area -= simplex_area_triangle(xb, yb, xc, yc, xb, ya);
    }
    if (verbose)
        printf("ATC: (%g,%g) (%g,%g) (%g,%g): = %g\n",
                xa, ya, xb, yb, xc, yc, area);
    return area;
}

double area_triangle(double xa, double ya, double xb, double yb, double xc, double yc)
{
    double xmax = fmax3(xa, xb, xc);
    double xmin = fmin3(xa, xb, xc);
    double ymax = fmax3(ya, yb, yc);
    double ymin = fmin3(ya, yb, yc);
    /*
    ** If each of the points A, B, C touches the bounding rectangle
    ** (that is, if each of points A, B, C has at least one coordinate
    ** equal to the corresponding minimum or maximum) then the simple
    ** formula here applies.
    ** If any one of the points doesn't meet that criterion, then (a)
    ** the other two points are BL and TR (or TL and BR) of a rectangle
    ** with sides parallel to the axes.  Without loss of generality,
    ** assume A and B are at two corners of the rectangle.  Calculate
    ** the smaller distance from C to the other corners A' and B', the
    ** unspecified corners; designate the nearer corner D.  Then the
    ** area of triangle ABC is equal to the area of rectangle AB minus
    ** the area of triangle ABD (equivalent to the area of triangle ABB'
    ** and triangle ABA', and equivalent to half the area of rectangle
    ** AB) minus the area of triangle ACD minus the area of triangle
    ** BCD.  Triangles ACD and BCD are both guaranteed to be simple
    ** (that is, each point touches the bounding square).  If the
    ** distances to the unspecified corners is equal, then C is colinear
    ** with A and B and bisects the line AB.
    */
    if (!point_on_boundary(xa, ya, xmin, xmax, ymin, ymax))
        return complex_area_triangle(xb, yb, xc, yc, xa, ya);
    else if (!point_on_boundary(xb, yb, xmin, xmax, ymin, ymax))
        return complex_area_triangle(xc, yc, xa, ya, xb, yb);
    else if (!point_on_boundary(xc, yc, xmin, xmax, ymin, ymax))
        return complex_area_triangle(xa, ya, xb, yb, xc, yc);
    else
        return simplex_area_triangle(xa, ya, xb, yb, xc, yc);
}

static double area_square(double x1, double y1, double x2, double y2)
{
    double dx = x1 - x2;
    double dy = y1 - y2;
    return (dx * dx + dy * dy) / 2.0;
}

/* Is point (px,py) inside square with BL (x1,y1) and TR (x2,y2)? */
void inside_square(double x1, double y1, double x2, double y2, double px, double py)
{
    double xc = (x1 + x2)/2;
    double yc = (y1 + y2)/2;    // Centre point
    double xd = (x1 - x2)/2;
    double yd = (y1 - y2)/2;    // Half-diagonal

    double x3 = xc - yd;
    double y3 = yc + xd;    // Third corner
    double x4 = xc + yd;
    double y4 = yc - xd;    // Fourth corner

    double area_sq = area_square(x1, y1, x2, y2);
    double area_p_1_3 = area_triangle(px, py, x1, y1, x3, y3);
    double area_p_3_2 = area_triangle(px, py, x3, y3, x2, y2);
    double area_p_2_4 = area_triangle(px, py, x2, y2, x4, y4);
    double area_p_4_1 = area_triangle(px, py, x4, y4, x1, y1);
    double area_p_tot = area_p_1_3 + area_p_3_2 + area_p_2_4 + area_p_4_1;

    printf("A (%g,%g), C (%g,%g), ", x1, y1, x2, y2);
    printf("B (%g,%g), D (%g,%g): ", x3, y3, x4, y4);

    const char *decision;
    if (reldiff(area_sq, area_p_tot) < 1.0E-6)
        decision = "Inside";
    else
        decision = "Outside";
    printf("P (%g,%g): A(sq) = %g; %g + %g + %g + %g = %g (%s)\n",
           px, py, area_sq, area_p_1_3, area_p_3_2, area_p_2_4, area_p_4_1, area_p_tot, decision);
}

int main(void)
{
    verbose = 1;
    area_triangle(0, 0, 3.5, 3.5, 1, 1);        /* Line - area 0 */
    area_triangle(0, 0, 3.5, 3.5, 1, 1.001);
    area_triangle(0, 0, 6, 6, 12, 0);
    area_triangle(0, 0, 6, 1, 12, 0);
    area_triangle(0, 0, 6, 0.1, 12, 0);
    area_triangle(0, 0, 6, 0.01, 12, 0);
    area_triangle(0, 0, 6, 0.001, 12, 0);
    area_triangle(0, 0, 6, 0.0001, 12, 0);
    area_triangle(0, 0, 6, 0.00001, 12, 0);
    area_triangle(0, 0, 6, 0, 12, 0);           /* Line - area 0 */
    area_triangle(0, 0, 3, 1, 6, 2);            /* Line - area 0 */
    area_triangle(0, 0, 3, 2, 6, 2);
    area_triangle(0, 0, 3, 0, 6, 2);
    area_triangle(0, 0, 4, 4, 2, 2);            /* Line - area 0 */
    /* Check for consistency under permutation of points */
    area_triangle(0, 0, 2, 3, 5, 4);
    area_triangle(0, 0, 5, 4, 2, 3);
    area_triangle(2, 3, 0, 0, 5, 4);
    area_triangle(2, 3, 5, 4, 0, 0);
    area_triangle(5, 4, 0, 0, 2, 3);
    area_triangle(5, 4, 2, 3, 0, 0);

    verbose = 0;
    inside_square(0, 0, 3, 7, 1, 4);        /* Inside */
    inside_square(0, 0, 3, 7, -3, -5);      /* Outside */
    inside_square(0, 0, 3, 6, 1, 4);        /* Inside */
    inside_square(0, 0, 3, 6, -3, -5);      /* Outside */
    inside_square(0, 0, 3, 6, 1, 5);        /* Inside */
    inside_square(0, 0, 3, 6, 1, 4);        /* Inside */

    inside_square(0, 0, 7, 7, 1, 4);        /* Inside */
    inside_square(0, 0, 7, 7, -3, -5);      /* Outside */
    inside_square(0, 0, 7, 7, 0, 5);        /* Inside */
    inside_square(0, 0, 7, 7, 3, 0);        /* Outside */
    inside_square(0, 0, 7, 7, 0, 0);        /* Inside (at corner) */
    inside_square(0, 0, 7, 7, 7, 7);        /* Inside (at corner) */
    inside_square(0, 0, 7, 7, 3, +1E-4);    /* Inside */
    inside_square(0, 0, 7, 7, 3, -1E-4);    /* Outside */
    inside_square(0, 0, 7, 7, 3, -1E-5);    /* Outside */
    inside_square(0, 0, 7, 7, 3, -1E-6);    /* Inside because of reldiff */
    inside_square(0, 0, 7, 7, 3, -1E-7);    /* Inside because of reldiff */
    inside_square(0, 0, 7, 7, 3, -1E-8);    /* Inside because of reldiff */

    inside_square(0, 0, 0, 7, 1, 1);        /* Inside (on boundary) */
    inside_square(0, 0, 0, 7, 2, 2);        /* Inside (on boundary) */
    inside_square(0, 0, 0, 7, 3, 3);        /* Inside (on boundary) */
    inside_square(0, 0, 0, 7, 3.5, 3.5);    /* Inside (at corner) */
    inside_square(0, 0, 0, 7, 1, 2);        /* Outside */
    inside_square(0, 0, 0, 7, 2, 1);        /* Inside */

    return 0;
}
