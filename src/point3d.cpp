//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_point3d.hpp"

template < typename T > my_apoint3d< T > operator+(my_apoint3d< T > const &a, my_apoint3d< T > const &b)
{
  return my_apoint3d< T >(a.x + b.x, a.y + b.y, a.z + b.z);
}
template my_apoint3d< short > operator+< short >(my_apoint3d< short > const &, my_apoint3d< short > const &);
template my_apoint3d< float > operator+< float >(my_apoint3d< float > const &, my_apoint3d< float > const &);

template < typename T > my_apoint3d< T > operator-(my_apoint3d< T > const &a, my_apoint3d< T > const &b)
{
  return my_apoint3d< T >(a.x - b.x, a.y - b.y, a.z - b.z);
}
template my_apoint3d< short > operator-< short >(my_apoint3d< short > const &, my_apoint3d< short > const &);
template my_apoint3d< float > operator-< float >(my_apoint3d< float > const &, my_apoint3d< float > const &);

template < typename T > my_apoint3d< T > operator*(my_apoint3d< T > const &a, T b)
{
  return my_apoint3d< T >(a.x * b, a.y * b, a.z * b);
}
template my_apoint3d< short > operator*< short >(my_apoint3d< short > const &, short);
template my_apoint3d< float > operator*< float >(my_apoint3d< float > const &, float);

template < typename T > my_apoint3d< T > operator/(my_apoint3d< T > const &a, T b)
{
  return my_apoint3d< T >(a.x / b, a.y / b, a.z / b);
}
template my_apoint3d< short > operator/< short >(my_apoint3d< short > const &, short);
template my_apoint3d< float > operator/< float >(my_apoint3d< float > const &, float);

template < typename T > bool operator==(my_apoint3d< T > const &a, my_apoint3d< T > const &b)
{
  return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}
template bool operator==< short >(my_apoint3d< short > const &, my_apoint3d< short > const &);
template bool operator==< float >(my_apoint3d< float > const &, my_apoint3d< float > const &);

template < typename T > void my_apoint3d< T >::operator+=(my_apoint3d< T > const &b)
{
  x += b.x;
  y += b.y;
  z += b.z;
}
template void my_apoint3d< short >::operator+=(my_apoint3d< short > const &);
template void my_apoint3d< float >::operator+=(my_apoint3d< float > const &);

template < typename T > void my_apoint3d< T >::operator-=(my_apoint3d< T > const &b)
{
  x -= b.x;
  y -= b.y;
  z -= b.z;
}
template void my_apoint3d< short >::operator-=(my_apoint3d< short > const &);
template void my_apoint3d< float >::operator-=(my_apoint3d< float > const &);

template < typename T > void my_apoint3d< T >::operator*=(T b)
{
  x *= b;
  y *= b;
  z *= b;
}
template void my_apoint3d< short >::operator*=(short);
template void my_apoint3d< float >::operator*=(float);

template < typename T > void my_apoint3d< T >::operator/=(T b)
{
  x /= b;
  y /= b;
  z /= b;
}
template void my_apoint3d< short >::operator/=(short);
template void my_apoint3d< float >::operator/=(float);

template < typename T > std::string my_apoint3d< T >::to_string(void) const
{
  return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + " )";
}
template std::string my_apoint3d< short >::to_string(void) const;
template std::string my_apoint3d< float >::to_string(void) const;

point make_point(const point3d &f) { return point(f.x, f.y); }
