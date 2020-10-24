//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_minicon.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_game.h"
#include "my_thing.h"

static void wid_minicon_wid_create(void);

Widp wid_minicon_container {};
Widp wid_minicon_vert_scroll {};
Widp wid_minicon_input_line {};
Widp wid_minicon_window {};

static std::wstring last_msg;
static int last_msg_count;

static std::map< unsigned int, std::wstring > wid_minicon_lines;

void wid_minicon_fini (void)
{_
    wid_destroy(&wid_minicon_container);
    wid_destroy(&wid_minicon_vert_scroll);
    wid_destroy(&wid_minicon_input_line);
    wid_destroy(&wid_minicon_window);
}

uint8_t wid_minicon_init (void)
{_
    wid_minicon_wid_create();
    wid_not_visible(wid_minicon_window);

    last_msg = L"";
    last_msg_count = 0;

    return (true);
}

//
// Key down etc...
//
uint8_t wid_minicon_input (Widp w, const SDL_KEYSYM *key)
{_
    if (!game) {
        return false;
    }

    auto level = game->level;
    if (!level) {
        return false;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_zoom_out) {
        CON("USERCFG: zoom out");
        config_gfx_zoom_out();
        return true;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_zoom_in) {
        MINICON("Zoom in");
        config_gfx_zoom_in();
        return true;
    }

    //
    // Events after this cannot be invoked when dead
    //
    auto player = level->player;
    if (player && player->is_dead) {
        return false;
    }

    //
    // Stop rapid pickup/drop events if particles are still in progress
    //
    if (player->particle_anim_exists()) {
        return false;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_load) {
        CON("USERCFG: loading game");
        game->load_select();
        return true;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_save) {
        CON("USERCFG: saving the game");
        game->save_select();
        return true;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_pause) {
        MINICON("Pausing the game");
        CON("USERCFG: pausing the game");
        game->pause_select();
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_help) {
        game->config_keyboard_select();
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_quit) {
        game->quit_select();
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action0) {
        level->actionbar_select(0);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action1) {
        level->actionbar_select(1);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action2) {
        level->actionbar_select(2);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action3) {
        level->actionbar_select(3);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action4) {
        level->actionbar_select(4);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action5) {
        level->actionbar_select(5);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action6) {
        level->actionbar_select(6);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action7) {
        level->actionbar_select(7);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action8) {
        level->actionbar_select(8);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_action9) {
        level->actionbar_select(9);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_drop) {
	auto what = level->actionbar_get();
	if (what) {
	    if (player->drop(what)) {
                game->tick_begin("drop");
            }
        }
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_use) {
        auto what = level->actionbar_get();
        if (what) {
            player->use(what);
        }
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_eat) {
        auto what = level->actionbar_get();
        if (what) {
            player->use(what);
        }
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_throw) {
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_gfx_mode) {
        g_opt_ascii_mode = !g_opt_ascii_mode;
        if (g_opt_ascii_mode) {
            MINICON("Switch to tiled mode");
            game->config.gfx_zoom = 1;
        } else {
            MINICON("Switch to ascii mode");
            game->config.gfx_zoom = 3;
        }
        config_update_all();

        //
        // Looks like a nice transition
        //
        game->level->timestamp_fade_in_begin = time_get_time_ms_cached();

        return true;
    }

    return false;
}

//
// Scroll back to the bottom of the screen.
//
static void wid_minicon_reset_scroll (void)
{_
    if (!wid_minicon_vert_scroll) {
        return;
    }

    wid_move_to_bottom(wid_minicon_vert_scroll);
}

static void wid_minicon_scroll (Widp w, std::wstring str)
{_
    Widp tmp {};

    wid_scroll_text(w);

    //
    // Get the wid on the bottom of the list/screen.
    //
    tmp = wid_get_head(w);
    if (tmp) {
        wid_set_text(tmp, str);
    }
}

static void wid_minicon_replace (Widp w, std::wstring str)
{_
    Widp tmp {};

    //
    // Get the wid on the bottom of the list/screen.
    //
    tmp = wid_get_head(w);
    if (tmp) {
        wid_set_text(tmp, str);
    }
}

//
// Log a message to the minicon
//
static void wid_minicon_log_ (std::wstring s)
{_
    static int32_t log_wid_minicon_buffered_lines;

    wid_minicon_reset_scroll();

    //
    // Before the minicon is ready, we buffer the logs.
    //
    if (!wid_minicon_input_line) {
        auto result = wid_minicon_lines.insert(
                        std::make_pair(log_wid_minicon_buffered_lines++, s));

        if (result.second == false) {
            DIE("wid minicon lines insert name [%s] failed",
                wstring_to_string(s).c_str());
        }

        return;
    }

    //
    // Flush the logs now the minicon exists.
    //
    wid_minicon_flush();

    if (last_msg == s) {
        s = last_msg + L" (x" + std::to_wstring(last_msg_count + 2) + L")";
        last_msg_count++;
        wid_minicon_replace(wid_minicon_input_line, s);
    } else {
        last_msg = s;
        last_msg_count = 0;
        wid_minicon_scroll(wid_minicon_input_line, s);
    }
}

void wid_minicon_flush (void)
{_
    auto iter = wid_minicon_lines.begin();

    while (iter != wid_minicon_lines.end()) {
        wid_minicon_scroll(wid_minicon_input_line, iter->second);
        iter = wid_minicon_lines.erase(iter);
    }

    wid_minicon_reset_scroll();
}

//
// Log a message to the minicon
//
void wid_minicon_log (std::string s)
{_
    int chars_per_line = UI_MINICON_WIDTH;

    auto d = split(s, chars_per_line);

    if (d) {
        for (const auto& c : *d) {
            wid_minicon_log_(string_to_wstring(c));
        }
    }
}

//
// Log a message to the minicon
//
void wid_minicon_log (std::wstring s)
{_
    int chars_per_line = UI_MINICON_WIDTH;

    auto d = split(s, chars_per_line);

    if (d) {
        for (const auto& c : *d) {
            wid_minicon_log_(c);
        }
    }
}

//
// Create the minicon
//
static void wid_minicon_wid_create (void)
{_
    int h = UI_MINICON_VIS_HEIGHT;

    {
        point tl = make_point(0, 0);
        point br = make_point(UI_MINICON_VIS_WIDTH - 1, h);

        wid_minicon_window = wid_new_square_window("wid minicon");
        wid_set_name(wid_minicon_window, "wid minicon window");
        wid_set_pos(wid_minicon_window, tl, br);
        wid_set_shape_none(wid_minicon_window);
        wid_set_on_key_down(wid_minicon_window, wid_minicon_input);
        wid_set_ignore_scroll_events(wid_minicon_window, true);
    }

    {
        point tl = make_point(0, 0);
        point br = make_point(UI_MINICON_VIS_WIDTH - 1, h);

        wid_minicon_container = wid_new_container(wid_minicon_window,
                                                  "wid minicon container");
        wid_set_pos(wid_minicon_container, tl, br);
        wid_set_shape_square(wid_minicon_container);
        wid_set_style(wid_minicon_container, 1);
        color c = GRAY;
        c.a = 150;
        wid_set_color(wid_minicon_container, WID_COLOR_BG, c);
    }

  {
        int32_t row;
        int row_bottom = h - 1;

        Widp child {};
        Widp prev {};

        for (row = 0; row < UI_MINICON_HEIGHT; row++) {
            row_bottom --;
            point tl = make_point(0, row_bottom);
            point br = make_point(UI_MINICON_WIDTH, row_bottom);

            child = wid_new_container(wid_minicon_container, "");

            wid_set_shape_none(child);
            wid_set_pos(child, tl, br);
            wid_set_text_lhs(child, true);

            wid_set_prev(child, prev);
            prev = child;

            if (row == 0) {
                wid_minicon_input_line = child;
            }

            wid_set_color(child, WID_COLOR_TEXT_FG, UI_MINICON_TEXT_COLOR);
            wid_set_color(child, WID_COLOR_BG, COLOR_NONE);
            wid_set_name(child, "minicon output");
        }

        wid_raise(wid_minicon_input_line);
    }

    wid_minicon_vert_scroll =
        wid_new_vert_scroll_bar(wid_minicon_window, "", wid_minicon_container);

    wid_not_visible(wid_get_parent(wid_minicon_vert_scroll));

    wid_update(wid_minicon_window);
}

std::vector<std::wstring> wid_minicon_serialize (void)
{_
    std::vector<std::wstring> r;
    auto tmp = wid_get_head(wid_minicon_input_line);
    while (tmp) {
        auto s = wid_get_text(tmp);
        if (s.size()) {
            r.push_back(wid_get_text(tmp));
        }
        tmp = wid_get_next(tmp);
    }
    std::reverse(r.begin(), r.end());
    return (r);
}

void wid_minicon_deserialize(std::vector<std::wstring> r)
{_
    for (const auto& s : r) {
        auto tmp = wstring_to_string(s);
        if (tmp.size()) {
            MINICON("%s", tmp.c_str());
        }
    }
}
