//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_sdl.h"
#include <SDL_mixer.h>

Game::Game (std::string appdata)
{_
    this->appdata = appdata;

    saved_dir = appdata + DIR_SEP + "zorbash" + DIR_SEP;
    save_slot = 1;
    save_meta = string_timestamp();
    save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);

    config.key_action0                  = {SDL_SCANCODE_0};
    config.key_action1                  = {SDL_SCANCODE_1};
    config.key_action2                  = {SDL_SCANCODE_2};
    config.key_action3                  = {SDL_SCANCODE_3};
    config.key_action4                  = {SDL_SCANCODE_4};
    config.key_action5                  = {SDL_SCANCODE_5};
    config.key_action6                  = {SDL_SCANCODE_6};
    config.key_action7                  = {SDL_SCANCODE_7};
    config.key_action8                  = {SDL_SCANCODE_8};
    config.key_action9                  = {SDL_SCANCODE_9};
    config.key_attack                   = {SDL_SCANCODE_SPACE};
#ifdef __APPLE__
    //
    // Delete on mac seems to map to backspace...
    //
    config.key_drop                     = {SDL_SCANCODE_BACKSPACE};
#else
    config.key_drop                     = {SDL_SCANCODE_DELETE};
#endif
    config.key_eat                      = {SDL_SCANCODE_E};
    config.key_help                     = {SDL_SCANCODE_H};
    config.key_jump                     = {SDL_SCANCODE_J};
    config.key_load                     = {SDL_SCANCODE_F11};
    config.key_map_down                 = {SDL_SCANCODE_DOWN};
    config.key_map_left                 = {SDL_SCANCODE_LEFT};
    config.key_map_right                = {SDL_SCANCODE_RIGHT};
    config.key_map_up                   = {SDL_SCANCODE_UP};
    config.key_move_down                = {SDL_SCANCODE_S};
    config.key_move_left                = {SDL_SCANCODE_A};
    config.key_move_right               = {SDL_SCANCODE_D};
    config.key_move_up                  = {SDL_SCANCODE_W};
    config.key_pause                    = {SDL_SCANCODE_P};
    config.key_quit                     = {SDL_SCANCODE_Q};
    config.key_save                     = {SDL_SCANCODE_F12};
    config.key_screenshot               = {SDL_SCANCODE_F10};
    config.key_throw                    = {SDL_SCANCODE_T};
    config.key_inventory                = {SDL_SCANCODE_I};
    config.key_console                  = {SDL_SCANCODE_BACKSLASH};
    config.key_unused3                  = 0;
    config.key_unused4                  = 0;
    config.key_unused5                  = 0;
    config.key_use                      = {SDL_SCANCODE_U};
    config.key_wait_or_collect          = {SDL_SCANCODE_PERIOD};
    config.key_zoom_in                  = {SDL_SCANCODE_Z};
    config.key_zoom_out                 = {SDL_SCANCODE_X};
    config.music_volume                 = {MIX_MAX_VOLUME / 2};
    config.sdl_delay                    = 1;
    config.sound_volume                 = {MIX_MAX_VOLUME / 2};
}
