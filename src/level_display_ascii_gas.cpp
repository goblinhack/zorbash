//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_unicode.hpp"
#include "my_wid.hpp"

void Level::display_ascii_gas(point tl, point br, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
{
  TRACE_NO_INDENT();

  static uint32_t last_anim_change;
  if (time_have_x_tenths_passed_since(5, last_anim_change)) { last_anim_change = time_ms(); }

  for (auto y = miny; y < maxy - 1; y++) {
    for (auto x = minx; x < maxx - 1; x++) {

      int intensity = is_gas_poison(x, y);
      if (intensity == 0) { continue; }

      if (intensity > 255) { intensity = 255; }

      point p(x, y);
      int   tx = tl.x + (p.x - minx) - (MAP_BORDER_ROCK - 1);
      int   ty = tl.y + (p.y - miny) - (MAP_BORDER_ROCK - 1);

      ascii_set(TILE_LAYER_FG_1, tx, ty, UNICODE_BLOCK);

      color c = LIMEGREEN;
      c       = color_change_hue(c, non_pcg_random_range(0, 50));
      c.a     = intensity / 2;
      ascii_set(TILE_LAYER_FG_1, tx, ty, c);
    }
  }
}
