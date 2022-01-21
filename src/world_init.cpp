//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
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

Levelp World::new_level_at(point3d world_at, point grid_at, uint32_t seed, int difficulty_depth,
                           int dungeon_walk_order_level_no)
{
  TRACE_AND_INDENT();
  auto old_level = get(levels, world_at.x, world_at.y, world_at.z);
  delete old_level;

  auto new_level = new Level();
  set(levels, world_at.x, world_at.y, world_at.z, new_level);
  new_level->create(world_at, seed, difficulty_depth, dungeon_walk_order_level_no);

  return new_level;
}
