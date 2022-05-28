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
  display_tick_animation();

  cursor_find_on_visible_things(minx, miny, maxx, maxy);

  ts_fade_in_begin  = 0;
  ts_fade_out_begin = 0;

  for (auto z = (int) 0; z < MAP_DEPTH; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        point p(x, y);

        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
        {
          if (t->gfx_pixelart_animated()) {
            t->animate();
          }
          t->blit_ascii(tl, br, p);
        }
        FOR_ALL_THINGS_END()
      }
    }
  }
}
