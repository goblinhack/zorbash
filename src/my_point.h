//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_POINT_H_
#define _MY_POINT_H_

#include "my_main.h"
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
        out << "(" << my.x << ", " << my.y << ")";
        return (out);
    }

    std::string to_string(void)
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
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

    my_apoint rotate (T angle, const my_apoint O) const
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

    my_apoint rotate (T angle) const
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
};

typedef my_apoint<int16_t> spoint;
typedef my_apoint<int> point;
typedef my_apoint<float> fpoint;

template<class T> class my_apoint3d
{
public:

    T x {};
    T y {};
    T z {};

    my_apoint3d (void) : x(0), y(0), z(0) { }

    my_apoint3d (T x, T y, T z) : x(x), y(y), z(z) { }

    my_apoint3d (const my_apoint3d &a) : x(a.x), y(a.y), z(a.z) { }

    friend std::ostream& operator<<(std::ostream &out,
                                    Bits<const my_apoint3d & > const my)
    {
        out << bits(my.t.x) << bits(my.t.y) << bits(my.t.z);
        return (out);
    }

    friend std::istream& operator>>(std::istream &in, Bits<my_apoint3d &> my)
    {
        in >> bits(my.t.x) >> bits(my.t.y) >> bits(my.t.z);
        return (in);
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

    std::string to_string(void)
    {
        return "(" + std::to_string(x) + ", " +
                     std::to_string(y) + ", " +
                     std::to_string(z) + ")";
    }
};

typedef my_apoint3d<int> point3d;
typedef my_apoint3d<float> fpoint3d;

#endif // _MY_POINT_H_
