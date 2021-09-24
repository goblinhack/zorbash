// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_monst.h"
#include "my_thing_template.h"
#include "my_wid_console.h"
#include "my_player.h"
#include "my_array_bounds_check.h"
#include "my_wid_thing_info.h"
#include "my_sdl.h"
#include "my_ptrcheck.h"

void player_tick (bool left, bool right, bool up, bool down, bool attack, bool wait, bool jump)
{ TRACE_AND_INDENT();
  //
  // Trying to move when the console is visible.
  //
  if (wid_console_window && wid_console_window->visible) {
    IF_DEBUG4 {
      LOG("Player tick; ignore, console open");
    }
    return;
  }

  if (game->level->ts_fade_in_begin ||
    game->level->ts_fade_out_begin) {
    IF_DEBUG4 {
      LOG("Player tick; ignore, level fading im/out");
    }
    return;
  }

  //
  // Trying to move when moving items?
  //
  switch (game->state) {
    case Game::STATE_NORMAL:
      break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU:
      {
        IF_DEBUG4 {
          LOG("Ignore player action when choosing item options");
        }
      }
      return;
    case Game::STATE_MOVING_ITEMS:     // Currently managing inventory
      {
        IF_DEBUG4 {
          LOG("Ignore player action when moving items");
        }
      }
      return;
    case Game::STATE_WIELDING_ITEMS:
      {
        IF_DEBUG4 {
          LOG("Ignore player action when wielding items");
        }
      }
      return;
    case Game::STATE_COLLECTING_ITEMS: // Collecting en masse from the level
      {
        IF_DEBUG4 {
          LOG("Ignore player action when collecting items");
        }
      }
      return;
    case Game::STATE_ENCHANTING_ITEMS:
      {
        IF_DEBUG4 {
          LOG("Ignore player action when enchanting items");
        }
      }
      return;
    case Game::STATE_CHOOSING_SKILLS:
      {
        IF_DEBUG4 {
          LOG("Ignore player action when choosing skills");
        }
      }
      return;
    case Game::STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
      {
        IF_DEBUG4 {
          LOG("Ignore player action when choosing target");
        }
      }
      return;
    case Game::STATE_LOAD_MENU:
    case Game::STATE_SAVE_MENU:
    case Game::STATE_QUIT_MENU:
      {
        IF_DEBUG4 {
          LOG("Ignore player action when in menu");
        }
      }
      return;
  }

  auto level = game->level;
  if (!level) {
    IF_DEBUG4 {
      LOG("Player tick; ignore, no level");
    }
    return;
  }

  auto player = level->player;
  if (!player) {
    IF_DEBUG4 {
      LOG("Player tick; ignore, no player");
    }
    return;
  }

  //
  // Trying to scroll the map?
  //
  const float map_move_scroll_delta = 0.2;
  const uint8_t *state = SDL_GetKeyboardState(0);

  if (state[game->config.key_map_left]) {
    level->map_wanted_at.x -= map_move_scroll_delta;
    level->cursor_found = false;
    level->map_follow_player = false;
  }

  if (state[game->config.key_map_right]) {
    level->map_wanted_at.x += map_move_scroll_delta;
    level->cursor_found = false;
    level->map_follow_player = false;
  }

  if (state[game->config.key_map_up]) {
    level->map_wanted_at.y -= map_move_scroll_delta;
    level->cursor_found = false;
    level->map_follow_player = false;
  }

  if (state[game->config.key_map_down]) {
    level->map_wanted_at.y += map_move_scroll_delta;
    level->cursor_found = false;
    level->map_follow_player = false;
  }

  if (player->is_dead || player->is_hidden) {
    IF_DEBUG4 {
      LOG("Player tick; ignore, is dead");
    }
    return;
  }

  if (state[game->config.key_move_left]) {
    left = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (state[game->config.key_move_right]) {
    right = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (state[game->config.key_move_up]) {
    up = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (state[game->config.key_move_down]) {
    down = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (get(sdl_joy_buttons, SDL_JOY_BUTTON_UP)) {
    up = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (get(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN)) {
    down = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT)) {
    left = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT)) {
    right = true;
    if (level && level->cursor) {
      level->cursor_path_clear();
      level->cursor->hide();
    }
  }

  if (sdl_joy_axes) {
    if (sdl_joy_axes[3] > sdl_joy_deadzone) {
      right = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }

    if (sdl_joy_axes[3] < -sdl_joy_deadzone) {
      left = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }

    if (sdl_joy_axes[4] > sdl_joy_deadzone) {
      down = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }

    if (sdl_joy_axes[4] < -sdl_joy_deadzone) {
      up = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }

    if (sdl_joy_axes[0] > sdl_joy_deadzone) {
      right = true;
    }

    if (sdl_joy_axes[0] < -sdl_joy_deadzone) {
      left = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }

    if (sdl_joy_axes[1] > sdl_joy_deadzone) {
      down = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }

    if (sdl_joy_axes[1] < -sdl_joy_deadzone) {
      up = true;
      if (level && level->cursor) {
        level->cursor_path_clear();
        level->cursor->hide();
      }
    }
  }

  attack |= state[game->config.key_attack] ? true : false;
  wait   |= state[game->config.key_wait_or_collect] ? true : false;
  jump   |= state[game->config.key_jump] ? true : false;

  double d = 1.0;
  double dx = 0.0;
  double dy = 0.0;

  if (left) {
    dx = -d;
  }
  if (right) {
    dx = d;
  }
  if (up) {
    dy = -d;
  }
  if (down) {
    dy = d;
  }

  if (jump) {
    game->tick_begin("player jumped");

    if (game->cursor_move_path.size()) {
      //
      // A path to the target exists.
      //
      for (auto i = game->cursor_move_path.rbegin();
         i != game->cursor_move_path.rend(); i++) {
        auto p = *i;
        if (player->try_to_jump_carefree(make_point(p.x, p.y))) {
          player->clear_move_path("Tried to jump");
          break;
        }
      }
    } else if (level->cursor && (level->cursor->mid_at == player->mid_at)) {
      auto player_move_delta = player->dir_to_direction();
      point p = make_point(player->mid_at.x + player_move_delta.x,
                 player->mid_at.y + player_move_delta.y);
      if (level->is_obs_wall_or_door(p.x, p.y) ||
        level->is_obs_destructable(p.x, p.y)) {
        player->try_to_jump_carefree(make_point(player->mid_at));
      } else {
        player->try_to_jump_carefree(p);
      }
    } else if (level->cursor) {
      point p = make_point(level->cursor->mid_at.x,
                 level->cursor->mid_at.y);
      if (level->is_obs_wall_or_door(p.x, p.y) ||
        level->is_obs_destructable(p.x, p.y)) {
        player->try_to_jump_carefree(make_point(player->mid_at));
      } else {
        player->try_to_jump_carefree(p);
      }
    }
    player->clear_move_path("Tried to jump");
  } else if (up || down || left || right || attack || wait) {
    if (attack) {
      player->log("Player attack");
    } else if (wait) {
      player->log("Player collect or wait");
    } else {
      player->log("Player move attempt");
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
    // if (player->get_weapon_id_use_anim().ok()) {
    //     player->topcon("Don't move while swinging weapon");
    //     return;
    // }

    //
    // If something was being described and we moved, clear it now
    //
    bool moving = player->is_moving;

    fpoint future_pos = player->mid_at + fpoint(dx, dy);
    bool shove_allowed = true;
    bool attack_allowed = true;
    if (wait) {
      shove_allowed = false;
      attack_allowed = false;
    }
    bool moved = player->move(future_pos, up, down, left, right, attack, wait,
                  shove_allowed, attack_allowed);

    if (moved) {
      if (!moving) {
        wid_thing_info_fini();
      }
    }
  }

  left = false;
  right = false;
  up = false;
  down = false;
}
