//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_world.h"
#include "my_depth.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void World::clear (void)
{ TRACE_AND_INDENT();
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

Levelp World::new_level_at (point3d at, int seed)
{ TRACE_AND_INDENT();
  auto old_level = get(levels, at.x, at.y, at.z);
  delete old_level;

  auto new_level = new Level();
  set(levels, at.x, at.y, at.z, new_level);
  new_level->create(at, seed);

  return new_level;
}
