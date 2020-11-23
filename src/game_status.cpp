//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_game_status.h"
#include "my_game_monsts.h"
#include "my_thing.h"

static void game_status_wid_create(void);

Widp wid_actionbar {};
Widp wid_fake_itembar {};
Widp wid_item_popup {};
Widp wid_sidebar {};

void game_status_wid_fini (void)
{_
    wid_destroy(&wid_actionbar);
    wid_destroy(&wid_fake_itembar);
    wid_destroy(&wid_item_popup);
    wid_destroy(&wid_sidebar);
    game_monsts_wid_fini();
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

static void game_status_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
    auto level = game->level;
    if (!level) {
        return;
    }

    auto slot = wid_get_int_context(w);
    if (!level->actionbar_select(slot)) {
        return;
    }

    level->actionbar_describe(slot);
    game_status_wid_create();
}

static void game_status_mouse_over_e (Widp w)
{
    auto level = game->level;
    if (!level) {
        return;
    }

    auto slot = wid_get_int_context(w);
    if (!level->actionbar_select(slot)) {
        return;
    }

    //
    // Do not create new wids in here
    //
}

//
// Create the test
//
static void game_status_wid_create (void)
{_
    auto level = game->level;
    if (!level) {
        return;
    }
    auto player = level->player;
    if (!player) {
        return;
    }

    //
    // Stop this window popping on top of dialogs like when setting keys
    //
    if (game->paused()) {
        return;
    }

    game_status_wid_fini();
    game_monsts_wid_init();

    {

        {_
            auto x1 = TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH;
            auto x2 = TERM_WIDTH - 1;
            point tl = make_point(x1, TERM_HEIGHT - 20);
            point br = make_point(x2, TERM_HEIGHT - 11);
            color c;

            wid_actionbar = wid_new_square_window("actionbar (bottom)");
            wid_set_pos(wid_actionbar, tl, br);
            wid_set_style(wid_actionbar, 0);
            wid_lower(wid_actionbar);
        }
    }

    if (0) {
        auto actionbar_items = player->monstp->actionbar_id.size();

        for (auto i = 0U; i < actionbar_items; i++) {
            auto tp_id = player->monstp->actionbar_id[i];
            if (!tp_id) {
                continue;
            }

            auto tpp = tp_find(tp_id);
            if (!tpp) {
                continue;
            }
        }

        std::vector<Widp> wid_actionbar_items;

        for (auto i = 0U, x = 0U; i < actionbar_items; i++) {
            auto s = "actionbar item" + std::to_string(0);
            auto w = wid_new_square_button(wid_actionbar, s);
            wid_actionbar_items.push_back(w);
            point tl = make_point(x, 0);
            point br = make_point(x + UI_ACTIONBAR_ITEM_WIDTH - 1, UI_ACTIONBAR_ITEM_HEIGHT);

            wid_set_pos(w, tl, br);

            if (i == game->actionbar_highlight_slot) {
                std::string tile = "ui_action_bar_highlight" + std::to_string(i);
                wid_set_bg_tilename(w, tile.c_str());
            } else {
                std::string tile = "ui_action_bar" + std::to_string(i);
                wid_set_bg_tilename(w, tile.c_str());
            }

            x += UI_ACTIONBAR_ITEM_WIDTH;
        }

        for (auto i = 0U; i < actionbar_items; i++) {
            std::string name = "actionbar icon" + std::to_string(i);
            auto w = wid_new_square_button(wid_actionbar_items[i], name);
            point tl = make_point(0, 0);
            point br = make_point(UI_ACTIONBAR_ITEM_WIDTH - 1, UI_ACTIONBAR_ITEM_HEIGHT - 1);

            wid_set_pos(w, tl, br);
            wid_set_text_lhs(w, true);
            wid_set_text_top(w, true);

            wid_set_on_mouse_down(w, game_status_mouse_down);
            wid_set_on_mouse_over_b(w, game_status_mouse_over_b);
            wid_set_on_mouse_over_e(w, game_status_mouse_over_e);
            wid_set_int_context(w, i);

            auto count = player->actionbar_id_slot_count(i);
            if (count > 1) {
                wid_set_text(w, " x" + std::to_string(count));
            }

            if (player->monstp) {
                auto tp_id = player->monstp->actionbar_id[i];
                if (tp_id) {
                    auto tpp = tp_find(tp_id);
                    auto tiles = &tpp->tiles;
                    if (tiles) {
                        auto tile = tile_first(tiles);
                        if (tile) {
                            wid_set_fg_tile(w, tile);
                        }
                    }
                }
            }

            wid_set_color(w, WID_COLOR_BG, COLOR_NONE);
            wid_set_mode(w, WID_MODE_OVER);
            wid_set_color(w, WID_COLOR_BG, COLOR_NONE);
            wid_set_mode(w, WID_MODE_NORMAL);
        }

        wid_update(wid_actionbar);
    }

    {_
        point tl = make_point(TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH, 0);
        point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT);
        color c;

        wid_sidebar = wid_new_square_window("right sidebar");
        wid_set_ignore_events(wid_sidebar, true);
        wid_set_pos(wid_sidebar, tl, br);
        wid_set_shape_none(wid_sidebar);
        wid_set_style(wid_sidebar, UI_WID_STYLE_OUTLINE);
        wid_set_ignore_events(wid_sidebar, true);
    }

    int y_at = 0;

    {
        {_
            auto w = wid_new_plain(wid_sidebar, "zorbash-0");
            point tl = make_point(0, y_at);
            point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at);
            wid_set_ignore_events(w, true);
            wid_set_pos(w, tl, br);
            wid_set_bg_tilename(w, "zorbash-0");
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
        y_at += 1;
        {_
            auto w = wid_new_plain(wid_sidebar, "zorbash-1");
            point tl = make_point(0, y_at);
            point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at);
            wid_set_ignore_events(w, true);
            wid_set_pos(w, tl, br);
            wid_set_bg_tilename(w, "zorbash-1");
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
    }

    y_at += 1;
    {_
        auto w = wid_new_plain(wid_sidebar, "level no");
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + 1);

        auto s = dynprintf("Level %u", level->world_at.z);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        wid_set_shape_none(w);
        myfree(s);
    }

    y_at += 1;
    {_
        auto w = wid_new_plain(wid_sidebar, "Seed");
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + 1);

        auto s = dynprintf("%%fg=gray$\"%s\"", game->seed_name.c_str());
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        wid_set_shape_none(w);
        myfree(s);
    }

    y_at += 2;
    {_
        auto w = wid_new_plain(wid_sidebar, "title name");
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + 1);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, player->text_title());
        wid_set_shape_none(w);
    }

    y_at += 3;

    {_
        auto w = wid_new_plain(wid_sidebar, "gold");
        point tl = make_point(2, y_at-2);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at-2);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        auto g = dynprintf("%%fg=green$$%%fg=gray$%06d", player->get_gold());
        wid_set_text(w, g);
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    {_
        auto w = wid_new_plain(wid_sidebar, "keys");
        point tl = make_point(10, y_at-2);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at-2);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        auto k = std::to_string(player->get_keys());
        wid_set_text(w, "%%fg=yellow$%%tile=key-icon$%%fg=gray$" + k);
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

#if 0
    {_
        auto w = wid_new_plain(wid_sidebar, "weight");
        point tl = make_point(0, y_at-1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at-1);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, L"%tile=weight-icon$%fg=green$ 150");
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Health
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_sidebar, "Health-status-bar");
        point tl = make_point(2, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 3, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);

        int i = ((float)player->get_stats_health() /
                 (float)player->get_stats_health_max()) *
                 (float)UI_HEALTH_BAR_STEPS - 1;
        i = std::min(i, UI_HEALTH_BAR_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "status-bar-" + std::to_string(i);
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_sidebar, "health-status");
        point tl = make_point(2, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "health-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_sidebar, "health-value");
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(player->get_stats_health()) + "/" +
            std::to_string(player->get_stats_health_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 2;

    ///////////////////////////////////////////////////////////////////////////
    // Defence
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_sidebar, "defence-status-bar");
        point tl = make_point(2, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 3, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);

        int i = ((float)player->get_stats_defence() /
                 (float)player->get_stats_defence_max()) *
                 (float)UI_HEALTH_BAR_STEPS - 1;
        i = std::min(i, UI_HEALTH_BAR_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "status-bar-" + std::to_string(i);
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_sidebar, "defence-status");
        point tl = make_point(2, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "defence-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_sidebar, "defence-value");
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(player->get_stats_defence()) + "/" +
            std::to_string(player->get_stats_defence_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 2;

    ///////////////////////////////////////////////////////////////////////////
    // stamina
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_sidebar, "stamina-status-bar");
        point tl = make_point(2, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 3, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);

        int i = ((float)player->get_stats_stamina() /
                 (float)player->get_stats_stamina_max()) *
                 (float)UI_HEALTH_BAR_STEPS - 1;
        i = std::min(i, UI_HEALTH_BAR_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "status-bar-" + std::to_string(i);
        wid_set_bg_tilename(w, icon);
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_sidebar, "stamina-status");
        point tl = make_point(2, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "stamina-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_sidebar, "stamina-value");
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(player->get_stats_stamina()) + "/" +
            std::to_string(player->get_stats_stamina_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 2;

    wid_update(wid_sidebar);
}

bool is_mouse_over_actionbar (void)
{
    extern Widp wid_actionbar;

    if (!wid_actionbar) {
        return false;
    }

    //
    // If we are in the portion of the lower screen above the itembar
    // then do not scroll
    //
    int x = mouse_x;
    int y = mouse_y;
    pixel_to_ascii(&x, &y);

    static int tlx, tly, brx, bry, cached;
    if (cached != TERM_HEIGHT) {
        cached = TERM_HEIGHT;
    }

    wid_get_tl_x_tl_y_br_x_br_y(wid_actionbar, &tlx, &tly, &brx, &bry);

    //
    // Add some border
    //
    tlx -= 1;
    brx += 1;
    tly -= 1;
    bry += 1;

    if ((x >= tlx) && (x < brx) && (y >= tly)) {
        //CON("    actionbar %d %d %d", tlx, brx, x);
        return true;
    }
    //CON("NOT actionbar %d %d %d", tlx, brx, x);

    return false;
}
