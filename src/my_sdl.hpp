//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_SDL_HPP_
#define _MY_SDL_HPP_

#include <SDL.h>
#include <array>

#include "c_plus_plus_serializer.hpp"
#include "my_command.hpp"
#include "my_main.hpp"
#include "my_time.hpp"

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

typedef struct sdl_t_ {
  int exiting {};
  int held_mouse_x {};
  int held_mouse_y {};
  int init_video {};
  int joy1_down {};
  int joy1_left {};
  int joy1_right {};
  int joy1_up {};
  int joy2_down {};
  int joy2_left {};
  int joy2_right {};
  int joy2_up {};
  int joy_balls {};
  int joy_deadzone {};
  int joy_index {};
  int joy_naxes {};
  int joy_nbuttons {};
  int key_repeat_count {};
  int left_fire {};
  int mouse_tick {};
  int mouse_x {};
  int mouse_y {};
  int right_fire {};
  int shift_held {};
  int wheel_x {};
  int wheel_y {};

  uint32_t mouse_down;
  uint32_t mouse_down_when;
  uint32_t last_mouse_held_down_when {};
  uint32_t mouse_down_ts {};

  SDL_Haptic   *haptic {};
  SDL_Joystick *joy {};

  int                                   *joy_axes {};
  std::array< uint8_t, SDL_MAX_BUTTONS > joy_buttons {};

  typedef void (*on_sdl_key_grab_t)(SDL_Keysym);
  on_sdl_key_grab_t on_sdl_key_grab {};
  SDL_Keysym        grabbed_key {};

  ts_t key_repeat_this_key {};

  SDL_GLContext context {}; // Our opengl context handle
  SDL_Window   *window {};  // Our window handle
} sdl_t;

#define SDL_KEY_REPEAT_HUNDREDTHS_FIRST 20
#define SDL_KEY_REPEAT_HUNDREDTHS_NEXT  10

extern sdl_t sdl;

bool sdlk_eq(const SDL_Keysym &a, const SDL_Keysym &b);

int sdl_filter_events(void *userdata, SDL_Event *event);
int sdl_get_mouse(void);

SDL_Keysym   sdlk_normalize(SDL_Keysym k);
SDL_Scancode sdlk_to_scancode(const SDL_Keysym &k);

std::istream &operator>>(std::istream &in, Bits< SDL_Keysym & > my);
std::ostream &operator<<(std::ostream &out, Bits< const SDL_Keysym & > const my);

std::string to_string(const SDL_Keysym &k);
std::string to_string_ignoring_mods(const SDL_Keysym &k);

std::vector< uint8_t > sdl_fbo_save(int fbo);

uint8_t config_errored(tokensp, void *context);
uint8_t config_fps_counter_set(tokensp, void *context);
uint8_t config_game_pix_zoom_set(tokensp, void *context);
uint8_t config_gfx_inverted_set(tokensp, void *context);
uint8_t config_gfx_lights_set(tokensp, void *context);
uint8_t config_gfx_vsync_enable(tokensp, void *context);
uint8_t sdl_init(void);

struct tokens_t_;
uint8_t sdl_user_exit(struct tokens_t_ *tokens, void *context);

void config_game_pix_zoom_in(void);
void config_game_pix_zoom_out(void);
void config_game_gfx_update(void);
void config_gfx_inverted_toggle(void);
void config_gfx_lights_toggle(void);
void config_gfx_map_mini_toggle(void);
void config_gfx_vsync_update(void);
void sdl_config_update_all(void);
void sdl_display(void);
void sdl_display_reset(void);
void sdl_event(SDL_Event *event, bool &processed_mouse_motion_event);
void sdl_exit(void);
void sdl_fbo_dump(int fbo, const std::string &name);
void sdl_fbo_load(int fbo, const std::vector< uint8_t > &pixels);
void sdl_fini(void);
void sdl_flush_display(bool force = false);
void sdl_joy_rumble(float strength, ts_t ms);
void sdl_key_repeat_events(void);
void sdl_loop(void);
void sdl_mouse_center(void);
void sdl_mouse_warp(int x, int y);
void sdl_screenshot_do(void);
void sdl_screenshot(void);
void sdl_show_keyboard(void);
void sdl_tick(void);

#endif
