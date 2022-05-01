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

void Level::display_ascii_map(point tl, point br)
{
  display_map_set_bounds();

  for (auto z = 0; z < MAP_DEPTH; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        point p(x, y);

        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
        {
          t->animate();
          t->blit_ascii(tl, br, p);
        }
        FOR_ALL_THINGS_END()

        FOR_TMP_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit_ascii(tl, br, p); }
        FOR_ALL_THINGS_END()
      }
    }
  }
}
