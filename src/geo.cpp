/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_geo.h"
#include "my_math_util.h"

/*
 * triangle_line_intersect(): find the 3D intersection of a line with a
 * triangle
 * -1 = triangle is degenerate (a segment or point)
 *  0 =  disjoint (no intersect)
 *  1 =  intersect in unique point I1
 *  2 =  are in the same plane
 */
int
triangle_line_intersect (const line ray,
                         const triangle triangle,
                         fpoint3d *intersection)
{_
    /*
     * A triangle is describe by a point and then two vectors. Any point in
     * the triangle can be reached by walking some way along u and then some
     * way along v.
     *
     * Notice now that if u or v < 0 then we've walked in the wrong direction
     * and must be outside the triangle. Also if u or v > 1 then we've walked
     * too far in a direction and are outside the triangle. Finally if u + v >
     * 1 then we've crossed the far edge again leaving the triangle.
     */
    fpoint3d u = triangle.V1 - triangle.V0;
    fpoint3d v = triangle.V2 - triangle.V0;

    /*
     * Cross product for the plane of this triangle.
     */
    fpoint3d n = cross(u, v);

    /*
     * Degenerate triangle. Triangle is either a point or a line.
     */
    static const fpoint3d null = {0,0,0};

    if (n == null) {
        return (-1);
    }

    /*
     * p0 - a point on the plane
     * l0 - a point on the line
     * l  - the line fpoint3d
     * n  - the plane normal
     *
     * A plane can be expressed as all points p where the dot product is
     * 90 degrees between the plane normal and the plane points
     *
     *     (p - p0) . n = 0
     *
     * A line can be expressed as all points p where
     *
     *     p = dl + l0
     *
     * Substitute the line equation into the plane
     *
     *     (dl + l0 - p0) . n = 0
     *
     *     (dl . n) + (l0 - p0) . n = 0
     *
     *     (l0 - p0) . n = - (dl . n)
     *
     *     (l0 - p0) . n / (l . n) = - d
     *
     *     d = (p0 - l0) . n / (l . n)
     */
    fpoint3d p0 = triangle.V0;
    fpoint3d l0 = ray.P0;
    fpoint3d l = ray.P1 - l0;

    float numerator = (p0 - l0).dot(n);
    float denominator = l.dot(n);

    /*
     * If the line starts outside the plane and is parallel to the plane,
     * there is no intersection. In this case, the above denominator will be
     * zero and the numerator will be non-zero.
     *
     * If the line starts inside the plane and is parallel to the plane, the
     * line intersects the plane everywhere. In this case, both the numerator
     * and denominator above will be zero.
     *
     * In all other cases, the line intersects the plane once and d represents
     * the intersection as the distance along the line from l0 i.e. dl + l0.
     */
    if (fabs(denominator) < 0.00000001) { // avoid division overflow
        if (numerator == 0) {
            /*
             * Line is inside plane.
             */
            return (2);
        }

        /*
         * Else it is parallel and disjoint from the plane.
         */
        return (0);
    }

    /*
     * Else this line goes through the plane.
     */
    double d = numerator / denominator;

    if ((d < 0.0) || (d > 1.0)) {
        /*
         * Interection point is beyond the length of the line segment.
         */
        return (0);
    }

    /*
     * Intersection point on the plane dl + l0.
     */
    *intersection = ((l * d) + l0);

    /*
     * We hit the plane but are we in the triangle? This is a bit complex
     * but involves two vectors u and v that describe the triangle. All
     * points where u and v total < 1.0 are in the triangle. We solve s
     * and t that are fractions along u and v.
     */
    float uu = u.dot(u);
    float uv = u.dot(v);
    float vv = v.dot(v);

    fpoint3d w = *intersection - triangle.V0;

    float wu = w.dot(u);
    float wv = w.dot(v);

    float D = uv * uv - uu * vv;

    float s, t;

    s = (uv * wv - vv * wu) / D;
    if ((s < 0.0) || (s > 1.0)) {
        /*
         * Intersection outside triangle
         */
        return (0);
    }

    t = (uv * wu - uu * wv) / D;
    if ((t < 0.0) || ((s + t) > 1.0)) {
        /*
         * Intersection outside triangle
         */
        return (0);
    }

    /*
     * intersection is in triangle
     */
    return (1);
}

/*
 * Returns the distance to the closest intersection point of the light
 * with this cube.
 */
uint8_t
cube_line_intersect (const line ray,
                     const fpoint3d p0,
                     const fpoint3d p1,
                     const fpoint3d p2,
                     const fpoint3d p3,
                     const fpoint3d p4,
                     const fpoint3d p5,
                     const fpoint3d p6,
                     const fpoint3d p7,
                     fpoint3d *best_intersection,
                     float *best_distance)
{_
    uint8_t gotone = false;

    const fpoint3d VA = {p0.x, p0.y, p0.z};
    const fpoint3d VB = {p1.x, p1.y, p1.z};
    const fpoint3d VC = {p2.x, p2.y, p2.z};
    const fpoint3d VD = {p3.x, p3.y, p3.z};
    const fpoint3d VE = {p4.x, p4.y, p4.z};
    const fpoint3d VF = {p5.x, p5.y, p5.z};
    const fpoint3d VG = {p6.x, p6.y, p6.z};
    const fpoint3d VH = {p7.x, p7.y, p7.z};

    const triangle T[] = {
        {VA, VC, VD},
        {VC, VB, VD},
        {VG, VH, VE},
        {VH, VF, VG},
        {VD, VE, VA},
        {VD, VH, VE},
        {VB, VG, VC},
        {VB, VF, VG},
        {VB, VH, VD},
        {VH, VF, VB},
        {VC, VE, VA},
        {VE, VG, VC},
    };

    FOR_ALL_IN_ARRAY(t, T) {

        fpoint3d intersection;

        if (triangle_line_intersect(ray, *t, &intersection) != 1) {
            continue;
        }

        float d = distance(ray.P1, intersection);

        if (!gotone) {
            *best_intersection = intersection;
            *best_distance = d;
            gotone = true;
            continue;
        }

        if (d < *best_distance) {
            *best_intersection = intersection;
            *best_distance = d;
        }
    }

    return (gotone);
}

/*
 * true if perpendicular line from point is in line segment.
 */
uint8_t
dist_point_line (fpoint3d P0, fpoint3d L0, fpoint3d L1, float *dist)
{_
    fpoint3d intersect;
    float mag;
    float U;

    mag = distance(L1, L0);

    U = (((P0.x - L0.x) * (L1.x - L0.x)) +
         ((P0.y - L0.y) * (L1.y - L0.y)) +
         ((P0.z - L0.z) * (L1.z - L0.z))) /
         (mag * mag);

    if ((U < 0.0f) || (U > 1.0f)) {
        return (0);   // closest P0 does not fall within the line segment
    }

    intersect.x = L0.x + U * (L1.x - L0.x);
    intersect.y = L0.y + U * (L1.y - L0.y);
    intersect.z = L0.z + U * (L1.z - L0.z);

    *dist = distance(P0, intersect);

    return (1);
}
