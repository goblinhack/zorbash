//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_depth.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_unicode.hpp"

void Level::display_ascii_gas(point tl, point br, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
{
  TRACE_NO_INDENT();

  static int      r;
  static uint32_t last_anim_change;
  if (time_have_x_tenths_passed_since(5, last_anim_change)) {
    last_anim_change = time_ms();
    r++;
  }

  for (auto y = miny; y < maxy - 1; y++) {
    for (auto x = minx; x < maxx - 1; x++) {

      int intensity = is_gas_poison_no_check(x, y);
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
