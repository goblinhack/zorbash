//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WORLD_HPP_
#define _MY_WORLD_HPP_

#include <unordered_map>

#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_point.hpp"

namespace std
{
template <> struct hash< ThingId > {
  size_t operator()(const ThingId &x) const noexcept { return std::hash< uint32_t >()(x.id); }
};
}; // namespace std

class World
{
public:
  std::array< std::array< std::array< Levelp, LEVELS_DEEP >, LEVELS_DOWN >, LEVELS_ACROSS > levels {};
  //
  // All things on all levels
  //
  std::unordered_map< ThingId, Thingp > all_thing_ptrs {};
  //
  // Which level in the world
  //
  point3d at;

  void clear(void);
  void fini(void);
  void alloc_thing_id(Thingp t);
  void alloc_tmp_thing_id(Thingp t);
  void realloc_thing_id(Thingp t);
  void free_thing_id(Thingp t);

  Levelp new_level_at(point3d at, point grid_at, uint32_t seed, int difficulty_depth,
                      int dungeon_walk_order_level_no);

  Thingp thing_find_optional(ThingId id);
  Thingp thing_find(ThingId id);
};

#endif
