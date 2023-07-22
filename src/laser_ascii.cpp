//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid.hpp"

void Level::display_ascii_lasers(point tl, point br)
{
  TRACE_NO_INDENT();

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  auto now = time_game_ms();
  auto e   = std::remove_if(all_lasers.begin(), all_lasers.end(), [ =, this ](Laser &l) {
    TRACE_NO_INDENT();
    float timestep = l.info.ts_stop - l.info.ts_start;
    float dt       = (((float) (now) -l.info.ts_start)) / timestep;

    Thingp t;

    t = thing_find(l.id);
    if (unlikely(! t)) { return true; }

    if (dt > 1) {
      if (t) {
        //
        // Cannot kill at this point as will be in the display loop and
        // that will break repeatable randomness.
        //
        t->dead_scheduled("End of laser");
        t->laser_count--;
      }
      return true;
    }

    if (l.info.follow_moving_target) {
      auto t = thing_find_optional(l.victim_id);
      if (t) { l.info.map_stop = t->curr_at; }
    }

    auto start = l.info.map_start;
    auto stop  = l.info.map_stop;

    int frame = (int) (((float) Laser::max_frames) * dt);
    if (frame >= Laser::max_frames) { frame = Laser::max_frames - 1; }

    auto tiles = &t->tp()->tiles;
    auto tile  = tile_n(tiles, frame);
    if (tile) {
      int x0 = tl.x + (start.x - minx) - (MAP_BORDER_ROCK - 1);
      int y0 = tl.y + (start.y - miny) - (MAP_BORDER_ROCK - 1);
      int x1 = tl.x + (stop.x - minx) - (MAP_BORDER_ROCK - 1);
      int y1 = tl.y + (stop.y - miny) - (MAP_BORDER_ROCK - 1);

      color c = tile->ascii_fg_col_value;
      c.a     = tile->ascii_fg_alpha;
      ascii_draw_line(TILE_LAYER_FG_3, x0, y0, x1, y1, tile->ascii_fg_char, c);
    }

    return false;
  });

  all_lasers.erase(e, all_lasers.end());
}
