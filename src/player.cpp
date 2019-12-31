/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_game.h"
#include "my_wid_console.h"

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

    if ((time_get_time_ms_cached() - player->get_timestamp_move_begin()) < 100) {
        return;
    }

    uint8_t right  = 0;
    uint8_t left   = 0;
    uint8_t up     = 0;
    uint8_t down   = 0;
    uint8_t attack = 0;

    const uint8_t *state = SDL_GetKeyboardState(0);

    right  = state[SDL_SCANCODE_RIGHT] ? 1 : 0;
    left   = state[SDL_SCANCODE_LEFT] ? 1 : 0;
    up     = state[SDL_SCANCODE_UP] ? 1 : 0;
    down   = state[SDL_SCANCODE_DOWN] ? 1 : 0;
    attack   = state[SDL_SCANCODE_SPACE] ? 1 : 0;

    bool key_pressed = false;
    static uint32_t last_key_pressed_when;
    if (!last_key_pressed_when) {
        last_key_pressed_when = time_get_time_ms_cached() - 1000;
    }

    if ((time_get_time_ms_cached() - last_key_pressed_when) > 125) {
        key_pressed = true;
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

    fpoint future_pos = player->mid_at + fpoint(dx, dy);

    player->move(future_pos, up, down, left, right, attack);
    if (up || down || left || right || attack) {
        key_pressed = true;
    }

    if (key_pressed) {
        last_key_pressed_when = time_get_time_ms_cached();
    }
}
