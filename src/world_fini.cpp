//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_sys.hpp"
#include "my_world.hpp"

void World::fini(void)
{
  LOG("World fini: Destroy all levels");
  TRACE_AND_INDENT();

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          l->fini();
          delete l;
          set(levels, x, y, z, (Level *) nullptr);
        }
      }
    }
  }
}
