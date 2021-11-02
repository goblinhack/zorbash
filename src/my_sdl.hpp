//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_SDL_HPP_
#define _MY_SDL_HPP_

#include <SDL.h>

#include "my_command.hpp"
#include "my_main.hpp"
#include "my_time.hpp"

extern uint8_t sdl_init_video;
extern uint8_t sdl_exiting;

enum {
  SDL_JOY_BUTTON_A,                // 0
  SDL_JOY_BUTTON_B,                // 1
  SDL_JOY_BUTTON_X,                // 2
  SDL_JOY_BUTTON_Y,                // 3
  SDL_JOY_BUTTON_TOP_LEFT,         // 4
  SDL_JOY_BUTTON_TOP_RIGHT,        // 5
  SDL_JOY_BUTTON_LEFT_STICK_DOWN,  // 6
  SDL_JOY_BUTTON_RIGHT_STICK_DOWN, // 7
  SDL_JOY_BUTTON_START,            // 8
  SDL_JOY_BUTTON_XBOX,             // 9
  SDL_JOY_BUTTON_BACK,             // 10
  SDL_JOY_BUTTON_UP,               // 11
  SDL_JOY_BUTTON_DOWN,             // 12
  SDL_JOY_BUTTON_LEFT,             // 13
  SDL_JOY_BUTTON_RIGHT,            // 14
  //
  // Not real buttons, faking the left and right fire to be buttons.
  //
  SDL_JOY_BUTTON_LEFT_FIRE  = 30,
  SDL_JOY_BUTTON_RIGHT_FIRE = 31,
#define SDL_MAX_BUTTONS 32
};

struct tokens_t_;
uint8_t sdl_user_exit(struct tokens_t_ *tokens, void *context);
void    sdl_mouse_center(void);
void    sdl_mouse_warp(int x, int y);

extern uint32_t mouse_down;
extern int      mouse_x;
extern int      mouse_y;
extern int      wheel_x;
extern int      wheel_y;
extern int      mouse_tick;
extern uint8_t  sdl_shift_held;

extern int *sdl_joy_axes;
extern int  sdl_joy_deadzone;

extern int joy_index;
extern int joy_axes;
extern int joy_buttons;
extern int joy_balls;

extern int sdl_left_fire;
extern int sdl_right_fire;

extern int sdl_joy1_right;
extern int sdl_joy1_left;
extern int sdl_joy1_down;
extern int sdl_joy1_up;

extern int sdl_joy2_right;
extern int sdl_joy2_left;
extern int sdl_joy2_down;
extern int sdl_joy2_up;

extern SDL_Scancode sdl_grabbed_scancode;
extern bool         g_grab_next_key;
typedef void (*on_sdl_key_grab_t)(SDL_Scancode);
extern on_sdl_key_grab_t                      on_sdl_key_grab;
extern std::array< uint8_t, SDL_MAX_BUTTONS > sdl_joy_buttons;

void                   sdl_fbo_load(int fbo, const std::vector< uint8_t > &pixels);
std::vector< uint8_t > sdl_fbo_save(int fbo);
uint8_t                config_errored(tokensp, void *context);
uint8_t                config_fps_counter_set(tokensp, void *context);
uint8_t                config_game_pix_zoom_set(tokensp, void *context);
uint8_t                config_gfx_inverted_set(tokensp, void *context);
uint8_t                config_gfx_lights_set(tokensp, void *context);
uint8_t                config_gfx_minimap_set(tokensp, void *context);
uint8_t                config_gfx_vsync_enable(tokensp, void *context);
uint8_t                sdl_init(void);
void                   config_game_pix_zoom_in(void);
void                   config_game_pix_zoom_out(void);
void                   config_game_pix_zoom_update(void);
void                   config_gfx_inverted_toggle(void);
void                   config_gfx_lights_toggle(void);
void                   config_gfx_minimap_toggle(void);
void                   config_gfx_vsync_update(void);
void                   my_sdl_hide_keyboard(void);
void                   sdl_config_update_all(void);
void                   sdl_exit(void);
void                   sdl_fini(void);
void                   sdl_flush_display(void);
void                   sdl_joy_rumble(float strength, ts_t ms);
void                   sdl_loop(void);
void                   sdl_screenshot_do(void);
void                   sdl_screenshot(void);
void                   sdl_show_keyboard(void);
void                   sdl_fbo_dump(int fbo, const std::string &name);

#endif
