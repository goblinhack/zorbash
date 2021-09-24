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
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid.h"
#include "my_wid_console.h"

bool Thing::cursor_path_pop_next_and_move(void)
{
  TRACE_AND_INDENT();
  if (monstp && monstp->move_path.size()) {
    IF_DEBUG3
    {
      std::string s = "";
      for (auto p : monstp->move_path) {
        s += p.to_string() + " ";
      }
      log("Move path: %s", s.c_str());
    }

    auto to         = monstp->move_path[ 0 ];
    auto future_pos = point(to.x, to.y);

    FOR_ALL_CURSOR_PATH_THINGS(level, t, to.x, to.y) { t->dead("by end of life"); }
    FOR_ALL_THINGS_END()

    //
    // Just in case the cursor next hop ends up too far away
    // for a single move, then reset it.
    //
    if (! game->robot_mode) {
      if ((fabs(to.x - mid_at.x) > 1) || (fabs(to.x - mid_at.x) > 1)) {
        clear_move_path("Cursor next-hop is too far away");
        return false;
      }
    }

    monstp->move_path.erase(monstp->move_path.begin());

    //
    // If in robot mode, or player mode? jump over obstacles if they
    // appear in the path
    //
    if (is_player() && game->robot_mode) {
      if (will_avoid_hazard(future_pos) || level->is_barrel(future_pos)) {
        CON("Robot: Next position %d,%d is a hazard", (int) future_pos.x, (int) future_pos.y);
        TRACE_AND_INDENT();
        if (monstp->move_path.size()) {
          auto jump_pos = monstp->move_path[ 0 ];
          monstp->move_path.erase(monstp->move_path.begin());

          //
          // If the thing we are going to land on is also a hazard,
          // can we jump further?
          //
          CON("Robot: Next-next position %d,%d is also a hazard", (int) jump_pos.x, (int) jump_pos.y);
          TRACE_AND_INDENT();
          if (will_avoid_hazard(jump_pos) && monstp->move_path.size()) {
            auto jump_pos = monstp->move_path[ 0 ];
            monstp->move_path.erase(monstp->move_path.begin());

            if (will_avoid_hazard(jump_pos)) {
              //
              // Give up
              //
              // Don't bump the tick. This allows the robot to try an
              // alternative path.
              //
              CON("Robot: Cannot jump over hazards");
              clear_move_path("Cannot jump over all hazards");
              return false;
            } else if (try_to_jump_carefully(jump_pos)) {
              CON("Robot: Try a long jump");
              game->tick_begin("robot tried a long jump");
              clear_move_path("robot tried a long jump");
              return true;
            } else {
              //
              // Don't bump the tick. This allows the robot to try an
              // alternative path.
              //
              CON("Robot: Failed to try a long jump");
              clear_move_path("robot tried a jump but cannot pass");
              return false;
            }
          } else if (try_to_jump_carefully(jump_pos)) {
            CON("Robot: Jumped carefully");
            game->tick_begin("robot Jumped carefully");
            clear_move_path("robot Jumped carefully");
            return true;
          } else {
            //
            // Don't bump the tick. This allows the robot to try an
            // alternative path.
            //
            CON("Robot: Failed to jump");
            clear_move_path("robot cannot pass");
            return false;
          }
        } else {
          //
          // Fall through to allow attack
          //
        }
      }

      //
      // Someone in our way?
      //
      if (level->is_shovable(future_pos)) {
        //
        // Can the robot shove it into a something bad?
        //
        auto delta = mid_at - make_fpoint(future_pos);
        FOR_ALL_THINGS(level, t, future_pos.x, future_pos.y)
        {
          if (! t->is_shovable()) {
            continue;
          }
          switch (try_to_shove_into_hazard(t, delta)) {
            case THING_SHOVE_TRIED_AND_FAILED :
              CON("Robot: Try to shove monst at %s but failed", future_pos.to_string().c_str());
              game->tick_begin("robot tried to shove but failed");
              clear_move_path("robot tried to shove but failed");
              return false;
            case THING_SHOVE_TRIED_AND_PASSED :
              CON("Robot: Shoved monst at %s", future_pos.to_string().c_str());
              game->tick_begin("robot tried to shove");
              clear_move_path("robot tried to shove");
              return true;
            case THING_SHOVE_NEVER_TRIED : break;
          }
        }
        FOR_ALL_THINGS_END()

        CON("Robot: Try to attack monst at %s", future_pos.to_string().c_str());
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
      if (will_avoid_hazard(future_pos)) {
        CON("Robot: Cannot pass hazard at %s", future_pos.to_string().c_str());
        return false;
      }

      CON("Robot: Try to move (shoving not allowed, attack allowed) to %s", future_pos.to_string().c_str());
      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }

      //
      // Did we try or attempt to try to do something?
      //
      if (! game->tick_requested.empty()) {
        return true;
      }

      CON("Robot: Try to move (shoving and attacking allowed) to %s", future_pos.to_string().c_str());
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

    if (move_no_shove_no_attack(future_pos)) {
      return true;
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
    new_monst();
    monstp->move_path = game->cursor_move_path;
    game->cursor_move_path.clear();

    if (cursor_path_pop_next_and_move()) {
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
  if (game->robot_mode) {
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
