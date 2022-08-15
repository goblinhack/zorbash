//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

bool Thing::try_to_escape(void)
{
  if (is_able_to_jump()) {
    auto health_max_val = health_max();
    auto health_val     = health();

    if (health_val > health_max_val / 2) {
      return false;
    }

    //
    // Don't try and escape too often else the player can never kill the monst!
    //
    if (game->tick_current - tick_last_escape() < 20) {
      return false;
    }

    if (d1000() < tp()->is_able_to_jump_on_low_hp_chance_d1000()) {
      if (try_to_jump_away_from_player()) {
        tick_last_escape_set(game->tick_current);
        return true;
      }
    }
  }

  return false;
}

bool Thing::ai_escape(void)
{
  dbg("AI escape");
  TRACE_AND_INDENT();

  if (! is_moveable()) {
    dbg("No cannot move");
    return false;
  }

  //
  // Need to clear any existing path, so we don't come back to that later and jump around the screen
  //
  clear_move_path("AI escape");

  if (is_able_to_teleport_escape()) {
    if (teleport_randomly()) {
      dbg("AI escape teleport");
      return false;
    }
  }

  if (is_able_to_jump_escape()) {
    if (try_to_jump()) {
      dbg("AI escape jump");
      return false;
    }
  }

  if (ai_blocked_completely()) {
    if (is_able_to_jump()) {
      if (try_to_jump()) {
        dbg("AI escape last resort");
        return false;
      }
      dbg("AI escape blocked");
      return false;
    }
  }

  auto tries = THING_AI_ESCAPE_ATTEMPTS;
  if (game->tick_current_is_too_slow || game->prev_tick_was_too_slow) {
    tries = 1;
  }
  while (tries-- > 0) {
    point nh;
    if (ai_choose_wander(nh)) {
      if (move_to_or_attack(nh)) {
        return true;
      }

      //
      // Set this so next time we will choose another target
      //
      aip()->wander_dest = point(0, 0);
    }
  }

  dbg("No escape goal");
  return false;
}
