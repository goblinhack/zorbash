/*
    goblinhack.
    Copyright (C) 1999-2010 Neil McGill

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This game is distributed in the hope that it will be fun,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this game; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Neil McGill

    $Id: my_point.h 477 2007-03-10 22:40:46Z goblinhack $
*/

#ifndef _MY_POINT_H_
#define _MY_POINT_H_

#include <cereal/types/memory.hpp>
#include "my_math_util.h"

template<class T> class my_apoint
{
public:

    T x {};
    T y {};

    my_apoint (void) : x(0), y(0) {};

    my_apoint (T x, T y) : x(x), y(y) { }

    my_apoint (const my_apoint &a) : x(a.x), y(a.y) { }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(x, y);
    }

    void operator+= (my_apoint a)
    {
        x += a.x; y += a.y;
    }

    void operator-= (my_apoint a)
    {
        x -= a.x; y -= a.y;
    }

    void operator/= (my_apoint a)
    {
        x /= a.x; y /= a.y;
    }

    void operator*= (my_apoint a)
    {
        x *= a.x; y *= a.y;
    }

    void operator*= (T a)
    {
        x *= a; y *= a;
    }

    void operator/= (T a)
    {
        x /= a; y /= a;
    }

    friend bool operator< (my_apoint a, my_apoint b)
    {
        return (a.y < b.y) && (a.x < b.x);
    }

    friend bool operator> (my_apoint a, my_apoint b)
    {
        return (a.y > b.y) && (a.x > b.x);
    }

    friend my_apoint operator+ (my_apoint a, my_apoint b)
    {
        return (my_apoint(a.x + b.x, a.y + b.y));
    }

    friend my_apoint operator- (my_apoint a, my_apoint b)
    {
        return (my_apoint(a.x - b.x, a.y - b.y));
    }

    friend my_apoint operator/ (my_apoint a, my_apoint b)
    {
        return (my_apoint(a.x / b.x, a.y / b.y));
    }

    friend my_apoint operator/ (my_apoint a, T b)
    {
        return (my_apoint(a.x / b, a.y / b));
    }

    friend my_apoint operator* (my_apoint a, T b)
    {
        return (my_apoint(a.x * b, a.y * b));
    }

    friend my_apoint operator* (my_apoint a, my_apoint b)
    {
        return (my_apoint(a.x * b.x, a.y * b.y));
    }

    friend bool operator== (my_apoint a, my_apoint b)
    {
        return (a.x == b.x) && (a.y == b.y);
    }

    friend bool operator!= (my_apoint a, my_apoint b)
    {
        return (!(a==b));
    }

    friend T distance (my_apoint a, my_apoint b)
    {
        return ((T) DISTANCE((float)a.x,(float)a.y,(float)b.x,(float)b.y));
    }

    T length (void) const
    {
        return (sqrt(x*x + y*y));
    }

    void unit (void)
    {
        T length = sqrt(x*x + y*y);

        x /= length;
        y /= length;
    }

    friend my_apoint unit (const my_apoint p)
    {
        const T length = sqrt(p.x*p.x + p.y*p.y);

        return (my_apoint(p.x / length, p.y / length));
    }

    T dot (const my_apoint b) const
    {
        return (x*b.x + y*b.y);
    }

    //
    // Yields an angle between 0 and 180 deg radians
    //
    friend T angle (const my_apoint A, const my_apoint B)
    {
        const T a = sqrt(A.x*A.x + A.y*A.y);
        const T b = sqrt(B.x*B.x + B.y*B.y);

        return (acos((A.x*B.x + A.y*B.y) / (a * b)));
    }

    //
    // Yields an angle between 0 and 180 deg radians
    //
    T angle (const my_apoint A) const
    {
        const T a = sqrt(A.x*A.x + A.y*A.y);
        const T b = sqrt(x*x + y*y);

        return (acos((A.x*x + A.y*y) / (a * b)));
    }

    //
    // Yields an angle between 0 and 360 deg radians - essentially, how much
    // this point has been rotated about the origin.
    //
    T anglerot (void) const
    {
        T theta = asin(y / length());

        if (x > 0) {
            if (y > 0) {
                return (theta);
            } else {
                return (RAD_360 + theta);
            }
        } else {
            return (RAD_180 - theta);
        }
    }

    /*
     * Two lines we already know intersect.
     */
    friend uint8_t get_line_known_intersection (my_apoint p0,
                                                my_apoint p1,
                                                my_apoint p2,
                                                my_apoint p3,
                                                my_apoint *intersect)
    {
        T denominator = 
            ((p3.y - p2.y) * (p1.x - p0.x)) - ((p3.x - p2.x) * (p1.y - p0.y));

        if (denominator == 0) {
            return (false);
        }

        T a = p0.y - p2.y;
        T b = p0.x - p2.x;

        T numerator1 = ((p3.x - p2.x) * a) - ((p3.y - p2.y) * b);
        T numerator2 = ((p1.x - p0.x) * a) - ((p1.y - p0.y) * b);

        a = numerator1 / denominator;
        b = numerator2 / denominator;

        // if we cast these lines infinitely in both directions, they intersect 
        // here:
        intersect->x = p0.x + (a * (p1.x - p0.x));
        intersect->y = p0.y + (a * (p1.y - p0.y));

        return (true);
    }
};

typedef my_apoint<int> point;
typedef my_apoint<double> fpoint;

#ifdef NEED_3D_MATH
template<class T> class my_apoint3d
{
public:

    T x {};
    T y {};
    T z {};

    my_apoint3d (void) : x(0), y(0), z(0) { }

    my_apoint3d (T x, T y, T z) : x(x), y(y), z(z) { }

    my_apoint3d (const my_apoint3d &a) : x(a.x), y(a.y), z(a.z) { }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(x, y, z);
    }

    void operator+= (my_apoint3d a)
    {
        x += a.x; y += a.y; z += a.z;
    }

    void operator-= (my_apoint3d a)
    {
        x -= a.x; y -= a.y; z -= a.z;
    }

    friend my_apoint3d operator+ (my_apoint3d a, my_apoint3d b)
    {
        return (my_apoint3d(a.x + b.x, a.y + b.y, a.z + b.z));
    }

    friend my_apoint3d operator- (my_apoint3d a, my_apoint3d b)
    {
        return (my_apoint3d(a.x - b.x, a.y - b.y, a.z - b.z));
    }

    friend my_apoint3d operator/ (my_apoint3d a, my_apoint3d b)
    {
        return (my_apoint3d(a.x / b.x, a.y / b.y, a.z / b.z));
    }

    friend my_apoint3d operator* (my_apoint3d a, my_apoint3d b)
    {
        return (my_apoint3d(a.x * b.x, a.y * b.y, a.z * b.z));
    }

    friend my_apoint3d operator/ (my_apoint3d a, T b)
    {
        return (my_apoint3d(a.x / b, a.y / b, a.z / b));
    }

    friend my_apoint3d operator* (my_apoint3d a, T b)
    {
        return (my_apoint3d(a.x * b, a.y * b, a.z * b));
    }

    void operator*= (T a)
    {
        x *= a; y *= a; z *= a;
    }

    void operator/= (T a)
    {
        x /= a; y /= a; z /= a;
    }

    friend bool operator== (my_apoint3d a, my_apoint3d b)
    {
        return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
    }

    friend bool operator!= (my_apoint3d a, my_apoint3d b)
    {
        return (!(a==b));
    }

    void unit (void)
    {
        T length = sqrt(x*x + y*y + z*z);

        x /= length;
        y /= length;
        z /= length;
    }

    friend T distance (my_apoint3d a, my_apoint3d b)
    {
        return ((T) DISTANCE3f((float)a.x,(float)a.y,(float)a.z,
                                (float)b.x,(float)b.y,(float)b.z));
    }

    T length (void)
    {
        return (sqrt(x*x + y*y + z*z));
    }

    friend my_apoint3d unit (const my_apoint3d p)
    {
        const T length = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);

        return (my_apoint3d(p.x / length, p.y / length, p.z / length));
    }

    T dot (const my_apoint3d b)
    {
        return (x*b.x + y*b.y + z*b.z);
    }

    //
    // Yields an angle between 0 and 180 deg radians
    //
    friend T angle (const my_apoint3d A, const my_apoint3d B)
    {
        const T a = sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
        const T b = sqrt(B.x*B.x + B.y*B.y + B.z*B.z);

        return (acos((A.x*B.x + A.y*B.y + A.z*B.z) / (a * b)));
    }

    //
    // Yields an angle between 0 and 180 deg radians
    //
    T angle (const my_apoint3d A) const
    {
        const T a = sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
        const T b = sqrt(x*x + y*y + z*z);

        return (acos((A.x*x + A.y*y + A.z*z) / (a * b)));
    }

    void cross (const my_apoint3d b) const
    {
        T xn = y*b.z - b.y*z;
        T yn = z*b.x - x*b.z;
        T zn = x*b.y - y*b.x;

        x = xn;
        y = yn;
        z = zn;
    }

    friend my_apoint3d cross (
        const my_apoint3d a, const my_apoint3d b)
    {
        return my_apoint3d(a.y*b.z - b.y*a.z, a.z*b.x - a.x*b.z,
                           a.x*b.y - a.y*b.x);
    }

    void scale (const T b)
    {
        x *= b;
        y *= b;
        z *= b;
    }

    friend my_apoint3d scale (const my_apoint3d a, const T b)
    {
        return (my_apoint3d(a.x * b, a.y * b, a.z * b));
    }
};

typedef my_apoint3d<int> point3d;
typedef my_apoint3d<double> fpoint3d;
#endif

#endif /* _MY_POINT_H_ */
