/*
 * Copyright (C) 2011-2017 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_player.h"
#include "my_thing.h"

void player_tick (void)
{
    auto player = game.state.player;
    if (!player || player->is_dead || player->is_hidden) {
        return;
    }

    uint8_t right = 0;
    uint8_t left  = 0;
    uint8_t up    = 0;
    uint8_t down  = 0;
    uint8_t fire  = 0;
    uint8_t jump  = 0;
    uint8_t bomb  = 0;
    uint8_t rope  = 0;
    uint8_t torch  = 0;
    uint8_t run = sdl_shift_held;

    const uint8_t *state = SDL_GetKeyboardState(0);

    right  = state[SDL_SCANCODE_RIGHT] ? 1 : 0;
    left   = state[SDL_SCANCODE_LEFT] ? 1 : 0;
    up     = state[SDL_SCANCODE_UP] ? 1 : 0;
    down   = state[SDL_SCANCODE_DOWN] ? 1 : 0;
    fire   = state[SDL_SCANCODE_SPACE] ? 1 : 0;
    jump   = state[SDL_SCANCODE_Z] ? 1 : 0;
    bomb   = state[SDL_SCANCODE_B] ? 1 : 0;
    rope   = state[SDL_SCANCODE_R] ? 1 : 0;
    torch  = state[SDL_SCANCODE_T] ? 1 : 0;

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
    } else if (sdl_joy_buttons[SDL_JOY_BUTTON_A]) {
        rope = true;
    } else if (sdl_joy_buttons[SDL_JOY_BUTTON_X]) {
        bomb = true;
    } else if (sdl_joy_buttons[SDL_JOY_BUTTON_Y]) {
        torch = true;
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

    if (!up && !down && !left && !right && 
        !fire && 
        !jump && 
        !bomb && 
        !rope && 
        !torch) {
        return;
    }

    /*
     * Check if we are allowed to fire our gun again so soon.
     */
    if (fire) {
        auto weapon = player->get_weapon();
        if (!weapon) {
            fire = 0;
        }

        if (fire) {
            static uint32_t last_fired = 0;

            uint32_t delay = tp_get_weapon_use_delay_hundredths(weapon);
            
            if (!time_have_x_hundredths_passed_since(delay, last_fired)) {
                fire = 0;

                if (!up && !down && !left && !right && !jump) {
                    return;
                }
            }

            if (fire) {
                last_fired = time_get_time_ms();
            }
        }

        if (fire) {
            player->use();
        }
    }

#if 0
    double submerged = thing_is_partially_or_fully_submerged(level, player);

    if (up) {
        if (!submerged) {
            if (!thing_overlaps(level, player, player->x, player->y -0.5, 
                                thing_is_climbable) &&
                !thing_overlaps(level, player, player->x, player->y,      
                                thing_is_climbable)) {
                up = 0;
            }
        }
    }

    if (down) {
        if (!submerged) {
            if (!thing_overlaps(level, player, player->x, player->y + 0.5, 
                                thing_is_climbable)) {
                down = 0;
            }
        }
    }
#endif

    if (!time_have_x_hundredths_passed_since(
          tp_move_delay_hundredths(player->tp), player->last_move_ms)) {
#if 0
        double x = player->x;
        double y = player->y;

        thing_move(level, player, x, y, false, false, false, false, fire);
#endif
        return;
    }
#if 0
    level->last_moved = time_get_time_ms();

    double x = player->x;
    double y = player->y;

    double max_momentum = 0.5;
    double move_momentum = 0.012;
    double jump_speed = 0.15;
    double wall_friction = 0.95;

    /*
     * run?
     */
    if (sdl_shift_held) {
        max_momentum = 1.0;
        move_momentum = 0.020;
        jump_speed = 0.20;
    }

    /*
     * Don't move too fast either way as we build up speed
     */
    if (left) {
        player->momentum -= move_momentum;
        if (player->momentum <= -max_momentum) {
            player->momentum = -max_momentum;
        }
    }

    if (right) {
        player->momentum += move_momentum;
        if (player->momentum >= max_momentum) {
            player->momentum = max_momentum;
        }
    }

    /*
     * Don't allow too frequent jumps
     */
    if (jump) {
        if (player->is_submerged) {
            if (!time_have_x_hundredths_passed_since(50, level->last_jumped)) {
                jump = 0;
            }
        } else if (player->is_partially_submerged) {
            if (!time_have_x_hundredths_passed_since(25, level->last_jumped)) {
                jump = 0;
            }
        } else {
            if (!time_have_x_hundredths_passed_since(10, level->last_jumped)) {
                jump = 0;
            }
        }
    }

    if (jump) {
        if (level->last_hit_obstacle &&
            !time_have_x_hundredths_passed_since(15, level->last_hit_obstacle)) {

            /*
             * Allow the player to cling onto and jump when they hit a ledge 
             * as long as not falling too fast
             */
            if (player->fall_speed < THING_FALL_SPEED_CLING_ONTO_WALLS) {
                if (!player->jump_speed) {
                    player->jump_speed = jump_speed;
                }
            }
        }

        /*
         * Else if not falling, allow the jump
         */
        if (!player->fall_speed) {
            if (!player->jump_speed) {
                player->jump_speed = jump_speed;
            }
        }
    }

    if (submerged && jump) {
        jump = 0;
        up = 1;
    }

    if (bomb) {
        if (!time_have_x_hundredths_passed_since(15, level->last_bomb)) {
            bomb = 0;
        }

        if (bomb) {
            level->last_bomb = time_get_time_ms();

            thing_place_bomb(level, player, player->x, player->y);
        }
    }

    if (rope) {
        if (!time_have_x_hundredths_passed_since(15, level->last_rope)) {
            rope = 0;
        }

        if (rope) {
            level->last_rope = time_get_time_ms();

            thing_place_ropetop(level, player, player->x, player->y);
        }
    }

    if (torch) {
        if (!time_have_x_hundredths_passed_since(15, level->last_torch)) {
            torch = 0;
        }

        if (torch) {
            level->last_torch = time_get_time_ms();

            thing_place_torch(level, player, player->x, player->y);
        }
    }

    /*
     * If we hit a side wall when falling, slow the fall.
     */
    if (thing_hit_solid_obstacle(level, player, x + player->momentum, y)) {
        level->last_hit_obstacle = time_get_time_ms();

        if (player->fall_speed) {
            player->fall_speed *= wall_friction;
        }

        player->momentum = 0;
    }

    double lr_delta = player->momentum;
    double ud_delta = 0.1;

    x += lr_delta;
    y -= (double)up * ud_delta;
    y += (double)down * ud_delta;

    thing_move(level, player, x, y, up, down, left, right, fire);

    if (jump) {
        level->last_jumped = time_get_time_ms();
    }

#endif

    double d = 0.1;
    if (left) {
        player->move_delta(fpoint(-d, 0));
    }
    if (right) {
        player->move_delta(fpoint(d, 0));
    }
}
