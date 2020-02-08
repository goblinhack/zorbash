//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_SDL_H_
#define _MY_SDL_H_

#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>
#include "my_command.h"
typedef int32_t timestamp_t;

uint8_t sdl_init(void);
void sdl_fini(void);
void sdl_loop(void);
void sdl_show_keyboard(void);
void my_sdl_hide_keyboard(void);
void sdl_exit(void);
void sdl_joy_rumble(float strength, timestamp_t ms);

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
    //
    // Not real buttons, faking the left and right fire to be buttons.
    //
    SDL_JOY_BUTTON_LEFT_FIRE                = 30,
    SDL_JOY_BUTTON_RIGHT_FIRE               = 31,
#define SDL_MAX_BUTTONS                     32
};

#if SDL_MAJOR_VERSION == 1 // {
#define SDL_KEYSYM SDL_keysym
#else
#define SDL_KEYSYM SDL_Keysym
#endif // }

struct tokens_t_;
uint8_t sdl_user_exit(struct tokens_t_ *tokens, void *context);
void sdl_mouse_center(void);
void sdl_mouse_warp(int x, int y);

extern uint32_t mouse_down;
extern timestamp_t mouse_down_when;
extern int mouse_x;
extern int mouse_y;
extern int wheel_x;
extern int wheel_y;
extern int mouse_tick;
extern uint8_t sdl_shift_held;

extern int *sdl_joy_axes;
extern int sdl_joy_deadzone;

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
extern bool sdl_grab_next_key;
typedef void(*on_sdl_key_grab_t)(SDL_Scancode);
extern on_sdl_key_grab_t on_sdl_key_grab;

extern std::array<uint8_t, SDL_MAX_BUTTONS> sdl_joy_buttons;
extern void sdl_screenshot(void);
extern uint8_t config_fps_counter_set(tokensp, void *context);
extern void config_gfx_inverted_toggle(void);
extern uint8_t config_gfx_inverted_set(tokensp, void *context);
extern void config_gfx_minimap_toggle(void);
extern uint8_t config_gfx_minimap_set(tokensp, void *context);
extern void config_gfx_show_hidden_toggle(void);
extern uint8_t config_gfx_show_hidden_set(tokensp, void *context);
extern void config_gfx_lights_toggle(void);
extern uint8_t config_gfx_lights_set(tokensp, void *context);
extern void config_gfx_zoom_in(void);
extern void config_gfx_zoom_out(void);
extern void config_gfx_zoom_update(void);
extern void config_update_all(void);
extern uint8_t config_gfx_zoom_set(tokensp, void *context);
extern uint8_t config_gfx_vsync_enable(tokensp, void *context);
extern uint8_t config_debug_mode(tokensp, void *context);
extern uint8_t config_errored(tokensp, void *context);
extern void config_gfx_vsync_update(void);
extern void sdl_flush_display(void);
#endif
