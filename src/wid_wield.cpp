//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_ui.h"
#include "my_wid_bag.h"
#include "my_wid_botcon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
#include "my_wid_topcon.h"
#include "my_wid_actionbar.h"

WidPopup *wid_wield;
static std::vector<Thingp> wield_items;

void wid_wield_destroy (void)
{_
    delete wid_wield;
    wid_wield = nullptr;
    wield_items.clear();
    game->change_state(Game::STATE_NORMAL);
}

static void wid_wield_slot (int slot)
{_
    DBG3("Wield slot %d", slot);
_
    if (slot >= (int)wield_items.size()) {
        wid_wield_destroy();
        return;
    }

    auto level = game->level;
    if (!level) {
        return;
    }

    auto player = level->player;
    if (!player) {
        return;
    }

    auto t = wield_items[slot];
    if (t) {
        player->wield(t);
        game->tick_begin("wield weapon");
    }

    wid_wield_destroy();
}

static uint8_t wid_wield_key_up (Widp w, const struct SDL_Keysym *key)
{_
    auto level = game->level;
    if (!level) {
        return true;
    }

    auto player = level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }

    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        wid_wield_slot(c - '1');
                        return true;
                    case SDLK_ESCAPE: {_
                        CON("PLAYER: wield cancelled");
                        wid_wield_destroy();
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

static uint8_t wid_wield_key_down (Widp w, const struct SDL_Keysym *key)
{_
    auto level = game->level;
    if (!level) {
        return true;
    }

    auto player = level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

static uint8_t wid_wield_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    auto level = game->level;
    if (!level) {
        return true;
    }

    auto player = level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }

    wid_wield_slot(wid_get_int_context(w));
    return true;
}

static void wid_wield_mouse_over_b (Widp w, int32_t relx, int32_t rely,
                                      int32_t wheelx, int32_t wheely)
{_
    int slot = wid_get_int_context(w);

    DBG3("Describe wield slot %d", slot);
_
    if (slot >= (int)wield_items.size()) {
        wid_wield_destroy();
        return;
    }

    auto level = game->level;
    if (!level) {
        return;
    }

    auto player = level->player;
    if (!player) {
        return;
    }

    auto t = wield_items[slot];
    if (t) {
        wid_thing_info_fini();
        game->wid_thing_info_create(t);
    }
}

void Game::wid_wield_create (void)
{_
    BOTCON("Choose a weapon to wield.");

    DBG3("Thing wield create");
    change_state(Game::STATE_WIELDING_ITEMS);

    auto player = game->level->player;
    if (!player){
        change_state(Game::STATE_NORMAL);
        ERR("No player");
        return;
    }

    wield_items.clear();

    for (const auto& item : player->monstp->carrying) {
        auto t = level->thing_find(item.id);
        if (t->is_weapon()) {
            wield_items.push_back(t);
        }
    }

    //
    // In case a scancode was used to open this widget
    //
    wid_ignore_events_briefly();

    auto m = TERM_WIDTH / 2;
    point tl = make_point(m - 35, UI_TOPCON_VIS_HEIGHT + 10);
    point br = make_point(m + 35, tl.y + 25);
    auto width = br.x - tl.x;

    wid_wield = new WidPopup("wield", tl, br, nullptr, "",
                               false, true,
                               wield_items.size() * 3);

    wid_set_on_key_up(wid_wield->wid_popup_container, wid_wield_key_up);
    wid_set_on_key_down(wid_wield->wid_popup_container, wid_wield_key_down);

    wid_wield->log("Choose something to wield");

    int y_at = 3;
    for (auto slot = 0; slot < (int)wield_items.size(); slot++) {
        Game tmp;
        auto p = wid_wield->wid_text_area->wid_text_area;
        auto w = wid_new_container(p, "item slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 3, y_at + 2);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        auto t = wield_items[slot];

        {
            auto wid_icon = wid_new_square_button(w, "item icon");
            wid_set_int_context(wid_icon, slot);
            wid_set_on_mouse_up(wid_icon, wid_wield_mouse_up);
            wid_set_on_mouse_over_b(wid_icon, wid_wield_mouse_over_b);

            point tl = make_point(0, 0);
            point br = make_point(2, 2);
            wid_set_pos(wid_icon, tl, br);

            if (t) {
                auto tpp = t->tp();
                auto tiles = &tpp->tiles;
                if (tiles) {
                    auto tile = tile_first(tiles);
                    if (tile) {
                        wid_set_style(wid_icon, UI_WID_STYLE_DARK);
                        wid_set_fg_tile(wid_icon, tile);
                    }
                }
            } else {
                wid_set_style(wid_icon, UI_WID_STYLE_DARK);
            }

            wid_update(wid_icon);
        }

        {
            auto wid_item = wid_new_square_button(w, "item name");
            wid_set_int_context(wid_item, slot);
            wid_set_on_mouse_up(wid_item, wid_wield_mouse_up);
            wid_set_on_mouse_over_b(wid_item, wid_wield_mouse_over_b);

            point tl = make_point(3, 0);
            point br = make_point(width - 3, 2);
            wid_set_pos(wid_item, tl, br);
            wid_set_style(wid_item, UI_WID_STYLE_DARK);

            if (t) {
                if (slot < 9) {
                    wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". " +
                                 t->text_description());
                } else {
                    wid_set_text(wid_item, t->text_description());
                }
            }

            wid_set_text_lhs(wid_item, true);
            wid_update(wid_item);
        }
        wid_update(w);

        y_at += 3;
    }

    wid_update(wid_wield->wid_text_area->wid_text_area);
    wid_actionbar_init();
}
