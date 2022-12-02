//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_color_defs.hpp"
// REMOVED #include "my_depth.hpp"
// REMOVED #include "my_font.hpp"
#include "my_game.hpp"
// REMOVED #include "my_gl.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_tex.hpp"
// REMOVED #include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"
#include "my_unicode.hpp"

void Level::display_ascii_gas(point tl, point br, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
{
  TRACE_NO_INDENT();

  static uint32_t last_anim_change;
  if (time_have_x_tenths_passed_since(5, last_anim_change)) {
    last_anim_change = time_ms();
  }

  for (auto y = miny; y < maxy - 1; y++) {
    for (auto x = minx; x < maxx - 1; x++) {

      int intensity = is_gas_poison(x, y);
      if (intensity == 0) {
        continue;
      }

      if (intensity > 255) {
        intensity = 255;
      }

      point p(x, y);
      int   tx = tl.x + (p.x - minx);
      int   ty = tl.y + (p.y - miny);

      ascii_set_fg2(tx, ty, UNICODE_BLOCK);

      color c = LIMEGREEN;
      c       = color_change_hue(c, non_pcg_random_range(0, 50));
      c.a     = intensity / 2;
      ascii_set_fg2(tx, ty, c);
    }
  }
}
