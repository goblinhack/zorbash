//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_POINT_H_
#define _MY_POINT_H_

#include "my_math.h"
#include "c_plus_plus_serializer.h"

template<class T> class my_apoint
{
public:
    T x {};
    T y {};

    my_apoint (void) : x(0), y(0) {};

    my_apoint (T x, T y) : x(x), y(y) { }

    my_apoint (const my_apoint &a) : x(a.x), y(a.y) { }

    friend std::ostream& operator<<(std::ostream &out,
                                    Bits<const my_apoint & > const my)
    {
        out << bits(my.t.x) << bits(my.t.y);
        return (out);
    }

    friend std::istream& operator>>(std::istream &in, Bits<my_apoint &> my)
    {
        in >> bits(my.t.x) >> bits(my.t.y);
        return (in);
    }

    friend std::ostream& operator << (std::ostream &out, const my_apoint &my)
    {
        out << "(" << my.x << "," << my.y << ")";
        return (out);
    }

    std::string to_string(void)
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
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

    friend my_apoint normal (const my_apoint p)
    {
        T length = sqrt((p.x * p.x) + (p.y * p.y));
        return (my_apoint(p.x / length, p.y / length));
    }

    friend my_apoint unit (const my_apoint p)
    {
        const T length = sqrt(p.x*p.x + p.y*p.y);

        return (my_apoint(p.x / length, p.y / length));
    }

#ifdef UNUSED
    T dot (const my_apoint b) const
    {
        return (x*b.x + y*b.y);
    }
#endif

    //
    // Yields an angle between 0 and 360 deg radians - essentially, how much
    // this point has been rotated about the origin.
    //
    T angle_radians (void) const
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

    my_apoint rotate_radians (T angle, const my_apoint O) const
    {
        T s;
        T c;
        sincosf(angle, &s, &c);

        // translate point back to origin:
        T X = x - O.x;
        T Y = y - O.y;

        // rotate point
        T xnew = X * c - Y * s;
        T ynew = X * s + Y * c;

        // translate point back:
        return (my_apoint(xnew + O.x, ynew + O.y));
    }

    my_apoint rotate_radians (float angle) const
    {
        T s;
        T c;
        sincosf(angle, &s, &c);

        T X = x;
        T Y = y;

        // rotate point
        T xnew = X * c - Y * s;
        T ynew = X * s + Y * c;

        return (my_apoint(xnew, ynew));
    }

    my_apoint rotate_radians (double angle) const
    {
        T s;
        T c;
        sincos(angle, &s, &c);

        T X = x;
        T Y = y;

        // rotate point
        T xnew = X * c - Y * s;
        T ynew = X * s + Y * c;

        return (my_apoint(xnew, ynew));
    }

#ifdef UNUSED
    friend uint8_t get_line_intersection (my_apoint p0,
                                          my_apoint p1,
                                          my_apoint p2,
                                          my_apoint p3,
                                          my_apoint *intersect)
    {
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

    friend uint8_t get_line_intersection (my_apoint p0,
                                          my_apoint p1,
                                          my_apoint p2,
                                          my_apoint p3)
    {
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

        // if line1 is a segment and line2 is infinite, they intersect if:
        if ((a >= 0) && (a <= 1.0) && (b >= 0) && (b <= 1.0)) {
            return (true);
        }

        return (false);
    }

    //
    // Two lines we already know intersect.
    //
    friend uint8_t get_line_known_intersection (my_apoint p0,
                                                my_apoint p1,
                                                my_apoint p2,
                                                my_apoint p3,
                                                my_apoint *intersect)
    {
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

    friend int
    distance_to_line (my_apoint P0, my_apoint L0, my_apoint L1, T *dist,
                      my_apoint *intersect_out)
    {
        my_apoint intersect;
        double mag;
        double U;

        //
        // Can get the squared distance to avoid this.
        //
        mag = distance(L1, L0);

        //
        // Project point P onto the line and then calc the dot product.
        //
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
            return (0); // closest P0 does not fall within the line segment
        }

        return (1);
    }
#endif
};

typedef my_apoint<int16_t> point;
typedef my_apoint<float> fpoint;

static inline point make_point (const int x, const int y) {
    return point(x, y);
}

static inline point make_point (const fpoint& f) {
    return point(f.x, f.y);
}

static inline fpoint make_fpoint (const point& f) {
    return fpoint(f.x, f.y);
}

#endif // _MY_POINT_H_
