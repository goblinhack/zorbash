//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_rightbar.h"
#include "my_thing.h"

static void wid_rightbar_create(void);

Widp wid_item_popup {};
Widp wid_rightbar {};

void wid_rightbar_fini (void)
{_
    wid_destroy(&wid_item_popup);
    wid_destroy(&wid_rightbar);
}

uint8_t wid_rightbar_init (void)
{_
    wid_rightbar_create();

    return true;
}

//
// Create the test
//
static void wid_rightbar_create (void)
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

    wid_rightbar_fini();

    {_
        point tl = make_point(TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH, 0);
        point br = make_point(TERM_WIDTH - 1, 13);
        color c;

        wid_rightbar = wid_new_square_window("right rightbar");
        wid_set_pos(wid_rightbar, tl, br);
        wid_set_shape_none(wid_rightbar);
        wid_set_style(wid_rightbar, UI_WID_STYLE_OUTLINE);
        wid_set_ignore_events(wid_rightbar, true);
    }

    int y_at = 0;

    {
        {_
            auto w = wid_new_plain(wid_rightbar, "zorbash-0");
            point tl = make_point(0, y_at);
            point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at);
            wid_set_ignore_events(w, true);
            wid_set_pos(w, tl, br);
            wid_set_bg_tilename(w, "zorbash-0");
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }
        y_at += 1;
        {_
            auto w = wid_new_plain(wid_rightbar, "zorbash-1");
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
        auto w = wid_new_plain(wid_rightbar, "level no");
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at + 1);

        auto s = dynprintf("Level %u", level->world_at.z);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        wid_set_shape_none(w);
        myfree(s);
    }

    y_at += 1;
    {_
        auto w = wid_new_plain(wid_rightbar, "Seed");
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at + 1);

        auto s = dynprintf("%%fg=gray$\"%s\"", game->seed_name.c_str());
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        wid_set_shape_none(w);
        myfree(s);
    }

    y_at += 2;
    {_
        auto w = wid_new_plain(wid_rightbar, "title name");
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + 1);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, player->text_title());
        wid_set_shape_none(w);
    }

    y_at += 3;

    {_
        auto w = wid_new_plain(wid_rightbar, "gold");
        point tl = make_point(3, y_at-2);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at-2);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        auto g = dynprintf("%%fg=green$$%%fg=gray$%05d", player->get_gold());
        wid_set_text(w, g);
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    {_
        auto w = wid_new_plain(wid_rightbar, "keys");
        point tl = make_point(10, y_at-2);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at-2);

        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        auto k = std::to_string(player->get_keys());
        wid_set_text(w, "%%fg=yellow$%%tile=key-icon$%%fg=gray$" + k);
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Health
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "Health-status-bar");
        point tl = make_point(0, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 1, tl.y);
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
        auto w = wid_new_plain(wid_rightbar, "health-status");
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "health-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_rightbar, "health-value");
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
    // stamina
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "stamina-status-bar");
        point tl = make_point(0, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 1, tl.y);
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
        auto w = wid_new_plain(wid_rightbar, "stamina-status");
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "stamina-status");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_rightbar, "stamina-value");
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
    y_at += 1;

    ///////////////////////////////////////////////////////////////////////////
    // ATT DEF STR
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "stats1");
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "stats1");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_rightbar, "defence-value");
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s = "   16   17   18";
        wid_set_text(w, s);
        wid_set_text_lhs(w, true);
    }
    y_at += 1;

    ///////////////////////////////////////////////////////////////////////////
    // CON
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "stats2");
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "stats2");
        wid_set_color(w, WID_COLOR_BG, WHITE);
    }
    {_
        auto w = wid_new_plain(wid_rightbar, "defence-value");
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s = "   16   17   18";
        wid_set_text(w, s);
        wid_set_text_lhs(w, true);
    }
    y_at += 2;

    wid_update(wid_rightbar);
}
