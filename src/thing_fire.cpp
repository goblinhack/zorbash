//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::fire_tick(void)
{
  if (is_meltable() || is_burnable() || is_combustible() || is_very_combustible()) {
    //
    // Keep going
    //
  } else if (! environ_avoids_fire()) {
    IF_DEBUG3 { dbg("No, is not fire avoider"); }
    return;
  }

  bool  hit = false;
  point at  = curr_at;

  if (is_on_fire()) {
    dbg("Fire tick: on fire");
    TRACE_AND_INDENT();

    //
    // Give the player a chance
    //
    if (! level->is_smoke(at.x, at.y)) {
      hit = (d100() < 90);
      if (! hit) {
        if (is_player()) {
          msg("%%fg=green$You feel a brief cool breeze and reprieve from the "
              "flames!%%fg=reset$");

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
    if (hit) {
      dbg("Fire tick: very combustible and too close to the flames");
    }
  } else if (is_combustible() && (level->heatmap(at.x, at.y) > 2)) {
    //
    // Too close to the flames
    //
    hit = (d100() < 70);
    if (hit) {
      dbg("Fire tick: combustible and too close to the flames");
    }
  } else if (is_meltable() && (level->heatmap(at.x, at.y) > 0)) {
    //
    // Too close to the flames?
    //
    auto melt_chance = melting_chance_d1000();

    //
    // Make things more likely to melt the closer to the heat?
    //
    melt_chance += (melt_chance / 10) * level->heatmap(at.x, at.y);

    hit = d1000() < melt_chance;
    if (hit) {
      dbg("Fire tick: melting");
    }
  } else if (level->is_fire(at.x, at.y)) {
    //
    // Give the player a chance
    //
    if (! level->is_smoke(at.x, at.y)) {
      auto smoke = level->thing_new("smoke", at);
      smoke->set_lifespan(pcg_random_range(1, 10));

      hit = (d100() < 20);

      if (is_meltable() || is_burnable() || is_combustible() || is_very_combustible()) {
        hit = true;
      }

      if (hit) {
        if (is_player()) {
          msg("%%fg=red$The flames wrap around you!%%fg=reset$");
        }
      } else {
        if (is_player()) {
          msg("%%fg=red$You dodge the flames.%%fg=reset$");
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
      msg("%%fg=red$You take %u burn damage!%%fg=reset$", damage);
    }

    if (h <= 0) {
      h = set_health(0);
      if (is_meltable()) {
        if (! is_offscreen) {
          if (level->player && (level->tick_created < game->tick_current)) {
            if (get(level->player->get_aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
              msg("%s is melted!", text_The().c_str());
            }
          }
        }
        dead("by melting");
      } else {
        if (! is_offscreen) {
          if (level->player && (level->tick_created < game->tick_current)) {
            if (get(level->player->get_aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
              if (is_monst()) {
                msg("%s burns to death!", text_The().c_str());
              } else {
                msg("%s burns!", text_The().c_str());
              }
            }
          }
        }
        dead("by burning");
      }
    } else {
      if (is_meltable()) {
        if (! is_offscreen) {
          if (level->player && (level->tick_created < game->tick_current)) {
            if (get(level->player->get_aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
              msg("%s melts!", text_The().c_str());
            }
          }
        }
      } else {
        if (! is_offscreen) {
          if (level->player && (level->tick_created < game->tick_current)) {
            if (get(level->player->get_aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
              msg("%s burns!", text_The().c_str());
            }
          }
        }
      }
    }

    if (! level->is_smoke(at.x, at.y)) {
      auto smoke = level->thing_new("smoke", at);
      smoke->set_lifespan(pcg_random_range(1, 10));
    }
  }
}
