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
#include "my_wid_popup.h"
#include "my_ascii.h"

static void wid_test_wid_create(void);

widp wid_itembar;
widp wid_item_popup;
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
        wid_set_text(w, L"1");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_bg_tilename(w, "food_frog1");
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
        wid_set_bg_tilename(w, "key1.1");
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
        wid_set_bg_tilename(w, "food_frog1");
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
        wid_set_bg_tilename(w, "gem1.1");
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
        wid_set_bg_tilename(w, "gem1.2");
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
        wid_set_bg_tilename(w, "gem1.3");
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
        wid_set_bg_tilename(w, "gem1.4");
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
        wid_set_bg_tilename(w, "gem1.5");
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
        wid_set_bg_tilename(w, "gem1.6");
    }
    x += ITEMBAR_WIDTH;
    {
        auto w = wid_new_square_button(wid_itembar, "text box2");
        point tl = {x, 0};
        point br = {x+ITEMBAR_WIDTH - 1, ITEMBAR_HEIGHT - 1};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 0);
        wid_set_text(w, L"0");
        wid_set_text_lhs(w, true);
        wid_set_text_bot(w, true);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_bg_tilename(w, "sword1.1");
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

    int y_at = 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "zorbash-0");
        point tl = {0, y_at};
        point br = {TITLEBAR_WIDTH - 1, y_at+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "zorbash-0");
    }
    y_at += 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "zorbash-1");
        point tl = {0, y_at};
        point br = {TITLEBAR_WIDTH - 1, y_at+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "zorbash-1");
    }
    y_at += 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "zorbash-2");
        point tl = {0, y_at};
        point br = {TITLEBAR_WIDTH - 1, y_at+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "zorbash-2");
    }
    y_at += 3;

    {
        auto w = wid_new_square_button(wid_sidebar, "title box");
        point tl = {0, y_at};
        point br = {5, y_at + 5};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 4);
        wid_set_on_m_down(w, wid_test_mouse_down);
        wid_set_bg_tilename(w, "player1.pose");
    }

    y_at += 3;
    {
        auto w = wid_new_square_button(wid_sidebar, "title name");
        point tl = {0, y_at + 4};
        point br = {TITLEBAR_WIDTH, y_at + 4};

        wid_set_pos(w, tl, br);
        wid_set_style(w, 4);
        wid_set_text(w, L"Ser Hacksalot");
        wid_set_shape_none(w);
    }

    {
        auto w = wid_new_square_button(wid_sidebar, "gold");
        point tl = {7, y_at-3};
        point br = {TITLEBAR_WIDTH, y_at-3};

        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=dollar-icon$%fg=gold$666");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    {
        auto w = wid_new_square_button(wid_sidebar, "weight");
        point tl = {7, y_at-2};
        point br = {TITLEBAR_WIDTH, y_at-2};

        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=CWEIGHT$%fg=green$150%fg=grey$lbs");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    y_at += 6;
    {
        auto w = wid_new_square_button(wid_sidebar, "health-icon");
        point tl = {0, y_at};
        point br = {2, y_at + 2};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "health5-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "Health-value");
        point tl = {3, y_at + 2};
        point br = {tl.x + TITLEBAR_WIDTH, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);
        wid_set_text(w, L"     10/100");
        wid_set_text_lhs(w, true);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "Health-status-bar");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y + 1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "status-bar-9");
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "health-status");
        point tl = {3, y_at + 2};
        point br = {tl.x + 11, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "health-status");
    }

    y_at += 3;
    {
        auto w = wid_new_square_button(wid_sidebar, "strength-icon");
        point tl = {0, y_at};
        point br = {2, y_at + 2};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "strength-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "strength-value");
        point tl = {3, y_at + 2};
        point br = {tl.x + TITLEBAR_WIDTH, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);
        wid_set_text(w, L"     10/100");
        wid_set_text_lhs(w, true);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "strength-status-bar");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y + 1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "status-bar-9");
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "strength-status");
        point tl = {3, y_at + 2};
        point br = {tl.x + 11, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "strength-status");
    }

    y_at += 3;
    {
        auto w = wid_new_square_button(wid_sidebar, "armour-icon");
        point tl = {0, y_at};
        point br = {2, y_at + 2};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "armour-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "armour-value");
        point tl = {3, y_at + 2};
        point br = {tl.x + SIDEBAR_WIDTH, tl.y};

        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);
        wid_set_text(w, L"     90/100");
        wid_set_text_lhs(w, true);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "armour-status-bar");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y + 1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "status-bar-7");
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "armour-status");
        point tl = {3, y_at + 2};
        point br = {tl.x + 11, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "armour-status");
    }

    y_at += 3;
    {
        auto w = wid_new_square_button(wid_sidebar, "magic-icon");
        point tl = {0, y_at};
        point br = {2, y_at + 2};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "magic-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "magic-value");
        point tl = {3, y_at + 2};
        point br = {tl.x + SIDEBAR_WIDTH, tl.y};

        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);
        wid_set_text(w, L"     90/100");
        wid_set_text_lhs(w, true);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "magic-status-bar");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y + 1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "status-bar-7");
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "magick-status");
        point tl = {3, y_at + 2};
        point br = {tl.x + 11, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "magick-status");
    }

    y_at += 3;
    {
        auto w = wid_new_square_button(wid_sidebar, "karma-icon");
        point tl = {0, y_at};
        point br = {2, y_at + 2};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "karma-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "karma-status-bar");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y + 1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "karma-bar-1");
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "karma-status");
        point tl = {3, y_at + 2};
        point br = {tl.x + 11, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "karma-status");
    }

    y_at += 3;
    {
        auto w = wid_new_square_button(wid_sidebar, "anxiety-icon");
        point tl = {0, y_at};
        point br = {2, y_at + 2};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "anxiety5-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "anxiety-status-bar");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y + 1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "status-bar-1");
    }
    {
        auto w = wid_new_square_button(wid_sidebar, "anxiety-status");
        point tl = {3, y_at + 2};
        point br = {tl.x + 11, tl.y};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "anxiety-status");
    }

    y_at += 4;
    {
        auto w = wid_new_square_button(wid_sidebar, "blessings-0");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "blessings-0");
    }
    y_at += 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "blessings-1");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "blessings-1");
    }
    y_at += 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "curses-0");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "curses-0");
    }
    y_at += 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "curses-1");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "curses-1");
    }
    y_at += 2;
    {
        auto w = wid_new_square_button(wid_sidebar, "curses-2");
        point tl = {3, y_at};
        point br = {tl.x + 11, tl.y+1};
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "curses-2");
    }

    wid_update(wid_sidebar);

#if 0
    {
        point tl = {0, MINICON_VIS_HEIGHT + 2};
        point br = {ITEMBAR_TL_X - 2, ITEMBAR_TL_Y - 2};

        wid_item_popup = wid_new_square_window("text popup window");
        wid_set_pos(wid_item_popup, tl, br);
        wid_set_text(wid_item_popup, L"1");
        wid_update(wid_item_popup);
    }

    {
        fpoint tl = {0, 0};
        fpoint br = {1, 1};

        auto w = wid_new_square_button(wid_item_popup, "text popup");
        wid_set_pos_pct(w, tl, br);
        wid_set_style(w, 2);
        wid_update(w);
        wid_set_text(w, L"1");
    }
#endif

    {
        point tl = {0, MINICON_VIS_HEIGHT + 2};
        point br = {ITEMBAR_TL_X - 2, ITEMBAR_TL_Y - 2};
        auto w = new WidPopup(tl, br);
        w->log("ello1");
        w->log("ello2");
        w->log("ello3");
        w->log("ello4");
        w->log("ello5");
        w->log("ello6");
    }
}
