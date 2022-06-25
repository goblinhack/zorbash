//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <iterator>
#include <math.h>
#include <vector>

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

Projectile_::Projectile_(Levelp level, ThingId thing_id, ThingId victim_id, point start, point stop,
                         point pixel_map_at, uint32_t ts_start, uint32_t ts_stop, bool follow_moving_target)
    : id(thing_id), victim_id(victim_id), start(start), stop(stop), pixel_map_at(pixel_map_at), ts_start(ts_start),
      ts_stop(ts_stop), follow_moving_target(follow_moving_target)
{
  TRACE_AND_INDENT();
  auto t = level->thing_find(id);
  if (unlikely(! t)) {
    ERR("no projectile");
    return;
  }

  //
  // Can be either a wand or the projectile itself being fired
  //
  std::string name;
  if (t->is_projectile()) {
    name = t->tp()->name();
  } else {
    name = t->target_name_projectile();
    if (name.empty()) {
      t->err("no projectile name");
      return;
    }
  }

  //
  // Find all projectile animation tiles. Names look like this:
  //
  // "projectile_green.{frame}.1",
  // "projectile_green.{frame}.2",
  // "projectile_green.{frame}.3",
  // "projectile_green.{frame}.4",
  // "projectile_green.{frame}.5",
  // "projectile_green.{frame}.6",
  // "projectile_green.{frame}.7",
  // "projectile_green.{frame}.8",
  // "projectile_green.{frame}.9",
  // "projectile_green.{frame}.10",
  // "projectile_green.{frame}.11",
  // "projectile_green.{frame}.12",
  // "projectile_green.{frame}.13",
  // "projectile_green.{frame}.14",
  // "projectile_green.{frame}.15",
  // "projectile_green.{frame}.16",
  //
  for (int frame = 0; frame < max_frames; frame++) {
    tiles.push_back(tile_find_mand(name + "." + std::to_string(frame + 1)));
  }
}

void Level::new_projectile(ThingId id, ThingId victim_id, point start, point stop, uint32_t dur,
                           bool follow_moving_target)
{
  TRACE_AND_INDENT();
  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      if (t->has_projectile) {
        return;
      }
      t->has_projectile = true;
      t->log("New internal projectile");
    }
  }

  uint32_t now = time_game_ms();
  new_projectiles.push_back(
      Projectile(this, id, victim_id, start, stop, pixel_map_at, now, now + dur, follow_moving_target));
}

void Level::display_projectiles(void)
{
  TRACE_NO_INDENT();

#if 0
  CON("-");
  for (auto p : all_projectiles) {
    CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
  for (auto p : new_projectiles) {
    CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif

  all_projectiles.insert(std::end(all_projectiles), std::begin(new_projectiles), std::end(new_projectiles));
  new_projectiles.clear();

  if (all_projectiles.empty()) {
    return;
  }

  if (g_opt_ascii) {
    display_ascii_projectiles();
  } else {
    display_pixelart_projectiles();
  }
}

bool Thing::projectile_anim_exists(void)
{
  TRACE_AND_INDENT();
  return has_projectile;
}

void Thing::delete_projectile(void)
{
  TRACE_AND_INDENT();
  auto e = std::remove_if(level->all_projectiles.begin(), level->all_projectiles.end(), [ =, this ](Projectile &p) {
    if (p.id == id) {
      log("Remove projectile");
      return true;
    } else {
      return false;
    }
  });

  level->all_projectiles.erase(e, level->all_projectiles.end());
  has_projectile = false;
}
