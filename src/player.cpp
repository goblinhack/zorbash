//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"
#include "my_wid_console.hpp"
#include "my_wid_thing_info.hpp"

bool Game::player_tick_(bool left, bool right, bool up, bool down, bool attack, bool wait, bool jump)
{
  TRACE_AND_INDENT();

  auto level = get_current_level();
  if (! level) {
    LOG("Player tick; ignore, no level");
    return false;
  }

  auto player = level->player;
  if (! player) {
    LOG("Player tick; ignore, no player");
    return false;
  }

  if (player->is_dead) {
    LOG("Player tick; ignore, is dead");
    return false;
  }

  if (player->is_hidden) {
    LOG("Player tick; ignore, is hidden");
    return false;
  }

  //
  // Trying to move when the console is visible.
  //
  if (wid_console_window && wid_console_window->visible) {
    LOG("Player tick; ignore, console open");
    return false;
  }

  if (! g_opt_ascii && level->ts_fade_out_begin) {
    LOG("Player tick; ignore, level fading im/out");
    return false;
  }

  //
  // Trying to move when moving items?
  //
  switch (state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU : LOG("Ignore player action when choosing item options"); return false;
    case Game::STATE_INVENTORY : // Currently managing inventory
      LOG("Ignore player action when moving items");
      return false;
    case Game::STATE_COLLECTING_ITEMS : // Collecting en masse from the level
      LOG("Ignore player action when collecting items");
      return false;
    case Game::STATE_ENCHANTING_ITEMS : LOG("Ignore player action when enchanting items"); return false;
    case Game::STATE_CHOOSING_SKILLS : LOG("Ignore player action when choosing skills"); return false;
    case Game::STATE_CHOOSING_SPELLS : LOG("Ignore player action when choosing spells"); return false;
    case Game::STATE_CHOOSING_LEVEL : LOG("Ignore player action when choosing level"); return false;
    case Game::STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
      LOG("Ignore player action when choosing target");
      return false;
    case Game::STATE_LOAD_MENU :
    case Game::STATE_KEYBOARD_MENU :
    case Game::STATE_SAVE_MENU :
    case Game::STATE_QUIT_MENU : LOG("Ignore player action when in menu"); return false;
    default : ERR("Unhandled game state"); return false;
  }

  if (left || right || up || down) {
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  point dir;

  if (left) {
    dir.x = -1;
  }
  if (right) {
    dir.x = 1;
  }
  if (up) {
    dir.y = -1;
  }
  if (down) {
    dir.y = 1;
  }
  if (! dir.x && ! dir.y) {
    dir = player->dir_to_direction();
  }

  if (jump) {
    tick_begin("player jumped");
    DBG("Player jumped");

    if (cursor_move_path.size()) {
      //
      // A path to the target exists.
      //
      for (auto i = cursor_move_path.rbegin(); i != cursor_move_path.rend(); i++) {
        auto p = *i;
        // for (auto p : std::ranges::reverse_view(cursor_move_path)) {
        if (player->try_to_jump_carefree(make_point(p.x, p.y))) {
          player->clear_move_path("Tried to jump");
          break;
        }

        //
        // It's not good to try alternatives as the jump path might not be in s straight line.
        //
        break;
      }
    } else if (level->cursor && (level->cursor->curr_at == player->curr_at)) {
      auto  player_move_delta = player->dir_to_direction();
      point p = make_point(player->curr_at.x + player_move_delta.x, player->curr_at.y + player_move_delta.y);
      if (level->is_obs_wall_or_door(p.x, p.y) || level->is_obs_destructable(p.x, p.y)) {
        player->try_to_jump_carefree(player->curr_at);
      } else {
        player->try_to_jump_carefree(p);
      }
    } else if (level->cursor) {
      point p = make_point(level->cursor->curr_at.x, level->cursor->curr_at.y);
      if (level->is_obs_wall_or_door(p.x, p.y) || level->is_obs_destructable(p.x, p.y)) {
        player->try_to_jump_carefree(player->curr_at);
      } else {
        player->try_to_jump_carefree(p);
      }
    }
    player->clear_move_path("Tried to jump");
  } else if (up || down || left || right || attack || wait) {
    IF_DEBUG1
    {
      if (attack) {
        player->log("Player attack");
      } else if (wait) {
        player->log("Player collect or wait");
      } else {
        player->log("Player move attempt");
      }
    }

    //
    // If we move manually, clear the path as it visually gets
    // in the way
    //
    level->cursor_path_clear();

    //
    // If swinging, don't leave the weapon behind
    //
    // Not sure about this one
    // if (player->equip_id_use_anim().ok()) {
    //     player->topcon("Don't move while swinging weapon");
    //     return;
    // }

    //
    // If something was being described and we moved, clear it now
    //
    bool was_moving     = player->is_moving;
    auto old_thing_info = current_wid_thing_info;
    auto future_pos     = player->curr_at + dir;

    ThingAttackOptions attack_options {};
    attack_options.shove_allowed  = true;
    attack_options.attack_allowed = true;
    if (wait) {
      attack_options.shove_allowed  = false;
      attack_options.attack_allowed = false;
    }

    if (attack) {
      if (up || down || left || right) {
        attack_options.attack_at     = future_pos;
        attack_options.attack_at_set = true;
      }
    }

    bool moved = player->move(future_pos, up, down, left, right, attack, wait, &attack_options);

    //
    // If something was being described and we moved, clear it now
    //
    if (moved) {
      DBG("Player moved");
      if (! was_moving && old_thing_info && (old_thing_info == current_wid_thing_info)) {
        DBG("Player moved; clear thing info");
        wid_thing_info_fini("player moved");
      }
    }
  }

  return true;
}

bool Game::player_tick(bool left, bool right, bool up, bool down, bool attack, bool wait, bool jump)
{
  pcg_random_allowed++;
  auto ret = player_tick_(left, right, up, down, attack, wait, jump);
  pcg_random_allowed--;
  return ret;
}
