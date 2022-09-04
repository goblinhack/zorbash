//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iterator>
#include <math.h>
#include <vector>

#include "my_color_defs.hpp"
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

void Level::display_pixelart_projectiles(point tl, point br)
{
  TRACE_NO_INDENT();

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
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

    auto   dist  = distance(start, stop);
    float  steps = (int) ceil(dist) / TILE_WIDTH;
    fpoint diff(stop.x - start.x, stop.y - start.y);
    fpoint step       = diff / steps;
    float  ninety_deg = RAD_360 / 4;

    fpoint perp = step;
    perp        = rotate_radians(perp, ninety_deg);
    perp /= 2;

    int frame = (int) (((float) Projectile::max_frames) * dt);
    if (frame >= Projectile::max_frames) {
      frame = Projectile::max_frames - 1;
    }

    fpoint mid(start.x + (diff.x * dt), start.y + (diff.y * dt));

    step /= 2;
    point tl = make_point(mid - perp - step);
    point tr = make_point(mid - perp + step);
    point bl = make_point(mid + perp - step);
    point br = make_point(mid + perp + step);

    tile_blit(get(p.tiles, frame), tl, tr, bl, br);

#if 0
      //
      // Debug
      //
      gl_blitline(tl.x, tl.y, tr.x, tr.y);
      gl_blitline(tr.x, tr.y, br.x, br.y);
      gl_blitline(br.x, br.y, bl.x, bl.y);
      gl_blitline(bl.x, bl.y, tl.x, tl.y);
#endif

    return false;
  });

  blit_flush();

  all_projectiles.erase(e, all_projectiles.end());
}
