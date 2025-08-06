//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_ID_HPP_
#define _MY_THING_ID_HPP_

#include "my_sys.hpp"

//
// All levels share the same thing ID namespace so we can find any
// thing on any level just by its number
//
// If this gets too slow, consider using the first byte as level
// number.
//
using ThingId = struct ThingId_ {
public:
  uint32_t id {};
  ThingId_(int16_t id) : id(id) { DIE("error, ThingID must be uint32"); }
  ThingId_(int32_t id) : id(id) { DIE("error, ThingID must be uint32"); }
  ThingId_(uint32_t id) : id(id) {}
  constexpr ThingId_() = default;

  bool operator<(const ThingId_ &rhs) const { return (id < rhs.id); }
  bool operator!() const { return id == 0; }
  bool operator==(const ThingId_ &rhs) const { return (id == rhs.id); }
  bool operator!=(const ThingId_ &rhs) const { return (id != rhs.id); }
  bool ok(void) const { return id != 0; }
};

constexpr auto NoThingId = ThingId_();

#endif
