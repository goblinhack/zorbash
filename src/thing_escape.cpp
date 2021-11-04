//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::try_to_escape(void)
{
  if (ai_is_able_to_jump()) {
    auto health_max = get_health_max();
    auto health     = get_health();

    if (health > health_max / 2) {
      return false;
    }

    //
    // Don't try and escape too often else the player can never kill the monst!
    //
    if (game->tick_current - get_tick_last_escape() < 20) {
      return false;
    }

    if ((int) pcg_random_range(0, 1000) < tp()->ai_is_able_to_jump_on_low_hp_chance_d1000()) {
      if (try_to_jump_away_from_player()) {
        set_tick_last_escape(game->tick_current);
        return true;
      }
    }
  }

  return false;
}

bool Thing::ai_escape(void)
{
  TRACE_AND_INDENT();
  if (ai_blocked_completely()) {
    dbg("AI escape blocked");
    return false;
  }

  dbg("AI escape");
  auto tries = THING_AI_ESCAPE_ATTEMPTS;
  while (tries--) {
    point nh;
    if (ai_choose_wander(nh)) {
      if (move_to_or_attack(nh)) {
        return true;
      }

      //
      // Set this so next time we will choose another target
      //
      get_aip()->wander_target = point(-1, -1);
    }
  }
  TRACE_AND_INDENT();
  dbg("No escape goal");
  return false;
}
