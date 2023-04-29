//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FCOLOR_HPP_
#define _MY_FCOLOR_HPP_

//
// As above, but integer based so we can go beyond 255 when adding light sources, but of course we need to average out
// eventually.
//
class fcolor
{
public:
  float r {};
  float g {};
  float b {};
  float a {};

  //
  // For merging lights
  //
  int count {};

  fcolor(void) = default;

  fcolor(float r, float g, float b) : r(r), g(g), b(b), a(255) {}

  fcolor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

  fcolor(const fcolor &c) = default;

  friend fcolor operator+(fcolor c, fcolor b) { return (fcolor(c.r + b.r, c.g + b.g, c.b + b.b, c.a + b.a)); }

  friend fcolor operator-(fcolor c, fcolor b) { return (fcolor(c.r - b.r, c.g - b.g, c.b - b.b, c.a - b.a)); }

  friend fcolor operator/(fcolor c, fcolor b) { return (fcolor(c.r / b.r, c.g / b.g, c.b / b.b, c.a / b.a)); }

  friend fcolor operator*(fcolor c, fcolor b) { return (fcolor(c.r * b.r, c.g * b.g, c.b * b.b, c.a * b.a)); }

  friend fcolor operator/(fcolor c, float b) { return (fcolor(c.r / b, c.g / b, c.b / b, c.a / b)); }

  void operator*=(float c)
  {
    r *= c;
    g *= c;
    b *= c;
    a *= c;
  }

  void operator/=(float c)
  {
    r /= c;
    g /= c;
    b /= c;
    a /= c;
  }

  void operator+=(fcolor i)
  {
    r += i.r;
    g += i.g;
    b += i.b;
  }

  friend bool operator==(const fcolor &c, const fcolor &b)
  {
    return (c.r == b.r) && (c.g == b.g) && (c.b == b.b) && (c.a == b.a);
  }

  friend bool operator!=(const fcolor &c, const fcolor &b) { return (! (c == b)); }

  fcolor(color c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

  color tocolor(void)
  {
    color c;

    if (count == 0) {
      c.r = r;
      c.g = g;
      c.b = b;
    } else {
      c.r = r / count;
      c.g = g / count;
      c.b = b / count;
    }

    if (c.r > 255) {
      c.r = 255;
    }
    if (c.g > 255) {
      c.g = 255;
    }
    if (c.b > 255) {
      c.b = 255;
    }
    c.a = 255;

    return c;
  }
};

extern fcolor FCOLOR_NONE;

#endif // _MY_COLOR_HPP_
