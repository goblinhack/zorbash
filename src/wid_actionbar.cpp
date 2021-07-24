//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_thing_template.h"
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

static timestamp_t wid_last_wait;
static timestamp_t wid_last_wait_repeat;

void wid_actionbar_close_all_popups (void)
{_
    wid_thing_info_fini();
    wid_collect_destroy();
    wid_wield_destroy();
    wid_enchant_destroy();
    wid_skill_choose_destroy();
    wid_item_options_destroy();
    wid_load_destroy();
    wid_save_destroy();
    game_quit_destroy();
    game_config_keyboard_destroy();
    game->change_state(Game::STATE_NORMAL);
}

void wid_actionbar_fini (void)
{_
    wid_destroy_nodelay(&wid_actionbar);
}

static uint8_t wid_actionbar_quit (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar quit");
_
    wid_actionbar_close_all_popups();
    game->quit_select();
    return true;
}

static void wid_actionbar_quit_over_b (Widp w, int32_t relx, int32_t rely, 
                                       int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to quit the dungeon.");
}

static void wid_actionbar_quit_over_e (Widp w)
{_
    BOTCON(" ");
}

void wid_actionbar_robot_mode (void)
{_
    LOG("Actionbar robot");
_
    wid_actionbar_close_all_popups();
    game->robot_mode = !game->robot_mode;
    wid_actionbar_init();
}

void wid_actionbar_robot_mode_off (void)
{_
    LOG("Actionbar robot");
_
    wid_actionbar_close_all_popups();
    game->robot_mode = false;
    if (game->level) {
        game->level->debug_path_clear();
    }
    wid_actionbar_init();
}

static uint8_t wid_actionbar_robot (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_actionbar_robot_mode();
    return true;
}

static void wid_actionbar_robot_over_b (Widp w, int32_t relx, int32_t rely, 
                                        int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to explore the dungeon like a robot.");
}

static void wid_actionbar_robot_over_e (Widp w)
{_
    BOTCON(" ");
}

static void wid_actionbar_robot_tick (Widp w)
{_
    game->robot_mode_tick();
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

    wid_actionbar_close_all_popups();
    wid_actionbar_init();
    return true;
}

static void wid_actionbar_close_over_b (Widp w, int32_t relx, int32_t rely, 
                                        int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to close any popups.");
}

static void wid_actionbar_close_over_e (Widp w)
{_
    BOTCON(" ");
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

    wid_actionbar_close_all_popups();
    game->load_select();
    wid_actionbar_init();
    return true;
}

static void wid_actionbar_load_over_b (Widp w, int32_t relx, int32_t rely, 
                                       int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to load a previously saved dungeon.");
}

static void wid_actionbar_load_over_e (Widp w)
{_
    BOTCON(" ");
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

    wid_actionbar_close_all_popups();
    game->save_select();
    wid_actionbar_init();
    return true;
}

static void wid_actionbar_save_over_b (Widp w, int32_t relx, int32_t rely, 
                                       int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to save the current dungeon.");
}

static void wid_actionbar_save_over_e (Widp w)
{_
    BOTCON(" ");
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

    wid_actionbar_close_all_popups();
    game->change_state(Game::STATE_MOVING_ITEMS);
    game->request_remake_inventory = true;
    game->wid_thing_info_create(player, false);

    return true;
}

static void wid_actionbar_inventory_over_b (Widp w, int32_t relx, int32_t rely, 
                                            int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to see what you are carrying.");
}

static void wid_actionbar_inventory_over_e (Widp w)
{_
    BOTCON(" ");
}

static uint8_t wid_actionbar_collect (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar collect");
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

    wid_actionbar_close_all_popups();

    auto items = player->anything_to_carry();
    if (items.empty()) {
        TOPCON("Nothing to carry here.");
    } else {
        game->wid_collect_create(items);
    }
    return true;
}

static void wid_actionbar_collect_over_b (Widp w, int32_t relx, int32_t rely, 
                                          int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to collect any loot you are over.");
}

static void wid_actionbar_collect_over_e (Widp w)
{_
    BOTCON(" ");
}

static uint8_t wid_actionbar_wield (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar wield");
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

    wid_actionbar_close_all_popups();

    for (const auto& item : player->monstp->carrying) {
        auto t = game->level->thing_find(item.id);
        if (t->is_weapon()) {
            game->wid_wield_create();
            return true;
        }
    }

    TOPCON("You have no weapon to wield!");
    return true;
}

static void wid_actionbar_wield_over_b (Widp w, int32_t relx, int32_t rely, 
                                        int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to wield a new weapon.");
}

static void wid_actionbar_wield_over_e (Widp w)
{_
    BOTCON(" ");
}

static uint8_t wid_actionbar_wait (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar wait");
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

    wid_last_wait = time_get_time_ms_cached();

    wid_actionbar_close_all_popups();

    TOPCON("You pass the time...");
    game->tick_begin("wait");

    return true;
}

static uint8_t wid_actionbar_repeat_wait (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar wait");
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

    if (!time_have_x_tenths_passed_since(5, wid_last_wait)) {
        return true;
    }

    if (!time_have_x_tenths_passed_since(1, wid_last_wait_repeat)) {
        return true;
    }

    wid_last_wait_repeat = time_get_time_ms_cached();

    wid_actionbar_close_all_popups();

    TOPCON("You continue to pass the time...");
    game->tick_begin("wait");

    return true;
}

static void wid_actionbar_wait_over_b (Widp w, int32_t relx, int32_t rely, 
                                       int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to happily pass the time of day.");
}

static void wid_actionbar_wait_over_e (Widp w)
{_
    BOTCON(" ");
}

static uint8_t wid_actionbar_zoom_out (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar zoom out");
_
    if (!game->level) {
        return true;
    }

    wid_actionbar_close_all_popups();
    config_game_pix_zoom_out();
    return true;
}

static void wid_actionbar_zoom_out_over_b (Widp w, int32_t relx, int32_t rely, 
                                           int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to zoom out the map.");
}

static void wid_actionbar_zoom_out_over_e (Widp w)
{_
    BOTCON(" ");
}

static uint8_t wid_actionbar_zoom_in (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar zoom in");
_
    if (!game->level) {
        return true;
    }

    wid_actionbar_close_all_popups();
    config_game_pix_zoom_in();
    return true;
}

static void wid_actionbar_zoom_in_over_b (Widp w, int32_t relx, int32_t rely, 
                                          int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to zoom in the map.");
}

static void wid_actionbar_zoom_in_over_e (Widp w)
{_
    BOTCON(" ");
}

static uint8_t wid_actionbar_configure (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Actionbar configure");
_
    if (!game->level) {
        return true;
    }

    wid_actionbar_close_all_popups();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini(); // To remove bag or other info
    game->config_keyboard_select();
    return true;
}

static void wid_actionbar_configure_over_b (Widp w, int32_t relx, int32_t rely, 
                                            int32_t wheelx, int32_t wheely)
{_
    BOTCON("Select this to change key settings.");
}

static void wid_actionbar_configure_over_e (Widp w)
{_
    BOTCON(" ");
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
        wid_wield ||
        wid_skills ||
        wid_item_options_window ||
        wid_enchant ||
        wid_load ||
        wid_save ||
        game_config_keyboard_window ||
        game_quit_window) {
        icon_close = true;
    }

    int options = 10;

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
        wid_set_on_mouse_over_b(w, wid_actionbar_quit_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_quit_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar config");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_config");
        wid_set_on_mouse_up(w, wid_actionbar_configure);
        wid_set_on_mouse_over_b(w, wid_actionbar_configure_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_configure_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar robot");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_robot");
        wid_set_on_mouse_up(w, wid_actionbar_robot);
        wid_set_on_mouse_over_b(w, wid_actionbar_robot_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_robot_over_e);
        if (game->robot_mode) {
            wid_set_bg_tilename(w, "icon_robot_on");
            wid_set_on_tick(w, wid_actionbar_robot_tick);
        }
            wid_set_style(w, UI_WID_STYLE_RED);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar save");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_save");
        wid_set_on_mouse_up(w, wid_actionbar_save);
        wid_set_on_mouse_over_b(w, wid_actionbar_save_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_save_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar load");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_load");
        wid_set_on_mouse_up(w, wid_actionbar_load);
        wid_set_on_mouse_over_b(w, wid_actionbar_load_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_load_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar zoom_in");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_zoom_in");
        wid_set_on_mouse_up(w, wid_actionbar_zoom_in);
        wid_set_on_mouse_over_b(w, wid_actionbar_zoom_in_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_zoom_in_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar zoom_out");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_zoom_out");
        wid_set_on_mouse_up(w, wid_actionbar_zoom_out);
        wid_set_on_mouse_over_b(w, wid_actionbar_zoom_out_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_zoom_out_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar wield");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_wield");

        auto weapon = player->weapon_get();
        if (weapon) {
            auto tpp = weapon->tp();
            auto tiles = &tpp->tiles;
            if (tiles) {
                auto tile = tile_first(tiles);
                if (tile) {
                    wid_set_bg_tilename(w, "icon_none");
                    wid_set_fg_tile(w, tile);
                }
            }
        }
        wid_set_on_mouse_up(w, wid_actionbar_wield);
        wid_set_on_mouse_over_b(w, wid_actionbar_wield_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_wield_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar inventory");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_inventory");
        wid_set_on_mouse_up(w, wid_actionbar_inventory);
        wid_set_on_mouse_over_b(w, wid_actionbar_inventory_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_inventory_over_e);
        x_at += option_width;
    }

    {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar wait");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_wait");
        wid_set_on_mouse_down(w, wid_actionbar_wait);
        wid_set_on_mouse_held_down(w, wid_actionbar_repeat_wait);
        wid_set_on_mouse_over_b(w, wid_actionbar_wait_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_wait_over_e);
        x_at += option_width;
    }

    if (icon_collect) {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar collect");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_collect");
        wid_set_on_mouse_up(w, wid_actionbar_collect);
        wid_set_on_mouse_over_b(w, wid_actionbar_collect_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_collect_over_e);
        x_at += option_width;
    }

    if (icon_close) {
        auto w = wid_new_square_button(wid_actionbar, "wid actionbar close");
        point tl = make_point(x_at, 0);
        point br = make_point(x_at + option_width - 1, option_width - 1);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "icon_close");
        wid_set_on_mouse_up(w, wid_actionbar_close);
        wid_set_on_mouse_over_b(w, wid_actionbar_close_over_b);
        wid_set_on_mouse_over_e(w, wid_actionbar_close_over_e);
        x_at += option_width;
    }

    wid_update(wid_actionbar);
}
