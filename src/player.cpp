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

    auto player = world->player;
    if (!player || player->is_dead || player->is_hidden) {
        return;
    }

    int delay = 100;
#if 0
    //
    // Always move
    //
    if ((time_get_time_ms_cached() -
            player->get_timestamp_move_begin()) < delay) {
        return;
    }
#endif

    uint8_t right  = 0;
    uint8_t left   = 0;
    uint8_t up     = 0;
    uint8_t down   = 0;
    uint8_t attack = 0;
    uint8_t wait   = 0;

    const uint8_t *state = SDL_GetKeyboardState(0);

    right  = state[game->config.key_move_right] ? 1 : 0;
    left   = state[game->config.key_move_left] ? 1 : 0;
    up     = state[game->config.key_move_up] ? 1 : 0;
    down   = state[game->config.key_move_down] ? 1 : 0;
    attack = state[game->config.key_attack] ? 1 : 0;
    wait   = state[game->config.key_wait] ? 1 : 0;
    bool some_key_event_was_pressed = false;

    if (state[game->config.key_map_left]) {
        world->map_wanted_at.x--;
        world->cursor_needs_update = true;
        world->cursor_found = false;
        world->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_right]) {
        world->map_wanted_at.x++;
        world->cursor_needs_update = true;
        world->cursor_found = false;
        world->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_up]) {
        world->map_wanted_at.y--;
        world->cursor_needs_update = true;
        world->cursor_found = false;
        world->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_down]) {
        world->map_wanted_at.y++;
        world->cursor_needs_update = true;
        world->cursor_found = false;
        world->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_zoom_out]) {
        MINICON("Zoom out");
        CON("USERCFG: zoom out");
        config_gfx_zoom_out();
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_load]) {
        CON("USERCFG: loading game");
        game->load_select();
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_save]) {
        MINICON("Saving the game");
        CON("USERCFG: saving the game");
        game->save_select();
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_pause]) {
        MINICON("Pausing the game");
        CON("USERCFG: pausing the game");
        game->pause_select();
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_help]) {
        game->config_keyboard_select();
        some_key_event_was_pressed = true;
    }

    if (some_key_event_was_pressed) {
        return;
    }

    bool key_pressed = false;
    static uint32_t last_key_pressed_when;
    if (!last_key_pressed_when) {
        last_key_pressed_when = time_get_time_ms_cached() - 1000;
    }

    if ((time_get_time_ms_cached() - last_key_pressed_when) > (uint)delay) {
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

        if (up || down || left || right || attack || wait) {
            key_pressed = true;
        }

        if (key_pressed) {
            fpoint future_pos = player->mid_at + fpoint(dx, dy);
            player->move(future_pos, up, down, left, right, attack, wait);
            last_key_pressed_when = time_get_time_ms_cached();
        }
    }
}
