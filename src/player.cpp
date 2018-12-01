/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_player.h"
#include "my_thing.h"
#include "my_wid_console.h"

void player_tick (void)
{_
    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    auto player = game.state.player;
    if (!player || player->is_dead || player->is_hidden) {
        return;
    }

    if ((time_get_time_ms() - player->begin_move_ms) < 100) {
        return;
    }

    uint8_t right = 0;
    uint8_t left  = 0;
    uint8_t up    = 0;
    uint8_t down  = 0;
    uint8_t fire  = 0;
    uint8_t run = sdl_shift_held;

    const uint8_t *state = SDL_GetKeyboardState(0);

    right  = state[SDL_SCANCODE_RIGHT] ? 1 : 0;
    left   = state[SDL_SCANCODE_LEFT] ? 1 : 0;
    up     = state[SDL_SCANCODE_UP] ? 1 : 0;
    down   = state[SDL_SCANCODE_DOWN] ? 1 : 0;
    fire   = state[SDL_SCANCODE_SPACE] ? 1 : 0;

    if (sdl_joy_buttons[SDL_JOY_BUTTON_UP]) {
        up = true;
    }

    if (sdl_joy_buttons[SDL_JOY_BUTTON_DOWN]) {
        down = true;
    }

    if (sdl_joy_buttons[SDL_JOY_BUTTON_LEFT]) {
        left = true;
    }

    if (sdl_joy_buttons[SDL_JOY_BUTTON_RIGHT]) {
        right = true;
    }

    if (sdl_joy_buttons[SDL_JOY_BUTTON_LEFT_FIRE]) {
        fire = true;
    } else if (sdl_joy_buttons[SDL_JOY_BUTTON_RIGHT_FIRE]) {
        run = true;
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

    if ((dx != 0) || (dy != 0)) {
        fpoint future_pos = player->at + fpoint(dx, dy);

        (void) light_new(100, 2, 
                         fpoint(player->at.x, player->at.y), 
                         LIGHT_QUALITY_POINT, GRAY30);

        player->move(future_pos, up, down, left, right, fire);
    }
}
