//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//
//
#include "my_level.hpp"
// REMOVED #include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

point Thing::get_random_target(void)
{
  int16_t d     = (int) get_distance_vision();
  auto    tries = 100;

  if (is_player()) {
    d = MAP_WIDTH / 2;
  }

  //
  // Minions cannot wander too far
  //
  auto mob_spawner = get_top_mob_spawner();
  if (mob_spawner) {
    d = (int) get_distance_mob_spawner_max();
  }

  auto leader = get_leader();
  if (leader) {
    d = (int) get_distance_leader_max();
  }

  while (tries--) {
    point   start(curr_at.x, curr_at.y);
    int16_t dx = pcg_random_range(-d, d);
    int16_t dy = pcg_random_range(-d, d);
    if (! dx && ! dy) {
      continue;
    }

    auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

    if (level->is_rock(x, y) || level->is_wall(x, y)) {
      continue;
    }

    if (collision_obstacle(point(x, y))) {
      continue;
    } else {
      auto c = get_terrain_cost(point(x, y));
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
    point   start(curr_at.x, curr_at.y);
    int16_t dx = pcg_random_range(-d, d);
    int16_t dy = pcg_random_range(-d, d);
    if (! dx && ! dy) {
      continue;
    }
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
  point   start(curr_at.x, curr_at.y);
  int16_t dx = pcg_random_range(-d, d);
  int16_t dy = pcg_random_range(-d, d);
  if (! dx && ! dy) {
    return start;
  }
  auto x = std::min(std::max(MAP_BORDER_ROCK, start.x + dx), MAP_WIDTH - MAP_BORDER_ROCK);
  auto y = std::min(std::max(MAP_BORDER_ROCK, start.y + dy), MAP_HEIGHT - MAP_BORDER_ROCK);

  if (is_player()) {
    if (! level->is_lit_currently(x, y)) {
      return point(x, y);
    }
  }

  return point(x, y);
}
