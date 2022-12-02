//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

void Level::display_tick_animation(void)
{
  TRACE_NO_INDENT();
  static uint32_t anim_speed;
  if (! anim_speed) {
    anim_speed = time_ms_cached();
  }

  if ((time_ms_cached() - anim_speed) < (uint) 20) {
    return;
  }

  anim_speed = time_ms_cached();

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
