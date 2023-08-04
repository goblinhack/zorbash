//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SDL_PROTO_HPP_
#define _MY_SDL_PROTO_HPP_

#include <SDL.h>
#include <string>
#include <vector>

bool sdlk_eq(const SDL_Keysym &a, const SDL_Keysym &b);

int sdl_filter_events(void *userdata, SDL_Event *event);
int sdl_get_mouse(void);

SDL_Keysym   sdlk_normalize(SDL_Keysym k);
SDL_Scancode sdlk_to_scancode(const SDL_Keysym &k);

std::string to_string(const SDL_Keysym &k);
std::string to_string_ignoring_mods(const SDL_Keysym &k);

std::vector< uint8_t > sdl_fbo_save(int fbo);

uint8_t config_errored(class Tokens *, void *context);
uint8_t config_fps_counter_set(class Tokens *, void *context);
uint8_t config_debug_set(class Tokens *, void *context);
uint8_t config_game_pix_zoom_set(class Tokens *, void *context);
uint8_t config_gfx_inverted_set(class Tokens *, void *context);
uint8_t config_gfx_monochrome_set(class Tokens *, void *context);
uint8_t config_gfx_lights_set(class Tokens *, void *context);
uint8_t config_gfx_vsync_enable(class Tokens *, void *context);
uint8_t sdl_init(void);

class Tokens;
uint8_t sdl_user_exit(class Tokens *tokens, void *context);

void config_game_pix_zoom_in(void);
void config_game_pix_zoom_out(void);
void config_game_gfx_update(void);
void config_gfx_inverted_toggle(void);
void config_gfx_monochrome_toggle(void);
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
void sdl_joy_rumble(float strength, uint32_t ms);
void sdl_key_repeat_events(void);
void sdl_loop(void);
void sdl_mouse_center(void);
void sdl_mouse_warp(int x, int y);
void sdl_screenshot_do(void);
void sdl_screenshot(void);
void sdl_show_keyboard(void);
void sdl_tick(void);

#endif
