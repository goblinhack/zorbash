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
#include "my_laser.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_vector_bounds_check.hpp"

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
    if (unlikely(! t)) {
      return true;
    }

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
      if (t) {
        l.info.map_stop = t->curr_at;
      }
    }

    auto start = l.info.map_start;
    auto stop  = l.info.map_stop;

    int frame = (int) (((float) Laser::max_frames) * dt);
    if (frame >= Laser::max_frames) {
      frame = Laser::max_frames - 1;
    }

    auto tiles = &t->tp()->tiles;
    auto tile  = tile_n(tiles, frame);
    if (tile) {
      int x0 = tl.x + (start.x - minx);
      int y0 = tl.y + (start.y - miny);
      int x1 = tl.x + (stop.x - minx);
      int y1 = tl.y + (stop.y - miny);

      color c = tile->ascii_fg_col_value;
      c.a     = tile->ascii_alpha;
      ascii_draw_line_fg4(x0, y0, x1, y1, tile->ascii_fg_char, c);
    }

    return false;
  });

  all_lasers.erase(e, all_lasers.end());
}
