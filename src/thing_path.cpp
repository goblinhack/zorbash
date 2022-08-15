//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

//
// Return true on success.
//
bool Thing::path_pop_next_move(ThingMoveReason reason)
{
  bool too_far = false;

  auto ai = maybe_aip();
  if (! ai) {
    return false;
  }

  if (! ai->move_path.size()) {
    return false;
  }

  TRACE_NO_INDENT();
  std::string s = "";
  IF_DEBUG3
  {
    for (auto p : ai->move_path) {
      s += " " + p.to_string();
      (void) level->thing_new("ai_path1", point(p.x, p.y));
    }
  }
  auto to         = ai->move_path[ 0 ];
  auto future_pos = point(to.x, to.y);

  IF_DEBUG
  {
    std::string s = "";
    for (auto p : ai->move_path) {
      s += " " + p.to_string();
    }

    if (s.empty()) {
      dbg("Path pop next move %s, path empty", future_pos.to_string().c_str());
    } else {
      dbg("Path pop next move %s, path:%s", future_pos.to_string().c_str(), s.c_str());
    }
  }
  TRACE_AND_INDENT();

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
      if ((fabs(to.x - curr_at.x) > 1) || (fabs(to.x - curr_at.x) > 1)) {
        clear_move_path("Cursor next-hop is too far away");
        return false;
      }
    }
  }

  //
  // Remove the first element
  //
  ai->move_path.erase(ai->move_path.begin());

  //
  // Jump over obstacles if they appear in the path
  //
  if (is_able_to_jump()) {
    dbg("Is able to jump check");
    TRACE_AND_INDENT();

    if (is_monst() || (is_player() && game->robot_mode)) {
      dbg("Can try to jump");
      TRACE_AND_INDENT();

      if (is_disliked_by_me(future_pos) || level->is_icecube(future_pos) || level->is_barrel(future_pos) ||
          level->is_brazier(future_pos)) {
        IF_DEBUG2
        {
          auto s = string_sprintf("Next position %d,%d is a hazard (move path size %d)", (int) future_pos.x,
                                  (int) future_pos.y, (int) ai->move_path.size());
          AI_LOG(s);
        }
        TRACE_AND_INDENT();

        if (ai->move_path.size()) {
          auto jump_pos = ai->move_path[ 0 ];
          ai->move_path.erase(ai->move_path.begin());

          IF_DEBUG2
          {
            if (is_disliked_by_me(jump_pos)) {
              auto s = string_sprintf("Next jump pos %d,%d (is disliked)", (int) jump_pos.x, (int) jump_pos.y);
              AI_LOG(s);
            } else {
              auto s = string_sprintf("Next jump pos %d,%d", (int) jump_pos.x, (int) jump_pos.y);
              AI_LOG(s);
            }
          }

          //
          // If the thing we are going to land on is also a hazard, can we jump further?
          //
          TRACE_AND_INDENT();
          if (is_disliked_by_me(jump_pos) && ai->move_path.size()) {
            IF_DEBUG2
            {
              auto s =
                  string_sprintf("Next-next position %d,%d is also a hazard", (int) jump_pos.x, (int) jump_pos.y);
              AI_LOG(s);
            }

            auto jump_pos = ai->move_path[ 0 ];
            ai->move_path.erase(ai->move_path.begin());

            if (is_disliked_by_me(jump_pos)) {
              //
              // Give up. Don't bump the tick. This allows the monst to try an alternative path.
              //
              AI_LOG("Failed to jump cannot jump over hazards");
              clear_move_path("Failed to jump cannot jump over all hazards");
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
          } else if (is_disliked_by_me(jump_pos)) {
            IF_DEBUG2
            {
              auto s =
                  string_sprintf("Final jump position %d,%d is also a hazard", (int) jump_pos.x, (int) jump_pos.y);
              AI_LOG(s);
            }

            //
            // Give up. Don't bump the tick. This allows the monst to try an alternative path.
            //
            AI_LOG("Failed to jump cannot jump over hazards");
            clear_move_path("Failed to jump cannot jump over all hazards");
            return false;
          } else if (try_to_jump_carefully(jump_pos, &too_far)) {
            AI_LOG("Jumped carefully");
            if (is_player()) {
              game->tick_begin("Jumped carefully");
            }
            clear_move_path("Jumped carefully");
            return true;
          } else {
            AI_LOG("Failed to jump carefully; try entire path");

            //
            // Try the entire path. This allows us to jump next to a thing that
            // might have moved into our move path (and where we were trying to land.)
            //
            for (auto pit = ai->move_path.rbegin(); pit != ai->move_path.rend(); pit++) {
              jump_pos = *pit;
              if (distance(curr_at, jump_pos) < 2) {
                break;
              }
              if (try_to_jump_carefully(jump_pos, &too_far)) {
                IF_DEBUG2
                {
                  auto s = string_sprintf("Jumped carefully; try entire path %d,%d", jump_pos.x, jump_pos.y);
                  AI_LOG(s);
                }
                if (is_player()) {
                  game->tick_begin("Jumped carefully");
                }
                clear_move_path("Jumped carefully");
                return true;
              }
            }

            clear_move_path("Failed to jump carefully");

            if (too_far) {
              if (any_unfriendly_monst_visible()) {
                change_state(MONST_STATE_IDLE, "too far, need to rest but threat nearby, failed to jump");
              } else {
                change_state(MONST_STATE_RESTING, "too far, need to rest, failed to jump");
              }
            } else {
              if (any_unfriendly_monst_visible()) {
                change_state(MONST_STATE_IDLE, "need to rest but threat nearby, failed to jump");
              } else {
                change_state(MONST_STATE_RESTING, "need to rest, failed to jump");
              }
            }

            if (is_player() && game->robot_mode) {
              AI_LOG("Failed to jump carefully; try wandering instead");
              return ai_wander();
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
  }

  if (is_able_to_shove() && (is_monst() || (is_player() && game->robot_mode))) {
    //
    // Someone in our way?
    //
    if (level->is_shovable(future_pos) && d1000() < tp()->ai_shove_chance_d1000()) {
      //
      // Can the monst shove it into a something bad?
      //
      AI_LOG("Something is in our way that can be shoved");
      auto delta = future_pos - curr_at;
      FOR_ALL_THINGS(level, t, future_pos.x, future_pos.y)
      {
        if (t->is_hidden) {
          continue;
        }

        if (! t->is_shovable()) {
          continue;
        }
        switch (try_to_shove_into_hazard(t, delta)) {
          case THING_SHOVE_TRIED_AND_FAILED:
            {
              IF_DEBUG2
              {
                auto s = string_sprintf("Tried to shove monst into hazard at %s but failed",
                                        future_pos.to_string().c_str());
                AI_LOG(s);
              }
              if (is_player()) {
                game->tick_begin("Tried to shove but failed");
              }
              clear_move_path("Tried to shove but failed");
              return false;
            }
          case THING_SHOVE_TRIED_AND_PASSED:
            {
              IF_DEBUG2
              {
                auto s = string_sprintf("Shoved monst at %s", future_pos.to_string().c_str());
                AI_LOG(s);
              }
              if (is_player()) {
                game->tick_begin("Tried to shove");
              }
              clear_move_path("Tried to shove");
              return true;
            }
          case THING_SHOVE_NEVER_TRIED: break;
        }
      }
      FOR_ALL_THINGS_END()

      IF_DEBUG2
      {
        auto s = string_sprintf("Try to attack monst at %s", future_pos.to_string().c_str());
        AI_LOG(s);
      }

      AI_LOG("Move, no shove allowed, no attack allowed");
      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }

      //
      // Did we try or attempt to try to do something?
      //
      if (is_player()) {
        if (! game->tick_requested.empty()) {
          return true;
        }
      }
    }

    //
    // Make sure and check for hazard after the monst, as the monst could be floating over lava or a chasm
    //
    if (is_disliked_by_me(future_pos)) {
      IF_DEBUG2
      {
        auto s = string_sprintf("Cannot pass hazard at %s", future_pos.to_string().c_str());
        AI_LOG(s);
      }

      //
      // Could be a monster sitting in lava, attack it?
      //
      if (level->is_monst(future_pos)) {
        AI_LOG("Hazard, but a monst is on it. Try to attack it.");
        if (move_no_shove_attack_allowed(future_pos)) {
          return true;
        }
      }

      IF_DEBUG2
      {
        auto s = string_sprintf("Cannot pass hazard at %s, failed to move", future_pos.to_string().c_str());
        AI_LOG(s);
      }

      clear_move_path("Could not move");
      return false;
    }

    IF_DEBUG2
    {
      auto s =
          string_sprintf("Try to move (shoving not allowed, attack allowed) to %s", future_pos.to_string().c_str());
      AI_LOG(s);
    }

    AI_LOG("Move, no shove allowed, attack allowed");
    if (move_no_shove_attack_allowed(future_pos)) {
      return true;
    }

    //
    // Did we try or attempt to try to do something?
    //
    if (! game->tick_requested.empty()) {
      return true;
    }

    IF_DEBUG2
    {
      auto s = string_sprintf("Try to move (shoving and attacking allowed) to %s", future_pos.to_string().c_str());
      AI_LOG(s);
    }

    AI_LOG("Move, shove allowed, attack allowed");
    if (move(future_pos)) {
      return true;
    }

    //
    // Did we try or attempt to try to do something?
    //
    if (is_player()) {
      if (! game->tick_requested.empty()) {
        return true;
      }
    }
  }

  //
  // If moving along a path and we bump into a monster, just stop. Don't auto attack as that might lead to bad things.
  //
  // However, if at the start of the path and trying to click through a monster, allow that.
  //
  // e.g.
  //     end       start
  //      |          |
  //      v          v
  //      ......m@....   (no attack)
  //
  //     end       start
  //      |          |
  //      v          v
  //      e.........m@   (attack)
  //
  if (is_player() && aip()->move_path.size()) {
    if (reason == THING_MOVE_REASON_MOUSE) {
      AI_LOG("Try to move, no shove, attack allowed as mouse clicked");
      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }
    } else {
      AI_LOG("Try to move, no shove, no attack as have move path");
      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }
    }
  } else {
    if (possible_to_attack_at(future_pos)) {
      AI_LOG("Try to move and attack");
      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }
    } else {
      AI_LOG("Try to move, no shove, no attack");
      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }

      if (possible_to_attack_at(future_pos)) {
        AI_LOG("Try to move, no shove, attack allowed");
        if (move_no_shove_attack_allowed(future_pos)) {
          return true;
        }
      }
    }
  }

  //
  // Need this else monsts will keep on trying to continue along a long path
  // and end up lunging crazy distances.
  //
  clear_move_path("Could not move");
  return false;
}

//
// true on having performed an action
//
bool Thing::cursor_path_pop_first_move(ThingMoveReason reason)
{
  dbg("Cursor pop first move");
  TRACE_AND_INDENT();

  auto cursor = level->cursor;
  if (! cursor) {
    dbg("Cursor pop first move: no cursor, recreate");
    TRACE_AND_INDENT();

    level->cursor_recreate();
    cursor = level->cursor;
    if (! cursor) {
      dbg("Cursor pop first move: no cursor");
      return false;
    }
  }

  if (game->cursor_move_path.size()) {
    dbg("Cursor path exists");

    //
    // A path to the target exists.
    //
    new_aip();
    aip()->move_path = game->cursor_move_path;
    game->cursor_move_path.clear();

    if (path_pop_next_move(reason)) {
      dbg("Move to cursor next hop");
      if (game->cursor_move_path.empty()) {
        level->cursor_path_create(this);
      }
      return true;
    }

    //
    // We get here if for example we click on a monster but are unable to move into its cell because it blocks
    // Or we click on a locked door and cannot pass through.
    //
    dbg("Failed to move to cursor next hop");
    level->cursor_path_create(this);
    return false;
  }

  //
  // A path to the target does not exist. Jump?
  //
  point future_pos = make_point(cursor->curr_at.x, cursor->curr_at.y);

  //
  // If adjacent, try to move there. There may be no path because perhaps a monster just moved but now we can
  // step there.
  //
  if ((fabs(future_pos.x - curr_at.x) <= 1) && (fabs(future_pos.y - curr_at.y) <= 1)) {
    dbg("Target is adjacent, attack or move to %d,%d", cursor->curr_at.x, cursor->curr_at.y);

    //
    // If we are able to walk through walls, then don't attack the wall, move into it.
    //
    if (is_able_to_walk_through_walls()) {
      if (level->is_obs_wall_or_door(future_pos.x, future_pos.y)) {
        move(cursor->curr_at);
        level->cursor_path_create(this);
        return true;
      }
    }

    if (possible_to_attack_at(future_pos)) {
      attack(cursor->curr_at);
      level->cursor_path_create(this);
      return true;
    }
  }

  //
  // If not adjacent, try and jump.
  //
  if (get(level->can_see_ever.can_see, future_pos.x, future_pos.y)) {
    dbg("Cursor path does not exist; jump?");
    if (is_able_to_jump() && (is_monst() || (is_player() && game->robot_mode))) {
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
  } else {
    if (is_player()) {
      msg("You cannot see to move there.");
    }
  }

  //
  // Jump failed. Maybe too tired?
  //
  // game->tick_begin("not sure about this one");
  return false;
}

/*
 * Make L shaped moves into diagonal ones
 */
void Thing::path_shorten(std::vector< point > &path)
{
  if (path.size() == 2) {
    auto px = curr_at.x;
    auto py = curr_at.y;

    auto n  = path[ 0 ];
    auto nx = n.x;
    auto ny = n.y;

    auto m  = path[ 1 ];
    auto mx = m.x;
    auto my = m.y;

    if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level->is_obs_wall_or_door(px - 1, py)) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py + 1)) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level->is_obs_wall_or_door(px + 1, py)) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py + 1)) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level->is_obs_wall_or_door(px - 1, py)) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py - 1)) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level->is_obs_wall_or_door(px + 1, py)) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py - 1)) {
      path.erase(path.begin());
      return;
    }
  }

  if (path.size()) {
    if (path[ 0 ] == curr_at) {
      path.erase(path.begin());
    }
  }

  for (; /*ever*/;) {
    auto   modified = false;
    size_t i        = 0;

    for (; /*ever*/;) {
      if (i + 2 >= path.size()) {
        break;
      }

      auto p  = path[ i ];
      auto px = p.x;
      auto py = p.y;

      auto n  = path[ i + 1 ];
      auto nx = n.x;
      auto ny = n.y;

      auto m  = path[ i + 2 ];
      auto mx = m.x;
      auto my = m.y;

      if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level->is_obs_wall_or_door(px - 1, py)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py + 1)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level->is_obs_wall_or_door(px + 1, py)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py + 1)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level->is_obs_wall_or_door(px - 1, py)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py - 1)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level->is_obs_wall_or_door(px + 1, py)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && ! level->is_obs_wall_or_door(px, py - 1)) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      i++;
    }

    if (! modified) {
      break;
    }
  }
}
