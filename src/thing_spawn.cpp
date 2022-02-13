//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <math.h>

#include "my_game.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::spawn_next_to(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn %s next to", what.c_str());
  TRACE_NO_INDENT();
  std::vector< point >              possible;
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1), point(-1, 0), point(1, 0), point(0, 1),
  };

  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  //
  // Don't spawn too many monsts
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_MAX) {
      dbg("Too many minions");
      return false;
    }
  }

  //
  // Don't spawn too many minions
  //
  if (is_mob()) {
    if (minion_count() >= minion_limit()) {
      return false;
    }
  }

  for (const auto &d : all_deltas) {
    auto x = curr_at.x + d.x;
    auto y = curr_at.y + d.y;
    auto p = point(x, y);

    //
    // No spawning onto chasms for example
    //
    if (tpp->is_disliked_by_me(level, p)) {
      continue;
    }

    if (collision_obstacle(p)) {
      continue;
    }

    if (tpp->ai_obstacle_for_me(level, p)) {
      continue;
    }

    possible.push_back(p);
  }

  auto cands = possible.size();
  if (! cands) {
    return false;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];
  auto c      = level->thing_new(what, chosen);
  c->inherit_from(this);

  if (c->is_minion()) {
    c->mob_set(this);
  }

  if (is_spawner()) {
    c->spawned_owner_set(this);
  }

  //
  // Check if we are newly spawned over a chasm
  // Or if something we spawned at needs to react to us
  //
  c->location_check_forced_all_things_at();

  return true;
}

bool Thing::spawn_next_to_or_on_monst(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn %s next to or on monst", what.c_str());

  std::vector< point >              possible;
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1), point(-1, 0), point(1, 0), point(0, 1),
  };

  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  //
  // Don't spawn too many monsts
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_MAX) {
      return false;
    }
  }

  for (const auto &d : all_deltas) {
    auto x = curr_at.x + d.x;
    auto y = curr_at.y + d.y;
    auto p = point(x, y);

    if (level->is_door(x, y) || level->is_secret_door(x, y) || level->is_mob(x, y) || level->is_hazard(x, y) ||
        level->is_rock(x, y) || level->is_wall(x, y)) {
      continue;
    }

    //
    // No spawning onto chasms for example
    //
    if (tpp->is_disliked_by_me(level, p)) {
      continue;
    }

    if (collision_obstacle(p)) {
      continue;
    }

    if (ai_obstacle_for_me(p)) {
      continue;
    }

    possible.push_back(p);
  }

  auto cands = possible.size();
  if (! cands) {
    return false;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];

  auto c = level->thing_new(what, chosen);
  c->inherit_from(this);
  if (is_spawner()) {
    c->spawned_owner_set(this);
  }

  //
  // Check if we are newly spawned over a chasm
  // Or if something we spawned at needs to react to us
  //
  c->location_check_forced_all_things_at();

  return true;
}

bool Thing::spawn_radius_range(Thingp item, Thingp target, const std::string &what, uint32_t radius_min,
                               uint32_t radius_max)
{
  TRACE_NO_INDENT();
  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  if (! target) {
    err("No target to spawn %s", what.c_str());
    return false;
  }

  if (! item) {
    err("No item to spawn %s", what.c_str());
    return false;
  }

  if (! radius_min && ! radius_max) {
    radius_min = item->tp()->blast_min_radius();
    radius_max = item->tp()->blast_max_radius();
  }

  dbg("Spawn %s in radius range %u to %u", what.c_str(), radius_min, radius_max);

  //
  // Don't spawn too many monsts
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_MAX) {
      return false;
    }
  }

  auto curr_at = target->curr_at;

  for (auto x = curr_at.x - radius_max; x <= curr_at.x + radius_max; x++) {
    for (auto y = curr_at.y - radius_max; y <= curr_at.y + radius_max; y++) {
      float dist = DISTANCE(x, y, curr_at.x, curr_at.y);

      //
      // Radius needs to be the same as the check in carried_wand_highest_value_for_target
      //
      if (dist >= radius_max) {
        continue;
      }

      if (dist < radius_min) {
        continue;
      }

      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        continue;
      }

      auto c = level->thing_new(what, point(x, y));
      c->inherit_from(this);
      c->ts_anim_delay_end_set(time_get_time_ms_cached() + dist * 100);

      if (is_spawner()) {
        c->spawned_owner_set(this);
      }

      //
      // Check if we are newly spawned over a chasm
      // Or if something we spawned at needs to react to us
      //
      c->location_check_forced_all_things_at();
    }
  }

  location_check_forced_all_things_at();
  return true;
}

bool Thing::spawn_radius_range(const std::string &what, uint32_t radius_min, uint32_t radius_max)
{
  TRACE_NO_INDENT();
  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  dbg("Spawn %s in radius range %u to %u", what.c_str(), radius_min, radius_max);

  //
  // Don't spawn too many monsts
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_MAX) {
      return false;
    }
  }

  for (auto x = curr_at.x - radius_max; x <= curr_at.x + radius_max; x++) {
    for (auto y = curr_at.y - radius_max; y <= curr_at.y + radius_max; y++) {
      float dist = DISTANCE(x, y, curr_at.x, curr_at.y);

      //
      // Radius needs to be the same as the check in carried_wand_highest_value_for_target
      //
      if (dist >= radius_max) {
        continue;
      }

      if (dist < radius_min) {
        continue;
      }

      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        continue;
      }

      auto c = level->thing_new(what, point(x, y));
      c->inherit_from(this);
      c->ts_anim_delay_end_set(time_get_time_ms_cached() + dist * 100);

      if (is_spawner()) {
        c->spawned_owner_set(this);
      }

      //
      // Check if we are newly spawned over a chasm
      // Or if something we spawned at needs to react to us
      //
      c->location_check_forced_all_things_at();
    }
  }

  location_check_forced_all_things_at();
  return true;
}

int Thing::spawn_randomly_in_radius_range(const std::string &what, int amount, uint32_t radius_min,
                                          uint32_t radius_max)
{
  TRACE_NO_INDENT();
  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  dbg("Spawn randomly %s in radius range %u to %u", what.c_str(), radius_min, radius_max);

  //
  // Don't spawn too many monsts
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_MAX) {
      dbg("Too many monsters");
      return false;
    }
  }

  int spawned = 0;
  while (--amount > 0) {
    int tries = 10;
    while (tries--) {
      int x = pcg_random_range(radius_min, radius_max);
      int d = pcg_random_range(0, 10);
      if (d < 5) {
        x = -x;
      }

      int y = pcg_random_range(radius_min, radius_max);
      d     = pcg_random_range(0, 10);
      if (d < 5) {
        y = -y;
      }

      point spawn_at = curr_at + point(x, y);

      //
      // Radius needs to be the same as the check in carried_wand_highest_value_for_target
      //
      float dist = distance(spawn_at, curr_at);
      if (dist >= radius_max) {
        continue;
      }

      if (dist < radius_min) {
        continue;
      }

      if (level->is_rock(spawn_at) || level->is_wall(spawn_at)) {
        continue;
      }

      if (tpp->is_disliked_by_me(level, spawn_at)) {
        continue;
      }

      if (collision_obstacle(spawn_at)) {
        continue;
      }

      if (ai_obstacle_for_me(spawn_at)) {
        continue;
      }

      //
      // For pack spawning make sure all followers can see each other
      //
      if (is_able_to_follow()) {
        if (! level->can_see_unimpeded(spawn_at.x, spawn_at.y, curr_at.x, curr_at.y)) {
          continue;
        }
      }

      auto c = level->thing_new(what, spawn_at);

      c->inherit_from(this);
      c->ts_anim_delay_end_set(time_get_time_ms_cached() + dist * 100);

      if (is_spawner()) {
        c->spawned_owner_set(this);
      }

      //
      // Check if we are newly spawned over a chasm
      // Or if something we spawned at needs to react to us
      //
      c->location_check_forced_all_things_at();
      spawned++;
      break;
    }
  }

  location_check_forced_all_things_at();
  return spawned;
}

bool Thing::spawn_fire(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn fire: %s", what.c_str());

  std::vector< point >              possible;
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1), point(-1, 0), point(1, 0), point(0, 1),
  };

  for (const auto &d : all_deltas) {
    auto x = curr_at.x + d.x;
    auto y = curr_at.y + d.y;
    auto p = point(x, y);

    if (level->is_hazard(x, y) || level->is_rock(x, y) || level->is_wall(x, y)) {
      continue;
    }

    if (collision_obstacle(p)) {
      continue;
    }

    if (ai_obstacle_for_me(p)) {
      continue;
    }

    possible.push_back(p);
  }

  auto cands = possible.size();
  if (! cands) {
    return false;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];

  auto c = level->thing_new(what, chosen);
  c->inherit_from(this);

  if (is_spawner()) {
    c->spawned_owner_set(this);
  }

  //
  // Check if we are newly spawned over a chasm
  // Or if something we spawned at needs to react to us
  //
  c->location_check_forced_all_things_at();

  return true;
}

bool Thing::spawn_gas_poison(int radius)
{
  TRACE_NO_INDENT();
  dbg("Spawn gas swamp");

  std::vector< point > possible;

  for (int dx = -radius; dx <= radius; dx++) {
    for (int dy = -radius; dy <= radius; dy++) {

      auto x = curr_at.x + dx;
      auto y = curr_at.y + dy;

      if (x < MAP_BORDER_ROCK) {
        continue;
      }
      if (x >= MAP_WIDTH - MAP_BORDER_ROCK) {
        continue;
      }
      if (y < MAP_BORDER_ROCK) {
        continue;
      }
      if (y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
        continue;
      }

      float dist = DISTANCE(x, y, curr_at.x, curr_at.y);

      //
      // Radius needs to be the same as the check in carried_wand_highest_value_for_target
      //
      if (dist > radius) {
        continue;
      }

      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        continue;
      }

      auto p = point(x, y);

      if (collision_obstacle(p)) {
        continue;
      }

      if (ai_obstacle_for_me(p)) {
        continue;
      }

      possible.push_back(p);
    }
  }

  auto cands = possible.size();
  if (! cands) {
    return false;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];

  uint16_t gx =
      (chosen.x * DUNGEON_GAS_RESOLUTION) + pcg_random_range(-DUNGEON_GAS_RESOLUTION, DUNGEON_GAS_RESOLUTION);
  uint16_t gy =
      (chosen.y * DUNGEON_GAS_RESOLUTION) + pcg_random_range(-DUNGEON_GAS_RESOLUTION, DUNGEON_GAS_RESOLUTION);

  level->gas_poison[ gy ][ gx ] = 254;

  return true;
}

Thingp Thing::spawn_at_if_possible(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn under: %s", what.c_str());

  std::vector< point > possible;
  auto                 x = curr_at.x;
  auto                 y = curr_at.y;
  auto                 p = point(x, y);

  if (level->is_hazard(x, y) || level->is_rock(x, y) || level->is_wall(x, y)) {
    return nullptr;
  }

  possible.push_back(p);

  auto cands = possible.size();
  if (! cands) {
    return nullptr;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];

  auto c = level->thing_new(what, chosen);
  c->inherit_from(this);
  if (is_spawner()) {
    c->spawned_owner_set(this);
  }

  //
  // Check if we are newly spawned over a chasm
  // Or if something we spawned at needs to react to us
  //
  c->location_check_forced_all_things_at();

  return c;
}

Thingp Thing::spawn_at(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn under: %s", what.c_str());

  std::vector< point > possible;
  auto                 x = curr_at.x;
  auto                 y = curr_at.y;
  auto                 p = point(x, y);

  possible.push_back(p);

  auto cands = possible.size();
  if (! cands) {
    return nullptr;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];

  auto c = level->thing_new(what, chosen);
  c->inherit_from(this);
  if (is_spawner()) {
    c->spawned_owner_set(this);
  }

  //
  // Check if we are newly spawned over a chasm
  // Or if something we spawned at needs to react to us
  //
  c->location_check_forced_all_things_at();

  return c;
}
