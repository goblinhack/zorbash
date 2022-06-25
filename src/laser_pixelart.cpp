//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <iterator>
#include <math.h>
#include <vector>

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

void Level::display_pixelart_lasers(void)
{
  TRACE_NO_INDENT();

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();
  auto now = time_game_ms();
  auto e   = std::remove_if(all_lasers.begin(), all_lasers.end(), [ =, this ](Laser &p) {
    TRACE_NO_INDENT();
    float timestep = p.ts_stop - p.ts_start;
    float dt       = (((float) (now) -p.ts_start)) / timestep;

    Thingp t;

    t = thing_find(p.id);
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

    if (p.follow_moving_target) {
      auto t = thing_find_optional(p.victim_id);
      if (t) {
        p.stop = t->last_blit_at;
      }
    }

    auto start = p.start - p.pixel_map_at;
    auto stop  = p.stop - p.pixel_map_at;

    auto   dist  = distance(start, stop);
    auto   steps = (int) ceil(dist) / TILE_WIDTH;
    fpoint diff(stop.x - start.x, stop.y - start.y);
    fpoint step       = diff / steps;
    float  ninety_deg = RAD_360 / 4;

    fpoint perp = step;
    perp        = rotate_radians(perp, ninety_deg);
    perp /= 2;

    point p1;
    point p2;
    point old_p1;
    point old_p2;

    int frame = (int) (((float) Laser::max_frames) * dt);
    if (frame >= Laser::max_frames) {
      frame = Laser::max_frames - 1;
    }

    for (int animstep = 0; animstep <= steps; animstep++) {
      fpoint mid(start.x + step.x * animstep, start.y + step.y * animstep);

      old_p1 = p1;
      old_p2 = p2;

      p1.x = mid.x - perp.x;
      p1.y = mid.y - perp.y;
      p2.x = mid.x + perp.x;
      p2.y = mid.y + perp.y;

      if (animstep == 0) {
        continue;
      }

      Tilep tile;

      TRACE_NO_INDENT();
      if (animstep == 1) {
        tile = get(p.tiles, frame, 0);
      } else if ((animstep >= steps) || (animstep >= (int) p.tiles.size())) {
        tile = get(p.tiles, frame, Laser::max_frames - 1);
      } else if (animstep >= (int) p.tiles.size()) {
        tile = get(p.tiles, frame, (frame % (p.tiles.size() - 2)) + 1);
      } else {
        tile = get(p.tiles, frame, animstep);
      }

      if (unlikely(! tile)) {
        t->err("No tile for laser, animstep %d, frame %d, steps %d", animstep, frame, steps);
        break;
      }
      if (! g_opt_ascii) {
        tile_blit(tile, old_p1, p1, old_p2, p2);
      }
    }

    return false;
    });

  blit_flush();

  all_lasers.erase(e, all_lasers.end());
}
