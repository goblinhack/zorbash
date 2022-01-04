//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_world.hpp"

void World::clear(void)
{
  TRACE_AND_INDENT();
  LOG("World init: Clear all levels");
  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          l->clear();
        }
      }
    }
  }
}

Levelp World::new_level_at(point3d at, int seed)
{
  TRACE_AND_INDENT();
  auto old_level = get(levels, at.x, at.y, at.z);
  delete old_level;
  std::array< std::array< Roomp, DUNGEON_GRID_CHUNK_HEIGHT >, DUNGEON_GRID_CHUNK_WIDTH > node_rooms {};

  auto new_level = new Level();
  set(levels, at.x, at.y, at.z, new_level);
  new_level->create(at, seed);

  return new_level;
}
