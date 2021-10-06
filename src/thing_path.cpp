//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_ascii.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sdl.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid.h"
#include "my_wid_console.h"

bool Thing::path_pop_next_move(void)
{
  bool too_far = false;

  if (! monst_aip) {
    return false;
  }

  if (! monst_aip->move_path.size()) {
    return false;
  }

  TRACE_AND_INDENT();
  std::string s = "";
  IF_DEBUG3
  {
    for (auto p : monst_aip->move_path) {
      s += p.to_string() + " ";
      (void) level->thing_new("ai_path1", fpoint(p.x, p.y));
    }
  }
  auto to         = monst_aip->move_path[ 0 ];
  auto future_pos = point(to.x, to.y);
  dbg("Path pop next move %s, path: %s", future_pos.to_string().c_str(), s.c_str());

  //
  // Clean up the old cursor path
  //
  if (is_player()) {
    FOR_ALL_CURSOR_PATH_THINGS(level, t, to.x, to.y) { t->dead("by end of life"); }
    FOR_ALL_THINGS_END()

    //
    // Just in case the cursor next hop ends up too far away for a single move, then reset it.
    //
    if (! game->robot_mode) {
      if ((fabs(to.x - mid_at.x) > 1) || (fabs(to.x - mid_at.x) > 1)) {
        clear_move_path("Cursor next-hop is too far away");
        return false;
      }
    }
  }

  //
  // Remove the first element
  //
  monst_aip->move_path.erase(monst_aip->move_path.begin());

  //
  // Jump over obstacles if they appear in the path
  //
  if (ai_is_able_to_jump() && (is_monst() || (is_player() && game->robot_mode))) {
    if (is_hated_by_me(future_pos) || level->is_barrel(future_pos)) {
      IF_DEBUG3
      {
        auto s = string_sprintf("Next position %d,%d is a hazard", (int) future_pos.x, (int) future_pos.y);
        AI_LOG("", s);
      }

      TRACE_AND_INDENT();
      if (monst_aip->move_path.size()) {
        auto jump_pos = monst_aip->move_path[ 0 ];
        monst_aip->move_path.erase(monst_aip->move_path.begin());

        //
        // If the thing we are going to land on is also a hazard, can we jump further?
        //
        IF_DEBUG3
        {
          auto s = string_sprintf("Next-next position %d,%d is also a hazard", (int) jump_pos.x, (int) jump_pos.y);
          AI_LOG("", s);
        }

        TRACE_AND_INDENT();
        if (is_hated_by_me(jump_pos) && monst_aip->move_path.size()) {
          auto jump_pos = monst_aip->move_path[ 0 ];
          monst_aip->move_path.erase(monst_aip->move_path.begin());

          if (is_hated_by_me(jump_pos)) {
            //
            // Give up. Don't bump the tick. This allows the monst to try an alternative path.
            //
            AI_LOG("Cannot jump over hazards");
            clear_move_path("Cannot jump over all hazards");
            return false;
          } else if (try_to_jump_carefully(jump_pos)) {
            AI_LOG("Long jump");
            if (is_player()) {
              game->tick_begin("Tried a long jump");
            }
            clear_move_path("long jump");
            return true;
          } else {
            //
            // Don't bump the tick. This allows the monst to try an alternative path.
            //
            AI_LOG("Failed to try a long jump");
            clear_move_path("Failed to try a long jump");
            return false;
          }
        } else if (try_to_jump_carefully(jump_pos, &too_far)) {
          AI_LOG("Jumped carefully");
          if (is_player()) {
            game->tick_begin("Jumped carefully");
          }
          clear_move_path("Jumped carefully");
          return true;
        } else {
          //
          // Don't bump the tick. This allows the monst to try an alternative path.
          //
          AI_LOG("Failed to jump");
          clear_move_path("Failed to jump");
          if (is_player() && game->robot_mode) {
            if (too_far) {
              ai_change_state(MONST_STATE_RESTING, "need to rest, failed to jump");
              game->tick_begin("Failed to jump");
              return false;
            }
          }
          return false;
        }
      } else {
        //
        // Fall through to allow attack
        //
      }
    }
  }

  if (ai_is_able_to_shove() && (is_monst() || (is_player() && game->robot_mode))) {
    //
    // Someone in our way?
    //
    if (level->is_shovable(future_pos) && (int) pcg_random_range(0, 1000) < tp()->ai_shove_chance_d1000()) {
      //
      // Can the monst shove it into a something bad?
      //
      AI_LOG("", "Something is in our way that can be shoved");
      auto delta = make_fpoint(future_pos) - mid_at;
      FOR_ALL_THINGS(level, t, future_pos.x, future_pos.y)
      {
        if (! t->is_shovable()) {
          continue;
        }
        switch (try_to_shove_into_hazard(t, delta)) {
          case THING_SHOVE_TRIED_AND_FAILED :
            {
              IF_DEBUG3
              {
                auto s =
                    string_sprintf("Tried to shove monst into hazard at %s but failed", future_pos.to_string().c_str());
                AI_LOG("", s);
              }
              if (is_player()) {
                game->tick_begin("Tried to shove but failed");
              }
              clear_move_path("Tried to shove but failed");
              return false;
            }
          case THING_SHOVE_TRIED_AND_PASSED :
            {
              IF_DEBUG3
              {
                auto s = string_sprintf("Shoved monst at %s", future_pos.to_string().c_str());
                AI_LOG("", s);
              }
              if (is_player()) {
                game->tick_begin("Tried to shove");
              }
              clear_move_path("Tried to shove");
              return true;
            }
          case THING_SHOVE_NEVER_TRIED : break;
        }
      }
      FOR_ALL_THINGS_END()

      IF_DEBUG3
      {
        auto s = string_sprintf("Try to attack monst at %s", future_pos.to_string().c_str());
        AI_LOG("", s);
      }

      AI_LOG("", "Move, no shove allowed, no attack allowed");
      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }

      //
      // Did we try or attempt to try to do something?
      //
      if (! game->tick_requested.empty()) {
        return true;
      }
    }

    //
    // Make sure and check for hazard after the monst, as the monst
    // could be floating over lava or a chasm
    //
    if (is_hated_by_me(future_pos)) {
      IF_DEBUG3
      {
        auto s = string_sprintf("Cannot pass hazard at %s", future_pos.to_string().c_str());
        AI_LOG("", s);
      }
      return false;
    }

    IF_DEBUG3
    {
      auto s =
          string_sprintf("Try to move (shoving not allowed, attack allowed) to %s", future_pos.to_string().c_str());
      AI_LOG("", s);
    }

    AI_LOG("", "Move, no shove allowed, attack allowed");
    if (move_no_shove_attack_allowed(future_pos)) {
      return true;
    }

    //
    // Did we try or attempt to try to do something?
    //
    if (! game->tick_requested.empty()) {
      return true;
    }

    IF_DEBUG3
    {
      auto s = string_sprintf("Try to move (shoving and attacking allowed) to %s", future_pos.to_string().c_str());
      AI_LOG("", s);
    }

    AI_LOG("", "Move, shove allowed, attack allowed");
    if (move(future_pos)) {
      return true;
    }

    //
    // Did we try or attempt to try to do something?
    //
    if (! game->tick_requested.empty()) {
      return true;
    }
  }

  if (possible_to_attack_at(future_pos)) {
    AI_LOG("", "Try to move and attack");
    if (move_no_shove_attack_allowed(future_pos)) {
      return true;
    }
  } else {
    AI_LOG("", "Try to move, no shove, no attack");
    if (move_no_shove_no_attack(future_pos)) {
      return true;
    }

    if (possible_to_attack_at(future_pos)) {
      AI_LOG("", "Try to move, no shove, attack allowed");
      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }
    }
  }

  return false;
}

//
// true on having performed an action
//
bool Thing::cursor_path_pop_first_move(void)
{
  TRACE_AND_INDENT();
  auto cursor = level->cursor;

  if (game->cursor_move_path.size()) {
    dbg("Cursor path exists");

    //
    // A path to the target exists.
    //
    new_monst_ai();
    monst_aip->move_path = game->cursor_move_path;
    game->cursor_move_path.clear();

    if (path_pop_next_move()) {
      dbg("Move to cursor next hop");
      if (game->cursor_move_path.empty()) {
        level->cursor_path_create();
      }
      return true;
    }

    //
    // We get here if for example we click on a monster but
    // are unable to move into its cell because it blocks
    //
    // Or we click on a locked door and cannot pass through.
    //
    dbg("Failed to move to cursor next hop");
    level->cursor_path_create();
    return false;
  }

  //
  // A path to the target does not exist. Jump?
  //
  point future_pos = make_point(cursor->mid_at.x, cursor->mid_at.y);

  //
  // If adjacent, try to move there. There may be no path
  // because perhaps a monster just moved but now we can
  // step there.
  //
  if ((fabs(future_pos.x - mid_at.x) <= 1) && (fabs(future_pos.y - mid_at.y) <= 1)) {
    dbg("Target is adjacent, attack or move to %f,%F", cursor->mid_at.x, cursor->mid_at.y);
    attack(cursor->mid_at);
    level->cursor_path_create();
    return true;
  }

  //
  // If not adjacent, try and jump.
  //
  if (ai_is_able_to_jump() && (is_monst() || (is_player() && game->robot_mode))) {
    if (try_to_jump_carefully(future_pos)) {
      game->tick_begin("player tried to jump");
      return true;
    }
  } else {
    if (try_to_jump_carefree(future_pos)) {
      game->tick_begin("player tried to jump");
      return true;
    }
  }

  //
  // Jump failed. Maybe too tired?
  //
  // game->tick_begin("not sure about this one");
  return false;
}
