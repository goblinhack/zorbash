//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid_thing_info.hpp"

static uint8_t game_mouse_down_(int x, int y, uint32_t button)
{
  DBG("Game mouse down");
  TRACE_AND_INDENT();

  if (! game || ! game->started) {
    DBG2("Game mouse down; no game or not started");
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG2("Game mouse down; no level");
    return false;
  }

  auto player = level->player;
  if (! player) {
    DBG2("Game mouse down; no player");
    return false;
  }

  if (player->is_dead) {
    DBG2("Game mouse down; player dead");
    return true;
  }

  //
  // If mid air, we're done. Let other things move.
  //
  if (player->is_jumping) {
    DBG2("Game mouse down; player jumping");
    return true;
  }

  if (! level->cursor) {
    DBG2("Game mouse down; no cursor");
    return false;
  }

  if (wid_some_recent_event_occurred()) {
    DBG2("Game mouse down; some recent wid event occurred");
    return false;
  }

  if (game->state == Game::STATE_CHOOSING_LEVEL) {
    DBG2("Game mouse down; choosing level");
    return false;
  }

  IF_DEBUG2 { player->log("Mouse down"); }
  wid_thing_info_fini("mouse down");

  if (game->state == Game::STATE_CHOOSING_TARGET) {
    IF_DEBUG2 { player->log("Game mouse down; in normal state"); }
    TRACE_AND_INDENT();

    //
    // Check for trying to teleport or fire too far away.
    //
    if (! game->request_destination_ok) {
      if (! game->request_to_throw_item) {
        //
        // e.g. boots of teleport trying to enter a wall ?
        //
        auto item = game->request_to_use_item;
        if (item && item->is_item_targetted()) {
          player->msg("You cannot target that location.");
          return true;
        }
      }
    }

    if (game->request_to_throw_item) {
      auto item = game->request_to_throw_item;
      player->throw_at(item, level->cursor);
    }

    if (game->request_to_use_item) {
      auto item = game->request_to_use_item;

      player->used(item, level->cursor, true);

      //
      // The laser name is provided by the likes of wand
      //
      if (! item->gfx_targetted_laser().empty()) {
        player->laser_shoot_at(item, item->gfx_targetted_laser(), level->cursor->curr_at);
      } else if (! item->target_name_projectile().empty()) {
        player->fire_projectile_at(item, item->target_name_projectile(), level->cursor->curr_at);
      } else if (item->is_item_targetted()) {
        player->item_targetted_use_at(item, level->cursor->curr_at);
      } else {
        TOPCON("Unknown beam weapon: %s.", item->text_the().c_str());
      }

      //
      // Get the damage from the enchanted wand, so the laser
      // inflicts that damage.
      //
      player->dmg_current_set(item->dmg_current());
    }
    return true;
  }

  if (game->state == Game::STATE_NORMAL) {
    //
    // Have we moved close enough to attack? Do this prior to checking for
    // double click so we can attack monsters sitting in lava
    //
    if (level->cursor) {
      if ((std::abs(player->curr_at.x - level->cursor->curr_at.x) <= 1) &&
          (std::abs(player->curr_at.y - level->cursor->curr_at.y) <= 1)) {
        IF_DEBUG2 { player->log("Close enough to attack check"); }
        TRACE_AND_INDENT();

        int x = level->cursor->curr_at.x;
        int y = level->cursor->curr_at.y;
        FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
        {
          if (t == level->player) {
            continue;
          }

          IF_DEBUG2 { player->log("Yes; close enough to attack %s?", t->to_short_string().c_str()); }
          TRACE_AND_INDENT();

          //
          // Not sure if we want to be able to attack corpses via the mouse.
          //
          if (t->is_dead && t->is_monst()) {
            continue;
          }

          //
          // If the door is not broken, we can close it
          //
          if (t->is_door() && t->is_open) {
            IF_DEBUG2 { player->log("Close door"); }
            TRACE_AND_INDENT();
            game->tick_begin("close door");

            if (player->close_door(t)) {
              IF_DEBUG2 { player->log("Closed a door"); }
              return true;
            }

            //
            // If we fail to close the door; there could be a larger thing standing there,
            // then fall through to attack.
            //
            IF_DEBUG2 { player->log("Failed to close door"); }
          }

          //
          // Try to open the door with a key.
          //
          if (t->is_door() && ! t->is_open) {
            IF_DEBUG2 { player->log("Open door"); }
            TRACE_AND_INDENT();
            game->tick_begin("open door");

            if (player->open_door(t)) {
              IF_DEBUG2 { player->log("Opened a door"); }
              return true;
            }

            //
            // Fall through to attack if we fail to open the door. Maybe there is a monst
            // in the way
            //
          }

          //
          // Attack
          //
          if (t->is_attackable_by_player()) {
            IF_DEBUG2 { player->log("Close enough to attack"); }
            player->attack(level->cursor->curr_at);
            return true;
          }
        }
        FOR_ALL_THINGS_END()

        //
        // 2nd try, see if we can shove it. Like a brazier for example.
        //
        IF_DEBUG2 { player->log("Close enough to shove check"); }
        TRACE_AND_INDENT();

        FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
        {
          if (t == level->player) {
            continue;
          }

          //
          // Not sure if we want to be able to shove corpses via the mouse.
          //
          if (t->is_dead && t->is_monst()) {
            continue;
          }

          if (t->is_shovable()) {
            IF_DEBUG2 { player->log("Yes; close enough to shove %s?", t->to_short_string().c_str()); }
            TRACE_AND_INDENT();
            player->try_to_shove(level->cursor->curr_at);
            return true;
          }
        }
        FOR_ALL_THINGS_END()
      }
    }

    //
    // If hovering over a double click thing then don't jump in unless the user really means it.
    //
    if (! wid_mouse_two_clicks) {
      auto to = level->cursor->curr_at;
      FOR_ALL_NON_INTERNAL_THINGS(level, t, to.x, to.y)
      {
        if (t->is_cursor_can_hover_over_x2_click()) {
          IF_DEBUG2 { player->log("Needs double click"); }
          if (level->is_chasm(to)) {
            TOPCON("Double click to jump into the abyss.");
          } else if (level->is_lava(to)) {
            TOPCON("Double click to jump into the lava.");
          } else {
            TOPCON("Double click to move to move onto that.");
          }
          return true;
        }
      }
      FOR_ALL_THINGS_END()
    }

    //
    // Have we moved close enough to collect? Do this after the double
    // click check so we do not try to collect things in lava.
    //
    if (level->cursor) {
      if (player->curr_at == level->cursor->curr_at) {
        auto items = player->anything_to_carry_at(player->curr_at);
        if (items.size()) {
          game->wid_collect_create(items);
        }
      }
    }

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    if (player->cursor_path_pop_first_move(THING_MOVE_REASON_MOUSE)) {
      return true;
    }
  } else {
    IF_DEBUG2 { player->log("Game mouse down; not in normal state"); }
    TRACE_AND_INDENT();
  }

  return false;
}

uint8_t game_mouse_down(int x, int y, uint32_t button)
{
  pcg_random_allowed++;
  auto ret = game_mouse_down_(x, y, button);
  pcg_random_allowed--;
  return ret;
}

uint8_t game_mouse_up(int x, int y, uint32_t button) { return false; }

static uint8_t game_mouse_motion_(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  DBG2("Game mouse motion");
  TRACE_AND_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  //
  // Make the cursor visible once we enter a level.
  //
  if (level->cursor) {
    if (level->ts_entered && time_have_x_tenths_passed_since(10, level->ts_entered)) {
      if (! player->is_dead) {
        level->cursor->visible();
      }
    }
  }

  game->request_recreate_cursor_path = true;

  return true;
}

uint8_t game_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  pcg_random_allowed++;
  auto ret = game_mouse_motion_(x, y, relx, rely, wheelx, wheely);
  pcg_random_allowed--;
  return ret;
}
