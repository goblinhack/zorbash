// See the README.md file for license info.
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

    auto level = game->level;
    if (!level) {
        return;
    }

    auto player = level->player;
    if (!player) {
        return;
    }

    float delta = 0.2;
    bool some_key_event_was_pressed = false;
    const uint8_t *state = SDL_GetKeyboardState(0);

    if (state[game->config.key_map_left]) {
        level->map_wanted_at.x -= delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_right]) {
        level->map_wanted_at.x += delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_up]) {
        level->map_wanted_at.y -= delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (state[game->config.key_map_down]) {
        level->map_wanted_at.y += delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
        some_key_event_was_pressed = true;
    }

    if (player->is_dead || player->is_hidden) {
        return;
    }

    if (game->paused()) {
        return;
    }

    g_thing_callframes_depth = callframes_depth;

    static bool left = false;
    static bool right = false;
    static bool up = false;
    static bool down = false;

    static uint8_t pending_cnt = 0;
    static const uint8_t pending_max_delay = 2;

    if (state[game->config.key_move_left]) {
        left = true;
    }

    if (state[game->config.key_move_right]) {
        right = true;
    }

    if (state[game->config.key_move_up]) {
        up = true;
    }

    if (state[game->config.key_move_down]) {
        down = true;
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

    if (left || right || up || down) {
        pending_cnt++;
        if (pending_cnt < pending_max_delay) {
            return;
        }
    }

    auto delay = PLAYER_KEY_REPEAT_MS;

    uint8_t attack = 0;
    uint8_t wait   = 0;
    uint8_t jump   = 0;

    attack = state[game->config.key_attack] ? 1 : 0;
    wait   = state[game->config.key_wait] ? 1 : 0;
    jump   = state[game->config.key_jump] ? 1 : 0;

    if (some_key_event_was_pressed) {
        return;
    }

    static uint32_t last_key_pressed_when;
    if (!last_key_pressed_when) {
        last_key_pressed_when = time_get_time_ms_cached() - 1000;
    }

    if ((time_get_time_ms_cached() - last_key_pressed_when) < (uint)delay) {
        left = false;
        right = false;
        up = false;
        down = false;
        pending_cnt = 0;
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
        if (game->cursor_move_path.size()) {
            //
            // A path to the target exists.
            //
            for (auto i = game->cursor_move_path.rbegin();
                 i != game->cursor_move_path.rend(); i++) {
                auto p = *i;
                player->try_to_jump(make_point(p.x, p.y));
            }
            game->cursor_move_path.clear();
        } else if (level->cursor->mid_at == player->mid_at) {
            auto delta = player->dir_to_direction();
            point p = make_point(player->mid_at.x + delta.x,
                                 player->mid_at.y + delta.y);
            player->try_to_jump(p);
        } else if (level->cursor) {
            point p = make_point(level->cursor->mid_at.x,
                                 level->cursor->mid_at.y);
            player->try_to_jump(p);
        }
        last_key_pressed_when = time_get_time_ms_cached();
        player->monstp->move_path.clear();
        game->cursor_move_path.clear();
        level->cursor_path_clear();
        game->tick_begin();
    } else if (up || down || left || right || attack || wait) {
        //
        // If we move manually, clear the path as it visually gets
        // in the way
        //
        level->cursor_path_clear();

        fpoint future_pos = player->mid_at + fpoint(dx, dy);
        player->move(future_pos, up, down, left, right, attack, wait, true);
        last_key_pressed_when = time_get_time_ms_cached();
    }

    left = false;
    right = false;
    up = false;
    down = false;
    pending_cnt = 0;
}
