/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

#ifndef _MY_GEO_H_
#define _MY_GEO_H_

#include <math.h>

typedef struct {
    fpoint3d P0;
    fpoint3d P1;
} line;

typedef struct {
    fpoint3d V0;
    fpoint3d V1;
    fpoint3d V2;
} triangle;

/*
 * triangle_line_intersect(): find the 3D intersection of a line with a
 * triangle
 *
 * -1 = triangle is degenerate (a segment or point)
 *  0 =  disjoint (no intersect)
 *  1 =  intersect in unique point I1
 *  2 =  are in the same plane
 */
int
triangle_line_intersect(const line ray,
                        const triangle triangle,
                        fpoint3d *intersection);

/*
 * true on intersection.
 */
uint8_t
cube_line_intersect(const line ray,
                    const fpoint3d p0,
                    const fpoint3d p1,
                    const fpoint3d p2,
                    const fpoint3d p3,
                    const fpoint3d p4,
                    const fpoint3d p5,
                    const fpoint3d p6,
                    const fpoint3d p7,
                    fpoint3d *best_intersection,
                    float *best_distance);

/*
 * true if perpendicular line from point is in line segment.
 */
uint8_t
dist_point_line(fpoint3d P0, fpoint3d L0, fpoint3d L1, float *dist);
#endif
