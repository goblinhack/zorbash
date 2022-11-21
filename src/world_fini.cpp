//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_wid_progress_bar.hpp"
#include "my_world.hpp"

void World::fini(void)
{
  LOG("World fini: Destroy all levels");
  TRACE_AND_INDENT();

  int count = 0;
  int step  = 0;

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          count++;
        }
      }
    }
  }

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          step++;
          if (count > 1) {
            wid_progress_bar("Dismantling the dungeon...", ((float) step) / ((float) count));
          }
          l->fini();
          delete l;
          set(levels, x, y, z, (Level *) nullptr);
        }
      }
    }
  }
  wid_progress_bar_destroy();
}
