//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_wid_popup.h"
#include "my_wid_rightbar.h"
#include "my_wid_inventory.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_wid_actionbar.h"
#include "my_sdl.h"
#include "my_wid.h"
#include "my_ui.h"

static Widp wid_actionbar;

void wid_actionbar_fini (void)
{_
    wid_destroy_nodelay(&wid_actionbar);
}

#if 0
static uint8_t wid_actionbar_use (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_actionbar_fini();

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return false;
    }

    player->use(chosen_thing);

    game->change_state(Game::STATE_NORMAL);
    return true;
}

static uint8_t wid_actionbar_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar back");
_
    wid_actionbar_fini();

    if (came_from_inventory) {
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini(); // To remove bag or other info
        return true;
    }

    game->change_state(Game::STATE_MOVING_ITEMS);
    game->request_remake_inventory = true;
    game->wid_thing_info_create(game->level->player, false);
    return true;
}

static uint8_t wid_actionbar_key_up (Widp w, const struct SDL_Keysym *key)
{_
    LOG("Actionbar key up");
_
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
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case 'u':
                        wid_actionbar_use(nullptr, 0, 0, 0);
                        return true;
                    case 't':
                        wid_actionbar_throw(nullptr, 0, 0, 0);
                        return true;
                    case 'e':
                        wid_actionbar_eat(nullptr, 0, 0, 0);
                        return true;
                    case 'd':
                        wid_actionbar_drop(nullptr, 0, 0, 0);
                        return true;
                    case 'm':
                        wid_actionbar_move(nullptr, 0, 0, 0);
                        return true;
                    case 'b':
                    case SDLK_ESCAPE:
                        wid_actionbar_back(nullptr, 0, 0, 0);
                        return true;
                }
            }
        }
    }

    return false;
}

static uint8_t wid_actionbar_key_down (Widp w, const struct SDL_Keysym *key)
{_
    LOG("Actionbar key down");
_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}
#endif

static uint8_t wid_actionbar_quit (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar quit");
_
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini(); // To remove bag or other info
    game->quit_select();
    return true;
}

static uint8_t wid_actionbar_close (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar close");
_
    if (!game->level) {
        return true;
    }

    auto player = game->level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }

    wid_thing_info_fini();
    wid_collect_destroy();
    wid_enchant_destroy();
    wid_skill_choose_destroy();
    wid_item_options_destroy();
    wid_load_destroy();
    wid_save_destroy();
    game_quit_destroy();

    game->change_state(Game::STATE_NORMAL);
    wid_actionbar_init();
    return true;
}

static uint8_t wid_actionbar_load (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar load");
_
    if (!game->level) {
        return true;
    }

    auto player = game->level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }

    wid_thing_info_fini();
    wid_collect_destroy();
    wid_enchant_destroy();
    wid_skill_choose_destroy();
    wid_item_options_destroy();
    wid_load_destroy();
    wid_save_destroy();
    game_quit_destroy();

    game->load_select();
    wid_actionbar_init();
    return true;
}

static uint8_t wid_actionbar_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar save");
_
    if (!game->level) {
        return true;
    }

    auto player = game->level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }

    wid_thing_info_fini();
    wid_collect_destroy();
    wid_enchant_destroy();
    wid_skill_choose_destroy();
    wid_item_options_destroy();
    wid_load_destroy();
    wid_save_destroy();
    game_quit_destroy();

    game->save_select();
    wid_actionbar_init();
    return true;
}

static uint8_t wid_actionbar_inventory (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar inventory");
_
    if (!game->level) {
        return true;
    }

    auto player = game->level->player;
    if (!player){
        return true;
    }

    if (player->is_dead){
        return true;
    }

    if (game->in_transit_item) {
        return true;
    }

    game->change_state(Game::STATE_MOVING_ITEMS);
    game->request_remake_inventory = true;
    game->wid_thing_info_create(player, false);

    return true;
}

void wid_actionbar_init (void)
{_
    LOG("Actionbar");
_
    if (!game->level) {
        return;
    }

    auto player = game->level->player;
    if (!player){
        return;
    }

    if (player->is_dead){
        return;
    }

    //
    // In case a scancode was used to open this widget
    //
    wid_ignore_events_briefly();

    if (wid_actionbar) {
        wid_actionbar_fini();
    }

    bool icon_collect = false;
    if (player->check_anything_to_carry()) {
        icon_collect = true;
    }

    bool icon_close = false;
    if (game->bags.size() ||
        wid_collect ||
        wid_skills ||
        wid_item_options_window ||
        wid_enchant ||
        wid_load ||
        wid_save ||
        game_quit_window) {
        icon_close = true;
    }

    int options = 9;

    if (icon_collect) {
        options++;
    }

    if (icon_close) {
        options++;
    }

    int option_width = 4;
    int w = options * option_width;
    int left_half = w / 2;
    int right_half = w - left_half;

    {_
        point tl = make_point(TERM_WIDTH / 2 - left_half,
                              TERM_HEIGHT - (option_width + 1));
        point br = make_point(TERM_WIDTH / 2 + right_half - 1,
                              TERM_HEIGHT - 2);

        wid_actionbar = wid_new_square_window("wid actionbar");
        wid_set_ignore_scroll_events(wid_actionbar, true);
        wid_set_pos(wid_actionbar, tl, br);
        wid_set_style(wid_actionbar, UI_WID_STYLE_DARK);
        wid_lower(wid_actionbar);
    }

    int x_at = 0;

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar quit");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_quit");
        wid_set_on_mouse_up(w, wid_actionbar_quit);
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar config");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_config");
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar save");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_save");
        wid_set_on_mouse_up(w, wid_actionbar_save);
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar load");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_load");
        wid_set_on_mouse_up(w, wid_actionbar_load);
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar zoom_in");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_zoom_in");
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar zoom_out");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_zoom_out");
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar wield");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_wield");
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar inventory");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_inventory");
        wid_set_on_mouse_up(w, wid_actionbar_inventory);
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar wait");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_wait");
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    if (icon_collect) {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar collect");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_collect");
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    if (icon_close) {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar close");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_close");
        wid_set_on_mouse_up(w, wid_actionbar_close);
#if 0
        wid_set_on_mouse_over_b(w, wid_inventory_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_inventory_mouse_over_e);
#endif
        x_at += option_width;
    }

    wid_update(wid_actionbar);
}
