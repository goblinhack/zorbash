//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_game_status.h"
#include "my_thing.h"

static void game_status_wid_create(void);

Widp wid_itembar {};
Widp wid_fake_itembar {};
Widp wid_item_popup {};
Widp wid_sidebar {};

void game_status_fini (void)
{_
    wid_destroy(&wid_itembar);
    wid_destroy(&wid_fake_itembar);
    wid_destroy(&wid_item_popup);
    wid_destroy(&wid_sidebar);
}

uint8_t game_status_wid_init (void)
{_
    game_status_wid_create();

    return (true);
}

static uint8_t game_status_mouse_down (Widp w,
                                       int32_t x,
                                       int32_t y,
                                       uint32_t button)
{_
    CON("status button %d", button);
    return (true);
}

//
// Create the test
//
static void game_status_wid_create (void)
{_
    if (!level->player) {
        return;
    }

    game_status_fini();

    {_
        point tl = make_point(ACTIONBAR_TL_X, ACTIONBAR_TL_Y);
        point br = make_point(ACTIONBAR_BR_X, ACTIONBAR_BR_Y);
        color c;

        wid_itembar = wid_new_square_window("text container1");
        wid_set_pos(wid_itembar, tl, br);
        wid_set_style(wid_itembar, -1);
    }

    auto highlight_slot = 0;

    std::array<Widp, ACTIONBAR_ITEMS> wid_items;

    for (auto i = 0, x = 0; i < ACTIONBAR_ITEMS; i++) {
        auto w = wid_new_square_button(wid_itembar, "text box2");
        wid_items[i] = w;
        point tl = make_point(x, 0);
        point br = make_point(x + ACTIONBAR_WIDTH - 1, ACTIONBAR_HEIGHT);

        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_on_mouse_down(w, game_status_mouse_down);

        if (i == highlight_slot) {
            std::string tile = "ui_action_bar_highlight" + std::to_string(i);
            wid_set_bg_tilename(w, tile.c_str());
        } else {
            std::string tile = "ui_action_bar" + std::to_string(i);
            wid_set_bg_tilename(w, tile.c_str());
        }

        x += ACTIONBAR_WIDTH;
    }

    for (auto i = 0, x = 0; i < ACTIONBAR_ITEMS; i++) {
        auto w = wid_new_square_button(wid_items[i], "text box2");
        point tl = make_point(x, 0);
        point br = make_point(x + ACTIONBAR_WIDTH - 1, ACTIONBAR_HEIGHT - 1);

        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_text_lhs(w, true);
        wid_set_text_top(w, true);

        auto count = player->actionbar_id_slot_count(i);
        if (count > 1) {
            wid_set_text(w, " x" + std::to_string(count));
        }
        wid_set_on_mouse_down(w, game_status_mouse_down);

        if (player->monstp) {
            auto a = player->monstp->actionbar_id[i];
            if (a) {
                auto it = thing_find(a);
                if (it) {
                    auto tpp = it->tp();
                    auto tiles = &tpp->tiles;
                    if (tiles) {
                        auto tile = tile_first(tiles);
                        if (tile) {
                            wid_set_fg_tile(w, tile);
                        }
                    }
                }
            }
        }

        wid_set_color(w, WID_COLOR_BG, COLOR_NONE);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_BG, COLOR_NONE);
        wid_set_mode(w, WID_MODE_NORMAL);
        x += ACTIONBAR_WIDTH;
    }

    wid_update(wid_itembar);

    {_
        point tl = make_point(ASCII_WIDTH - SIDEBAR_WIDTH, 0);
        point br = make_point(ASCII_WIDTH - 1, ASCII_HEIGHT);
        color c;

        wid_sidebar = wid_new_square_window("text container2");
        wid_set_pos(wid_sidebar, tl, br);
        wid_set_shape_none(wid_sidebar);
        wid_set_style(wid_sidebar, WID_STYLE_OUTLINE);
    }

    int y_at = 0;
    {_
        auto w = wid_new_square_button(wid_sidebar, "zorbash-0");
        point tl = make_point(0, y_at);
        point br = make_point(SIDEBAR_WIDTH - 1, y_at+1);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "zorbash-0");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    y_at += 2;
    {_
        auto w = wid_new_square_button(wid_sidebar, "zorbash-1");
        point tl = make_point(0, y_at);
        point br = make_point(SIDEBAR_WIDTH - 1, y_at+1);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "zorbash-1");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    y_at += 2;
    {_
        auto w = wid_new_square_button(wid_sidebar, "zorbash-2");
        point tl = make_point(0, y_at);
        point br = make_point(SIDEBAR_WIDTH - 1, y_at+1);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "zorbash-2");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    y_at += 2;

#if 0
    {_
        auto w = wid_new_square_button(wid_sidebar, "title box");
        point tl = make_point(0, y_at);
        point br = make_point(5, y_at + 5);

        wid_set_pos(w, tl, br);
        wid_set_on_mouse_down(w, game_status_mouse_down);
        wid_set_style(w, WID_STYLE_DARK;
        wid_set_bg_tilename(w, "player1.pose");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }

    y_at += 3;
    {_
        auto w = wid_new_square_button(wid_sidebar, "title name");
        point tl = make_point(0, y_at + 4);
        point br = make_point(SIDEBAR_WIDTH, y_at + 4);

        wid_set_pos(w, tl, br);
        wid_set_style(w, WID_STYLE_DARK;
        wid_set_text(w, L"Ser Hacksalot");
        wid_set_shape_none(w);
    }

    {_
        auto w = wid_new_square_button(wid_sidebar, "gold");
        point tl = make_point(7, y_at-3);
        point br = make_point(SIDEBAR_WIDTH, y_at-3);

        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=dollar-icon$%fg=gold$666");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    {_
        auto w = wid_new_square_button(wid_sidebar, "weight");
        point tl = make_point(7, y_at-2);
        point br = make_point(SIDEBAR_WIDTH, y_at-2);

        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=CWEIGHT$%fg=green$150%fg=grey$lbs");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    y_at += 1;
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Health
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_square_button(wid_sidebar, "health-icon");
        point tl = make_point(0, y_at);
        point br = make_point(1, y_at + 1);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        int i = ((float)level->player->get_stats_health() /
                 (float)level->player->get_stats_health_max()) *
                 (float)HEALTH_ICON_STEPS;
        i = std::min(i, HEALTH_ICON_STEPS);
        i = std::max(i, 1);
        auto icon = "health" + std::to_string(i) + "-icon";
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "Health-status-bar");
        point tl = make_point(2, y_at);
        point br = make_point(tl.x + SIDEBAR_WIDTH - 3, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);

        int i = ((float)level->player->get_stats_health() /
                 (float)level->player->get_stats_health_max()) *
                 (float)STATUSBAR_ICON_STEPS - 1;
        i = std::min(i, STATUSBAR_ICON_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "status-bar-" + std::to_string(i);
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "health-status");
        point tl = make_point(2, y_at + 1);
        point br = make_point(tl.x + SIDEBAR_WIDTH, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "health-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "health-value");
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + SIDEBAR_WIDTH - 3, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(level->player->get_stats_health()) + "/" +
            std::to_string(level->player->get_stats_health_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 3;

#if 0
    ///////////////////////////////////////////////////////////////////////////
    // Attack
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_square_button(wid_sidebar, "attack-icon");
        point tl = make_point(0, y_at);
        point br = make_point(1, y_at + 1);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "attack-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "attack-status-bar");
        point tl = make_point(2, y_at);
        point br = make_point(tl.x + SIDEBAR_WIDTH - 3, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);

        int i = ((float)level->player->get_stats_attack() /
                 (float)level->player->get_stats_attack_max()) *
                 (float)STATUSBAR_ICON_STEPS - 1;
        i = std::min(i, STATUSBAR_ICON_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "status-bar-" + std::to_string(i);
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "attack-status");
        point tl = make_point(2, y_at + 1);
        point br = make_point(tl.x + SIDEBAR_WIDTH, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "attack-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "attack-value");
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + SIDEBAR_WIDTH - 3, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(level->player->get_stats_attack()) + "/" +
            std::to_string(level->player->get_stats_attack_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 3;
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Defence
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_square_button(wid_sidebar, "defence-icon");
        point tl = make_point(0, y_at);
        point br = make_point(1, y_at + 1);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "defence-icon");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "defence-status-bar");
        point tl = make_point(2, y_at);
        point br = make_point(tl.x + SIDEBAR_WIDTH - 3, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);

        int i = ((float)level->player->get_stats_defence() /
                 (float)level->player->get_stats_defence_max()) *
                 (float)STATUSBAR_ICON_STEPS - 1;
        i = std::min(i, STATUSBAR_ICON_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "status-bar-" + std::to_string(i);
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "defence-status");
        point tl = make_point(2, y_at + 1);
        point br = make_point(tl.x + SIDEBAR_WIDTH, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_style(w, -1);
        wid_set_bg_tilename(w, "defence-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_square_button(wid_sidebar, "defence-value");
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + SIDEBAR_WIDTH - 3, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(level->player->get_stats_defence()) + "/" +
            std::to_string(level->player->get_stats_defence_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 3;

    wid_update(wid_sidebar);
}
