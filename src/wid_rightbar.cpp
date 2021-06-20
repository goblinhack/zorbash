//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_rightbar.h"
#include "my_traceback.h"
#include "my_thing.h"
#include "my_string.h"
#include "my_ui.h"
#include "my_monst.h"
#include "my_wid_inventory.h"
#include "my_wid_skillbox.h"
#include "my_sdl.h"
#include "my_ptrcheck.h"
#include "my_vector_bounds_check.h"

static bool wid_rightbar_create(void);

Widp wid_item_popup {};
Widp wid_rightbar {};

void wid_rightbar_fini (void)
{_
    wid_destroy(&wid_item_popup);
    wid_destroy(&wid_rightbar);
}

bool wid_rightbar_init (void)
{_
    return wid_rightbar_create();
}

static void wid_rightbar_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{_
    LOG("rightbar: begin over rightbar");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS ||
        game->state == Game::STATE_ENCHANTING_ITEMS) {
        LOG("rightbar: moving items; ignore");
        return;
    }

    if (game->in_transit_item) {
        LOG("rightbar: in transit item; ignore");
        return;
    }

    if (game->paused()) {
        LOG("rightbar: game paused; ignore");
        return;
    }

    auto level = game->level;
    if (!level) {
        LOG("rightbar: no level; ignore");
        return;
    }

    if (level->player) {
        game->wid_thing_info_create(level->player);
    }
}

static void wid_rightbar_mouse_over_e (Widp w)
{_
    LOG("rightbar: end over rightbar");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS ||
        game->state == Game::STATE_ENCHANTING_ITEMS) {
        LOG("rightbar: moving items; ignore");
        return;
    }

    if (game->in_transit_item) {
        LOG("rightbar: in transit item; ignore");
        return;
    }

    if (game->paused()) {
        LOG("rightbar: paused; ignore");
        return;
    }

    auto level = game->level;
    if (!level) {
        LOG("rightbar: no level; ignore");
        return;
    }

    game->wid_thing_info_destroy_deferred();

    //
    // Do not create new wids in here
    //
}

//
// Create the test
//
static bool wid_rightbar_create (void)
{_
    LOG("Remake rightbar");

    auto level = game->level;
    if (!level) {
        return false;
    }

    auto player = level->player;
    if (!player) {
        return false;
    }

    //
    // Stop this window popping on top of dialogs like when setting keys
    //
    if (game->paused()) {
        LOG("Remake rightbar; paused");
        return false;
    }

    wid_rightbar_fini();

    {_
        point tl = make_point(TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH, 0);
        point br = make_point(TERM_WIDTH - 1, 63);

        wid_rightbar = wid_new_square_window("wid rightbar");
        wid_set_ignore_scroll_events(wid_rightbar, true);
        wid_set_pos(wid_rightbar, tl, br);
        wid_set_style(wid_rightbar, UI_WID_STYLE_SOLID_NONE);
        wid_set_bg_tilename(wid_rightbar, "ui_status_bar");
        wid_lower(wid_rightbar);
    }

    int y_at = 6;
    
    {_
        auto w = wid_new_plain(wid_rightbar, "level no");
        wid_set_ignore_events(w, true);
        point tl = make_point(0, y_at - 1);

        //
        // Level nos are divided by 2 as we have sewer levels under each level
        //
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at + 1);

        auto s = dynprintf("Level %u", (level->world_at.z + 1) / 2);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        wid_set_shape_none(w);
        myfree(s);
    }

    y_at += 1;
    {_
        auto w = wid_new_plain(wid_rightbar, "Seed");
        wid_set_ignore_events(w, true);
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at + 1);

        auto s = dynprintf("%%fg=gray$%s", game->seed_name.c_str());
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        wid_set_shape_none(w);
        myfree(s);
    }

    y_at += 2;
    {_
        auto w = wid_new_plain(wid_rightbar, "title name");
        wid_set_ignore_events(w, true);
        point tl = make_point(0, y_at - 1);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + 1);

        wid_set_pos(w, tl, br);
        wid_set_text(w, player->title());
        wid_set_shape_none(w);
    }

    y_at += 3;

    {_
        auto w = wid_new_plain(wid_rightbar, "gold and keys"); // NOTE this same is referenced elsewhere for particles
        wid_set_ignore_events(w, true);
        point tl = make_point(1, y_at-2);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at-2);

        wid_set_pos(w, tl, br);
        auto g = dynprintf("%%fg=gray$%06d %%fg=white$$%%fg=gray$%03d %%fg=yellow$%%tile=key_icon$%%fg=gray$%d", 
                           player->get_score(), player->get_gold(), player->get_keys());
        wid_set_text(w, g);
        wid_set_text_lhs(w, true);
        wid_set_shape_none(w);
        myfree(g);
    }


    ///////////////////////////////////////////////////////////////////////////
    // Health
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "Health-bar");
        wid_set_ignore_events(w, true);
        point tl = make_point(0, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 1, tl.y);
        wid_set_pos(w, tl, br);

        int i = ((float)player->get_health() /
                 (float)player->get_health_max()) *
                 (float)UI_HEALTH_BAR_STEPS - 1;
        i = std::min(i, UI_HEALTH_BAR_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "health_bar_" + std::to_string(i);
        wid_set_fg_tilename(w, icon);
    }
    {_
        auto w = wid_new_plain(wid_rightbar, "health-value");
        wid_set_ignore_events(w, true);
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(player->get_health()) + "/" +
            std::to_string(player->get_health_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 2;

    ///////////////////////////////////////////////////////////////////////////
    // stamina
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "stamina-bar");
        wid_set_ignore_events(w, true);
        point tl = make_point(0, y_at);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 1, tl.y);
        wid_set_pos(w, tl, br);

        int i = ((float)player->get_stamina() /
                 (float)player->get_stamina_max()) *
                 (float)UI_HEALTH_BAR_STEPS - 1;
        i = std::min(i, UI_HEALTH_BAR_STEPS - 1);
        i = std::max(i, 0);
        auto icon = "health_bar_" + std::to_string(i);
        wid_set_fg_tilename(w, icon);
    }
    {_
        auto w = wid_new_plain(wid_rightbar, "stamina-value");
        wid_set_ignore_events(w, true);
        point tl = make_point(3, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s =
            std::to_string(player->get_stamina()) + "/" +
            std::to_string(player->get_stamina_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
    }
    y_at += 3;

    ///////////////////////////////////////////////////////////////////////////
    // ATT DEF STR
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "stats1-value");
        wid_set_on_mouse_over_b(w, wid_rightbar_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_rightbar_mouse_over_e);
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        char tmp[UI_SIDEBAR_RIGHT_WIDTH + 1];
        snprintf(tmp, sizeof(tmp) - 1,
                 "   %2d   %2d   %2d",
                 player->get_stat_attack(),
                 player->get_stat_defence(),
                 player->get_stat_strength());
        wid_set_text(w, tmp);
        wid_set_text_lhs(w, true);
    }
    y_at += 1;

    ///////////////////////////////////////////////////////////////////////////
    // CON
    ///////////////////////////////////////////////////////////////////////////
    {_
        auto w = wid_new_plain(wid_rightbar, "stats2-value");
        wid_set_on_mouse_over_b(w, wid_rightbar_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_rightbar_mouse_over_e);
        point tl = make_point(0, y_at + 1);
        point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        char tmp[UI_SIDEBAR_RIGHT_WIDTH + 1];
        snprintf(tmp, sizeof(tmp) - 1,
                 "   %2d   %2d   %2d",
                 player->get_stat_constitution(),
                 0,
                 0);
        wid_set_text(w, tmp);
        wid_set_text_lhs(w, true);
    }
    y_at += 4;

    //
    // Inventory items
    //
    {
        auto monstp = player->monstp;
        std::vector<Widp> wid_inventory_items;

        uint8_t item = 0;
        for (auto i = 0U; i < UI_ACTIONBAR_MAX_ITEMS; i++) {
            //
            // slot number
            //
            auto slot(std::to_string(i));

            //
            // Always create the slot even if empty as we use this for 
            // particles when dropping items.
            //
            auto x = (i % 5) * 3 + 1;
            auto y = (i / 5) * 3 + 1 + y_at;

            {
                auto w = wid_new_plain(wid_rightbar, "inventory slot bg");
                point tl = make_point(x-1, y-1);
                point br = make_point(x+2, y+2);
                wid_set_shape_none(w);
                wid_set_pos(w, tl, br);
                wid_set_int_context(w, i);
                wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
                wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
            }

            auto s = "inventory slot" + std::to_string(i);
            auto w = wid_new_plain(wid_rightbar, s);
            point tl = make_point(x, y);
            point br = make_point(x+1, y+1);

            wid_set_pos(w, tl, br);
            wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

            if (item < monstp->inventory_id.size()) {
                auto tp_id = get(monstp->inventory_id, item);
                if (!tp_id) {
                    item++;
                    continue;
                }

                auto tpp = tp_find(tp_id);
                auto tiles = &tpp->tiles;

                if (!tiles) {
                    item++;
                    continue;
                }

                auto tile = tile_first(tiles);
                if (!tile) {
                    item++;
                    continue;
                }

                wid_set_fg_tile(w, tile);

                //
                // If choosing a target, highlight the item
                //
                if (i == game->inventory_highlight_slot) {
                    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
                } else {
                    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY60);
                }

                //
                // Print highlighted weapon
                //
                auto weapon = player->weapon_get();
                if (weapon) {
                    auto weapon_tp_id = weapon->tp()->id;
                    auto tp_id = monstp->inventory_id[i];
                    if (tp_id == weapon_tp_id) {
                        static Tilep tile;
                        if (!tile) {
                            tile = tile_find_mand("item_wielded");
                        }
                        wid_set_fg2_tile(w, tile);
                    }
                }

                //
                // Print item count
                //
                auto item_count = player->item_slot_charge_count(i);
                if (item_count > 9) {
                    auto tile = tile_find_mand("item_count_N");
                    wid_set_fg3_tile(w, tile);
                } else if (item_count > 1) {
                    auto tile = tile_find_mand("item_count_" + std::to_string(item_count));
                    wid_set_fg3_tile(w, tile);
                }

                //
                // Print enchant count. This overrides the above. If you have
                // both I'm not sure how to represent that.
                //
                auto enchant_count = player->item_enchant_count(i);
                if (enchant_count > 9) {
                    auto tile = tile_find_mand("item_enchant_N");
                    wid_set_fg3_tile(w, tile);
                } else if (enchant_count > 0) {
                    auto tile = tile_find_mand("item_enchant_" + std::to_string(enchant_count));
                    wid_set_fg3_tile(w, tile);
                }

                wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
                wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);

                if (tpp->is_item_container()) {
                    wid_set_on_mouse_up(w, wid_inventory_item_mouse_up_on_bag);
                } else {
                    wid_set_on_mouse_up(w, wid_inventory_item_mouse_up);
                }

                wid_set_int_context(w, i);
            }
            item++;
        }
    }

    //
    // Skills
    //
    y_at += 8;
    {
        auto monstp = player->monstp;
        std::vector<Widp> wid_skillbox_items;

        uint8_t item = 0;
        for (auto i = 0U; i < UI_ACTIONBAR_MAX_ITEMS; i++) {
            //
            // slot number
            //
            auto slot(std::to_string(i));

            //
            // Always create the slot even if empty as we use this for particles
            //
            auto s = "skill slot" + std::to_string(i);
            auto w = wid_new_plain(wid_rightbar, s);
            auto x = (i % 5) * 3 + 1;
            auto y = (i / 5) * 3 + 1 + y_at;
            point tl = make_point(x, y);
            point br = make_point(x+1, y+1);

            wid_set_pos(w, tl, br);
            wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

            if (item < monstp->skillbox_id.size()) {
                auto tp_id = get(monstp->skillbox_id, item);
                if (!tp_id) {
                    item++;
                    continue;
                }

                auto tpp = tp_find(tp_id);
                bool activated = false;

                for (auto id : monstp->skills) {
                    auto t = level->thing_find(id);
                    if (t) {
                        if (t->tp() == tpp) {
                            activated = t->is_activated;
                        }
                    }
                }

                auto tiles = &tpp->tiles;

                if (!tiles) {
                    item++;
                    continue;
                }

                auto tile = tile_n(tiles, activated ? 2 : 1);
                if (!tile) {
                    item++;
                    continue;
                }

                wid_set_fg_tile(w, tile);

                //
                // If choosing a target, highlight the item
                //
                if (i == game->skillbox_highlight_slot) {
                    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
                } else {
                    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY60);
                }

                wid_set_on_mouse_over_b(w, wid_skillbox_mouse_over_b);
                wid_set_on_mouse_over_e(w, wid_skillbox_mouse_over_e);
                wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up);

                wid_set_int_context(w, i);

                //
                // Print enchant count. This overrides the above. If you have
                // both I'm not sure how to represent that.
                //
                auto enchant_count = player->skill_enchant_count(i);
                if (enchant_count > 9) {
                    auto tile = tile_find_mand("item_enchant_N");
                    wid_set_fg3_tile(w, tile);
                } else if (enchant_count > 0) {
                    auto tile = tile_find_mand("item_enchant_" + std::to_string(enchant_count));
                    wid_set_fg3_tile(w, tile);
                }
            }
            item++;
        }
    }

    //
    // Map
    //
    y_at += 18;
    {
        auto w = wid_new_container(wid_rightbar, "minimap wid");
        point tl = make_point(0, y_at);
        point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1,
                              y_at + UI_SIDEBAR_RIGHT_WIDTH - 1);

        wid_set_pos(w, tl, br);
        wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        wid_set_style(w, UI_WID_STYLE_RED);
        wid_set_shape_none(w);

        wid_update(wid_rightbar);

        int tlx, tly, brx, bry;
        wid_get_tl_x_tl_y_br_x_br_y(w, &tlx, &tly, &brx, &bry);

        level->minimap_tl.x = tlx;
        level->minimap_tl.y = tly;
        level->minimap_br.x = brx;
        level->minimap_br.y = bry;
    }

    wid_update(wid_rightbar);

    if (game->request_remake_inventory) {
        if (game->state == Game::STATE_MOVING_ITEMS) {
            auto slot = game->inventory_highlight_slot;
            LOG("Inventory: remaking inventory for slot %d", slot);

            auto t = level->inventory_get(slot);
            if (t) {
                LOG("Inventory: remaking inventory, remake thing info too");
                game->wid_thing_info_create(t);
            } else {
                LOG("Inventory: remaking inventory, no thing info");
            }
        }
    }

    LOG("Remade rightbar");
    return true;
}

bool is_mouse_over_rightbar (void)
{
    if (!wid_rightbar) {
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

    wid_get_tl_x_tl_y_br_x_br_y(wid_rightbar, &tlx, &tly, &brx, &bry);

    //
    // Add some border
    //
    tlx -= 1;
    brx += 1;
    tly -= 1;
    bry += 1;

    if ((x >= tlx) && (x < brx) && (y >= tly)) {
        //CON("    rightbar %d %d %d", tlx, brx, x);
        return true;
    }
    //CON("NOT rightbar %d %d %d", tlx, brx, x);

    return false;
}
