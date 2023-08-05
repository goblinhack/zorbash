//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_math.hpp"
#include "my_point.hpp"
#include <math.h>

template < typename T > my_apoint< T > operator+(my_apoint< T > const &a, my_apoint< T > const &b)
{
  return my_apoint< T >(a.x + b.x, a.y + b.y);
}
template my_apoint< short > operator+< short >(my_apoint< short > const &, my_apoint< short > const &);
template my_apoint< float > operator+< float >(my_apoint< float > const &, my_apoint< float > const &);

template < typename T > my_apoint< T > operator-(my_apoint< T > const &a, my_apoint< T > const &b)
{
  return my_apoint< T >(a.x - b.x, a.y - b.y);
}
template my_apoint< short > operator-< short >(my_apoint< short > const &, my_apoint< short > const &);
template my_apoint< float > operator-< float >(my_apoint< float > const &, my_apoint< float > const &);

template < typename T > my_apoint< T > operator*(my_apoint< T > const &a, T b)
{
  return my_apoint< T >(a.x * b, a.y * b);
}
template my_apoint< short > operator*< short >(my_apoint< short > const &, short);
template my_apoint< float > operator*< float >(my_apoint< float > const &, float);

template < typename T > my_apoint< T > operator/(my_apoint< T > const &a, T b)
{
  return my_apoint< T >(a.x / b, a.y / b);
}
template my_apoint< short > operator/< short >(my_apoint< short > const &, short);
template my_apoint< float > operator/< float >(my_apoint< float > const &, float);

template < typename T > bool operator==(my_apoint< T > const &a, my_apoint< T > const &b)
{
  return (a.x == b.x) && (a.y == b.y);
}
template bool operator==< short >(my_apoint< short > const &, my_apoint< short > const &);
template bool operator==< float >(my_apoint< float > const &, my_apoint< float > const &);

template < typename T > void my_apoint< T >::operator+=(my_apoint< T > const &b)
{
  x += b.x;
  y += b.y;
}
template void my_apoint< short >::operator+=(my_apoint< short > const &);
template void my_apoint< float >::operator+=(my_apoint< float > const &);

template < typename T > void my_apoint< T >::operator-=(my_apoint< T > const &b)
{
  x -= b.x;
  y -= b.y;
}
template void my_apoint< short >::operator-=(my_apoint< short > const &);
template void my_apoint< float >::operator-=(my_apoint< float > const &);

template < typename T > void my_apoint< T >::operator*=(T b)
{
  x *= b;
  y *= b;
}
template void my_apoint< short >::operator*=(short);
template void my_apoint< float >::operator*=(float);

template < typename T > void my_apoint< T >::operator/=(T b)
{
  x /= b;
  y /= b;
}
template void my_apoint< short >::operator/=(short);
template void my_apoint< float >::operator/=(float);

template < typename T > std::string my_apoint< T >::to_string(void) const
{
  return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}
template std::string my_apoint< short >::to_string(void) const;
template std::string my_apoint< float >::to_string(void) const;

template < typename T > float my_apoint< T >::length(void) const { return (sqrt(x * x + y * y)); }
template float                my_apoint< short >::length(void) const;
template float                my_apoint< float >::length(void) const;

template < typename T > void my_apoint< T >::unit(void)
{
  T len = sqrt(x * x + y * y);
  x /= len;
  y /= len;
}
template void my_apoint< short >::unit(void);
template void my_apoint< float >::unit(void);

// template class my_apoint< short >;
// template class my_apoint< float >;

float distance(const fpoint &a, const fpoint &b) { return (((float) DISTANCE(a.x, a.y, b.x, b.y))); }

float distance(const point a, const point b)
{
  return ((float) DISTANCE((float) a.x, (float) a.y, (float) b.x, (float) b.y));
}

//
// Yields an angle between 0 and 360 deg radians - essentially, how much
// this point has been rotated about the origin.
//
float angle_radians(const fpoint &p)
{
  float theta = asin(p.y / p.length());

  if (p.x > 0) {
    if (p.y > 0) {
      return theta;
    }
    return (RAD_360 + theta);
  }
  return (RAD_180 - theta);
}

fpoint rotate_radians(float angle, const fpoint &p, const fpoint &O)
{
  float s;
  float c;
  sincosf(angle, &s, &c);

  // translate point back to origin:
  float X = p.x - O.x;
  float Y = p.y - O.y;

  // rotate point
  float xnew = X * c - Y * s;
  float ynew = X * s + Y * c;

  // translate point back:
  return (fpoint(xnew + O.x, ynew + O.y));
}

fpoint rotate_radians(const fpoint &p, float angle)
{
  float s;
  float c;
  sincosf(angle, &s, &c);

  float X = p.x;
  float Y = p.y;

  // rotate point
  float xnew = X * c - Y * s;
  float ynew = X * s + Y * c;

  return (fpoint(xnew, ynew));
}

fpoint normal(const fpoint &p)
{
  float length = sqrt((p.x * p.x) + (p.y * p.y));
  return (fpoint(p.x / length, p.y / length));
}

fpoint unit(const fpoint &p)
{
  float length = sqrt(p.x * p.x + p.y * p.y);
  return (fpoint(p.x / length, p.y / length));
}

#ifdef is_unused_flag
uint8_t get_line_intersection(fpoint p0, fpoint p1, fpoint p2, fpoint p3, fpoint *intersect)
{
  double denominator = ((p3.y - p2.y) * (p1.x - p0.x)) - ((p3.x - p2.x) * (p1.y - p0.y));

  if (denominator == 0) {
    return false;
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
    return true;
  }

  return false;
}

uint8_t get_line_intersection(fpoint p0, fpoint p1, fpoint p2, fpoint p3)
{
  double denominator = ((p3.y - p2.y) * (p1.x - p0.x)) - ((p3.x - p2.x) * (p1.y - p0.y));

  if (denominator == 0) {
    return false;
  }

  double a = p0.y - p2.y;
  double b = p0.x - p2.x;

  double numerator1 = ((p3.x - p2.x) * a) - ((p3.y - p2.y) * b);
  double numerator2 = ((p1.x - p0.x) * a) - ((p1.y - p0.y) * b);

  a = numerator1 / denominator;
  b = numerator2 / denominator;

  // if line1 is a segment and line2 is infinite, they intersect if:
  if ((a >= 0) && (a <= 1.0) && (b >= 0) && (b <= 1.0)) {
    return true;
  }

  return false;
}

//
// Two lines we already know intersect.
//
uint8_t get_line_known_intersection(fpoint p0, fpoint p1, fpoint p2, fpoint p3, fpoint *intersect)
{
  double denominator = ((p3.y - p2.y) * (p1.x - p0.x)) - ((p3.x - p2.x) * (p1.y - p0.y));

  if (denominator == 0) {
    return false;
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

  return true;
}

int distance_to_line(fpoint P0, fpoint L0, fpoint L1, float *dist, fpoint *intersect_out)
{
  fpoint intersect;
  double mag;
  double U;

  //
  // Can get the squared distance to avoid this.
  //
  mag = distance(L1, L0);

  //
  // Project point P onto the line and then calc the dot product.
  //
  U = (((P0.x - L0.x) * (L1.x - L0.x)) + ((P0.y - L0.y) * (L1.y - L0.y))) / (mag * mag);

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
    return 0; // closest P0 does not fall within the line segment
  }

  return 1;
}

float dot (const my_apoint b
{
  return (x * b.x + y * b.y);
}
#endif
