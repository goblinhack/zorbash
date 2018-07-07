/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */


#include "my_main.h"
#include "my_math_util.h"

uint32_t nextpoweroftwo (uint32_t val)
{_
    val--;
    val = (val >> 1) | val;
    val = (val >> 2) | val;
    val = (val >> 4) | val;
    val = (val >> 8) | val;
    val = (val >> 16) | val;
    val++; // Val is now the next highest power of 2.

    return (val);
}

double FSIN[RAD_MAX];
double FASIN[RAD_MAX];
double FCOS[RAD_MAX];

static void fsin_init (void)
{_
    uint16_t i;

    for (i = 0; i < RAD_MAX; i++) {
        FSIN[i] = (double)sin(RAD_STEP * (double) i);
    }
}

static void fasin_init (void)
{_
    uint16_t i;

    for (i = 0; i < RAD_MAX; i++) {
        FASIN[i] = (double)asin(RAD_STEP * (double) i);
    }
}

static void fcos_init (void)
{_
    uint16_t i;

    for (i = 0; i < RAD_MAX; i++) {
        FCOS[i] = (double)cos(RAD_STEP * (double) i);
    }
}

void math_init (void)
{_
    fsin_init();
    fasin_init();
    fcos_init();
}

/*
 * true if perpendicular line from point is in line segment.
 */
#if 0
uint8_t get_line_intersection (fpoint p0,
                               fpoint p1,
                               fpoint p2,
                               fpoint p3,
                               fpoint *intersect)
{_
    fpoint s1, s2;

    s1.x = p1.x - p0.x;
    s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;
    s2.y = p3.y - p2.y;

    double s, t;

    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) /
            (-s2.x * s1.y + s1.x * s2.y);

    t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) /
            (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        intersect->x = p0.x + (t * s1.x);
        intersect->y = p0.y + (t * s1.y);
        return (true);
    }

    return (false); // No collision
}
#endif

uint8_t get_line_intersection (fpoint p0,
                               fpoint p1,
                               fpoint p2,
                               fpoint p3,
                               fpoint *intersect)
{_
    double denominator =
        ((p3.y - p2.y) * (p1.x - p0.x)) - ((p3.x - p2.x) * (p1.y - p0.y));

    if (denominator == 0) {
        return (false);
    }

    double a = p0.y - p2.y;
    double b = p0.x - p2.x;

    double numerator1 = ((p3.x - p2.x) * a) - ((p3.y - p2.y) * b);
    double numerator2 = ((p1.x - p0.x) * a) - ((p1.y - p0.y) * b);

    a = numerator1 / denominator;
    b = numerator2 / denominator;

    // if we cast these lines infinitely in both directions, they intersect
    // here:
    intersect->x = p0.x + (a * (p1.x - p0.x));
    intersect->y = p0.y + (a * (p1.y - p0.y));

    // if line1 is a segment and line2 is infinite, they intersect if:
    if ((a >= 0) && (a <= 1.0) && (b >= 0) && (b <= 1.0)) {
        return (true);
    }

    return (false);
}

/*
 * Two lines we already know intersect.
 */
uint8_t get_line_known_intersection (fpoint p0,
                                     fpoint p1,
                                     fpoint p2,
                                     fpoint p3,
                                     fpoint *intersect)
{_
    double denominator =
        ((p3.y - p2.y) * (p1.x - p0.x)) - ((p3.x - p2.x) * (p1.y - p0.y));

    if (denominator == 0) {
        return (false);
    }

    double a = p0.y - p2.y;
    double b = p0.x - p2.x;

    double numerator1 = ((p3.x - p2.x) * a) - ((p3.y - p2.y) * b);
    double numerator2 = ((p1.x - p0.x) * a) - ((p1.y - p0.y) * b);

    a = numerator1 / denominator;
    b = numerator2 / denominator;

    // if we cast these lines infinitely in both directions, they intersect
    // here:
    intersect->x = p0.x + (a * (p1.x - p0.x));
    intersect->y = p0.y + (a * (p1.y - p0.y));

    return (true);
}

uint8_t
fpoint_dist_line (fpoint P0, fpoint L0, fpoint L1, double *dist,
                  fpoint *intersect_out)
{_
    fpoint intersect;
    float mag;
    float U;

    /*
     * Can get the squared distance to avoid this.
     */
    mag = distance(L1, L0);

    /*
     * Project point P onto the line and then calc the dot product.
     */
    U = (((P0.x - L0.x) * (L1.x - L0.x)) +
         ((P0.y - L0.y) * (L1.y - L0.y))) /
         (mag * mag);

    if (U < 0.0f) {
        intersect = L0;
    } else if (U > 1.0f) {
        intersect = L1;
    } else {
        intersect.x = L0.x + U * (L1.x - L0.x);
        intersect.y = L0.y + U * (L1.y - L0.y);
    }

    *dist = distance(P0, intersect);

    if (intersect_out) {
        *intersect_out = intersect;
    }

    if ((U < 0.0f) || (U > 1.0f)) {
        return (0);   // closest P0 does not fall within the line segment
    }

    return (1);
}

int
fpoint_dist_line2 (fpoint P0, fpoint L0, fpoint L1, double *dist,
                  fpoint *intersect_out)
{_
    fpoint intersect;
    float mag;
    float U;

    /*
     * Can get the squared distance to avoid this.
     */
    mag = distance(L1, L0);

    /*
     * Project point P onto the line and then calc the dot product.
     */
    U = (((P0.x - L0.x) * (L1.x - L0.x)) +
         ((P0.y - L0.y) * (L1.y - L0.y))) /
         (mag * mag);

    if (U < 0.0f) {
        intersect = L0;
    } else if (U > 1.0f) {
        intersect = L1;
    } else {
        intersect.x = L0.x + U * (L1.x - L0.x);
        intersect.y = L0.y + U * (L1.y - L0.y);
    }

    *dist = distance(P0, intersect);

    if (intersect_out) {
        *intersect_out = intersect;
    }

    if ((U < 0.0f) || (U > 1.0f)) {
        return (0);   // closest P0 does not fall within the line segment
    }

    return (1);
}

double
fpoint_project_onto_line (fpoint P0, fpoint L0, fpoint L1)
{_
    float mag;
    float U;

    /*
     * Can get the squared distance to avoid this.
     */
    mag = distance(L1, L0);

    /*
     * Project point P onto the line and then calc the dot product.
     */
    U = (((P0.x - L0.x) * (L1.x - L0.x)) +
         ((P0.y - L0.y) * (L1.y - L0.y))) /
         (mag * mag);

    return (U);
}

/*
 * Yields an angle between 0 and 180 deg radians
 */
double fpoint_angle (const fpoint A, const fpoint B)
{_
    const double a = sqrt(A.x*A.x + A.y*A.y);
    const double b = sqrt(B.x*B.x + B.y*B.y);

    if (!a && !b) {
        return (0);
    }

    return (acos((A.x*B.x + A.y*B.y) / (a * b)));
}

/*
 * Yields an angle between -180 and 180 deg radians
 */
double fpoint_angle_clockwise (const fpoint A, const fpoint B)
{_
    return (atan2(A.x*B.y - A.y*B.x, A.x*B.x+A.y*B.y));
}

#if 0
static double EPSILON = 0.000001;

static double crossProduct (fpoint a, fpoint b) {
    return (a.x * b.y - b.x * a.y);
}

static boolean isPointOnLine (fpoint p0, fpoint p1, fpoint b)
{_
    p1.x -= p0.x;
    p1.y -= p0.y;
    p0.x = 0;
    p0.y = 0;

    fpoint bt;

    bt.x = b.x - p0.x;
    bt.y = b.y - p0.y;

    double r = crossProduct(p1, bt);

    return (fabs(r) < EPSILON);
}

static boolean isPointRightOfLine (fpoint p0, fpoint p1, fpoint b)
{_
    p1.x -= p0.x;
    p1.y -= p0.y;
    p0.x = 0;
    p0.y = 0;

    fpoint bt;

    bt.x = b.x - p0.x;
    bt.y = b.y - p0.y;

    return (crossProduct(p1, bt) < 0);
}

static boolean lineSegmentTouchesOrCrossesLine (
                fpoint p0, fpoint p1,
                fpoint p2, fpoint p3)
{_
    return (isPointOnLine(p0, p1, p2)
                || isPointOnLine(p0, p1, p3)
                || (isPointRightOfLine(p0, p1, p2) ^ isPointRightOfLine(p0, p1, p3));
}
#endif

double anglerot (fpoint p)
{_
    double theta = atan2_approximation1(p.y, p.x); // range (-PI, PI]
    if (theta < 0) {
        theta = RAD_360 + theta; // range [0, 360)
    }
    return theta;
}

fpoint fpoint_rotate (fpoint p, double theta)
{_
    fpoint r;

    r.x = p.x * cos(theta) - p.y * sin(theta);
    r.y = p.x * sin(theta) + p.y * cos(theta);

    return (r);
}
