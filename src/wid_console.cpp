//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_console.h"
#include "my_command.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"

static int32_t wid_console_inited;
static int32_t wid_console_exiting;
static void wid_console_wid_create(void);

Widp wid_console_container;
Widp wid_console_vert_scroll;
Widp wid_console_horiz_scroll;

Widp wid_console_input_line;
Widp wid_console_window;

static std::map< unsigned int, std::wstring > wid_console_lines;

void wid_console_fini (void)
{_
    wid_console_exiting = true;

    if (wid_console_inited) {
        wid_console_inited = false;
    }

    //
    // Flush the logs now the console exists.
    //
    auto iter = wid_console_lines.begin();

    while (iter != wid_console_lines.end()) {
        iter = wid_console_lines.erase(iter);
    }
}

uint8_t wid_console_init (void)
{_
    wid_console_inited = true;

    command_add(fps_enable, "set fps [01]", "frames per sec counter");
    command_add(vsync_enable, "set vsync [01]", "vertical sync enable");
    command_add(sdl_user_exit, "quit", "exit game");

    wid_console_wid_create();

    return (true);
}

//
// Scroll back to the bottom of the screen.
//
static void wid_console_reset_scroll (void)
{_
    if (!wid_console_vert_scroll) {
        return;
    }

    wid_move_to_bottom(wid_console_vert_scroll);
}

//
// Log a message to the console
//
static void wid_console_log_ (std::wstring s)
{_
    static int32_t log_wid_console_buffered_lines;

    if (wid_console_exiting) {
        return;
    }

    wid_console_reset_scroll();

    //
    // Before the console is ready, we buffer the logs.
    //
    if (!wid_console_input_line) {
        auto result = wid_console_lines.insert(
                        std::make_pair(log_wid_console_buffered_lines++, s));

        if (result.second == false) {
            DIE("wid console lines insert name [%s] failed", wstring_to_string(s).c_str());
        }

        return;
    }

    //
    // Flush the logs now the console exists.
    //
    auto iter = wid_console_lines.begin();

    while (iter != wid_console_lines.end()) {
        wid_scroll_with_input(wid_console_input_line, iter->second);
        iter = wid_console_lines.erase(iter);
    }

    wid_scroll_with_input(wid_console_input_line, s);
}

//
// Log a message to the console
//
void wid_console_log (std::string s)
{_
    int chars_per_line = CONSOLE_WIDTH;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            wid_console_log_(string_to_wstring(c));
        }
    }
}

//
// Log a message to the console
//
void wid_console_log (std::wstring s)
{_
    int chars_per_line = CONSOLE_WIDTH;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            wid_console_log_(c);
        }
    }
}

//
// Key down etc...
//
uint8_t wid_console_receive_input (Widp w, const SDL_KEYSYM *key)
{_
    wid_console_reset_scroll();

    switch (key->sym) {
        case SDLK_RETURN: {
            break;
        }

        default:
            break;
    }

    //
    // Feed to the general input handler
    //
    return (wid_receive_input(w, key));
}

//
// Create the console
//
static void wid_console_wid_create (void)
{_
    {
        point tl = {0, 0};
        point br = {ASCII_WIDTH - 1, ASCII_HEIGHT - 3};

        wid_console_window = wid_new_square_window("wid_console");
        wid_set_name(wid_console_window, "wid_console window");
        wid_set_pos(wid_console_window, tl, br);
        wid_set_shape_none(wid_console_window);
    }

    {
        point tl = {0, 0};
        point br = {ASCII_WIDTH - 1, ASCII_HEIGHT - 3};

        wid_console_container = wid_new_container(wid_console_window,
                                                  "wid console container");
        wid_set_pos(wid_console_container, tl, br);
        wid_set_shape_none(wid_console_container);
    }

    {
        int32_t row;
        int row_bottom = ASCII_HEIGHT - 4;

        Widp child = 0;
        Widp prev = 0;

        for (row = 0; row < CONSOLE_HEIGHT; row++) {
            row_bottom --;

            point tl = {
                0,
                row_bottom,
            };

            point br = {
                CONSOLE_WIDTH,
                row_bottom,
            };

            child = wid_new_container(wid_console_container, "");

            wid_set_shape_none(child);
            wid_set_pos(child, tl, br);
            wid_set_text_lhs(child, true);

            wid_set_prev(child, prev);
            prev = child;

            if (row == 0) {
                wid_set_on_key_down(child, wid_console_receive_input);

                wid_set_show_cursor(child, true);
                wid_set_name(child, "console input");
                wid_set_focusable(child, 1);
                wid_move_delta(child, 2, 0);
                wid_console_input_line = child;

                Widp prefix = wid_new_container(wid_console_container, "");
                wid_set_pos(prefix, tl, br);
                wid_set_text_lhs(prefix, true);
                wid_set_shape_none(prefix);
                wid_set_text(prefix, L"\u022e");
            } else {
                wid_set_color(child, WID_COLOR_TEXT, CONSOLE_TEXT_COLOR);
                wid_set_name(child, "console output");
            }
        }

        wid_raise(wid_console_input_line);
    }

    wid_console_vert_scroll =
        wid_new_vert_scroll_bar(wid_console_window, "", wid_console_container);
    wid_console_horiz_scroll =
        wid_new_horiz_scroll_bar(wid_console_window, "", wid_console_container);

    wid_hide(wid_get_parent(wid_console_vert_scroll));
    wid_hide(wid_get_parent(wid_console_horiz_scroll));
    wid_hide(wid_console_vert_scroll);
    wid_hide(wid_console_horiz_scroll);

    wid_hide(wid_console_window);

    wid_console_window->ignore_for_mouse_down = true;

    wid_update(wid_console_window);
}
