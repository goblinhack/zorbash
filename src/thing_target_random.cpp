//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"
#include <math.h>

point Thing::dest_random_get(int d)
{
  dbg2("Get random target");
  TRACE_AND_INDENT();

  if (! d) {
    if (is_player()) {
      d = MAP_WIDTH / 2;
    } else {
      d = (int) distance_vision_get();
      if (! d) {
        err("Thing has no distance_vision set");
      }
    }
  }

  dbg2("Get random target, dist %d", d);
  TRACE_AND_INDENT();

  auto  tries         = 100;
  point wander_source = curr_at;

  //
  // Minions cannot wander too far
  //
  auto mob = top_mob();
  if (mob && (mob != this)) {
    d             = (int) ceil(distance_minion_from_mob_max_float());
    wander_source = mob->curr_at;
    dbg2("Use mob %s as wander source: %s distance %d", mob->to_short_string().c_str(),
         wander_source.to_string().c_str(), d);
  }

  auto l = leader();
  if (l && (l != this)) {
    d             = (int) ceil(distance_leader_max_float());
    wander_source = l->curr_at;
    dbg2("Use leader %s as wander source: %s distance %d", l->to_short_string().c_str(),
         wander_source.to_string().c_str(), d);
  }

  while (tries--) {
    point   start = wander_source;
    int16_t dx    = pcg_random_range(-d, d);
    int16_t dy    = pcg_random_range(-d, d);

    //
    // Not too close. If we choose one tile adjacent then we may try to walk
    // onto adjacent lava instead of jumping over it.
    //
    if ((abs(dx) <= 1) && (abs(dy) <= 1)) {
      continue;
    }

    dbg2("Try: %d,%d", start.x + dx, start.y + dy);
    TRACE_AND_INDENT();

    auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

    if (! is_able_to_walk_through_walls()) {
      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        dbg2("Try: %d,%d; rock or wall", x, y);
        continue;
      }
    }

    if (is_hated_by_me(point(x, y))) {
      dbg2("Try: %d,%d; no hated terrain", x, y);
      continue;
    }

    if (collision_obstacle(point(x, y))) {
      dbg2("Try: %d,%d; obstacle", x, y);
      continue;
    }

    auto c = terrain_cost_get(point(x, y));
    if (c >= DMAP_LESS_PREFERRED_TERRAIN) {
      dbg2("Try: %d,%d; less preferred terrain", x, y);
      continue;
    }

    if (is_player()) {
      if (! get(level->can_see_currently.can_see, x, y)) {
        continue;
      }
    }

    dbg("Got random target => %d,%d", x, y);
    return point(x, y);
  }

  //
  // Less fussy
  //
  tries = 100;

  while (tries--) {
    point   start = wander_source;
    int16_t dx    = pcg_random_range(-d, d);
    int16_t dy    = pcg_random_range(-d, d);

    //
    // Not too close. If we choose one tile adjacent then we may try to walk
    // onto adjacent lava instead of jumping over it.
    //
    if ((abs(dx) <= 1) && (abs(dy) <= 1)) {
      continue;
    }

    dbg2("Try (2): %d,%d", start.x + dx, start.y + dy);
    TRACE_AND_INDENT();

    auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

    if (! is_able_to_walk_through_walls()) {
      if (level->is_rock(x, y) || level->is_wall(x, y)) {
        dbg2("Try: %d,%d; rock or wall", start.x + dx, start.y + dy);
        continue;
      }
    }

    if (is_player()) {
      if (! get(level->can_see_currently.can_see, x, y)) {
        continue;
      }
    }

    dbg("Got random target => %d,%d", x, y);
    return point(x, y);
  }

  //
  // Any point will do
  //
  point   start = wander_source;
  int16_t dx    = pcg_random_range(-d, d);
  int16_t dy    = pcg_random_range(-d, d);

  //
  // Not too close. If we choose one tile adjacent then we may try to walk
  // onto adjacent lava instead of jumping over it.
  //
  if ((abs(dx) <= 1) && (abs(dy) <= 1)) {
    return start;
  }

  dbg2("Try (3): %d,%d", start.x + dx, start.y + dy);
  TRACE_AND_INDENT();

  auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
  auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

  if (is_player()) {
    if (! get(level->can_see_currently.can_see, x, y)) {
      return point(x, y);
    }
  }

  dbg("Got random target => %d,%d", x, y);
  return point(x, y);
}
