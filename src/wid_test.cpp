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

widp wid_itembar;
widp wid_sidebar;

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

        wid_itembar = wid_new_square_window("text container1");
        wid_set_pos(wid_itembar, tl, br);
        wid_set_shape_none(wid_itembar);
        wid_set_style(wid_itembar, 1);
    }

    int x = 0;
    {
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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
        auto w = wid_new_square_button(wid_itembar, "text box2");
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

    wid_update(wid_itembar);

    {
        point tl = {ASCII_WIDTH - SIDEBAR_WIDTH, 0};
        point br = {ASCII_WIDTH - 1, ASCII_HEIGHT};
        color c;

        wid_sidebar = wid_new_square_window("text container2");
        wid_set_pos(wid_sidebar, tl, br);
        wid_set_shape_none(wid_sidebar);
        wid_set_style(wid_sidebar, 0);
    }

    {
        auto w = wid_new_square_button(wid_sidebar, "title box");
        point tl = {0, 0};
        point br = {5, 5};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 4);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_tilename(w, "player1.1");
    }

    {
        auto w = wid_new_square_button(wid_sidebar, "title name");
        point tl = {0, 6};
        point br = {TITLEBAR_WIDTH, 6};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 4);
        wid_set_text(w, L"Ser Hacksalot");
        wid_set_shape_none(w);
    }

    {
        auto w = wid_new_square_button(wid_sidebar, "gold");
        point tl = {7, 5};
        point br = {TITLEBAR_WIDTH, 5};

        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=dollar-icon$%fg=gold$666");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    {
        auto w = wid_new_square_button(wid_sidebar, "weight");
        point tl = {7, 4};
        point br = {TITLEBAR_WIDTH, 4};

        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=CWEIGHT$%fg=green$150%fg=grey$lbs");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    {
        int y_at = 8;
        {
            auto w = wid_new_square_button(wid_sidebar, "health-icon");
            point tl = {0, y_at};
            point br = {1, y_at+1};
            wid_set_pos(w, tl, br);
            wid_set_style(w, -1);
            wid_set_tilename(w, "health5-icon");
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
        {
            auto w = wid_new_square_button(wid_sidebar, "Health");
            point tl = {2, y_at};
            point br = {tl.x + TITLEBAR_WIDTH, tl.y};
            wid_set_pos(w, tl, br);
            wid_set_shape_none(w);
            wid_set_text(w, L"%bg=red$       %bg=black$  10/100");
            wid_set_text_lhs(w, true);
        }
        y_at += 2;
        {
            auto w = wid_new_square_button(wid_sidebar, "armour-icon");
            point tl = {0, y_at};
            point br = {1, y_at+1};
            wid_set_pos(w, tl, br);
            wid_set_style(w, -1);
            wid_set_tilename(w, "armour-icon");
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
        {
            auto w = wid_new_square_button(wid_sidebar, "Armour");
            point tl = {2, y_at};
            point br = {tl.x + SIDEBAR_WIDTH, tl.y};

            wid_set_pos(w, tl, br);
            wid_set_shape_none(w);
            wid_set_text(w, L"%bg=darkolivegreen4$         %bg=black$90/100");
            wid_set_text_lhs(w, true);
        }
        y_at += 2;
        {
            auto w = wid_new_square_button(wid_sidebar, "magic-icon");
            point tl = {0, y_at};
            point br = {1, y_at+1};
            wid_set_pos(w, tl, br);
            wid_set_style(w, -1);
            wid_set_tilename(w, "magic-icon");
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
        {
            auto w = wid_new_square_button(wid_sidebar, "Magic");
            point tl = {2, y_at};
            point br = {tl.x + SIDEBAR_WIDTH, tl.y};

            wid_set_pos(w, tl, br);
            wid_set_shape_none(w);
            wid_set_text(w, L"%bg=darkolivegreen$         %bg=black$90/100");
            wid_set_text_lhs(w, true);
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
        y_at += 2;
        {
            auto w = wid_new_square_button(wid_sidebar, "karma-icon");
            point tl = {0, y_at};
            point br = {1, y_at+1};
            wid_set_pos(w, tl, br);
            wid_set_style(w, -1);
            wid_set_tilename(w, "karma-icon");
        }
        {
            auto w = wid_new_square_button(wid_sidebar, "Karma");
            point tl = {2, y_at};
            point br = {tl.x + SIDEBAR_WIDTH, tl.y};
            wid_set_pos(w, tl, br);
            wid_set_shape_none(w);
            wid_set_text(w, L"%bg=darkolivegreen4$         %bg=black$Good");
            wid_set_text_lhs(w, true);
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
    }

    {
        for (auto y = 0; y < INVENTORY_DOWN ; y++) {
            for (auto x = 0; x < INVENTORY_ACROSS ; x++) {
                int y_at = ASCII_HEIGHT - INVENTORY_ITEM_HEIGHT * (y + 1);
                int x_at = INVENTORY_ITEM_HEIGHT * x;
                auto w = wid_new_square_button(wid_sidebar, "text box2");
                point tl = {x_at, y_at};
                point br = {x_at+INVENTORY_ITEM_WIDTH - 1, y_at + INVENTORY_ITEM_HEIGHT - 1};

                wid_set_pos(w, tl, br);
                wid_set_style(w, 0);
                wid_set_text(w, L"9");
                wid_set_text_lhs(w, true);
                wid_set_text_bot(w, true);
                wid_set_on_m_down(w, wid_test_mouse_down);
                wid_set_tilename(w, "gem1.6");
            }
        }
    }

    wid_update(wid_sidebar);
}
