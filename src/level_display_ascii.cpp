//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_laser.hpp"
#include "my_projectile.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_wid_asciimap.hpp"

void Level::display_ascii_map(point tl, point br)
{
  display_map_set_bounds();
  cursor_check_if_scroll_needed();
  cursor_find_on_visible_things(minx, miny, maxx, maxy);

  ts_fade_in_begin  = 0;
  ts_fade_out_begin = 0;

  for (auto z = (int) MAP_DEPTH_FLOOR; z <= MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        point p(x, y);

        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
        {
          cnt++;
          if (t->gfx_animated()) {
            t->animate();
          }
          t->blit_ascii(tl, br, p);
        }
        FOR_ALL_THINGS_END()

        FOR_TMP_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit_ascii(tl, br, p); }
        FOR_ALL_THINGS_END()
      }
    }
  }
  TOPCON("D %d %d %d %d cnt %d", minx, miny, maxx, maxy, cnt);
}
