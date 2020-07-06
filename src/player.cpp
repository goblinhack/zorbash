//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_wid_console.h"
#include "my_thing.h"

void player_tick (void)
{_
    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    if (game->paused()) {
        return;
    }

    auto level = game->level;
    if (!level) {
        return;
    }

    auto player = level->player;
    if (!player || player->is_dead || player->is_hidden) {
        return;
    }

    g_thing_callframes_depth = callframes_depth;

    auto delay = PLAYER_MOVE_SPEED_MS;

    uint8_t right  = 0;
    uint8_t left   = 0;
    uint8_t up     = 0;
    uint8_t down   = 0;
    uint8_t attack = 0;
    uint8_t wait   = 0;
    uint8_t jump   = 0;

    const uint8_t *state = SDL_GetKeyboardState(0);

    right  = state[game->config.key_move_right] ? 1 : 0;
    left   = state[game->config.key_move_left] ? 1 : 0;
    up     = state[game->config.key_move_up] ? 1 : 0;
    down   = state[game->config.key_move_down] ? 1 : 0;
    attack = state[game->config.key_attack] ? 1 : 0;
    wait   = state[game->config.key_wait] ? 1 : 0;
    jump   = state[game->config.key_jump] ? 1 : 0;
    bool some_key_event_was_pressed = false;

    if (state[game->config.key_map_left]) {
        level->map_wanted_at.x--;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_right]) {
        level->map_wanted_at.x++;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_up]) {
        level->map_wanted_at.y--;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_down]) {
        level->map_wanted_at.y++;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (some_key_event_was_pressed) {
        return;
    }

    static uint32_t last_key_pressed_when;
    if (!last_key_pressed_when) {
        last_key_pressed_when = time_get_time_ms_cached() - 1000;
    }

    if ((time_get_time_ms_cached() - last_key_pressed_when) < (uint)delay) {
        return;
    }

    if (wait) {
        MINICON("You wait...");
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_UP)) {
        up = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN)) {
        down = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT)) {
        left = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT)) {
        right = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE)) {
        attack = true;
    }

    if (sdl_joy_axes) {
        if (sdl_joy_axes[3] > sdl_joy_deadzone) {
            right = true;
        }

        if (sdl_joy_axes[3] < -sdl_joy_deadzone) {
            left = true;
        }

        if (sdl_joy_axes[4] > sdl_joy_deadzone) {
            down = true;
        }

        if (sdl_joy_axes[4] < -sdl_joy_deadzone) {
            up = true;
        }

        if (sdl_joy_axes[0] > sdl_joy_deadzone) {
            right = true;
        }

        if (sdl_joy_axes[0] < -sdl_joy_deadzone) {
            left = true;
        }

        if (sdl_joy_axes[1] > sdl_joy_deadzone) {
            down = true;
        }

        if (sdl_joy_axes[1] < -sdl_joy_deadzone) {
            up = true;
        }
    }

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
        bool jumped = false;
        if (game->cursor_move_path.size()) {
            //
            // A path to the target exists.
            //
            for (auto i = game->cursor_move_path.rbegin();
                 i != game->cursor_move_path.rend(); i--) {
                auto p = *i;
                if (player->try_to_jump(make_point(p.x, p.y))) {
                    game->tick_begin();
                    jumped = true;
                    break;
                }
            }
            game->cursor_move_path.clear();
        } else if (level->cursor->mid_at == player->mid_at) {
            auto delta = player->dir_to_direction();
            point p = make_point(player->mid_at.x + delta.x,
                                 player->mid_at.y + delta.y);
            if (player->try_to_jump(p)) {
                game->tick_begin();
            }
        } else if (level->cursor) {
            point p = make_point(level->cursor->mid_at.x,
                                 level->cursor->mid_at.y);
            if (player->try_to_jump(p)) {
                game->tick_begin();
            }
        }
        last_key_pressed_when = time_get_time_ms_cached();
        player->monstp->move_path.clear();
        game->cursor_move_path.clear();
        level->cursor_path_clear();
    } else if (up || down || left || right || attack || wait) {
        //
        // If we move manually, clear the path as it visually gets
        // in the way
        //
        level->cursor_path_clear();

        fpoint future_pos = player->mid_at + fpoint(dx, dy);
        player->move(future_pos, up, down, left, right, attack, wait);
        last_key_pressed_when = time_get_time_ms_cached();
    }
}
