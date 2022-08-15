//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT_HPP_
#define _MY_POINT_HPP_

#include "c_plus_plus_serializer.hpp"
#include "my_math.hpp"
#include <math.h>
#include <string>
#include <vector>

template < class T > class my_apoint
{
public:
  T x {};
  T y {};

  my_apoint(void) : x(0), y(0) {};
  my_apoint(T x, T y) : x(x), y(y) {}
  my_apoint(const my_apoint &a) : x(a.x), y(a.y) {}

  friend std::ostream &operator<<(std::ostream &out, Bits< const my_apoint & > const my)
  {
    out << bits(my.t.x) << bits(my.t.y);
    return (out);
  }

  friend std::istream &operator>>(std::istream &in, Bits< my_apoint & > my)
  {
    in >> bits(my.t.x) >> bits(my.t.y);
    return (in);
  }

  friend std::ostream &operator<<(std::ostream &out, const my_apoint &my)
  {
    out << "(" << my.x << "," << my.y << ")";
    return (out);
  }

  std::string to_string(void) const { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }

  void operator+=(my_apoint a)
  {
    x += a.x;
    y += a.y;
  }

  void operator-=(my_apoint a)
  {
    x -= a.x;
    y -= a.y;
  }

  void operator/=(my_apoint a)
  {
    x /= a.x;
    y /= a.y;
  }

  void operator*=(my_apoint a)
  {
    x *= a.x;
    y *= a.y;
  }

  void operator*=(T a)
  {
    x *= a;
    y *= a;
  }

  void operator/=(T a)
  {
    x /= a;
    y /= a;
  }

  friend bool operator<(my_apoint a, my_apoint b) { return (a.y < b.y) && (a.x < b.x); }

  friend bool operator>(my_apoint a, my_apoint b) { return (a.y > b.y) && (a.x > b.x); }

  friend my_apoint operator+(my_apoint a, my_apoint b) { return (my_apoint(a.x + b.x, a.y + b.y)); }

  friend my_apoint operator-(my_apoint a, my_apoint b) { return (my_apoint(a.x - b.x, a.y - b.y)); }

  friend my_apoint operator/(my_apoint a, my_apoint b) { return (my_apoint(a.x / b.x, a.y / b.y)); }

  friend my_apoint operator/(my_apoint a, T b) { return (my_apoint(a.x / b, a.y / b)); }

  friend my_apoint operator*(my_apoint a, T b) { return (my_apoint(a.x * b, a.y * b)); }

  friend my_apoint operator*(my_apoint a, my_apoint b) { return (my_apoint(a.x * b.x, a.y * b.y)); }

  friend bool operator==(my_apoint a, my_apoint b) { return (a.x == b.x) && (a.y == b.y); }

  friend bool operator!=(my_apoint a, my_apoint b) { return (! (a == b)); }

  T length(void) const { return (sqrt(x * x + y * y)); }

  void unit(void)
  {
    T length = sqrt(x * x + y * y);

    x /= length;
    y /= length;
  }
};

typedef my_apoint< int16_t > point;
typedef my_apoint< float >   fpoint;

static inline point make_point(const int x, const int y) { return point(x, y); }

static inline point make_point(const fpoint &f) { return point(f.x, f.y); }

static inline fpoint make_fpoint(const point f) { return fpoint(f.x, f.y); }

fpoint rotate_radians(float angle, const fpoint &p, const fpoint &origin);
fpoint rotate_radians(const fpoint &p, float angle);
fpoint normal(const fpoint &p);
fpoint unit(const fpoint &p);

float distance(const fpoint &a, const fpoint &b);
float distance(const point a, const point b);
float angle_radians(const fpoint &p);

std::vector< point > line(const point s, const point e, size_t max_elems = 0);

#endif // _MY_POINT_HPP_
