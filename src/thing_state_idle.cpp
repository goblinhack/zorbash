//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"
#include "my_wid_actionbar.hpp"

//
// Return true on having done something
//
bool Thing::state_idle(Thingp threat, int minx, int miny, int maxx, int maxy)
{
  TRACE_NO_INDENT();

  auto ai = aip();

  //
  // If on fire, try and put it out!
  //
  if (is_on_fire() && environ_avoids_fire()) {
    AI_LOG("I am on fire!");
    TRACE_AND_INDENT();
    if (is_intelligent()) {
      if (ai_on_fire()) {
        return true;
      }
    }
  }

  //
  // If somewhere bad, escape
  //
  if (terrain_cost_get(curr_at) >= DMAP_LESS_PREFERRED_TERRAIN) {
    AI_LOG("on bad terrain, escape");
    TRACE_AND_INDENT();
    if (ai_escape()) {
      return true;
    }

    ai->wander_dest = point(0, 0);
    AI_LOG("cannot escape, try to wander");
    TRACE_AND_INDENT();
    if (ai_wander()) {
      return true;
    }
  }

  if (threat) {
    if (is_dangerous(threat)) {
      AI_LOG("A dangerous threat is near", threat);
    } else if (is_enemy(threat)) {
      AI_LOG("An enemy threat is near", threat);
    } else if (is_to_be_avoided(threat)) {
      AI_LOG("An avoid threat is near", threat);
    } else {
      AI_LOG("A threat is near", threat);
    }
  }

  //
  // Look for doors or things to collect, if not being attacked.
  //
  if (threat && (is_dangerous(threat) || is_enemy(threat) || is_to_be_avoided(threat))) {
    //
    // If not too close to the thread we can try and do something else like pick up a weapon.
    //
    if (game->tick_current - tick_last_i_was_attacked() < 2) {
      //
      // Don't relax. You're being attacked.
      //
    } else if (distance(curr_at, threat->curr_at) > 2) {
      //
      // Look around for something nearby to do; like collect an item.
      //
      AI_LOG("Look around for some immediately adjacent goal as threat is not too close");
      if (ai_choose_immediately_adjacent_goal()) {
        return true;
      }
    }

    //
    // No resting when in danger unless in dire straits
    //
    // If we're absolutely exhausted, we must rest, threat or no threat
    //
    if (is_able_to_tire() && (stamina_get() < stamina_max() / 10)) {
      AI_LOG("Very low on stamina, forced to rest");
      if (is_player()) {
        game->tick_begin("Robot is forced to rest, very low on stamina");
      }
      change_state(MONST_STATE_RESTING, "need to rest, very low on stamina");
      return true;
    }

    //
    // If really low on health and we have something we can eat, try
    // that.
    //
    if (health() < health_max() / 10) {
      if (can_eat_something()) {
        AI_LOG("Very low on health, forced to rest");
        if (is_player()) {
          game->tick_begin("Robot needs to rest, very low on health");
        }
        change_state(MONST_STATE_RESTING, "need to rest, very low on health");
        return true;
      }
    }
  } else {
    //
    // Not under threat, so we can think about doing some other house cleaning tasks.
    //
    AI_LOG("Idle, look for something to do");

    //
    // If we're absolutely exhausted, we must rest, threat or no threat
    //
    AI_LOG("Idle, rest check");
    if (is_able_to_tire() && (stamina_get() < stamina_max() / 3)) {
      AI_LOG("Low on stamina, rest");
      if (is_player()) {
        game->tick_begin("Robot is low on stamina");
      }
      change_state(MONST_STATE_RESTING, "need to rest, low on stamina");
      return true;
    }

    //
    // If really low on health and we have something we can eat, try
    // that.
    //
    AI_LOG("Idle, health check");
    if (health() < health_max() / 3) {
      AI_LOG("Idle, eat check as a bit hungry");
      if (can_eat_something()) {
        AI_LOG("Low on health, rest");
        if (is_player()) {
          game->tick_begin("Robot is low on health");
        }
        change_state(MONST_STATE_RESTING, "need to rest, low on health");
        return true;
      }
    }

    if (try_to_enchant_items()) {
      return true;
    }
    if (try_to_use_weapon()) {
      return true;
    }
    if (try_to_use_armor()) {
      return true;
    }
    if (try_to_use_helmet()) {
      return true;
    }
    if (try_to_use_amulet()) {
      return true;
    }
    if (try_to_use_boots()) {
      return true;
    }
    if (try_to_use_gauntlet()) {
      return true;
    }
    if (try_to_use_shield()) {
      return true;
    }
    if (try_to_use_cloak()) {
      return true;
    }
    if (try_to_use_rings()) {
      return true;
    }

    //
    // Look around for something nearby to do; like collect an item.
    //
    AI_LOG("Look around for some immediately adjacent goal");
    if (ai_choose_immediately_adjacent_goal()) {
      return true;
    }
  }

  //
  // Look for goals. Each search type expands the scope of what we look at
  // until at the end, we end up looking for the exit.
  //
  AI_LOG("Idle, look for goals");
  int search_type_max;
  if (is_able_to_jump()) {
    if (is_explorer()) {
      if (is_exit_finder()) {
        search_type_max = MONST_SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED + 1;
      } else {
        search_type_max = MONST_SEARCH_TYPE_GLOBAL_JUMP_ALLOWED + 1;
      }
    } else {
      search_type_max = MONST_SEARCH_TYPE_LOCAL_JUMP_ALLOWED + 1;
    }
  } else {
    if (is_explorer()) {
      if (is_exit_finder()) {
        search_type_max = MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP + 1;
      } else {
        search_type_max = MONST_SEARCH_TYPE_GLOBAL_NO_JUMP + 1;
      }
    } else {
      search_type_max = MONST_SEARCH_TYPE_LOCAL_NO_JUMP + 1;
    }
  }

  for (int search_type = 0; search_type < search_type_max; search_type++) {
    if (ai_create_path_to_goal(minx, miny, maxx, maxy, search_type)) {
      if (ai->move_path.size()) {
        change_state(MONST_STATE_MOVING, "found a new goal");
      }
      return true;
    }
  }

  //
  // If going somewhere, continue
  //
  if (ai->wander_dest != point(0, 0)) {
    if (pcg_random_range(0, 100) < 50) {
      dbg("Try to continue wander");
      if (ai_wander()) {
        return true;
      }
    }
  }

  //
  // If nothing to do, might as well rest. If there is a point.
  //
  auto rest = true;
  if ((health() >= (health_max() / 4) * 3)) {
    if (is_able_to_tire()) {
      if (stamina_get() >= (stamina_max() / 4) * 3) {
        rest = false;
      }
    } else {
      rest = false;
    }
  }

  if (rest) {
    AI_LOG("Nothing to do. Rest.");
    if (is_player()) {
      game->tick_begin("nothing to do, rest");
    }
    change_state(MONST_STATE_RESTING, "nothing to do, rest");
    return true;
  }

  //
  // Compress the bag?
  //
  if (is_player()) {
    if (bag_compress()) {
      while (bag_compress()) {
      }
      AI_LOG("Repack inventory.");
      if (is_player()) {
        game->tick_begin("repacked bag");
        return true;
      }
    }
  }

  //
  // What is the point of it all?
  //
  AI_LOG("Nothing to do at all.");
  if (is_player()) {
    msg("Robot has ran out of things to do.");
    wid_actionbar_robot_mode_off();
  }

  return ai_wander();
}
