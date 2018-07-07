/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MATH_UTIL_H_
#define _MY_MATH_UTIL_H_

#include <math.h>

#include "my_main.h"
#include "stdlib.h"

#undef SQUARED
#define SQUARED(x) ((x) * (x))

#define ROUNDUP(x, r) ((r) * floor(((x) + (r)) / (r)))

#undef DISTANCE
#define DISTANCE(xa,ya,xb,yb) \
    sqrt((double)(SQUARED((xb)-(xa))+SQUARED((yb)-(ya))))

#undef DISTANCE3f
#define DISTANCE3f(xa,ya,za,xb,yb,zb) \
    sqrt((double)(SQUARED((xb)-(xa))+\
                 SQUARED((yb)-(ya))+\
                 SQUARED((zb)-(za))))

uint32_t nextpoweroftwo(uint32_t val);

#define PI      3.14159265358979323846f /* pi */
#define RAD_45  0.78539816339744830962f /* pi/4 */
#define RAD_90  1.57079632679489661923f /* pi/2 */
#define RAD_180 3.14159265358979323846f /* pi */
#define RAD_360 (2.0f * 3.14159265358979323846f) /* 2pi */
#define RAD_270 (RAD_180 + RAD_90)

static inline double angle2radians (const double angle)
{
    return (angle * (RAD_360 / 360.0));
}

static inline double radians2angle (const double rad)
{
    return ((360.0 * rad) / RAD_360);
}

void math_init(void);

/*
 * Fast cached sin/cos routines.
 */
#define RAD_MAX 0xFFFF
#define RAD_STEP (RAD_360 / (double)RAD_MAX)

static inline double fsin (double rad)
{
#ifdef ENABLE_MATH_ESTIMATES
    const uint16_t index = (uint16_t)(rad / RAD_STEP);
    extern double FSIN[RAD_MAX];

    return (FSIN[index & (RAD_MAX-1)]);
#else
    return (sin(rad));
#endif
}

static inline double fasin (double rad)
{
#ifdef ENABLE_MATH_ESTIMATES
    const uint16_t index = (uint16_t)(rad / RAD_STEP);
    extern double FASIN[RAD_MAX];

    return (FASIN[index & (RAD_MAX-1)]);
#else
    return (asin(rad));
#endif
}

static inline double fcos (double rad)
{
#ifdef ENABLE_MATH_ESTIMATES
    const uint16_t index = (uint16_t)(rad / RAD_STEP);
    extern double FCOS[RAD_MAX];

    return (FCOS[index & (RAD_MAX-1)]);
#else
    return (cos(rad));
#endif
}

static inline float atan2_approximation1(float y, float x)
{
#ifdef ENABLE_MATH_ESTIMATES
    //http://pubs.opengroup.org/onlinepubs/009695399/functions/atan2.html
    //Volkan SALMA

    const float ONEQTR_PI = M_PI / 4.0;
    const float THRQTR_PI = 3.0 * M_PI / 4.0;
    float r, angle;
    float abs_y = fabs(y) + 1e-10f;      // kludge to prevent 0/0 condition
    if ( x < 0.0f ) {
        r = (x + abs_y) / (abs_y - x);
        angle = THRQTR_PI;
    } else {
        r = (x - abs_y) / (x + abs_y);
        angle = ONEQTR_PI;
    }
    angle += (0.1963f * r * r - 0.9817f) * r;
    if ( y < 0.0f )
        return( -angle );     // negate if in quad III or IV
    else
        return( angle );
#else
    return (atan2(y, x));
#endif
}

#include "my_point.h"
#include "my_size.h"

double anglerot(fpoint p);

fpoint fpoint_rotate(fpoint p, double theta);

/*
 * Yields an angle between 0 and 180 deg radians
 */
double fpoint_angle(const fpoint A, const fpoint B);

double fpoint_angle_clockwise(const fpoint A, const fpoint B);

/*
 * true if perpendicular line from point is in line segment.
 */
uint8_t
fpoint_dist_line(fpoint P0, fpoint L0, fpoint L1, double *dist,
                 fpoint *intersect);

/*
 * true if perpendicular line from point is in line segment.
 */
int
fpoint_dist_line2(fpoint P0, fpoint L0, fpoint L1, double *dist,
                 fpoint *intersect);

/*
 * true if lines intersect
 */
uint8_t get_line_intersection(fpoint p0,
                              fpoint p1,
                              fpoint p2,
                              fpoint p3,
                              fpoint *intersect);
uint8_t get_line_known_intersection(fpoint p0,
                              fpoint p1,
                              fpoint p2,
                              fpoint p3,
                              fpoint *intersect);

double gauss(const double m, const double s);

double fpoint_project_onto_line(fpoint P0, fpoint L0, fpoint L1);

double gaussrand(double mean, double stddev);

/** You know that lines a and b have an intersection and now you
    want to get it!
*/
static inline void getIntersection (fpoint a0,
                                    fpoint a1,
                                    fpoint b0,
                                    fpoint b1,
                                    fpoint *i)
{
    /* the intersection [(x1,y1), (x2, y2)]
       it might be a line or a single point. If it is a line,
       then x1 = x2 and y1 = y2.  */
    double x1, y1;
    // double x2;
    // double y2;

    if (a0.x == a1.x) {
        // Case (A)
        // As a is a perfect vertical line, it cannot be represented
        // nicely in a mathematical way. But we directly know that
        //
        x1 = a0.x;
//        x2 = x1;
        if (b0.x == b1.x) {
            // Case (AA): all x are the same!
            // Normalize
            if (a0.y > a1.y) {
                swapval(a0, a1);
            }
            if (b0.y > b1.y) {
                swapval(b0, b1);
            }
            if (a0.y > b0.y) {
                swapval(a0, b0);
                swapval(a1, b1);
            }

            // Now we know that the y-value of a["first"] is the
            // lowest of all 4 y values
            // this means, we are either in case (AAA):
            //   a: x--------------x
            //   b:    x---------------x
            // or in case (AAB)
            //   a: x--------------x
            //   b:    x-------x
            // in both cases:
            // get the relavant y intervall
            y1 = b0.y;
//            y2 = min(a1.y, b1.y);
        } else {
            // Case (AB)
            // we can mathematically represent line b as
            //     y = m*x + t <=> t = y - m*x
            // m = (y1-y2)/(x1-x2)
            double m, t;
            m = (b0.y - b1.y)/
                (b0.x - b1.x);
            t = b0.y - m*b0.x;
            y1 = m*x1 + t;
//            y2 = y1;
        }
    } else if (b0.x == b1.x) {
        // Case (B)
        // essentially the same as Case (AB), but with
        // a and b switched
        x1 = b0.x;
//        x2 = x1;

        swapval(a0, b0);
        swapval(a1, b1);

        double m, t;
        m = (b0.y - b1.y)/
            (b0.x - b1.x);
        t = b0.y - m*b0.x;
        y1 = m*x1 + t;
//        y2 = y1;
    } else {
        // Case (C)
        // Both lines can be represented mathematically
        double ma, mb, ta, tb;
        ma = (a0.y - a1.y)/
             (a0.x - a1.x);
        mb = (b0.y - b1.y)/
             (b0.x - b1.x);
        ta = a0.y - ma*a0.x;
        tb = b0.y - mb*b0.x;
        if (ma == mb) {
            // Case (CA)
            // both lines are in parallel. As we know that they
            // intersect, the intersection could be a line
            // when we rotated this, it would be the same situation
            // as in case (AA)

            // Normalize
            if (a0.x > a1.x) {
                swapval(a0, a1);
            }
            if (b0.x > b1.x) {
                swapval(b0, b1);
            }
            if (a0.x > b0.x) {
                swapval(a0, b0);
                swapval(a1, b1);
            }

            // get the relavant x intervall
            x1 = b0.x;
//            x2 = min(a1.x, b1.x);
            y1 = ma*x1+ta;
//            y2 = ma*x2+ta;
        } else {
            // Case (CB): only a point as intersection:
            // y = ma*x+ta
            // y = mb*x+tb
            // ma*x + ta = mb*x + tb
            // (ma-mb)*x = tb - ta
            // x = (tb - ta)/(ma-mb)
            x1 = (tb-ta)/(ma-mb);
            y1 = ma*x1+ta;
//            x2 = x1;
//            y2 = y1;
        }
    }

    i->x = x1;
    i->y = y1;

    /*
     * If a line
     *
    i->x = x2;
    i->y = y2;
     */
}
#endif
