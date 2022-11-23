//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include <iterator>
// REMOVED #include <math.h>
// REMOVED #include <vector>

#include "my_game.hpp"
// REMOVED #include "my_gl.hpp"
// REMOVED #include "my_laser.hpp"
// REMOVED #include "my_point.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"
// REMOVED #include "my_tile.hpp"
// REMOVED #include "my_vector_bounds_check.hpp"

Laser_::Laser_(Levelp level, ThingId thing_id, ThingId victim_id, LaserInfo info)
    : id(thing_id), victim_id(victim_id), info(info)
{
  TRACE_AND_INDENT();
  auto t = level->thing_find(id);
  if (unlikely(! t)) {
    ERR("no laser");
    return;
  }

  //
  // Can be either a staff or the projectile itself being fired
  //
  std::string name;
  if (t->is_laser()) {
    name = t->tp()->name();
  } else {
    name = t->gfx_targetted_laser();
    if (name.empty()) {
      t->err("no laser name");
      return;
    }
  }

  //
  // Find all laser animation tiles. Names look like this:
  //
  // "staff_negation_laser.{frame}.start",
  // "staff_negation_laser.{frame}.{mid}.1",
  // "staff_negation_laser.{frame}.{mid}.2",
  // "staff_negation_laser.{frame}.{mid}.3",
  // "staff_negation_laser.{frame}.{mid}.4",
  // "staff_negation_laser.{frame}.{mid}.5",
  // "staff_negation_laser.{frame}.{mid}.6",
  // "staff_negation_laser.{frame}.{mid}.7",
  // "staff_negation_laser.{frame}.{mid}.8",
  // "staff_negation_laser.{frame}.{mid}.9",
  // "staff_negation_laser.{frame}.{mid}.10",
  // "staff_negation_laser.{frame}.{mid}.11",
  // "staff_negation_laser.{frame}.{mid}.12",
  // "staff_negation_laser.{frame}.{mid}.13",
  // "staff_negation_laser.{frame}.{mid}.14",
  // "staff_negation_laser.{frame}.end",
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

void Level::new_laser(ThingId id, ThingId victim_id, LaserInfo info, uint32_t dur)
{
  TRACE_AND_INDENT();
  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      t->laser_count++;
      IF_DEBUG { t->log("New internal laser"); }
    }
  }

  uint32_t now  = time_game_ms();
  info.ts_start = now;

  //
  // The ascii display is a bit slower, so to avoid not seeing the laser in all its glory, bump the duration.
  //
  dur *= 4;

  info.ts_stop = now + dur;

  new_lasers.push_back(Laser(this, id, victim_id, info));
}

void Level::display_lasers(point tl, point br)
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

  if (g_opt_ascii) {
    display_ascii_lasers(tl, br);
  } else {
    display_pixelart_lasers(tl, br);
  }
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
    }
    return false;
  });

  level->all_lasers.erase(e, level->all_lasers.end());
  laser_count--;
}
