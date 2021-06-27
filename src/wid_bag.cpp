//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_sys.h"
#include "my_sdl.h"
#include "my_wid_bag.h"
#include "my_main.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_wid_popup.h"
#include "my_game.h"
#include "my_level.h"
#include "my_wid_rightbar.h"
#include "my_wid_thing_info.h"
#include "my_wid_topcon.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"
#include "my_ui.h"
#include "my_monst.h"
#include "my_game.h"
#include "slre.h"

static uint8_t wid_bag_item_mouse_down(Widp w, int32_t x, int32_t y, uint32_t button);
static void wid_bag_item_mouse_over_b(Widp w, int32_t relx, int32_t rely, 
                                      int32_t wheelx, int32_t wheely);
static void wid_bag_item_mouse_over_e(Widp w);
static uint8_t wid_bag_item_key_down(Widp w, const struct SDL_Keysym *key);
static void wid_bag_tick(Widp w);

static void wid_bag_add_items (Widp wid_bag_container, Thingp bag)
{_
    bag->log("Empty bag");
    for (auto item : wid_find_all_containing(wid_bag_container, "wid_bag item")) {
        bag->log("+ destroy item %s", wid_get_name(item).c_str());
        wid_destroy_nodelay(&item);
    }

    bag->log("Populate the bag");

    for (const auto& item : bag->monstp->carrying) {
        auto t = game->thing_find(item.id);
        if (!t) {
            continue;
        }

        auto tl = t->monstp->bag_position + point(1, 1);

        if (t->monstp->bag_position == point(-1, -1)) {
            bag->log("+ item %s at %d,%d (not carried in bag)", t->to_string().c_str(),
                     t->monstp->bag_position.x, t->monstp->bag_position.y);
            continue;
        }

        auto br = tl + point(t->item_width() - 1, t->item_height() - 1);

        auto w = wid_new_square_button(wid_bag_container, "wid_bag item" + t->to_string());
        wid_set_pos(w, tl, br);
        wid_set_style(w, UI_WID_STYLE_DARK);

        if (t == game->level->player->weapon_get()) {
            bag->log("+ item %s at %d,%d (wielded)", t->to_string().c_str(),
                     t->monstp->bag_position.x, t->monstp->bag_position.y);
            wid_set_style(w, UI_WID_STYLE_RED);
        } else {
            bag->log("+ item %s at %d,%d", t->to_string().c_str(),
                     t->monstp->bag_position.x, t->monstp->bag_position.y);
        }

        wid_set_on_mouse_over_b(w, wid_bag_item_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_bag_item_mouse_over_e);
        wid_set_on_key_down(w, wid_bag_item_key_down);
        wid_set_thing_id_context(w, item.id);
        wid_set_thing_id2_context(w, bag->id);
        wid_set_on_mouse_down(w, wid_bag_item_mouse_down);

        auto tpp = t->tp();
        auto tiles = &tpp->tiles;

        auto tile = tile_first(tiles);
        if (tile) {
            wid_set_fg_tile(w, tile);
        } else {
            bag->err("+ no tile item %s at %d,%d", t->to_string().c_str(),
                     t->monstp->bag_position.x, t->monstp->bag_position.y);
        }

        //
        // Show a small visible button key
        //
        auto slot = game->level->inventory_get_slot(t);
        if (slot != -1) {
            auto w = wid_new_square_button(wid_bag_container, 
                                           "wid_bag button" + t->to_string());
            wid_set_pos(w, tl, tl);
            wid_set_on_mouse_over_b(w, wid_bag_item_mouse_over_b);
            wid_set_on_mouse_over_e(w, wid_bag_item_mouse_over_e);
            wid_set_on_key_down(w, wid_bag_item_key_down);
            wid_set_thing_id_context(w, item.id);
            wid_set_thing_id2_context(w, bag->id);
            wid_set_on_mouse_down(w, wid_bag_item_mouse_down);

            wid_set_fg_tilename(w, "key_" + std::to_string(slot + 1));
            wid_set_text_lhs(w, true);
            wid_set_text_top(w, true);
        }
    }

    wid_update(wid_bag_container);
}

uint8_t wid_in_transit_item_place (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Place in transit item");
_
    //
    // Allow click to move and then click to drop / or drag and drop
    //
    if (!time_have_x_tenths_passed_since(2, game->last_mouse_down)) {
        LOG("Mouse up too soon; ignore");
        return true;
    }

    if (!game->in_transit_item) {
        LOG("No in transit item");
        return false;
    }

    auto id = wid_get_thing_id_context(game->in_transit_item);
    auto t = game->thing_find(id);
    if (!t) {
        LOG("Cannot find thing");
        return false;
    }

    t->log("In transit item place");

    if (is_mouse_over_rightbar()) {
        t->log("Is over inventory");
        if (game->level->player->carry(t)) {
            t->log("Placed in inventory");
            wid_destroy(&game->in_transit_item);
            t->log("Placed item: request to remake inventory");
            game->request_remake_inventory = true;
        }
        return true;
    }

    auto wid_bag_container = is_mouse_over_any_bag();
    if (!wid_bag_container) {
        t->log("Is not over any bag");
        return false;
    }

    auto bag_id = wid_get_thing_id_context(wid_bag_container);
    auto bag = game->thing_find(bag_id);
    if (!bag) {
        t->log("Bag containing me not found");
        return false;
    }

    auto at = point(ascii_mouse_x, ascii_mouse_y);
    static int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_bag_container, &tlx, &tly, &brx, &bry);
    at.x -= tlx;
    at.y -= tly;
    at.x -= 1;
    at.y -= 1;

    bag->log("Try to place %s at %d,%d", t->to_string().c_str(), at.x, at.y);
    if (bag->bag_can_place_at(t, at)) {
        t->log("Can place at %d,%d", at.x, at.y);

        wid_destroy(&game->in_transit_item);

        t->monstp->preferred_bag_position = at;
        bag->carry(t);
        t->monstp->preferred_bag_position = point(-1, -1);

        if (t->is_bag_item_container()) {
            game->inventory_highlight_slot = game->previous_slot;
        }

        t->log("Compress bag and request to remake inventory");
        while (bag->bag_compress()) { }
        game->request_remake_inventory = true;

        t->log("In transit item place completed");
        wid_bag_add_items(wid_bag_container, bag);
    } else {
        t->log("In transit item place failed");
        TOPCON("Could not fit that item. You can always drop the item if needed.");
    }

    //
    // Moving things around your bag has a cost...
    //
    game->tick_begin("moved an in transit item");

    return true;
}

uint8_t wid_in_transit_item_drop (void)
{_
    LOG("Drop in transit item");
_
    if (!game->in_transit_item) {
        LOG("No in transit item");
        return false;
    }

    auto id = wid_get_thing_id_context(game->in_transit_item);
    auto t = game->thing_find(id);
    if (!t) {
        ERR("Cannot find thing to drop");
        return false;
    }

    t->log("Drop from ether");
    game->level->player->drop_from_ether(t);
    wid_destroy(&game->in_transit_item);
    game->request_remake_inventory = true;

    //
    // Moving things around your bag has a cost...
    //
    game->tick_begin("dropped an in transit item");

    return true;
}

static uint8_t wid_bag_item_mouse_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Mouse down, pickup up an item and make it in transit");
_
    if (game->in_transit_item) {
        return false;
    }

    auto id = wid_get_thing_id_context(w);
    auto t = game->thing_find(id);
    if (!t) {
        return false;
    }

    auto wid_bag_container = wid_get_parent(w);
    auto bag_id = wid_get_thing_id_context(wid_bag_container);
    auto bag = game->thing_find(bag_id);
    if (!bag) {
        return false;
    }

    auto old_owner = t->get_immediate_owner();
    if (!old_owner) {
        ERR("%s has no owner so cannot move it!", t->text_The().c_str());
        return true;
    }

    bag->bag_remove(t);
    old_owner->drop_into_ether(t);
    while (bag->bag_compress()) { }

    t->describe_when_hovered_over_in_rightbar();
    if (game->in_transit_item) {
        wid_destroy(&game->in_transit_item);
    }

    auto tl = point(ascii_mouse_x, ascii_mouse_y);
    auto br = tl + point(t->item_width() - 1, t->item_height() - 1);

    game->in_transit_item = wid_new_square_window("wid_bag in transit item");
    wid_set_ignore_scroll_events(game->in_transit_item, true);
    wid_set_pos(game->in_transit_item, tl, br);
    wid_set_style(game->in_transit_item, UI_WID_STYLE_GRAY);
    wid_set_do_not_lower(game->in_transit_item, true);

    wid_set_thing_id_context(game->in_transit_item, id);
    wid_set_on_mouse_up(game->in_transit_item, wid_in_transit_item_place);

    auto tpp = t->tp();
    auto tiles = &tpp->tiles;

    auto tile = tile_first(tiles);
    if (tile) {
        wid_set_fg_tile(game->in_transit_item, tile);
    }

    wid_set_moveable(game->in_transit_item, true);
    wid_update(game->in_transit_item);

    LOG("Remake the bag without the transit item");
    game->request_remake_inventory = true;
    game->wid_thing_info_create(game->level->player, false);
    LOG("Recreate inventory");
    game->change_state(Game::STATE_MOVING_ITEMS);

    return true;
}

static void wid_bag_item_mouse_over_b (Widp w, int32_t relx, int32_t rely, 
                                       int32_t wheelx, int32_t wheely)
{
    if (game->in_transit_item) {
        return;
    }

    auto id = wid_get_thing_id_context(w);
    auto t = game->thing_find(id);
    if (t) {
        t->describe_when_hovered_over_in_rightbar();
    }

    game->wid_thing_info_clear_popup();
    game->wid_thing_info_push_popup(t);
}

static void wid_bag_item_mouse_over_e (Widp w)
{
    if (game->in_transit_item) {
        return;
    }

    BOTCON(" ");
}

static uint8_t wid_bag_item_key_down (Widp w, const struct SDL_Keysym *key)
{_
    LOG("Bag item key down");
_
    auto level = game->level;
    if (!level) {
        return false;
    }

    auto player = level->player;
    if (player && player->is_dead) {
        LOG("Ignore input; player is dead");
        return false;
    }

    if (wid_over != w) {
        LOG("Pass key to topcon as not over wid");
        return wid_topcon_input(w, key);

    }

    if (game->state == Game::STATE_COLLECTING_ITEMS) {
        if (key->scancode == SDL_SCANCODE_ESCAPE) {
            LOG("Escape pressed, clear collecting items state");
_
            game->change_state(Game::STATE_NORMAL);
            return true;
        }
    }

    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    auto id = wid_get_thing_id_context(w);
    auto what = game->thing_find(id);
    if (!what) {
        LOG("Cannot find thing");
        return false;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_drop) {
        if (game->level->player->drop(what)) {
            game->tick_begin("drop");
        }

        game->request_remake_inventory = true;
        game->wid_thing_info_create(game->level->player, false);
        return true;
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
            if (key->scancode == (SDL_Scancode)game->config.key_action0) {
                game->level->inventory_assign(9, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action1) {
                game->level->inventory_assign(0, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action2) {
                game->level->inventory_assign(1, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action3) {
                game->level->inventory_assign(2, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action4) {
                game->level->inventory_assign(3, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action5) {
                game->level->inventory_assign(4, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action6) {
                game->level->inventory_assign(5, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action7) {
                game->level->inventory_assign(6, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action8) {
                game->level->inventory_assign(7, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            if (key->scancode == (SDL_Scancode)game->config.key_action9) {
                game->level->inventory_assign(8, what);
                game->request_remake_inventory = true;
                game->wid_thing_info_create(game->level->player, false);
                return true;
            }
            break;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_drop) {
        LOG("Pressed drop key");
_
        if (player->drop(what)) {
            game->tick_begin("drop");
        }
        game->request_remake_inventory = true;
        game->wid_thing_info_create(game->level->player, false);
        return true;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_eat) {
        LOG("Pressed eat key");
_
        player->use(what);
        if (game->state == Game::STATE_MOVING_ITEMS) {
            game->request_remake_inventory = true;
            game->wid_thing_info_create(game->level->player, false);
        }
        return true;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_use) {
        LOG("Pressed use key");
        player->use(what);
        if (game->state == Game::STATE_MOVING_ITEMS) {
            game->request_remake_inventory = true;
            game->wid_thing_info_create(game->level->player, false);
        }
        return true;
    }

    if (key->scancode == (SDL_Scancode)game->config.key_throw) {
        LOG("Pressed throw key");
_
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini(); // To remove bag or other info
        player->throw_item_choose_target(what);
        return true;
    }

    LOG("Pass key to topcon");
    return wid_topcon_input(w, key);
}

static void wid_bag_tick (Widp w)
{
    if (game->in_transit_item) {
        wid_move_to_abs(game->in_transit_item, ascii_mouse_x, ascii_mouse_y);
    }
}

WidBag::~WidBag()
{
    bag->log("Destroy bag");
_
    wid_destroy(&wid_bag_container);
    wid_destroy(&wid_bag_title);

    auto b = std::find(game->bags.begin(), game->bags.end(), this);
    if (b != game->bags.end()) {
        game->bags.erase(b);
    }
}

WidBag::WidBag (Thingp bag_, point tl, point br, const std::string &title) : tl(tl), br(br)
{_
    LOG("Create bag");
_
    bag = bag_;

    {
        wid_bag_container = wid_new_square_window("wid_bag " + title);
        wid_set_ignore_scroll_events(wid_bag_container, true);
        wid_set_pos(wid_bag_container, tl, br);
        wid_set_style(wid_bag_container, UI_WID_STYLE_BAG);
        wid_set_on_tick(wid_bag_container, wid_bag_tick);
        wid_set_thing_id_context(wid_bag_container, bag->id);
    }

    {
        wid_bag_title = wid_new_square_window("wid_bag_title " + title);
        wid_set_ignore_scroll_events(wid_bag_title, true);
        wid_set_pos(wid_bag_title, point(tl.x, tl.y - 1), point(br.x, tl.y - 1));
        wid_set_style(wid_bag_title, UI_WID_STYLE_SPARSE_NONE);
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
