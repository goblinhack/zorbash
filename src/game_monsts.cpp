//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_game_monsts.h"
#include "my_thing.h"
#include "my_level.h"
#include "my_sprintf.h"

static void game_monsts_wid_create(void);

Widp wid_items {};

void game_monsts_wid_fini (void)
{_
    wid_destroy(&wid_items);
}

uint8_t game_monsts_wid_init (void)
{_
    game_monsts_wid_create();

    return (true);
}

#if 0
static uint8_t game_monsts_mouse_down (Widp w,
                                       int32_t x,
                                       int32_t y,
                                       uint32_t button)
{_
    CON("status button %d", button);
    return (true);
}
#endif

static void game_monsts_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
    if (!game->level) {
        return;
    }

    auto id = wid_get_int_context(w);
    auto t = game->level->thing_find(id);
    game->level->highlight = t;
}

static void game_monsts_mouse_over_e (Widp w)
{
    if (!game->level) {
        return;
    }

    //
    // Do not create new wids in here
    //
    game->level->highlight = nullptr;
}

static void game_monsts_wid_create (void)
{_
    auto level = game->level;
    if (!level) {
        return;
    }
    auto player = level->player;
    if (!player) {
        return;
    }

    game_monsts_wid_fini();

    auto minx = std::max(0, (int) level->map_at.x);
    auto maxx = std::min(MAP_WIDTH, (int)level->map_at.x + TILES_ACROSS);

    auto miny = std::max(0, (int) level->map_at.y);
    auto maxy = std::min(MAP_HEIGHT, (int)level->map_at.y + TILES_DOWN);

    std::vector<Thingp> items;
    for (auto z = 0; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    if (!t->is_sidebar_item()) {
                        continue;
                    }

                    if (t->get_owner_id().ok()) {
                        continue;
                    }

                    auto p = make_point(t->mid_at.x, t->mid_at.y);
                    if (!level->is_lit(p)) {
                        continue;
                    }

                    auto tile = tile_index_to_tile(t->tile_curr);
                    if (tile && tile->is_invisible) {
                        continue;
                    }

                    items.push_back(t);
                } FOR_ALL_THINGS_END()
            }
        }
    }

    int height = items.size();

    {_
        point tl = make_point(0,  UI_MINICON_VIS_HEIGHT + 1);
        //
        // Add some below to avoid mouse scrolling being too close to
        // the menu items
        //
        point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, tl.y + height + 3);
        color c;

        wid_items = wid_new_square_window("text container2");
        wid_set_pos(wid_items, tl, br);
        wid_set_shape_none(wid_items);
        // wid_set_style(wid_items, UI_WID_STYLE_OUTLINE);
        // wid_set_style(wid_items, UI_WID_STYLE_GREEN);
        wid_set_shape_square(wid_items);
        wid_set_ignore_scroll_events(wid_items, true);
    }

    sort(items.begin(),
         items.end(),
         [](const Thingp a, const Thingp b) -> bool {
             return a->get_stats_health() > b->get_stats_health();
         });

    auto row = 1;
    for (auto t : items) {
        auto w = wid_new_plain(wid_items, "item");
        point tl = make_point(0, row);
        point br = make_point(0, row);
        wid_set_pos(w, tl, br);
        auto tile = tile_index_to_tile(t->tile_curr);
        wid_set_fg_tile(w, tile);
        wid_set_color(w, WID_COLOR_BG, WHITE);

        {
            auto w = wid_new_plain(wid_items, "item");
            point tl = make_point(2, row);
            point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, row);
            wid_set_pos(w, tl, br);
            wid_set_shape_none(w);

            auto s = t->text_name();
            if (t->is_resurrected) {
                if (t->is_dead) {
                    s += " (dead again)";
                } else {
                    s += " (alive again)";
                }
            } else if (t->is_dead) {
                if (t->is_door()) {
                    s += " (broken)";
                } else if (t->is_torch()) {
                    s += " (kicked over)";
                } else {
                    s += " (dead)";
                }
            }

            // s += " " + std::to_string(t->get_stats_health());
            if (level->hover_over == t) {
                wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
            } else {
                wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
            }

            wid_set_text(w, s);
            wid_set_text_lhs(w, true);
            wid_set_int_context(w, t->id.id);
            wid_set_on_mouse_over_b(w, game_monsts_mouse_over_b);
            wid_set_on_mouse_over_e(w, game_monsts_mouse_over_e);
        }

        row++;
    }

    wid_update(wid_items);
}
