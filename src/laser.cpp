//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
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

Laser_::Laser_(Levelp level, ThingId thing_id, ThingId victim_id, point start, point stop, point pixel_map_at,
               uint32_t ts_start, uint32_t ts_stop, bool follow_moving_target)
    : id(thing_id), victim_id(victim_id), start(start), stop(stop), pixel_map_at(pixel_map_at), ts_start(ts_start),
      ts_stop(ts_stop), follow_moving_target(follow_moving_target)
{
  TRACE_AND_INDENT();
  auto t = level->thing_find(id);
  if (unlikely(! t)) {
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
    name = t->target_name_laser();
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
    tiles[ frame ].push_back(tile_find_mand(name + "." + std::to_string(frame + 1) + ".start"));
    for (int mid = 0; mid < max_frames - 2; mid++) {
      tiles[ frame ].push_back(
          tile_find_mand(name + "." + std::to_string(frame + 1) + ".mid." + std::to_string(mid + 1)));
    }
    tiles[ frame ].push_back(tile_find_mand(name + "." + std::to_string(frame + 1) + ".end"));
  }
}

void Level::new_laser(ThingId id, ThingId victim_id, point start, point stop, uint32_t dur, bool follow_moving_target)
{
  TRACE_AND_INDENT();
  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      t->laser_count++;
      t->log("New internal laser");
    }
  }

  uint32_t now = time_game_ms();
  new_lasers.push_back(Laser(this, id, victim_id, start, stop, pixel_map_at, now, now + dur, follow_moving_target));
}

void Level::display_pixelart_lasers(void)
{
  TRACE_NO_INDENT();
#if 0
  CON("-");
  for (auto p : all_lasers) {
    CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
  for (auto p : new_lasers) {
    CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif

  all_lasers.insert(std::end(all_lasers), std::begin(new_lasers), std::end(new_lasers));
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
  auto now = time_game_ms();
  auto e   = std::remove_if(all_lasers.begin(), all_lasers.end(), [ =, this ](Laser &p) {
    TRACE_NO_INDENT();
    float timestep = p.ts_stop - p.ts_start;
    float dt       = ((float) (now - p.ts_start)) / timestep;

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

    int frame = (int) ((float) Laser::max_frames * dt);
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
  all_lasers.erase(e, all_lasers.end());

  blit_flush();
}

bool Thing::laser_anim_exists(void)
{
  TRACE_AND_INDENT();
  return laser_count > 0;
}

void Thing::delete_laser(void)
{
  TRACE_AND_INDENT();
  auto e = std::remove_if(level->all_lasers.begin(), level->all_lasers.end(), [ =, this ](Laser &p) {
    if (p.id == id) {
      log("Remove laser");
      return true;
    } else {
      return false;
    }
  });

  level->all_lasers.erase(e, level->all_lasers.end());
  laser_count--;
}
