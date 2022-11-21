//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_thing.hpp"

#include <math.h>

//
// A new born spawned thing. Perform common checks for it.
//
void Thing::spawned_newborn(Thingp it)
{
  TRACE_NO_INDENT();
  dbg("Spawned thing %s", it->to_short_string().c_str());
  TRACE_AND_INDENT();

  it->inherit_from(this);

  //
  // Like a kraken spwning a tentacle.
  //
  // Or could be an actual mob spawning.
  //
  if (it->is_minion()) {
    dbg("Spawned minion thing %s", it->to_short_string().c_str());
    it->mob_set(this);
  }

  //
  // Like a staff spawning a projectile
  //
  if (is_able_to_spawn_things()) {
    dbg("Spawned owned thing %s", it->to_short_string().c_str());
    it->spawned_owner_set(this);
  }

  //
  // Check if we are newly spawned over a chasm.
  // Or if something we spawned at needs to react to us
  // If a tick is pending there should be no need, as we will do a location check.
  //
  it->location_check_me();
}

bool Thing::spawn_next_to(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn %s next to", what.c_str());
  TRACE_AND_INDENT();

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
  // Don't spawn too many monsters
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_ABS_MAX) {
      dbg("No; too many monsters");
      return false;
    }
  }

  //
  // Don't spawn too many minions
  //
  if (is_mob()) {
    if (minion_count() >= minion_limit()) {
      dbg("No; too many minions");
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

    if (tpp->is_obs_for_ai_for_me(level, p)) {
      continue;
    }

    possible.push_back(p);
  }

  auto cands = possible.size();
  if (! cands) {
    return false;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];
  auto it     = level->thing_new(what, chosen);
  spawned_newborn(it);

  return true;
}

bool Thing::spawn_next_to_or_on_monst(const std::string &what)
{
  TRACE_NO_INDENT();
  dbg("Spawn %s next to or on monst", what.c_str());
  TRACE_AND_INDENT();

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
  // Don't spawn too many monsters
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_ABS_MAX) {
      dbg("No; too many monsters");
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

    if (is_obs_for_ai_for_me(p)) {
      continue;
    }

    possible.push_back(p);
  }

  auto cands = possible.size();
  if (! cands) {
    return false;
  }

  auto chosen = possible[ pcg_random_range(0, cands) ];

  auto it = level->thing_new(what, chosen);
  spawned_newborn(it);

  return true;
}

bool Thing::spawn_radius_range(Thingp item, Thingp target, const std::string &what, int radius_min, int radius_max)
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
    radius_max = item->tp()->effect_radius();
  }

  //
  // For radial effects
  //
  if (radius_min && ! radius_max) {
    radius_max = item->tp()->effect_radius();
  }

  dbg("Spawn %s in radius range %u to %u at %s", what.c_str(), radius_min, radius_max,
      target->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Don't spawn too many monsters
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_ABS_MAX) {
      dbg("No; too many monsters");
      return false;
    }
  }

  auto target_at = target->curr_at;

  for (auto x = target_at.x - radius_max; x <= target_at.x + radius_max; x++) {
    for (auto y = target_at.y - radius_max; y <= target_at.y + radius_max; y++) {
      float dist = DISTANCE(x, y, target_at.x, target_at.y);
      if (level->is_oob(x, y)) {
        continue;
      }

      //
      // Radius needs to be the same as the check in carried_staff_highest_value_for_target
      //
      if (dist > radius_max) {
        dbg("%d,%d too close", x, y);
        continue;
      }

      if (dist < radius_min) {
        dbg("%d,%d too far", x, y);
        continue;
      }

      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        dbg("%d,%d rock or wall", x, y);
        continue;
      }
      dbg("%d,%d ok", x, y);

      auto it = level->thing_new(what, point(x, y));
      spawned_newborn(it);
      it->ts_anim_delay_end_set(time_game_ms_cached() + dist * 100);
    }
  }

  return true;
}

bool Thing::spawn_radius_range(const std::string &what, int radius_min, int radius_max)
{
  TRACE_NO_INDENT();

  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  dbg("Spawn %s in radius range %u to %u", what.c_str(), radius_min, radius_max);
  TRACE_AND_INDENT();

  //
  // Don't spawn too many monsters
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_ABS_MAX) {
      dbg("No; too many monsters");
      return false;
    }
  }

  for (auto x = curr_at.x - radius_max; x <= curr_at.x + radius_max; x++) {
    for (auto y = curr_at.y - radius_max; y <= curr_at.y + radius_max; y++) {
      float dist = DISTANCE(x, y, curr_at.x, curr_at.y);
      if (level->is_oob(x, y)) {
        continue;
      }

      //
      // Radius needs to be the same as the check in carried_staff_highest_value_for_target
      //
      if (dist > radius_max) {
        continue;
      }

      if (dist < radius_min) {
        continue;
      }

      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        continue;
      }

      auto it = level->thing_new(what, point(x, y));
      spawned_newborn(it);
      it->ts_anim_delay_end_set(time_game_ms_cached() + dist * 100);
    }
  }

  return true;
}

int Thing::spawn_randomly_in_radius_range(const std::string &what, int amount, int radius_min, int radius_max)
{
  TRACE_NO_INDENT();

  auto tpp = tp_find(what);
  if (unlikely(! tpp)) {
    err("Cannot find %s to spawn", what.c_str());
    return false;
  }

  dbg("Spawn randomly %s in radius range %u to %u", what.c_str(), radius_min, radius_max);
  TRACE_AND_INDENT();

  //
  // Don't spawn too many monsters
  //
  if (tpp->is_monst()) {
    if (level->monst_count >= LEVEL_MONST_COUNT_ABS_MAX) {
      dbg("No; too many monsters");
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

      if (spawn_at.x < MAP_BORDER_ROCK) {
        continue;
      }
      if (spawn_at.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
        continue;
      }
      if (spawn_at.y < MAP_BORDER_ROCK) {
        continue;
      }
      if (spawn_at.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
        continue;
      }

      //
      // Radius needs to be the same as the check in carried_staff_highest_value_for_target
      //
      float dist = distance(spawn_at, curr_at);
      if (dist > radius_max) {
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

      if (is_obs_for_ai_for_me(spawn_at)) {
        continue;
      }

      //
      // Monster packs are not declared monsters until they polymorph. Until that
      // point make sure the members do not overlap.
      //
      bool skip = false;
      if (tpp->is_monst_pack()) {
        FOR_ALL_NON_INTERNAL_THINGS(level, it, x, y)
        {
          if (it->is_monst()) {
            skip = true;
            break;
          }
          if (! it->is_monst_pack()) {
            skip = true;
            break;
          }
        }
        FOR_ALL_THINGS_END()
      }
      if (skip) {
        continue;
      }

      //
      // For pack spawning make sure all followers can see each other
      //
      if (is_able_to_follow()) {
        if (! level->can_see_unimpeded(spawn_at, curr_at)) {
          continue;
        }
      }

      auto it = level->thing_new(what, spawn_at);
      spawned_newborn(it);
      it->ts_anim_delay_end_set(time_game_ms_cached() + dist * 100);

      spawned++;
      break;
    }
  }

  return spawned;
}

bool Thing::spawn_set_fire_to_things_around_me(const std::string &what, int radius)
{
  TRACE_NO_INDENT();

  dbg("Spawn fire around thing of type: %s", what.c_str());
  TRACE_AND_INDENT();

  if (! radius) {
    radius = 1;
  }

  for (int dx = -radius; dx <= radius; dx++) {
    for (int dy = -radius; dy <= radius; dy++) {

      auto x = curr_at.x + dx;
      auto y = curr_at.y + dy;

      if (! x && ! y) {
        continue;
      }
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
      // Radius needs to be the same as the check in carried_staff_highest_value_for_target
      //
      if (dist > (float) radius + 0.5) {
        continue;
      }

      if (level->is_hazard(x, y) || level->is_rock(x, y) || level->is_wall(x, y)) {
        continue;
      }

      if (level->is_fire(x, y)) {
        continue;
      }

      FOR_ALL_NON_INTERNAL_THINGS(level, it, x, y)
      {
        if (! it->is_combustible() && ! it->is_able_to_burn() && ! it->is_able_to_melt()) {
          continue;
        }

        auto f = level->thing_new(what, point(x, y));
        spawned_newborn(f);
      }
      FOR_ALL_THINGS_END()
    }
  }

  return true;
}

bool Thing::spawn_things_around_me(const std::string &what, int radius)
{
  TRACE_NO_INDENT();

  dbg("Spawn around thing of type: %s", what.c_str());
  TRACE_AND_INDENT();

  if (! radius) {
    radius = 1;
  }

  for (int dx = -radius; dx <= radius; dx++) {
    for (int dy = -radius; dy <= radius; dy++) {

      auto x = curr_at.x + dx;
      auto y = curr_at.y + dy;

      if (! x && ! y) {
        continue;
      }
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
      // Radius needs to be the same as the check in carried_staff_highest_value_for_target
      //
      if (dist > (float) radius + 0.5) {
        continue;
      }

      if (level->is_hazard(x, y) || level->is_rock(x, y) || level->is_wall(x, y)) {
        continue;
      }

      auto f = level->thing_new(what, point(x, y));
      spawned_newborn(f);
    }
  }

  return true;
}

bool Thing::spawn_gas_poison_around_thing(int radius)
{
  TRACE_NO_INDENT();

  dbg("Spawn gas swamp");
  TRACE_AND_INDENT();

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
      // Radius needs to be the same as the check in carried_staff_highest_value_for_target
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

      if (is_obs_for_ai_for_me(p)) {
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

  set(level->gas_poison_cloud, gx, gy, (uint8_t) 254);

  return true;
}

Thingp Thing::spawn_at_if_possible(const std::string &what)
{
  dbg("Spawn at if possible: %s", what.c_str());
  TRACE_AND_INDENT();

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

  auto it = level->thing_new(what, chosen);
  spawned_newborn(it);

  return it;
}

Thingp Thing::spawn_at(const std::string &what) { return spawn_at(what, curr_at); }

Thingp Thing::spawn_at(const std::string &what, point p)
{
  dbg("Spawn thing at: %s", what.c_str());
  TRACE_AND_INDENT();

  Thingp it;
  if (is_able_to_spawn_things()) {
    it = level->thing_new(what, p, this);
  } else {
    it = level->thing_new(what, p);
  }
  spawned_newborn(it);

  return it;
}

Thingp Thing::spawn_owned_thing_at_my_position(const std::string &what)
{
  dbg("Spawn owned thing at: %s", what.c_str());
  TRACE_AND_INDENT();

  auto it = level->thing_new(what, curr_at, this);
  spawned_newborn(it);

  return it;
}
