//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

bool Thing::thing_check_for_heat_damage(void)
{
  dbg("Heat damage check");
  TRACE_AND_INDENT();

  if (is_meltable() || is_burnable() || is_combustible() || is_very_combustible()) {
    //
    // Keep going
    //
  } else if (! environ_avoids_fire()) {
    IF_DEBUG3 { dbg("No, is not fire avoider"); }
    return false;
  }

  if (is_immune_to_fire()) {
    IF_DEBUG3 { dbg("No, is not immunie to fire"); }
    return false;
  }

  bool  hit = false;
  point at  = curr_at;

  if (is_on_fire()) {
    dbg("Heat damage check: on fire");
    TRACE_AND_INDENT();

    //
    // Give the player a chance
    //
    if (! level->is_smoke(at.x, at.y)) {
      hit = (d100() < 90);
      if (! hit) {
        if (is_player()) {
          msg("%%fg=green$You feel a brief cool breeze and reprieve from the flames!%%fg=reset$");

          //
          // Smoke ensures a reprieve.
          //
          if (! level->is_smoke(at.x, at.y)) {
            auto smoke = level->thing_new("smoke", at);
            smoke->lifespan_set(pcg_random_range(1, 10));
          }
        }
      }
    } else {
      if (stuck_count() || idle_count()) {
        hit = true;
      } else {
        hit = (d100() < 70);
      }
    }

    //
    // Allow flames to fade away
    //
    if (hit) {
      if (d20roll_under(stat_luck_total() - 5)) {
        if (is_player()) {
          msg("%%fg=green$The flames go out!%%fg=reset$");
        }

        dbg("Remove the flames");
        TRACE_AND_INDENT();
        on_fire_unset();
        hit = false;
      }
    }
  } else if (is_very_combustible() && level->heatmap(at.x, at.y)) {
    //
    // Too close to the flames
    //
    hit = true;
    if (hit) {
      dbg("Heat damage check: very is_combustible and too close to the flames");
    }
  } else if (is_combustible() && (level->heatmap(at.x, at.y) > 2)) {
    //
    // Too close to the flames
    //
    hit = (d100() < 70);
    if (hit) {
      dbg("Heat damage check: is_combustible and too close to the flames");
    }
  } else if (is_meltable() && (level->heatmap(at.x, at.y) > 0)) {
    //
    // Too close to the flames?
    //
    auto melt_chance = melting_chance_d1000();

    //
    // Make things more likely to melt the closer to the heat?
    //
    melt_chance += 100 * level->heatmap(at.x, at.y);

    dbg("Heat damage check, total chance of melting: %d", melt_chance);
    hit = d1000() < melt_chance;
    if (hit) {
      dbg("Heat damage check: is melting");
    }
  } else if (level->is_fire(at.x, at.y)) {
    if (! level->is_smoke(at.x, at.y)) {
      auto smoke = level->thing_new("smoke", at);
      smoke->lifespan_set(pcg_random_range(1, 10));
    }

    //
    // Give the player a chance
    //
    hit = (d100() < 20);

    if (is_meltable() || is_burnable() || is_combustible() || is_very_combustible()) {
      hit = true;
    }

    if (hit) {
      if (d20roll_under(stat_luck_total() - 10)) {
        if (is_player()) {
          msg("%%fg=red$The flames wrap around you but you luckily avoid them!%%fg=reset$");
        }
        hit = false;
      } else {
        if (is_player()) {
          msg("%%fg=red$The flames wrap around you!%%fg=reset$");
        }
      }
    } else {
      if (is_player()) {
        msg("%%fg=red$You dodge the flames.%%fg=reset$");
      }
      hit = false;
    }
  }

  if (hit) {
    dbg("Fire hit");
    TRACE_AND_INDENT();

    if (! is_on_fire()) {
      on_fire_set("caught fire");
    }

    if (! level->is_smoke(at.x, at.y)) {
      auto smoke = level->thing_new("smoke", at);
      smoke->lifespan_set(pcg_random_range(1, 10));
    }
  }

  is_frozen = false;

  return hit;
}

bool Thing::thing_check_for_cold_damage(void)
{
  dbg("Cold damage check");
  TRACE_AND_INDENT();

  if (is_able_to_freeze()) {
    //
    // Keep going
    //
  } else if (! environ_avoids_cold()) {
    IF_DEBUG3 { dbg("No, is not cold avoider"); }
    return false;
  }

  if (is_immune_to_cold()) {
    IF_DEBUG3 { dbg("No, is not immunie to cold"); }
    return false;
  }

  dbg("Fire hit");
  TRACE_AND_INDENT();

  is_frozen = true;
  on_fire_unset();

  return true;
}
