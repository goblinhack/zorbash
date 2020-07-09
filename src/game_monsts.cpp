//
// Copyright goblinhack@gmail.com
// See the README file for license info.
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

static void game_monsts_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
    auto slot = wid_get_int_context(w);
    highlight_slot = slot;
    game_monsts_wid_create();
}

static void game_monsts_mouse_over_e (Widp w)
{
    auto slot = wid_get_int_context(w);
    highlight_slot = slot;

    //
    // Do not create new wids in here
    //
}
#endif

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

    {_
        point tl = make_point(0,  UI_MINICON_VIS_HEIGHT + 2);
        point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, UI_ACTIONBAR_TL_Y - 1);
        color c;

        wid_items = wid_new_square_window("text container2");
        wid_set_pos(wid_items, tl, br);
        wid_set_shape_none(wid_items);
        wid_set_style(wid_items, UI_WID_STYLE_OUTLINE);
    }

    auto minx = std::max(0, (int) level->map_at.x);
    auto maxx = std::min(MAP_WIDTH, (int)level->map_at.x + TILES_ACROSS);

    auto miny = std::max(0, (int) level->map_at.y);
    auto maxy = std::min(MAP_HEIGHT, (int)level->map_at.y + TILES_DOWN);

    auto row = 0;

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

                    auto w = wid_new_plain(wid_items, "item");
                    point tl = make_point(0, row);
                    point br = make_point(0, row);
                    wid_set_pos(w, tl, br);
                    auto tile = tile_index_to_tile(t->tile_curr);
                    if (tile && tile->is_invisible) {
                        //
                        // Should we hide invisible things?
                        //
                        continue;
                        //
                        // Or just show as first tile?
                        //
                        auto tpp = t->tp();
                        auto tiles = &tpp->tiles;
                        tile = tile_first(tiles);
                    }
                    wid_set_fg_tile(w, tile);
                    wid_set_color(w, WID_COLOR_BG, WHITE);

                    {
                        auto w = wid_new_plain(wid_items, "item");
                        point tl = make_point(2, row);
                        point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, row);
                        wid_set_pos(w, tl, br);
                        wid_set_shape_none(w);

                        wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
                        auto s = t->text_name();
                        if (t->is_resurrected) {
                            if (t->is_dead) {
                                s += " (dead again)";
                            } else {
                                s += " (alive again)";
                            }
                        } else if (t->is_dead) {
                            s += " (dead)";
                        }
                        wid_set_text(w, s);
                        wid_set_text_lhs(w, true);
                    }

                    row++;
                } FOR_ALL_THINGS_END()
            }
        }
    }

    wid_update(wid_items);
}
