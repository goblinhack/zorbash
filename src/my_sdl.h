/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_SDL_H_
#define _MY_SDL_H_

#include <SDL.h>
#include <SDL_keyboard.h>
#include "my_command.h"

uint8_t sdl_init(void);
void sdl_fini(void);
void sdl_loop(void);
void sdl_show_keyboard(void);
void my_sdl_hide_keyboard(void);
void sdl_exit(void);
void sdl_joy_rumble(float strength, uint32_t ms);

extern uint8_t sdl_init_video;
extern uint8_t sdl_exiting;

enum {
    SDL_JOY_BUTTON_A,                       // 0
    SDL_JOY_BUTTON_B,                       // 1
    SDL_JOY_BUTTON_X,                       // 2
    SDL_JOY_BUTTON_Y,                       // 3
    SDL_JOY_BUTTON_TOP_LEFT,                // 4
    SDL_JOY_BUTTON_TOP_RIGHT,               // 5
    SDL_JOY_BUTTON_LEFT_STICK_DOWN,         // 6
    SDL_JOY_BUTTON_RIGHT_STICK_DOWN,        // 7
    SDL_JOY_BUTTON_START,                   // 8
    SDL_JOY_BUTTON_XBOX,                    // 9
    SDL_JOY_BUTTON_BACK,                    // 10
    SDL_JOY_BUTTON_UP,                      // 11
    SDL_JOY_BUTTON_DOWN,                    // 12
    SDL_JOY_BUTTON_LEFT,                    // 13
    SDL_JOY_BUTTON_RIGHT,                   // 14
    /*
     * Not real buttons, faking the left and right fire to be buttons.
     */
    SDL_JOY_BUTTON_LEFT_FIRE                = 30,
    SDL_JOY_BUTTON_RIGHT_FIRE               = 31,
#define SDL_MAX_BUTTONS                     32
};

#if SDL_MAJOR_VERSION == 1 /* { */
#define SDL_KEYSYM SDL_keysym
#else
#define SDL_KEYSYM SDL_Keysym
#endif /* } */

struct tokens_t_;
uint8_t sdl_user_exit(struct tokens_t_ *tokens, void *context);
void sdl_mouse_center(void);
void sdl_mouse_warp(int32_t x, int32_t y);

extern uint32_t mouse_down;
extern uint32_t mouse_down_when;
extern int32_t mouse_x;
extern int32_t mouse_y;
extern uint8_t sdl_shift_held;

extern int *sdl_joy_axes;
extern int sdl_joy_deadzone;

extern int joy_index;
extern int joy_axes;
extern int joy_buttons;
extern int joy_balls;

extern int32_t sdl_left_fire;
extern int32_t sdl_right_fire;

extern int32_t sdl_joy1_right;
extern int32_t sdl_joy1_left;
extern int32_t sdl_joy1_down;
extern int32_t sdl_joy1_up;

extern int32_t sdl_joy2_right;
extern int32_t sdl_joy2_left;
extern int32_t sdl_joy2_down;
extern int32_t sdl_joy2_up;

extern uint8_t sdl_joy_buttons[SDL_MAX_BUTTONS];
extern void sdl_screenshot(void);
extern uint8_t fps_enable(tokensp, void *context);
#endif
