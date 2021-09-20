//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include <math.h>

#include "my_sys.h"
#include "my_game.h"
#include "my_laser.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_vector_bounds_check.h"
#include "my_random.h"

Laser_::Laser_(
    Levelp level,
    ThingId thing_id,
    point start, point stop,
    point pixel_map_at,
    uint32_t timestamp_start, uint32_t timestamp_stop) :
  id(thing_id),
  start(start),
  stop(stop),
  pixel_map_at(pixel_map_at),
  timestamp_start(timestamp_start),
  timestamp_stop(timestamp_stop)
{_
  auto t = level->thing_find(id);
  if (!t) {
    ERR("no laser");
    return;
  }

  //
  // Can be either a wand or the projectile itself being fired
  //
  std::string name;
  if (t->is_laser()) {
    name = t->tp()->name();
  } else {
    name = t->laser_name();
    if (name.empty()) {
      t->err("no laser name");
      return;
    }
  }

  //
  // Find all laser animation tiles. Names look like this:
  //
  // "laser_green.{frame}.start",
  // "laser_green.{frame}.{mid}.1",
  // "laser_green.{frame}.{mid}.2",
  // "laser_green.{frame}.{mid}.3",
  // "laser_green.{frame}.{mid}.4",
  // "laser_green.{frame}.{mid}.5",
  // "laser_green.{frame}.{mid}.6",
  // "laser_green.{frame}.{mid}.7",
  // "laser_green.{frame}.{mid}.8",
  // "laser_green.{frame}.{mid}.9",
  // "laser_green.{frame}.{mid}.10",
  // "laser_green.{frame}.{mid}.11",
  // "laser_green.{frame}.{mid}.12",
  // "laser_green.{frame}.{mid}.13",
  // "laser_green.{frame}.{mid}.14",
  // "laser_green.{frame}.end",
  //
  tiles.resize(max_frames);

  for (int frame = 0; frame < max_frames; frame++) {
    tiles[frame].push_back(
      tile_find_mand(name + "." + std::to_string(frame + 1) + ".start"));
    for (int mid = 0; mid < max_frames - 2; mid++) {
      tiles[frame].push_back(
        tile_find_mand(name + "." + std::to_string(frame + 1) +
                 ".mid." + std::to_string(mid + 1)));
    }
    tiles[frame].push_back(
      tile_find_mand(name + "." + std::to_string(frame + 1) + ".end"));
  }
}

void Level::new_laser (ThingId id, point start, point stop, uint32_t dur)
{_
  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      if (t->has_laser) {
        return;
      }
      t->has_laser = true;
      t->log("New internal laser");
    }
  }

  uint32_t now = time_update_time_milli();
  new_lasers.push_back(Laser(this, id,
                 start, stop, pixel_map_at, now, now + dur));
}

void Level::display_lasers (void)
{_
#if 0
  CON("-");
  for (auto p : all_lasers) {
    CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
  for (auto p : new_lasers) {
    CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif

  all_lasers.insert(std::end(all_lasers),
            std::begin(new_lasers),
            std::end(new_lasers));
  new_lasers.clear();

  if (all_lasers.empty()) {
    return;
  }

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();
  auto now = time_update_time_milli();
  auto e = std::remove_if(all_lasers.begin(),
              all_lasers.end(),
    [=, this] (Laser &p) {
      float timestep = p.timestamp_stop - p.timestamp_start;
      float dt = ((float)(now - p.timestamp_start)) / timestep;

      Thingp t;

      t = thing_find(p.id);
      if (!t) {
        return true;
      }

      if (dt > 1) {
        if (t) {
          //
          // Cannot kill at this point as will be in the display loop and
          // that will break repeatable randomness.
          //
          t->dead_scheduled("End of laser");
          t->has_laser = false;
        }
        return true;
      }

      auto start = p.start - p.pixel_map_at;
      auto stop = p.stop - p.pixel_map_at;

      auto dist = distance(start, stop);
      auto steps = (int)ceil(dist) / TILE_WIDTH;
      fpoint diff(stop.x - start.x, stop.y - start.y);
      fpoint step = diff / steps;
      float ninety_deg = RAD_360 / 4;

      fpoint perp = step;
      perp = rotate_radians(perp, ninety_deg);
      perp /= 2;

      point p1;
      point p2;
      point old_p1;
      point old_p2;

      int frame = (int)((float)Laser::max_frames * dt);
      if (frame >= Laser::max_frames) {
        frame = Laser::max_frames - 1;
      }

      for (int animstep = 0; animstep <= steps; animstep++) {
        fpoint mid(start.x + step.x * animstep,
               start.y + step.y * animstep);

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

        if (animstep == 1) {
          tile = get(p.tiles, frame, 0);
        } else if (animstep == steps) {
          tile = get(p.tiles, frame, Laser::max_frames - 1);
        } else {
          tile = get(p.tiles, frame, animstep);
        }

        if (!tile) {
          t->err("No tile for laser, animstep %d, frame %d, steps %d",
               animstep, frame, steps);
          break;
        }
        tile_blit(tile, old_p1, p1, old_p2, p2);
      }

      return false;
    });
  all_lasers.erase(e, all_lasers.end());

  blit_flush();
}

bool Thing::laser_anim_exists (void)
{_
  return has_laser;
}

void Thing::delete_laser (void)
{_
  auto e = std::remove_if(level->all_lasers.begin(),
              level->all_lasers.end(),
    [=, this] (Laser &p) {
      if (p.id == id) {
        log("Remove laser");
        return true;
      } else {
        return false;
      }
    }
  );

  level->all_lasers.erase(e, level->all_lasers.end());
  has_laser = false;
}
