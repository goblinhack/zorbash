//
// Copyright goblinhack@gmail.com
//

#include "my_serialize.hpp"

std::istream &operator>>(std::istream &in, Bits< point & > my)
{
  in >> bits(my.t.x) >> bits(my.t.y);
  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const point & > const my)
{
  out << bits(my.t.x) << bits(my.t.y);
  return out;
}

std::istream &operator>>(std::istream &in, Bits< fpoint & > my)
{
  in >> bits(my.t.x) >> bits(my.t.y);
  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const fpoint & > const my)
{
  out << bits(my.t.x) << bits(my.t.y);
  return out;
}

std::ostream &operator<<(std::ostream &out, Bits< const point3d & > const my)
{
  out << bits(my.t.x) << bits(my.t.y) << bits(my.t.z);
  return out;
}

std::istream &operator>>(std::istream &in, Bits< point3d & > my)
{
  in >> bits(my.t.x) >> bits(my.t.y) >> bits(my.t.z);
  return in;
}
