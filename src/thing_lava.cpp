//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::lava_tick(void)
{
  TRACE_NO_INDENT();

  if (is_meltable() || is_able_to_burn() || is_combustible() || is_very_combustible()) {
    //
    // Keep going
    //
  } else if (! environ_avoids_fire()) {
    return;
  }

  point at = curr_at;
  if (! level->is_lava(at.x, at.y)) {
    return;
  }

  dbg("Lava tick");
  TRACE_AND_INDENT();

  bool hit = false;

  //
  // Give the player a chance
  //
  if (! level->is_smoke(at.x, at.y)) {
    if (d20roll_under(stat_luck_total())) {
      hit = false;
    } else {
      hit = (d100() < 80);
    }
  } else {
    hit = true;
  }

  if (is_on_fire()) {
    hit = true;
  }

  if (hit) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, at.x, at.y, MAP_DEPTH_LIQUID)
    {
      if (! t->is_lava()) {
        continue;
      }

      is_attacked_with_damage_fire(t, t, t->damage_fire());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    //
    // Even if we do not hit, we need to increase the recently_hit_by so that if a subsequent
    // location check happens, they do not get attacked.
    //
    if (maybe_aip()) {
      FOR_ALL_THINGS_AT_DEPTH(level, t, at.x, at.y, MAP_DEPTH_LIQUID)
      {
        if (t->is_lava()) {
          aip()->recently_hit_by[ t->id ]++;
        }
      }
      FOR_ALL_THINGS_END()
    }

    if (is_player()) {
      if (is_immune_to_fire()) {
        popup("Lovely lava!");
      } else {
        msg("You luckily stand on a sightly cooler rock in the lava!");
        popup("Hm, toasty!");
      }
    }
  }

  if (! level->is_smoke(at.x, at.y)) {
    auto smoke = level->thing_new("smoke", at);
    smoke->lifespan_set(pcg_random_range(1, 10));
  }
}

uint8_t Level::is_lava(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_lava, p.x, p.y));
}

uint8_t Level::is_lava(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_lava, x, y));
}

uint8_t Level::is_lava_no_check(const int x, const int y) { return (get(_is_lava, x, y)); }

void Level::is_lava_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_lava, x, y, (uint8_t) 1);
}

void Level::is_lava_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_lava, x, y, (uint8_t) 1);
}
