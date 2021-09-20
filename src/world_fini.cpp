//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_world.h"
#include "my_depth.h"
#include "my_array_bounds_check.h"

void World::fini (void)
{_
  LOG("World fini: Destroy all levels");
  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          l->fini();
          delete l;
          set(levels, x, y, z, (Level*)nullptr);
        }
      }
    }
  }
}
