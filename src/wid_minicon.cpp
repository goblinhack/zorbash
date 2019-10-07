//
// Copyright goblinhack@gmail.com
// See the README file for license info.
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

static int32_t wid_minicon_inited;
static int32_t wid_minicon_exiting;
static void wid_minicon_wid_create(void);

Widp wid_minicon_container;
Widp wid_minicon_vert_scroll;
Widp wid_minicon_horiz_scroll;

Widp wid_minicon_input_line;
Widp wid_minicon_window;

static std::map< unsigned int, std::wstring > wid_minicon_lines;

void wid_minicon_fini (void)
{_
    wid_minicon_exiting = true;

    if (wid_minicon_inited) {
        wid_minicon_inited = false;
    }

    //
    // Flush the logs now the minicon exists.
    //
    auto iter = wid_minicon_lines.begin();

    while (iter != wid_minicon_lines.end()) {
        iter = wid_minicon_lines.erase(iter);
    }
}

uint8_t wid_minicon_init (void)
{_
    wid_minicon_inited = true;

    wid_minicon_wid_create();

    return (true);
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

void wid_minicon_scroll (Widp w, std::wstring str)
{_
    Widp tmp;

    wid_scroll_text(w);

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

    if (wid_minicon_exiting) {
        return;
    }

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

    wid_minicon_scroll(wid_minicon_input_line, s);
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
    int chars_per_line = MINICON_WIDTH;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            wid_minicon_log_(string_to_wstring(c));
        }
    }
}

//
// Log a message to the minicon
//
void wid_minicon_log (std::wstring s)
{_
    int chars_per_line = MINICON_WIDTH;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            wid_minicon_log_(c);
        }
    }
}

//
// Create the minicon
//
static void wid_minicon_wid_create (void)
{_
    int h = MINICON_VIS_HEIGHT;

    {
        point tl = {0, 0};
        point br = {MINICON_VIS_WIDTH, h};

        wid_minicon_window = wid_new_square_window("wid_minicon");
        wid_set_name(wid_minicon_window, "wid_minicon window");
        wid_set_pos(wid_minicon_window, tl, br);
        wid_set_shape_none(wid_minicon_window);
    }

    {
        point tl = {0, 0};
        point br = {MINICON_VIS_WIDTH, h};

        wid_minicon_container = wid_new_container(wid_minicon_window,
                                                  "wid minicon container");
        wid_set_pos(wid_minicon_container, tl, br);
        wid_set_shape_none(wid_minicon_container);
    }

  {
        int32_t row;
        int row_bottom = h - 1;

        Widp child = 0;
        Widp prev = 0;

        for (row = 0; row < MINICON_HEIGHT; row++) {
            row_bottom --;
            point tl = {
                0,
                row_bottom,
            };

            point br = {
                MINICON_WIDTH,
                row_bottom,
            };

            child = wid_new_container(wid_minicon_container, "");

            wid_set_shape_none(child);
            wid_set_pos(child, tl, br);
            wid_set_text_lhs(child, true);

            wid_set_prev(child, prev);
            prev = child;

            if (row == 0) {
                wid_minicon_input_line = child;
            }

            wid_set_color(child, WID_COLOR_TEXT, MINICON_TEXT_COLOR);
            wid_set_name(child, "minicon output");
        }

        wid_raise(wid_minicon_input_line);
    }

    wid_minicon_vert_scroll =
        wid_new_vert_scroll_bar(wid_minicon_window, "", wid_minicon_container);
    wid_minicon_horiz_scroll =
        wid_new_horiz_scroll_bar(wid_minicon_window, "", wid_minicon_container);

    wid_hide(wid_get_parent(wid_minicon_vert_scroll));
    wid_hide(wid_get_parent(wid_minicon_horiz_scroll));

    wid_update(wid_minicon_window);
}
