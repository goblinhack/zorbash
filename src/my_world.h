//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_WORLD_H_
#define _MY_WORLD_H_

#include "my_point.h"
#include "my_level.h"

class World
{
public:
  std::array< std::array< std::array< Levelp, LEVELS_DEEP >, LEVELS_DOWN >, LEVELS_ACROSS > levels {};
  //
  // All things on all levels
  //
  std::map< ThingId, Thingp > all_thing_ptrs {};
  //
  // Which level in the world
  //
  point3d at;

  void                 clear(void);
  void                 fini(void);
  void                 dump(std::string prefix, std::ostream &out);
  void                 dump(std::string prefix);
  Levelp               new_level_at(point3d at, int seed);
  friend std::ostream &operator<<(std::ostream &out, Bits< const World & > const my);
  friend std::istream &operator>>(std::istream &in, Bits< World & > my);

  void   alloc_thing_id(Thingp t);
  void   alloc_tmp_thing_id(Thingp t);
  void   realloc_thing_id(Thingp t);
  void   free_thing_id(Thingp t);
  Thingp thing_find_optional(ThingId id);
  Thingp thing_find(ThingId id);
};

#endif
