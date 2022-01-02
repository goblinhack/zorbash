//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::fire_tick(void)
{
  if (is_burnable() || is_combustible() || is_very_combustible()) {
    //
    // Keep going
    //
  } else if (! environ_avoids_fire()) {
    IF_DEBUG3 { log("No, is not fire avoider"); }
    return;
  }

  bool  hit = false;
  point at  = curr_at;

  if (is_on_fire()) {
    dbg("Fire tick");
    TRACE_AND_INDENT();

    //
    // Give the player a chance
    //
    if (! level->is_smoke(at.x, at.y)) {
      hit = (d100() < 90);
      if (! hit) {
        if (is_player()) {
          TOPCON("%%fg=green$You feel a brief cool breeze and reprieve from the flames!%%fg=reset$");

          //
          // Smoke ensures a reprieve.
          //
          if (! level->is_smoke(at.x, at.y)) {
            auto smoke = level->thing_new("smoke", at);
            smoke->set_lifespan(pcg_random_range(1, 10));
          }
        }
      }
    } else {
      hit = false;
    }
  } else if (is_very_combustible() && level->heatmap(at.x, at.y)) {
    //
    // Too close to the flames
    //
    hit = true;
  } else if (is_combustible() && (level->heatmap(at.x, at.y) > 2)) {
    //
    // Too close to the flames
    //
    hit = (d100() < 70);
  } else if (level->is_fire(at.x, at.y)) {
    //
    // Give the player a chance
    //
    if (! level->is_smoke(at.x, at.y)) {
      auto smoke = level->thing_new("smoke", at);
      smoke->set_lifespan(pcg_random_range(1, 10));

      hit = (d100() < 20);
      if (hit) {
        if (is_player()) {
          TOPCON("%%fg=red$The flames wrap around you!%%fg=reset$");
        }
      } else {
        if (is_player()) {
          TOPCON("%%fg=red$You dodge the flames.%%fg=reset$");
        }
      }
    } else {
      hit = false;
    }
  }

  if (hit) {
    dbg("Fire hit");
    TRACE_AND_INDENT();

    if (! is_on_fire()) {
      set_on_fire("caught fire");
    }

    auto fire   = tp_find("fire");
    auto damage = fire->get_damage_fire();

    if (environ_avoids_fire()) {
      damage *= 2;
    }

    auto h = decr_health(damage);
    if (is_player()) {
      TOPCON("%%fg=red$You take %u burn damage!%%fg=reset$", damage);
    }

    if (h <= 0) {
      h = set_health(0);
      dead("by burning");
    }

    if (! level->is_smoke(at.x, at.y)) {
      auto smoke = level->thing_new("smoke", at);
      smoke->set_lifespan(pcg_random_range(1, 10));
    }
  }
}
