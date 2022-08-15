//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT3D_HPP_
#define _MY_POINT3D_HPP_

#include "c_plus_plus_serializer.hpp"
#include "my_math.hpp"

template < class T > class my_apoint3d
{
public:
  T x {};
  T y {};
  T z {};

  my_apoint3d(void) : x(0), y(0), z(0) {}

  my_apoint3d(T x, T y, T z) : x(x), y(y), z(z) {}

  my_apoint3d(const my_apoint3d &a) : x(a.x), y(a.y), z(a.z) {}

  friend std::ostream &operator<<(std::ostream &out, Bits< const my_apoint3d & > const my)
  {
    out << bits(my.t.x) << bits(my.t.y) << bits(my.t.z);
    return (out);
  }

  friend std::istream &operator>>(std::istream &in, Bits< my_apoint3d & > my)
  {
    in >> bits(my.t.x) >> bits(my.t.y) >> bits(my.t.z);
    return (in);
  }

  void operator+=(my_apoint3d a)
  {
    x += a.x;
    y += a.y;
    z += a.z;
  }

  void operator-=(my_apoint3d a)
  {
    x -= a.x;
    y -= a.y;
    z -= a.z;
  }

  friend my_apoint3d operator+(my_apoint3d a, my_apoint3d b)
  {
    return (my_apoint3d(a.x + b.x, a.y + b.y, a.z + b.z));
  }

  friend my_apoint3d operator-(my_apoint3d a, my_apoint3d b)
  {
    return (my_apoint3d(a.x - b.x, a.y - b.y, a.z - b.z));
  }

  friend my_apoint3d operator/(my_apoint3d a, my_apoint3d b)
  {
    return (my_apoint3d(a.x / b.x, a.y / b.y, a.z / b.z));
  }

  friend my_apoint3d operator*(my_apoint3d a, my_apoint3d b)
  {
    return (my_apoint3d(a.x * b.x, a.y * b.y, a.z * b.z));
  }

  friend my_apoint3d operator/(my_apoint3d a, T b) { return (my_apoint3d(a.x / b, a.y / b, a.z / b)); }

  friend my_apoint3d operator*(my_apoint3d a, T b) { return (my_apoint3d(a.x * b, a.y * b, a.z * b)); }

  void operator*=(T a)
  {
    x *= a;
    y *= a;
    z *= a;
  }

  void operator/=(T a)
  {
    x /= a;
    y /= a;
    z /= a;
  }

  friend bool operator==(my_apoint3d a, my_apoint3d b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }

  friend bool operator!=(my_apoint3d a, my_apoint3d b) { return (! (a == b)); }

#ifdef unused_flag
  void unit(void)
  {
    T length = sqrt(x * x + y * y + z * z);

    x /= length;
    y /= length;
    z /= length;
  }

  T length(void) { return (sqrt(x * x + y * y + z * z)); }

  friend my_apoint3d unit(const my_apoint3d p)
  {
    const T length = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);

    return (my_apoint3d(p.x / length, p.y / length, p.z / length));
  }

  T dot(const my_apoint3d b) { return (x * b.x + y * b.y + z * b.z); }

  //
  // Yields an angle between 0 and 180 deg radians
  //
  friend T angle(const my_apoint3d A, const my_apoint3d B)
  {
    const T a = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
    const T b = sqrt(B.x * B.x + B.y * B.y + B.z * B.z);

    return (acos((A.x * B.x + A.y * B.y + A.z * B.z) / (a * b)));
  }

  //
  // Yields an angle between 0 and 180 deg radians
  //
  T angle(const my_apoint3d A) const
  {
    const T a = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
    const T b = sqrt(x * x + y * y + z * z);

    return (acos((A.x * x + A.y * y + A.z * z) / (a * b)));
  }

  void cross(const my_apoint3d b) const
  {
    T xn = y * b.z - b.y * z;
    T yn = z * b.x - x * b.z;
    T zn = x * b.y - y * b.x;

    x = xn;
    y = yn;
    z = zn;
  }

  friend my_apoint3d cross(const my_apoint3d a, const my_apoint3d b)
  {
    return my_apoint3d(a.y * b.z - b.y * a.z, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
  }

  void scale(const T b)
  {
    x *= b;
    y *= b;
    z *= b;
  }

  friend my_apoint3d scale(const my_apoint3d a, const T b) { return (my_apoint3d(a.x * b, a.y * b, a.z * b)); }
#endif

  std::string to_string(void)
  {
    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
  }
};

typedef my_apoint3d< int16_t > point3d;
typedef my_apoint3d< float >   fpoint3d;

static inline point make_point(const point3d &f) { return point(f.x, f.y); }

#endif // _MY_POINT3D_HPP_
