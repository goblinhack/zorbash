//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_popup.h"
#include "my_game_notice.h"

static int last_vert_scroll_offset = -1;
static WidPopup *game_config_keyboard_window;

//
// Check for saving keys to config can fit
//
static_assert(sizeof(SDL_Scancode) <= sizeof(game->config.key_move_left));

static void game_config_check_for_conflicts (SDL_Scancode code)
{_
    if (game->config.key_action0) {
        if (game->config.key_action0 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action0");
            game->config.key_action0 = 0;
        }
    }
    if (game->config.key_action1) {
        if (game->config.key_action1 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action1");
            game->config.key_action1 = 0;
        }
    }
    if (game->config.key_action2) {
        if (game->config.key_action2 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action2");
            game->config.key_action2 = 0;
        }
    }
    if (game->config.key_action3) {
        if (game->config.key_action3 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action3");
            game->config.key_action3 = 0;
        }
    }
    if (game->config.key_action4) {
        if (game->config.key_action4 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action4");
            game->config.key_action4 = 0;
        }
    }
    if (game->config.key_action5) {
        if (game->config.key_action5 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action5");
            game->config.key_action5 = 0;
        }
    }
    if (game->config.key_action6) {
        if (game->config.key_action6 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action6");
            game->config.key_action6 = 0;
        }
    }
    if (game->config.key_action7) {
        if (game->config.key_action7 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action7");
            game->config.key_action7 = 0;
        }
    }
    if (game->config.key_action8) {
        if (game->config.key_action8 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action8");
            game->config.key_action8 = 0;
        }
    }
    if (game->config.key_action9) {
        if (game->config.key_action9 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key action9");
            game->config.key_action9 = 0;
        }
    }
    if (game->config.key_attack) {
        if (game->config.key_attack == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key attack");
            game->config.key_attack = 0;
        }
    }
    if (game->config.key_drop) {
        if (game->config.key_drop == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key drop");
            game->config.key_drop = 0;
        }
    }
    if (game->config.key_help) {
        if (game->config.key_help == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key help");
            game->config.key_help = 0;
        }
    }
    if (game->config.key_jump) {
        if (game->config.key_jump == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key jump");
            game->config.key_jump = 0;
        }
    }
    if (game->config.key_load) {
        if (game->config.key_load == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key load");
            game->config.key_load = 0;
        }
    }
    if (game->config.key_map_down) {
        if (game->config.key_map_down == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key map down");
            game->config.key_map_down = 0;
        }
    }
    if (game->config.key_map_left) {
        if (game->config.key_map_left == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key map left");
            game->config.key_map_left = 0;
        }
    }
    if (game->config.key_map_right) {
        if (game->config.key_map_right == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key map right");
            game->config.key_map_right = 0;
        }
    }
    if (game->config.key_map_up) {
        if (game->config.key_map_up == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key map up");
            game->config.key_map_up = 0;
        }
    }
    if (game->config.key_move_down) {
        if (game->config.key_move_down == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key move down");
            game->config.key_move_down = 0;
        }
    }
    if (game->config.key_move_left) {
        if (game->config.key_move_left == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key move left");
            game->config.key_move_left = 0;
        }
    }
    if (game->config.key_move_right) {
        if (game->config.key_move_right == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key move right");
            game->config.key_move_right = 0;
        }
    }
    if (game->config.key_move_up) {
        if (game->config.key_move_up == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key move up");
            game->config.key_move_up = 0;
        }
    }
    if (game->config.key_pause) {
        if (game->config.key_pause == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key pause");
            game->config.key_pause = 0;
        }
    }
    if (game->config.key_quit) {
        if (game->config.key_quit == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key quit");
            game->config.key_quit = 0;
        }
    }
    if (game->config.key_save) {
        if (game->config.key_save == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key save");
            game->config.key_save = 0;
        }
    }
    if (game->config.key_screenshot) {
        if (game->config.key_screenshot == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key screenshot");
            game->config.key_screenshot = 0;
        }
    }
    if (game->config.key_throw) {
        if (game->config.key_throw == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key throw");
            game->config.key_throw = 0;
        }
    }
    if (game->config.key_unused1) {
        if (game->config.key_unused1 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key unused1");
            game->config.key_unused1 = 0;
        }
    }
    if (game->config.key_unused2) {
        if (game->config.key_unused2 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key unused2");
            game->config.key_unused2 = 0;
        }
    }
    if (game->config.key_unused3) {
        if (game->config.key_unused3 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key unused3");
            game->config.key_unused3 = 0;
        }
    }
    if (game->config.key_unused4) {
        if (game->config.key_unused4 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key unused4");
            game->config.key_unused4 = 0;
        }
    }
    if (game->config.key_unused5) {
        if (game->config.key_unused5 == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key unused5");
            game->config.key_unused5 = 0;
        }
    }
    if (game->config.key_eat    ) {
        if (game->config.key_eat     == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key unused6");
            game->config.key_eat     = 0;
        }
    }
    if (game->config.key_use) {
        if (game->config.key_use == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key use");
            game->config.key_use = 0;
        }
    }
    if (game->config.key_wait) {
        if (game->config.key_wait == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key wait");
            game->config.key_wait = 0;
        }
    }
    if (game->config.key_zoom_in) {
        if (game->config.key_zoom_in == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key zoom in");
            game->config.key_zoom_in = 0;
        }
    }
    if (game->config.key_zoom_out) {
        if (game->config.key_zoom_out == code) {
            MINICON("%%fg=orange$Conflicting key, disabling key zoom out");
            game->config.key_zoom_out = 0;
        }
    }
}

static void game_config_keyboard_destroy (void)
{_
    auto w = game_config_keyboard_window->wid_text_area->wid_vert_scroll;
    last_vert_scroll_offset = wid_get_tl_y(w) - wid_get_tl_y(w->parent);

    delete game_config_keyboard_window;
    game_config_keyboard_window = nullptr;
    game->soft_unpause();
}

uint8_t game_config_keyboard_cancel (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: reload config");
    game->load_config();
    game_config_keyboard_destroy();
    if (game->started) {
        //
        // Back to the game
        //
    } else {
        game->config_top_select();
    }
    return (true);
}

uint8_t game_config_keyboard_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: save config");
    game->save_config();
    game_config_keyboard_destroy();
    if (game->started) {
        //
        // Back to the game
        //
    } else {
        game->config_top_select();
    }
    return (true);
}

uint8_t game_config_keyboard_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_keyboard_destroy();
    if (game->started) {
        //
        // Back to the game
        //
    } else {
        game->config_top_select();
    }
    return (true);
}

static void game_config_key_move_left_set (SDL_Scancode code)
{_
    game->config.key_move_left = 0;
    game_config_check_for_conflicts(code);
    game->config.key_move_left = code;
    game->config_keyboard_select();
}

static void game_config_key_move_right_set (SDL_Scancode code)
{_
    game->config.key_move_right = 0;
    game_config_check_for_conflicts(code);
    game->config.key_move_right = code;
    game->config_keyboard_select();
}

static void game_config_key_move_up_set (SDL_Scancode code)
{_
    game->config.key_move_up = 0;
    game_config_check_for_conflicts(code);
    game->config.key_move_up = code;
    game->config_keyboard_select();
}

static void game_config_key_move_down_set (SDL_Scancode code)
{_
    game->config.key_move_down = 0;
    game_config_check_for_conflicts(code);
    game->config.key_move_down = code;
    game->config_keyboard_select();
}

static void game_config_key_map_left_set (SDL_Scancode code)
{_
    game->config.key_map_left = 0;
    game_config_check_for_conflicts(code);
    game->config.key_map_left = code;
    game->config_keyboard_select();
}

static void game_config_key_map_right_set (SDL_Scancode code)
{_
    game->config.key_map_right = 0;
    game_config_check_for_conflicts(code);
    game->config.key_map_right = code;
    game->config_keyboard_select();
}

static void game_config_key_map_up_set (SDL_Scancode code)
{_
    game->config.key_map_up = 0;
    game_config_check_for_conflicts(code);
    game->config.key_map_up = code;
    game->config_keyboard_select();
}

static void game_config_key_map_down_set (SDL_Scancode code)
{_
    game->config.key_map_down = 0;
    game_config_check_for_conflicts(code);
    game->config.key_map_down = code;
    game->config_keyboard_select();
}

static void game_config_key_attack_set (SDL_Scancode code)
{_
    game->config.key_attack = 0;
    game_config_check_for_conflicts(code);
    game->config.key_attack = code;
    game->config_keyboard_select();
}

static void game_config_key_wait_set (SDL_Scancode code)
{_
    game->config.key_wait = 0;
    game_config_check_for_conflicts(code);
    game->config.key_wait = code;
    game->config_keyboard_select();
}

static void game_config_key_jump_set (SDL_Scancode code)
{_
    game->config.key_jump = 0;
    game_config_check_for_conflicts(code);
    game->config.key_jump = code;
    game->config_keyboard_select();
}

static void game_config_key_drop_set (SDL_Scancode code)
{_
    game->config.key_drop = 0;
    game_config_check_for_conflicts(code);
    game->config.key_drop = code;
    game->config_keyboard_select();
}

static void game_config_key_use_set (SDL_Scancode code)
{_
    game->config.key_use = 0;
    game_config_check_for_conflicts(code);
    game->config.key_use = code;
    game->config_keyboard_select();
}

static void game_config_key_eat_set (SDL_Scancode code)
{_
    game->config.key_eat = 0;
    game_config_check_for_conflicts(code);
    game->config.key_eat = code;
    game->config_keyboard_select();
}

static void game_config_key_action0_set (SDL_Scancode code)
{_
    game->config.key_action0 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action0 = code;
    game->config_keyboard_select();
}

static void game_config_key_action1_set (SDL_Scancode code)
{_
    game->config.key_action1 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action1 = code;
    game->config_keyboard_select();
}

static void game_config_key_action2_set (SDL_Scancode code)
{_
    game->config.key_action2 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action2 = code;
    game->config_keyboard_select();
}

static void game_config_key_action3_set (SDL_Scancode code)
{_
    game->config.key_action3 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action3 = code;
    game->config_keyboard_select();
}

static void game_config_key_action4_set (SDL_Scancode code)
{_
    game->config.key_action4 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action4 = code;
    game->config_keyboard_select();
}

static void game_config_key_action5_set (SDL_Scancode code)
{_
    game->config.key_action5 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action5 = code;
    game->config_keyboard_select();
}

static void game_config_key_action6_set (SDL_Scancode code)
{_
    game->config.key_action6 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action6 = code;
    game->config_keyboard_select();
}

static void game_config_key_action7_set (SDL_Scancode code)
{_
    game->config.key_action7 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action7 = code;
    game->config_keyboard_select();
}

static void game_config_key_action8_set (SDL_Scancode code)
{_
    game->config.key_action8 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action8 = code;
    game->config_keyboard_select();
}

static void game_config_key_action9_set (SDL_Scancode code)
{_
    game->config.key_action9 = 0;
    game_config_check_for_conflicts(code);
    game->config.key_action9 = code;
    game->config_keyboard_select();
}

static void game_config_key_save_set (SDL_Scancode code)
{_
    game->config.key_save = 0;
    game_config_check_for_conflicts(code);
    game->config.key_save = code;
    game->config_keyboard_select();
}

static void game_config_key_load_set (SDL_Scancode code)
{_
    game->config.key_load = 0;
    game_config_check_for_conflicts(code);
    game->config.key_load = code;
    game->config_keyboard_select();
}

static void game_config_key_zoom_in_set (SDL_Scancode code)
{_
    game->config.key_zoom_in = 0;
    game_config_check_for_conflicts(code);
    game->config.key_zoom_in = code;
    game->config_keyboard_select();
}

static void game_config_key_zoom_out_set (SDL_Scancode code)
{_
    game->config.key_zoom_out = 0;
    game_config_check_for_conflicts(code);
    game->config.key_zoom_out = code;
    game->config_keyboard_select();
}

static void game_config_key_pause_set (SDL_Scancode code)
{_
    game->config.key_pause = 0;
    game_config_check_for_conflicts(code);
    game->config.key_pause = code;
    game->config_keyboard_select();
}

static void game_config_key_help_set (SDL_Scancode code)
{_
    game->config.key_help = 0;
    game_config_check_for_conflicts(code);
    game->config.key_help = code;
    game->config_keyboard_select();
}

static void game_config_key_quit_set (SDL_Scancode code)
{_
    game->config.key_quit = 0;
    game_config_check_for_conflicts(code);
    game->config.key_quit = code;
    game->config_keyboard_select();
}

static void game_config_key_screenshot_set (SDL_Scancode code)
{_
    game->config.key_screenshot = 0;
    game_config_check_for_conflicts(code);
    game->config.key_screenshot = code;
    game->config_keyboard_select();
}

static void grab_key (void)
{_
    game_notice("Press any key");
    g_grab_next_key = true;
}

uint8_t game_config_keyboard_profile_arrow_keys (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config.key_move_up    = SDL_SCANCODE_UP;
    game->config.key_move_left  = SDL_SCANCODE_LEFT;
    game->config.key_move_down  = SDL_SCANCODE_DOWN;
    game->config.key_move_right = SDL_SCANCODE_RIGHT;
    game->config.key_map_up     = SDL_SCANCODE_W;
    game->config.key_map_left   = SDL_SCANCODE_A;
    game->config.key_map_down   = SDL_SCANCODE_S;
    game->config.key_map_right  = SDL_SCANCODE_D;
    game->config_keyboard_select();

    return (true);
}

uint8_t game_config_keyboard_profile_wasd (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config.key_move_up    = SDL_SCANCODE_W;
    game->config.key_move_left  = SDL_SCANCODE_A;
    game->config.key_move_down  = SDL_SCANCODE_S;
    game->config.key_move_right = SDL_SCANCODE_D;
    game->config.key_map_up     = SDL_SCANCODE_UP;
    game->config.key_map_left   = SDL_SCANCODE_LEFT;
    game->config.key_map_down   = SDL_SCANCODE_DOWN;
    game->config.key_map_right  = SDL_SCANCODE_RIGHT;
    game->config_keyboard_select();

    return (true);
}

uint8_t game_config_key_move_left (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_left_set;
    return (true);
}

uint8_t game_config_key_move_right (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_right_set;
    return (true);
}

uint8_t game_config_key_move_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_up_set;
    return (true);
}

uint8_t game_config_key_move_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_down_set;
    return (true);
}

uint8_t game_config_key_map_left (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_left_set;
    return (true);
}

uint8_t game_config_key_map_right (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_right_set;
    return (true);
}

uint8_t game_config_key_map_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_up_set;
    return (true);
}

uint8_t game_config_key_map_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_down_set;
    return (true);
}

uint8_t game_config_key_attack (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_attack_set;
    return (true);
}

uint8_t game_config_key_wait (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_wait_set;
    return (true);
}

uint8_t game_config_key_jump (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_jump_set;
    return (true);
}

uint8_t game_config_key_drop (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_drop_set;
    return (true);
}

uint8_t game_config_key_use (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_use_set;
    return (true);
}

uint8_t game_config_key_eat (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_eat_set;
    return (true);
}

uint8_t game_config_key_action0 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action0_set;
    return (true);
}

uint8_t game_config_key_action1 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action1_set;
    return (true);
}

uint8_t game_config_key_action2 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action2_set;
    return (true);
}

uint8_t game_config_key_action3 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action3_set;
    return (true);
}

uint8_t game_config_key_action4 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action4_set;
    return (true);
}

uint8_t game_config_key_action5 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action5_set;
    return (true);
}

uint8_t game_config_key_action6 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action6_set;
    return (true);
}

uint8_t game_config_key_action7 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action7_set;
    return (true);
}

uint8_t game_config_key_action8 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action8_set;
    return (true);
}

uint8_t game_config_key_action9 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_action9_set;
    return (true);
}

uint8_t game_config_key_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_save_set;
    return (true);
}

uint8_t game_config_key_load (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_load_set;
    return (true);
}

uint8_t game_config_key_zoom_in (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_zoom_in_set;
    return (true);
}

uint8_t game_config_key_zoom_out (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_zoom_out_set;
    return (true);
}

uint8_t game_config_key_pause (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_pause_set;
    return (true);
}

uint8_t game_config_key_help (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_help_set;
    return (true);
}

uint8_t game_config_key_quit (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_quit_set;
    return (true);
}

uint8_t game_config_key_screenshot (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_screenshot_set;
    return (true);
}

uint8_t game_config_keyboard_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case UI_CONSOLE_KEY1:
                    case UI_CONSOLE_KEY2:
                    case UI_CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case 'b':
                    case SDLK_ESCAPE:
                        game_config_keyboard_cancel(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_keyboard_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case UI_CONSOLE_KEY1:
                    case UI_CONSOLE_KEY2:
                    case UI_CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                }
            }
        }
    }

    return (true);
}

void Game::config_keyboard_select (void)
{_
    game_notice_destroy();

    if (game_config_keyboard_window) {
        game_config_keyboard_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = make_point(m - UI_WID_POPUP_WIDTH_WIDEST / 2,
                          UI_MINICON_VIS_HEIGHT + 2);
    point br = make_point(m + UI_WID_POPUP_WIDTH_WIDEST / 2,
                          UI_ACTIONBAR_TL_Y - 2);
    auto width = br.x - tl.x;

    game_config_keyboard_window =
                    new WidPopup(tl, br, nullptr, "ui_popup_widest",
                                 false, true);
    {_
        Widp w = game_config_keyboard_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_keyboard_key_up);
        wid_set_on_key_down(w, game_config_keyboard_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "The keys of mighty power");

        point tl = make_point(0, y_at);
        point br = make_point(width - 2, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "The keys of mighty power");
    }

    y_at = 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = make_point(0, y_at);
        point br = make_point(7, y_at + 2);
        wid_set_shape_square(w);
        wid_set_style(w, UI_WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_back);
        wid_set_pos(w, tl, br);
        if (started) {
            wid_set_text(w, "Resume");
        } else {
            wid_set_text(w, "Back");
        }
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = make_point(width - 17, y_at);
        point br = make_point(width - 12, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_config_keyboard_save);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Save");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Cancel");

        point tl = make_point(width - 10, y_at);
        point br = make_point(width - 3, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_config_keyboard_cancel);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Cancel");
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "");

        point tl = make_point(0, y_at);
        point br = make_point(45, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_profile_wasd);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use W,A,S,D for moving, arrow keys for map");
    }
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "");

        point tl = make_point(0, y_at);
        point br = make_point(45, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_profile_arrow_keys);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use arrow keys for moving, W,A,S,D for map");
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // Move up
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move up");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_text(w, "Move up");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_up));
        wid_set_on_mouse_up(w, game_config_key_move_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move left
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move left");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move left");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_left));
        wid_set_on_mouse_up(w, game_config_key_move_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move down
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move down");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move down");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_down));
        wid_set_on_mouse_up(w, game_config_key_move_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move right
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move right");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move right");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_right));
        wid_set_on_mouse_up(w, game_config_key_move_right);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // Map up
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map up");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map up");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_up));
        wid_set_on_mouse_up(w, game_config_key_map_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map left
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map left");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map left");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_left));
        wid_set_on_mouse_up(w, game_config_key_map_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map down
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map down");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map down");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_down));
        wid_set_on_mouse_up(w, game_config_key_map_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map right
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map right");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map right");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_right));
        wid_set_on_mouse_up(w, game_config_key_map_right);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // attack
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Attack");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Attack");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_attack));
        wid_set_on_mouse_up(w, game_config_key_attack);
    }
    ///////////////////////////////////////////////////////////////////////
    // wait
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Wait");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Wait / pass time");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_wait));
        wid_set_on_mouse_up(w, game_config_key_wait);
    }
    ///////////////////////////////////////////////////////////////////////
    // jump
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "jump");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Jump");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
        SDL_GetScancodeName((SDL_Scancode)game->config.key_jump));
        wid_set_on_mouse_up(w, game_config_key_jump);
    }
    ///////////////////////////////////////////////////////////////////////
    // drop
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Drop");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Drop");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_drop));
        wid_set_on_mouse_up(w, game_config_key_drop);
    }
    ///////////////////////////////////////////////////////////////////////
    // use
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Use");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Use");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_use));
        wid_set_on_mouse_up(w, game_config_key_use);
    }
    ///////////////////////////////////////////////////////////////////////
    // eat
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Eat");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Eat");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_eat));
        wid_set_on_mouse_up(w, game_config_key_eat);
    }
    ///////////////////////////////////////////////////////////////////////
    // action0
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 0");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 0");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action0));
        wid_set_on_mouse_up(w, game_config_key_action0);
    }
    ///////////////////////////////////////////////////////////////////////
    // action1
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 1");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 1");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action1));
        wid_set_on_mouse_up(w, game_config_key_action1);
    }
    ///////////////////////////////////////////////////////////////////////
    // action2
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 2");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 2");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action2));
        wid_set_on_mouse_up(w, game_config_key_action2);
    }
    ///////////////////////////////////////////////////////////////////////
    // action3
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 3");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 3");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action3));
        wid_set_on_mouse_up(w, game_config_key_action3);
    }
    ///////////////////////////////////////////////////////////////////////
    // action4
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 4");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 4");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action4));
        wid_set_on_mouse_up(w, game_config_key_action4);
    }
    ///////////////////////////////////////////////////////////////////////
    // action5
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 5");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 5");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action5));
        wid_set_on_mouse_up(w, game_config_key_action5);
    }
    ///////////////////////////////////////////////////////////////////////
    // action6
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 6");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 6");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action6));
        wid_set_on_mouse_up(w, game_config_key_action6);
    }
    ///////////////////////////////////////////////////////////////////////
    // action7
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 7");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 7");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action7));
        wid_set_on_mouse_up(w, game_config_key_action7);
    }
    ///////////////////////////////////////////////////////////////////////
    // action8
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 8");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 8");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action8));
        wid_set_on_mouse_up(w, game_config_key_action8);
    }
    ///////////////////////////////////////////////////////////////////////
    // action9
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inventory action 9");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inventory action 9");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_action9));
        wid_set_on_mouse_up(w, game_config_key_action9);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // save
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Save game");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_save));
        wid_set_on_mouse_up(w, game_config_key_save);
    }
    ///////////////////////////////////////////////////////////////////////
    // load
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "load");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Load game");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_load));
        wid_set_on_mouse_up(w, game_config_key_load);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // zoom_in
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "zoom_in");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Zoom in");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_zoom_in));
        wid_set_on_mouse_up(w, game_config_key_zoom_in);
    }
    ///////////////////////////////////////////////////////////////////////
    // zoom_out
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "zoom_out");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Zoom out");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_zoom_out));
        wid_set_on_mouse_up(w, game_config_key_zoom_out);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // pause
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "pause");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Pause game");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_pause));
        wid_set_on_mouse_up(w, game_config_key_pause);
    }
    ///////////////////////////////////////////////////////////////////////
    // quit
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "quit");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Quit");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_quit));
        wid_set_on_mouse_up(w, game_config_key_quit);
    }
    ///////////////////////////////////////////////////////////////////////
    // screenshot
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Take a screenshot");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Take a screenshot");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_screenshot));
        wid_set_on_mouse_up(w, game_config_key_screenshot);
    }
    ///////////////////////////////////////////////////////////////////////
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 1;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "help");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2,y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "This useless help");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = make_point(width / 2 + 8, y_at);
        point br = make_point(width / 2 + 21,y_at);
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_help));
        wid_set_on_mouse_up(w, game_config_key_help);
    }

    wid_update(game_config_keyboard_window->wid_text_area->wid_text_area);

    if (last_vert_scroll_offset != -1) {
        auto w = game_config_keyboard_window->wid_text_area->wid_vert_scroll;
        wid_move_to_y_off(w, last_vert_scroll_offset);
    }
}
