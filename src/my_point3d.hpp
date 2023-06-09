//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT3D_HPP_
#define _MY_POINT3D_HPP_

#include "my_point.hpp"

template < class T > class my_apoint3d
{
public:
  T x {};
  T y {};
  T z {};

  my_apoint3d(void) : x(0), y(0), z(0) {}

  my_apoint3d(T x, T y, T z) : x(x), y(y), z(z) {}

  my_apoint3d(const my_apoint3d &a) : x(a.x), y(a.y), z(a.z) {}

  void        operator+=(my_apoint3d< T > const &);
  void        operator-=(my_apoint3d< T > const &);
  void        operator*=(T);
  void        operator/=(T);
  std::string to_string(void) const;
};

template < typename T > std::ostream &operator<<(std::ostream &out, const my_apoint3d< T > &my);

template < typename T > bool             operator==(my_apoint3d< T > const &, my_apoint3d< T > const &);
template < typename T > my_apoint3d< T > operator+(my_apoint3d< T > const &, my_apoint3d< T > const &);
template < typename T > my_apoint3d< T > operator-(my_apoint3d< T > const &, my_apoint3d< T > const &);
template < typename T > my_apoint3d< T > operator*(my_apoint3d< T > const &, T);
template < typename T > my_apoint3d< T > operator/(my_apoint3d< T > const &, T);

using point3d = my_apoint3d< short >;

extern point make_point(const point3d &f);

#endif // _MY_POINT3D_HPP_
