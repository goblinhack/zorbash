//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Level::display_ascii_gas(int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
{
  TRACE_NO_INDENT();

  static int      r;
  static uint32_t last_anim_change;
  if (time_have_x_tenths_passed_since(2, last_anim_change)) {
    last_anim_change = time_ms();
    r++;
  }

  for (int g = 0; g < 8; g++) {
    for (auto y = miny; y < maxy - 1; y++) {
      for (auto x = minx; x < maxx - 1; x++) {
        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
            uint16_t gx        = x * DUNGEON_GAS_RESOLUTION + dx;
            uint16_t gy        = y * DUNGEON_GAS_RESOLUTION + dy;
            uint8_t  intensity = gas_poison[ gy ][ gx ];

            if (! intensity) {
              continue;
            }

            if (intensity == 255) {
              continue;
            }

            if (intensity > 7) {
              intensity = 7;
            }

            if (intensity != g) {
              continue;
            }
          }
        }
      }
    }
  }
}
