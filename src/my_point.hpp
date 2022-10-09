//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT_HPP_
#define _MY_POINT_HPP_

#include <string>
#include <vector>

template < class T > class my_apoint
{
public:
  T x {};
  T y {};

  my_apoint(const my_apoint &a) : x(a.x), y(a.y) {}
  my_apoint(T x, T y) : x(x), y(y) {}
  my_apoint(void) : x(0), y(0) {};

  void        operator+=(my_apoint< T > const &);
  void        operator-=(my_apoint< T > const &);
  void        operator*=(T);
  void        operator/=(T);
  std::string to_string(void) const;
  float       length(void) const;
  void        unit(void);
};

using point  = my_apoint< int16_t >;
using fpoint = my_apoint< float >;

template < typename T > std::ostream &operator<<(std::ostream &out, const my_apoint< T > &my);

template < typename T > bool           operator==(my_apoint< T > const &, my_apoint< T > const &);
template < typename T > my_apoint< T > operator+(my_apoint< T > const &, my_apoint< T > const &);
template < typename T > my_apoint< T > operator-(my_apoint< T > const &, my_apoint< T > const &);
template < typename T > my_apoint< T > operator*(my_apoint< T > const &, T);
template < typename T > my_apoint< T > operator/(my_apoint< T > const &, T);

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
