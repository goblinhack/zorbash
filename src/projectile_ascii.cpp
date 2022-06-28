//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <iterator>
#include <math.h>
#include <vector>

#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_point.hpp"
#include "my_projectile.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_vector_bounds_check.hpp"

void Level::display_ascii_projectiles(point tl, point br)
{
  TRACE_NO_INDENT();

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  blit_init();
  auto now = time_game_ms();
  auto e   = std::remove_if(all_projectiles.begin(), all_projectiles.end(), [ =, this ](Projectile &p) {
    float timestep = p.info.ts_stop - p.info.ts_start;
    float dt       = (((float) (now) -p.info.ts_start)) / timestep;

    Thingp t;

    t = thing_find(p.id);
    if (unlikely(! t)) {
      return true;
    }

    if (dt > 1) {
      if (t) {
        t->dead("End of projectile");
        t->has_projectile = false;
      }
      return true;
    }

    if (p.info.follow_moving_target) {
      auto t = thing_find_optional(p.victim_id);
      if (t) {
        p.info.pixel_stop = t->last_blit_at;
      }
    }

    auto start = p.info.pixel_start - p.info.pixel_map_at;
    auto stop  = p.info.pixel_stop - p.info.pixel_map_at;

    int frame = (int) (((float) Projectile::max_frames) * dt);
    if (frame >= Projectile::max_frames) {
      frame = Projectile::max_frames - 1;
    }

    auto tiles = &t->tp()->tiles;
    auto tile  = tile_n(tiles, frame);
    if (tile) {
      int x0 = tl.x + (start.x - minx);
      int y0 = tl.y + (start.y - miny);
      int x1 = tl.x + (stop.x - minx);
      int y1 = tl.y + (stop.y - miny);

      int x = x0 + (frame * ((float) (x1 - x0) / (float) Projectile::max_frames));
      int y = y0 + (frame * ((float) (y1 - y0) / (float) Projectile::max_frames));

      color c = tile->ascii_fg_col_value;
      c.a     = tile->ascii_alpha;
      ascii_set_fg4(x, y, tile->ascii_fg_char);
      ascii_set_fg4(x, y, c);
    }

    return false;
  });

  all_projectiles.erase(e, all_projectiles.end());
}
