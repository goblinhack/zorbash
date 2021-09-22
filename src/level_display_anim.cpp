//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

void Level::display_anim (void)
{ TRACE_AND_INDENT();
  static uint32_t anim_speed;
  if (!anim_speed) {
    anim_speed = time_get_time_ms_cached();
  }

  if ((time_get_time_ms_cached() - anim_speed) < (uint)20) {
    return;
  }

  anim_speed = time_get_time_ms_cached();

  //
  // Slow timer to scroll the water.
  //
  if (water_step1++ >= 20) {
    water_step1 = 0;
    if (water_step2++ >= (TILE_HEIGHT * 2) - 1) {
      water_step2 = 0;
    }
  }

  //
  // Slow timer to scroll the deep_water.
  //
  if (deep_water_step1++ >= 40) {
    deep_water_step1 = 0;
    if (deep_water_step2++ >= (TILE_HEIGHT * 2) - 1) {
      deep_water_step2 = 0;
    }
  }

  //
  // Slow timer to scroll the lava.
  //
  if (lava_step1++ >= 4) {
    lava_step1 = 0;
    if (lava_step2++ >= (TILE_HEIGHT * 2) - 1) {
      lava_step2 = 0;
    }
  }
}
