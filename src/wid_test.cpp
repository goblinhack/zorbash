/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_test.h"
#include "my_command.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"

static void wid_test_wid_create(void);

widp wid_test_window;

void wid_test_fini (void)
{_
}

uint8_t wid_test_init (void)
{_
    wid_test_wid_create();

    return (true);
}

static uint8_t wid_test_mouse_down (widp w,
                                    int32_t x,
                                    int32_t y,
                                    uint32_t button)
{_
    CON("button %d", button);
    return (true);
}

/*
 * Create the test
 */
static void wid_test_wid_create (void)
{_
    {
        point tl = {ITEMBAR_TL_X, ITEMBAR_TL_Y};
        point br = {ITEMBAR_BR_X, ITEMBAR_BR_Y};
        color c;

        wid_test_window = wid_new_square_window("text container1");
        wid_set_pos(wid_test_window, tl, br);
        wid_set_shape_none(wid_test_window);
        wid_set_style(wid_test_window, 1);
    }

    int x = 0;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {0, 0};
        point br = {ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"0");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "player1.1");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"1");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "key1.1");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"2");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "food_frog1");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"3");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "gem1.1");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"4");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "gem1.2");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"5");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "gem1.3");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"6");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "gem1.4");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"7");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "gem1.5");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"8");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "gem1.6");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"9");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "sword1.1");
    }

    wid_update(wid_test_window);

    {
        point tl = {ASCII_WIDTH - SIDEBAR_WIDTH + 1, 0};
        point br = {ASCII_WIDTH - 1, SIDEBAR_HEIGHT};
        color c;

        wid_test_window = wid_new_square_window("text container2");
        wid_set_pos(wid_test_window, tl, br);
        wid_set_shape_box(wid_test_window);
        wid_set_style(wid_test_window, 0);
    }

    {
        auto w = wid_new_square_button(wid_test_window, "text box2");
        point tl = {1, 1};
        point br = {INNER_SIDEBAR_WIDTH - 1, INNER_SIDEBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 4);
        wid_set_text(w, L"there this is a long string");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "player1.1");
    }

    wid_update(wid_test_window);
}
