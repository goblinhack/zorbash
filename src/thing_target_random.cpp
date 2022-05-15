//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

point Thing::dest_random_get(int d)
{
  dbg("Get random target");
  TRACE_AND_INDENT();

  if (! d) {
    if (is_player()) {
      d = MAP_WIDTH / 2;
    } else {
      d = (int) distance_vision_get();
    }
  }

  auto  tries         = 100;
  point wander_source = curr_at;

  //
  // Minions cannot wander too far
  //
  auto mob = top_mob();
  if (mob) {
    d             = (int) distance_mob_max_float();
    wander_source = mob->curr_at;
    dbg("Use mob %s as wander source: %s", mob->to_short_string().c_str(), wander_source.to_string().c_str());
  }

  auto l = leader();
  if (l) {
    d             = (int) distance_leader_max_float();
    wander_source = l->curr_at;
    dbg("Use leader %s as wander source: %s", l->to_short_string().c_str(), wander_source.to_string().c_str());
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

    dbg("Try: %s", start.to_string().c_str());
    TRACE_AND_INDENT();

    auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

    if (level->is_rock(x, y) || level->is_wall(x, y)) {
      continue;
    }

    if (collision_obstacle(point(x, y))) {
      continue;
    } else {
      auto c = terrain_cost_get(point(x, y));
      if (c >= DMAP_LESS_PREFERRED_TERRAIN) {
        continue;
      } else {
        if (is_player()) {
          if (! get(level->can_see_currently.can_see, x, y)) {
            continue;
          }
        }

        dbg("Get random target => %d,%d", x, y);
        return point(x, y);
      }
    }
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

    dbg("Try (2): %s", start.to_string().c_str());
    TRACE_AND_INDENT();

    auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

    if (level->is_rock(x, y) || level->is_wall(x, y)) {
      continue;
    }

    if (is_player()) {
      if (! get(level->can_see_currently.can_see, x, y)) {
        continue;
      }
    }

    dbg("Get random target => %d,%d", x, y);
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

  dbg("Try (3): %s", start.to_string().c_str());
  TRACE_AND_INDENT();

  auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
  auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

  if (is_player()) {
    if (! get(level->can_see_currently.can_see, x, y)) {
      return point(x, y);
    }
  }

  dbg("Get random target => %d,%d", x, y);
  return point(x, y);
}
