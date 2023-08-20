//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

//
// Return true on success.
//
bool Thing::player_or_monst_path_pop_next_move(ThingMoveReason reason)
{
  TRACE_NO_INDENT();

  bool too_far = false;

  auto ai = maybe_aip();
  if (! ai) {
    return false;
  }

  if (! ai->move_path.size()) {
    return false;
  }

  dbg("Pop next move (move speed %d)", move_speed_total());
  TRACE_AND_INDENT();

  //
  // If a monster has been slowed so it can no longer move, stop it
  //
  if (move_speed_total() <= 0) {
    clear_move_path("unable to move; slowed");
    return false;
  }

  //
  // If a monster is stuck, prevent it from moving
  //
  if (is_stuck_currently()) {
    clear_move_path("unable to move; stuck");
    return false;
  }

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

  IF_DEBUG2
  {
    if (is_debug_type()) {
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
  }

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
  if (is_able_to_jump() && (is_monst() || (is_player() && game->robot_mode))) {
    DBG2("Can try to jump");
    TRACE_AND_INDENT();

    //
    // Inject some randomness so we don't repeat cycles of jumping over something and failing.
    //
    if (d100() < 50) {
      //
      // Jump over hazards
      //
      if (is_disliked_by_me(future_pos) || level->is_block_of_ice(future_pos) || level->is_barrel(future_pos)
          || level->is_brazier(future_pos)) {
        DBG2("Next position %s is a hazard (move path size %d)", future_pos.to_string().c_str(),
             (int) ai->move_path.size());
        TRACE_AND_INDENT();

        if (ai->move_path.size()) {
          auto jump_pos = ai->move_path[ 0 ];
          ai->move_path.erase(ai->move_path.begin());

          IF_DEBUG2
          {
            if (is_disliked_by_me(jump_pos)) {
              DBG2("Next jump pos %s (is disliked)", jump_pos.to_string().c_str());
            } else {
              DBG2("Next jump pos %s", jump_pos.to_string().c_str());
            }
          }

          //
          // If the thing we are going to land on is also a hazard, can we jump further?
          //
          TRACE_NO_INDENT();

          if (is_disliked_by_me(jump_pos) && ai->move_path.size()) {
            DBG2("Next-next position %s is also a hazard", jump_pos.to_string().c_str());

            auto jump_pos = ai->move_path[ 0 ];
            ai->move_path.erase(ai->move_path.begin());

            if (is_disliked_by_me(jump_pos)) {
              //
              // Give up. Don't bump the tick. This allows the monst to try an alternative path.
              //
              DBG2("Failed to jump cannot jump over hazards");
              clear_move_path("Failed to jump cannot jump over all hazards");
              return false;
            } else if (try_to_jump_carefully(jump_pos)) {
              DBG2("Long jump");
              if (is_player()) {
                game->tick_begin("Tried a long jump");
              }
              clear_move_path("long jump");
              return true;
            } else {
              //
              // Don't bump the tick. This allows the monst to try an alternative path.
              //
              DBG2("Failed to try a long jump");
              clear_move_path("Failed to try a long jump");
              return false;
            }
          } else if (is_disliked_by_me(jump_pos)) {
            DBG2("Final jump position %d,%d is also a hazard", (int) jump_pos.x, (int) jump_pos.y);

            //
            // Give up. Don't bump the tick. This allows the monst to try an alternative path.
            //
            DBG2("Failed to jump cannot jump over hazards");
            clear_move_path("Failed to jump cannot jump over all hazards");
            return false;
          } else if (try_to_jump_carefully(jump_pos, &too_far)) {
            DBG2("Jumped carefully");
            if (is_player()) {
              game->tick_begin("Jumped carefully");
            }
            clear_move_path("Jumped carefully");
            return true;
          } else {
            DBG2("Failed to jump carefully; try entire path");

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
                DBG2("Jumped carefully; try entire path %d,%d", jump_pos.x, jump_pos.y);
                if (is_player()) {
                  game->tick_begin("Jumped carefully");
                }
                clear_move_path("Jumped carefully");
                return true;
              }
            }

            //
            // If diagonal jumps are failing, try straight line jumps.
            //
            for (auto pit = ai->move_path.rbegin(); pit != ai->move_path.rend(); pit++) {
              jump_pos   = *pit;
              jump_pos.y = curr_at.y;
              if (distance(curr_at, jump_pos) < 2) {
                break;
              }
              if (try_to_jump_carefully(jump_pos, &too_far)) {
                DBG2("Jumped carefully; try entire path %d,%d (horiz)", jump_pos.x, jump_pos.y);
                if (is_player()) {
                  game->tick_begin("Jumped carefully");
                }
                clear_move_path("Jumped carefully");
                return true;
              }
            }

            //
            // Try straight line vertical jump.
            //
            for (auto pit = ai->move_path.rbegin(); pit != ai->move_path.rend(); pit++) {
              jump_pos   = *pit;
              jump_pos.x = curr_at.x;
              if (distance(curr_at, jump_pos) < 2) {
                break;
              }
              if (try_to_jump_carefully(jump_pos, &too_far)) {
                DBG2("Jumped carefully; try entire path %d,%d (vert)", jump_pos.x, jump_pos.y);
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

            DBG2("Failed to jump carefully; try wandering instead");
            return ai_wander();
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
    if (level->is_shovable(future_pos) && d1000() < tp()->chance_d1000_shove()) {
      //
      // Can the monst shove it into a something bad?
      //
      DBG2("Something is in our way that can be shoved");
      auto delta = future_pos - curr_at;

      FOR_ALL_NON_INTERNAL_THINGS(level, t, future_pos.x, future_pos.y)
      {
        if (! t->is_shovable()) {
          continue;
        }

        switch (try_to_shove_into_hazard(t, delta)) {
          case THING_SHOVE_TRIED_AND_FAILED :
            {
              DBG2("Tried to shove monst into hazard at %s but failed", future_pos.to_string().c_str());
              if (is_player()) {
                game->tick_begin("Tried to shove but failed");
              }
              clear_move_path("Tried to shove but failed");
              return false;
            }
          case THING_SHOVE_TRIED_AND_PASSED :
            {
              DBG2("Shoved monst at %s", future_pos.to_string().c_str());
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

      DBG2("Move, no shove allowed, no attack allowed");
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
      DBG2("Cannot pass hazard at %s", future_pos.to_string().c_str());

      //
      // Could be a monster sitting in lava, attack it?
      //
      if (level->is_monst(future_pos)) {
        DBG2("Hazard, but a monst is on it. Try to attack it.");
        TRACE_AND_INDENT();

        if (move_no_shove_attack_allowed(future_pos)) {
          return true;
        }
      }

      DBG2("Cannot pass hazard at %s, failed to move", future_pos.to_string().c_str());
      clear_move_path("Could not move");
      return false;
    }

    DBG2("Try to move (shoving not allowed, attack allowed) to %s", future_pos.to_string().c_str());
    TRACE_AND_INDENT();

    if (move_no_shove_attack_allowed(future_pos)) {
      return true;
    }

    //
    // Did we try or attempt to try to do something?
    //
    if (! game->tick_requested.empty()) {
      return true;
    }

    DBG2("Try to move (shoving and attacking allowed) to %s", future_pos.to_string().c_str());
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

  if (is_able_to_grapple() && (is_monst() || (is_player() && game->robot_mode))) {
    //
    // Someone in our way we can grab?
    //
    if (d1000() < tp()->chance_d1000_grapple()) {
      //
      // Can the monst shove it into a something bad?
      //
      DBG2("Try to grapple");
      TRACE_AND_INDENT();

      FOR_ALL_NON_INTERNAL_THINGS(level, t, future_pos.x, future_pos.y)
      {
        if (! t->is_shovable()) {
          continue;
        }

        if (is_friend(t) || same_mob(t)) {
          continue;
        }

        t->move(curr_at);
        if (t->is_player()) {
          msg("You are grappled by %s.", text_the().c_str());
        }

        if (is_player()) {
          game->tick_begin("Grapple");
        }
        clear_move_path("Grapple");
        return true;
      }
      FOR_ALL_THINGS_END()
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
      if (level->cursor && (level->cursor->curr_at != future_pos)) {
        //
        // Here we have clicked on a location to jump but there is a monster next to us
        //
        // xC.
        // .m@
        //
        // We clicked on x. What we do not want to do is attack the monster. So, check if we can jump before
        // trying to move to the next hop at m which will be an attack.
        //
        auto mouse_at = level->cursor->curr_at;
        DBG2("Try to move, no shove, attack allowed as mouse clicked on %s", mouse_at.to_string().c_str());
        TRACE_AND_INDENT();

        if ((std::abs(curr_at.x - level->cursor->curr_at.x) <= 1)
            && (std::abs(curr_at.y - level->cursor->curr_at.y) <= 1)) {
          //
          // If more than one hop away, we must jump.
          //
          DBG2("Cursor is adjacent, try to move there");
          TRACE_AND_INDENT();

          //
          // Clear the move path, as if we are doing a diagonal move here, then we do not want to
          // leave the destination on the path as that will stop us collecting items/
          //
          ai->move_path.clear();
          if (move_no_shove_attack_allowed(mouse_at)) {
            return true;
          }
        } else {
          //
          // If more than one hop away, we must jump if we cannot move to the next hop without hitting something.
          //
          DBG2("Cursor is not adjacent, try to move to the next hop first");
          TRACE_AND_INDENT();

          if (move_no_shove_no_attack(future_pos)) {
            return true;
          }

          //
          // Ok something is in the way, try to jump.
          //
          DBG2("Cursor is not adjacent, try to jump there");
          TRACE_AND_INDENT();

          //
          // Clear the move path, as if we are doing a diagonal move here, then we do not want to
          // leave the destination on the path as that will stop us collecting items/
          //
          // Do not jump carefree just in case we jump short and land in lava.
          //
          ai->move_path.clear();
          if (try_to_jump_carefully(mouse_at)) {
            game->tick_begin("player tried to jump");
            return true;
          }
        }
      }

      DBG2("Try to move, no shove, attack allowed on next hop %s", future_pos.to_string().c_str());
      TRACE_AND_INDENT();

      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }
    } else {
      DBG2("Try to move, no shove, no attack as have move path");
      TRACE_AND_INDENT();

      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }
    }
  } else if (is_player() && ! game->robot_mode) {
    if (reason == THING_MOVE_REASON_MOUSE) {
      DBG2("Try to move player, no shove, attack allowed on next hop %s", future_pos.to_string().c_str());
      TRACE_AND_INDENT();

      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }
    } else {
      DBG2("Try to move player, no shove, no attack as have move path");
      TRACE_AND_INDENT();

      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }
    }
  } else {
    if (possible_to_attack_at(future_pos)) {
      DBG2("Try to move and attack");
      TRACE_AND_INDENT();

      if (move_no_shove_attack_allowed(future_pos)) {
        return true;
      }
    } else {
      DBG2("Try to move, no shove, no attack");
      TRACE_AND_INDENT();

      if (move_no_shove_no_attack(future_pos)) {
        return true;
      }

      if (possible_to_attack_at(future_pos)) {
        DBG2("Try to move, no shove, attack allowed");
        TRACE_AND_INDENT();

        if (move_no_shove_attack_allowed(future_pos)) {
          return true;
        }
      }
    }
  }

  //
  // Need this else monsters will keep on trying to continue along a long path
  // and end up lunging crazy distances.
  //
  clear_move_path("Could not move");

  IF_DEBUG2
  {
    if (is_debug_type()) {
      std::string s = "";
      for (auto p : ai->move_path) {
        s += " " + p.to_string();
      }

      if (s.empty()) {
        dbg("Path now %s, path empty", future_pos.to_string().c_str());
      } else {
        dbg("Path now %s, path:%s", future_pos.to_string().c_str(), s.c_str());
      }
    }
  }
  return false;
}

//
// true on having performed an action
//
bool Thing::player_cursor_path_pop_first_move(ThingMoveReason reason)
{
  DBG2("Cursor pop first move");
  TRACE_AND_INDENT();

  if (! is_player()) {
    err("Expected player only");
    return false;
  }

  auto cursor = level->cursor;
  if (! cursor) {
    DBG2("Cursor pop first move: no cursor, recreate");
    TRACE_AND_INDENT();

    level->cursor_recreate();
    cursor = level->cursor;
    if (! cursor) {
      DBG2("Cursor pop first move: no cursor");
      return false;
    }
  }

  if (game->cursor_move_path.size()) {
    DBG2("Cursor path exists");

    //
    // A path to the target exists.
    //
    new_aip();
    aip()->move_path = game->cursor_move_path;
    game->cursor_move_path.clear();

    if (player_or_monst_path_pop_next_move(reason)) {
      DBG2("Move to cursor next hop");
      if (game->cursor_move_path.empty()) {
        level->cursor_path_create(this);
      }
      return true;
    }

    //
    // We get here if for example we click on a monster but are unable to move into its cell because it blocks
    // Or we click on a locked door and cannot pass through.
    //
    DBG2("Failed to move to cursor next hop");
    level->cursor_path_create(this);
    return false;
  }

  //
  // A path to the target does not exist. Jump?
  //
  point future_pos = make_point(cursor->curr_at.x, cursor->curr_at.y);

  //
  // Not sure when/how this happens.
  //
  if (future_pos == curr_at) {
    return false;
  }

  //
  // If adjacent, try to move there. There may be no path because perhaps a monster just moved but now we can
  // step there.
  //
  if ((fabs(future_pos.x - curr_at.x) <= 1) && (fabs(future_pos.y - curr_at.y) <= 1)) {
    DBG2("Target is adjacent, attack or move to %d,%d", cursor->curr_at.x, cursor->curr_at.y);

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
  if (level->can_see_point_or_nearby(future_pos, THING_CAN_SEE_INTO_SHADOWS_DISTANCE)) {
    DBG2("Cursor path does not exist; jump?");
    if (is_able_to_jump() && game->robot_mode) {
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
    msg("You cannot see clearly to move there.");
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
