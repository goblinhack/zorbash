//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid.hpp"

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
    if (unlikely(! t)) { return true; }

    if (dt > 1) {
      if (t) {
        t->dead("End of projectile");
        t->has_projectile = false;
      }
      return true;
    }

    if (p.info.follow_moving_target) {
      auto t = thing_find_optional(p.victim_id);
      if (t) { p.info.map_stop = t->curr_at; }
    }

    auto start = p.info.map_start;
    auto stop  = p.info.map_stop;

    int frame = (int) (((float) Projectile::max_frames) * dt);
    if (frame >= Projectile::max_frames) { frame = Projectile::max_frames - 1; }

    auto tiles = &t->tp()->tiles;
    auto tile  = tile_n(tiles, frame);
    if (tile) {
      //
      // Draw an ascii line and then find where we are in that line. This is so the path for the projectile
      // takes the same path as we targeted.
      //
      auto points  = ::line(start, stop);
      auto npoints = points.size();
      auto index   = (int) ((((float) npoints) / ((float) Projectile::max_frames)) * ((float) frame));
      int  x       = tl.x + get(points, index).x - (MAP_BORDER_ROCK - 1);
      int  y       = tl.y + get(points, index).y - (MAP_BORDER_ROCK - 1);

      color c = tile->ascii_fg_col_value;
      ascii_set(TILE_LAYER_FG_3, x, y, tile->ascii_fg_char);
      ascii_set(TILE_LAYER_FG_3, x, y, c);
    }

    return false;
  });

  all_projectiles.erase(e, all_projectiles.end());
}
