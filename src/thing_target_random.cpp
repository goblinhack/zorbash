//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//
//
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

point Thing::dest_random_get(int d)
{
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
  auto mob = top_mob_get();
  if (mob) {
    d             = (int) distance_mob_max_get();
    wander_source = mob->curr_at;
    dbg("Use mob %s as wander source: %s", mob->to_short_string().c_str(), wander_source.to_string().c_str());
  }

  auto leader = leader_get();
  if (leader) {
    d             = (int) distance_leader_max_get();
    wander_source = leader->curr_at;
    dbg("Use leader %s as wander source: %s", leader->to_short_string().c_str(), wander_source.to_string().c_str());
  }

  while (tries--) {
    point   start = wander_source;
    int16_t dx    = pcg_random_range(-d, d);
    int16_t dy    = pcg_random_range(-d, d);
    if (! dx && ! dy) {
      continue;
    }

    dbg("Try: %s", start.to_string().c_str());
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
          if (! level->is_lit_currently(x, y)) {
            continue;
          }
        }

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
    if (! dx && ! dy) {
      continue;
    }

    dbg("Try (2): %s", start.to_string().c_str());
    auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

    if (level->is_rock(x, y) || level->is_wall(x, y)) {
      continue;
    }

    if (is_player()) {
      if (! level->is_lit_currently(x, y)) {
        continue;
      }
    }

    return point(x, y);
  }

  //
  // Any point will do
  //
  point   start = wander_source;
  int16_t dx    = pcg_random_range(-d, d);
  int16_t dy    = pcg_random_range(-d, d);
  if (! dx && ! dy) {
    return start;
  }
  dbg("Try (3): %s", start.to_string().c_str());
  auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
  auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

  if (is_player()) {
    if (! level->is_lit_currently(x, y)) {
      return point(x, y);
    }
  }

  return point(x, y);
}
