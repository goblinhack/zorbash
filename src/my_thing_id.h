//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_THING_ID_H_
#define _MY_THING_ID_H_

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
  ThingId_(uint32_t id) : id(id) {}
  constexpr ThingId_() {}

  bool operator<(const ThingId_ &rhs) const { return (id < rhs.id); }
  bool operator!() const { return id == 0; }
  bool operator==(const ThingId_ &rhs) const { return (id == rhs.id); }
  bool operator!=(const ThingId_ &rhs) const { return (id != rhs.id); }
  bool ok(void) const { return id != 0; }
};

constexpr auto NoThingId = ThingId_();

#endif
