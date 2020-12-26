//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_bag.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_thing.h"
#include "my_wid_popup.h"
#include "my_game.h"
#include "my_level.h"
#include "my_wid_inventory.h"

static void wid_bag_item_mouse_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
static void wid_bag_item_mouse_over_e(Widp w);
static void wid_bag_tick(Widp w);
static uint8_t wid_bag_item_mouse_down(Widp w, int32_t x, int32_t y, uint32_t button);

static void wid_bag_add_items (Widp wid_bag_container, Thingp bag)
{_
    bag->log("create bag with items widget");
    for (const auto& item : bag->monstp->carrying) {
        auto t = game->level->thing_find(item.id);
        auto tl = t->monstp->bag_position + point(1, 1);
        bag->log("+ item %s", t->to_string().c_str());

        if (t->monstp->bag_position == point(-1, -1)) {
            continue;
        }

        auto br = tl + point(t->bag_item_width() - 1, t->bag_item_height() - 1);

        auto w = wid_new_square_button(wid_bag_container, "wid_bag item");
        wid_set_pos(w, tl, br);
        wid_set_style(w, UI_WID_STYLE_DARK);

        if (t == game->level->player->weapon_get()) {
            wid_set_style(w, UI_WID_STYLE_RED);
        }

        wid_set_on_mouse_over_b(w, wid_bag_item_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_bag_item_mouse_over_e);
        wid_set_thing_id_context(w, item.id);
        wid_set_on_mouse_down(w, wid_bag_item_mouse_down);

        auto tpp = t->tp();
        auto tiles = &tpp->tiles;

        auto tile = tile_first(tiles);
        if (tile) {
            wid_set_fg_tile(w, tile);
        }
    }

    wid_update(wid_bag_container);
}

uint8_t wid_in_transit_item_place (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    if (!game->in_transit_item) {
        return false;
    }

    auto id = wid_get_thing_id_context(game->in_transit_item);
    auto t = game->level->thing_find(id);
    if (!t) {
        return false;
    }

    int slot;
    if (is_mouse_over_inventory_slot(slot)) {
        MINICON("placing in inventory");
        if (game->level->player->carry(t)) {
            MINICON("placing in inventory; carried");
            wid_destroy(&game->in_transit_item);
            game->remake_inventory = true;
        }
        return true;
    } else {
        MINICON("not over inventory");
    }

    auto wid_bag_container = is_mouse_over_any_bag();
    if (!wid_bag_container) {
        return false;
    }

    auto bag_id = wid_get_thing_id_context(wid_bag_container);
    auto bag = game->level->thing_find(bag_id);
    if (!bag) {
        return false;
    }

    auto at = point(ascii_mouse_x, ascii_mouse_y);
    static int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_bag_container, &tlx, &tly, &brx, &bry);
    at.x -= tlx;
    at.y -= tly;
    at.x -= 1;
    at.y -= 1;

    if (bag->bag_can_place_at(t, at)) {
        wid_destroy(&game->in_transit_item);
        t->monstp->preferred_bag_position = at;
        bag->carry(t);
        t->monstp->preferred_bag_position = point(-1, -1);
        while (bag->bag_compress()) { }
        game->remake_inventory = true;
    }

    return true;
}

static uint8_t wid_bag_item_mouse_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    if (game->in_transit_item) {
        return false;
    }

    auto id = wid_get_thing_id_context(w);
    auto t = game->level->thing_find(id);
    if (!t) {
        return false;
    }

    auto wid_bag_container = wid_get_parent(w);
    auto bag_id = wid_get_thing_id_context(wid_bag_container);
    auto bag = game->level->thing_find(bag_id);
    if (!bag) {
        return false;
    }

    auto old_owner = t->get_immediate_owner();
    if (!old_owner) {
        MINICON("%s has no owner so cannot move it!", t->text_The().c_str());
        return true;
    }

    bag->bag_remove(t);
    old_owner->drop_into_ether(t);
    while (bag->bag_compress()) { }

    t->describe_when_in_inventory();
    if (game->in_transit_item) {
        wid_destroy(&game->in_transit_item);
    }

    auto tl = point(ascii_mouse_x, ascii_mouse_y);
    auto br = tl + point(t->bag_item_width() - 1, t->bag_item_height() - 1);

    game->in_transit_item = wid_new_square_window("wid_bag in transit item");
    wid_set_pos(game->in_transit_item, tl, br);
    wid_set_style(game->in_transit_item, UI_WID_STYLE_GRAY);

    wid_set_thing_id_context(game->in_transit_item, id);
    wid_set_on_mouse_up(game->in_transit_item, wid_in_transit_item_place);

    auto tpp = t->tp();
    auto tiles = &tpp->tiles;

    auto tile = tile_first(tiles);
    if (tile) {
        wid_set_fg_tile(game->in_transit_item, tile);
    }

    wid_set_movable(game->in_transit_item, true);
    wid_update(game->in_transit_item);

    for (auto item : wid_find_all(wid_bag_container, "wid_bag item")) {
        wid_destroy_nodelay(&item);
    }

    wid_bag_add_items(wid_bag_container, bag);
    wid_update(wid_bag_container);

    return true;
}

static void wid_bag_item_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
    if (game->in_transit_item) {
        return;
    }

    auto id = wid_get_thing_id_context(w);
    auto t = game->level->thing_find(id);
    if (t) {
        t->describe_when_in_inventory();
    }
}

static void wid_bag_item_mouse_over_e (Widp w)
{
    if (game->in_transit_item) {
        return;
    }

    BOTCON("");
}

static void wid_bag_tick (Widp w)
{
    if (game->in_transit_item) {
        wid_move_to_abs(game->in_transit_item, ascii_mouse_x, ascii_mouse_y);
    }
}

WidBag::~WidBag()
{
    wid_destroy(&wid_bag_container);
    wid_destroy(&wid_bag_title);

    auto b = std::find(game->bags.begin(), game->bags.end(), this);
    if (b != game->bags.end()) {
        game->bags.erase(b);
    }
}

WidBag::WidBag (Thingp bag_, point tl, point br, const std::string &title) : tl(tl), br(br)
{_
    bag = bag_;

    {
        wid_bag_container = wid_new_square_window("wid_bag " + title);
        wid_set_pos(wid_bag_container, tl, br);
        wid_set_style(wid_bag_container, UI_WID_STYLE_BAG);
        wid_set_on_tick(wid_bag_container, wid_bag_tick);
        wid_set_thing_id_context(wid_bag_container, bag->id);
    }

    {
        wid_bag_title = wid_new_square_window("wid_bag_title " + title);
        wid_set_pos(wid_bag_title, point(tl.x, tl.y - 1), point(br.x, tl.y - 1));
        wid_set_style(wid_bag_title, UI_WID_STYLE_NONE);
        wid_set_text(wid_bag_title, title);
    }

    wid_bag_add_items(wid_bag_container, bag);

    wid_update(wid_bag_container);
    wid_update(wid_bag_title);

    game->bags.push_back(this);
}

Widp is_mouse_over_any_bag (void)
{
    for (auto b : game->bags) {
        auto w = b->wid_bag_container;

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

        wid_get_tl_x_tl_y_br_x_br_y(w, &tlx, &tly, &brx, &bry);

        //
        // Add some border
        //
        tlx -= 1;
        brx += 1;
        tly -= 1;
        bry += 1;

        if ((x >= tlx) && (x < brx) && (y >= tly)) {
            //CON("    inventory %d %d %d", tlx, brx, x);
            return w;
        }
        //CON("NOT inventory %d %d %d", tlx, brx, x);
    }
    return nullptr;
}
