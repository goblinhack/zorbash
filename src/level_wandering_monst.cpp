//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Level::create_wandering_monster_periodically(void)
{
  if (game->tick_current % 100) {
    return create_wandering_monster_if_unlucky();
  }

  return false;
}

bool Level::create_wandering_monster_if_unlucky(void)
{
  if (! player) {
    return false;
  }

  if (d20_ge(player->stat_luck_total(), SAVING_ROLL_MODERATE)) {
    //
    // Passed the saving throw
    //
    return false;
  }

  return create_wandering_monster_now();
}

bool Level::create_wandering_monster_now(void)
{
  if (is_being_destroyed) {
    return false;
  }

  if (monst_count >= LEVEL_MONST_COUNT_ABS_MAX) {
    return false;
  }

  TRACE_AND_INDENT();

  Tpp tp    = nullptr;
  int tries = 1000;

  while (tries--) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK);

    //
    // Don't spawn monsters in line of sight. They appear out of the darkness.
    //
    if (get(can_see_currently.can_see, x, y)) {
      return false;
    }

    if (is_ascend_dungeon(x, y) || is_monst(x, y) || is_rock(x, y) || is_door(x, y) || is_secret_door(x, y)
        || is_mob(x, y) || is_chasm(x, y) || is_wall(x, y) || is_ascend_sewer(x, y) || is_descend_sewer(x, y)
        || is_descend_dungeon(x, y)) {
      continue;
    }

    if (biome == BIOME_DUNGEON) {
      if (is_corridor(x, y) || is_bridge(x, y) || is_hazard(x, y)) {
        continue;
      }
    }

    point p(x, y);

    //
    // Choose the monster class and have tougher classes less often.
    //
    auto roll = d1000() + difficulty_depth * 10;
    if (roll < 950) {
      tp = get_random_monst_with_class(p, MONST_CLASS_A, 0);
    } else if (roll < 980) {
      tp = get_random_monst_with_class(p, MONST_CLASS_B, 0);
    } else if (roll < 990) {
      tp = get_random_monst_with_class(p, MONST_CLASS_C, 0);
    } else if (roll < 995) {
      tp = get_random_monst_with_class(p, MONST_CLASS_D, 0);
    } else {
      tp = get_random_monst_with_class(p, MONST_CLASS_E, 0);
    }

    //
    // We try to choose from the given class for the difficulty level.
    // If that fails we fallback to an easier class.
    //
    if (tp) {
      con("Place wandering monst %s", tp->name().c_str());
      thing_new(tp->name(), point(x, y));
      return true;
    }
  }
  return false;
}
