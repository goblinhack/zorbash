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
#include "my_light.hpp"
#include "my_projectile.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_wid_asciimap.hpp"

void Level::update_light_ascii_map(void)
{
  _ascii_light_source = {};

  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      FOR_ALL_LIGHTS_AT(this, t, x, y)
      {
        for (auto &l : t->light_get()) {
          //
          // In pixel art mode we have more lights. Ignore those.
          //
          if (l->fbo != FBO_PLAYER_VISIBLE_LIGHTING) {
            continue;
          }

          //
          // Skip lights that are in blocked off rooms the player cannot see
          //
          if (get(dmap_to_player.val, t->curr_at.x, t->curr_at.y) >= DMAP_IS_PASSABLE) {
            continue;
          }

          auto t = l->owner;

          int light_scale = l->light_dist / TILE_WIDTH;

          for (int dx = -light_scale; dx <= light_scale; dx++) {
            int x = t->curr_at.x + dx;
            for (int dy = -light_scale; dy <= light_scale; dy++) {
              int y = t->curr_at.y + dy;
              if (is_oob(x, y)) {
                continue;
              }

              float d = DISTANCE(0, 0, dx, dy);
              d *= d;

              fcolor c = fcolor(l->col);

              if (d > 0) {
                c.r /= d;
                c.g /= d;
                c.b /= d;
              }

              fcolor o = ascii_light_source_no_check(x, y);
              o += c;
              o.count++;
              ascii_light_source_set_no_check(x, y, o);
            }
          }
        }
      }
      FOR_ALL_THINGS_END()
    }
  }
}

void Level::display_ascii_map(point tl, point br)
{
  display_map_set_bounds();
  display_tick_animation();

  cursor_find_on_visible_things(minx, miny, maxx, maxy);
  update_light_ascii_map();

  ts_fade_in_begin  = 0;
  ts_fade_out_begin = 0;

  for (auto z = (int) 0; z < MAP_DEPTH; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        point p(x, y);

        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
        {
          if (t->is_gfx_ascii_animated) {
            t->animate();
          }
          t->blit_ascii(tl, br, p);
        }
        FOR_ALL_THINGS_END()
      }
    }
  }
}
