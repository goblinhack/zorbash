//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_game.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ttf.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "slre.hpp"

static void wid_bag_tick(Widp w);

static void wid_bag_add_items(Widp wid_bag_container, Thingp bag)
{
  TRACE_AND_INDENT();
  bag->log("Empty bag");
  for (auto item : wid_find_all_containing(wid_bag_container, "wid_bag item")) {
    bag->log("+ destroy item %s", wid_get_name(item).c_str());
    wid_destroy_nodelay(&item);
  }

  bag->log("Populate the bag");

  //
  // Intentionally not walking the bag children here
  //
  FOR_ALL_CARRIED_BY(bag, item)
  {
    auto t = game->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }

    auto tl = t->itemsp()->bag_position + point(1, 1);

    if (t->itemsp()->bag_position == point(-1, -1)) {
      bag->log("+ item %s at %d,%d (not carried in bag)", t->to_string().c_str(), t->itemsp()->bag_position.x,
               t->itemsp()->bag_position.y);
      continue;
    }

    auto br = tl + point(t->item_width() - 1, t->item_height() - 1);

    auto w = wid_new_square_button(wid_bag_container, "wid_bag item" + t->to_string());
    wid_set_pos(w, tl, br);
    wid_set_style(w, UI_WID_STYLE_DARK);

    if (t == wid_inventory_thing_selected) {
      wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
    }

    bag->log("+ item %s at %d,%d", t->to_string().c_str(), t->itemsp()->bag_position.x, t->itemsp()->bag_position.y);

    wid_set_on_mouse_over_begin(w, wid_bag_item_mouse_over_begin);
    wid_set_on_mouse_over_end(w, wid_bag_item_mouse_over_end);
    wid_set_on_key_down(w, wid_bag_item_key_down);
    wid_set_thing_id_context(w, t->id);
    wid_set_thing_id2_context(w, bag->id);
    wid_set_on_mouse_up(w, wid_bag_item_mouse_up);
    wid_set_on_mouse_held(w, wid_bag_item_mouse_held);

    auto tpp   = t->tp();
    auto tiles = &tpp->tiles;

    auto tile = tile_first(tiles);
    if (tile) {
      wid_set_fg_tile(w, tile);
    } else {
      bag->err("+ no tile item %s at %d,%d", t->to_string().c_str(), t->itemsp()->bag_position.x,
               t->itemsp()->bag_position.y);
    }

    //
    // Show a small visible button key
    //
    auto slot = game->level->inventory_get_slot(t);
    if (slot != -1) {
      auto w = wid_new_square_button(wid_bag_container, "wid_bag button" + t->to_string());
      wid_set_pos(w, tl, tl);
      wid_set_fg_tilename(w, "key_" + std::to_string(slot + 1));
      wid_set_text_lhs(w, true);
      wid_set_text_top(w, true);
    }
  }

  wid_update(wid_bag_container);
}

static void wid_in_transit_item_place_in_bag(Widp wid_bag_container, Thingp bag, Thingp t, point at)
{
  t->log("Can place at %d,%d", at.x, at.y);

  wid_destroy(&game->in_transit_item);

  t->itemsp()->preferred_bag_position = at;
  bag->carry(t, false /* auto equip */);
  t->itemsp()->preferred_bag_position = point(-1, -1);

  if (t->is_bag_item_container()) {
    game->inventory_highlight_slot = game->previous_slot;
  }

  t->log("Compress bag and request to remake inventory");
  while (bag->bag_compress()) {
  }
  game->request_remake_rightbar = true;

  t->log("In transit item place completed");
  wid_bag_add_items(wid_bag_container, bag);

  wid_inventory_select_requested(t);
}

uint8_t wid_in_transit_item_place(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Place in transit item");
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (player && player->is_dead) {
    DBG3("Ignore input; player is dead");
    return false;
  }

  if (! game->in_transit_item) {
    DBG3("No in transit item");
    return false;
  }

  auto id = wid_get_thing_id_context(game->in_transit_item);
  auto t  = game->thing_find(id);
  if (unlikely(! t)) {
    DBG3("Cannot find thing");
    return false;
  }

  t->log("In transit item place");

  //
  // Pver the rightbar?
  //
  if (is_mouse_over_rightbar()) {
    t->log("Is over inventory");
    if (game->level->player->carry(t)) {
      t->log("Placed in inventory");
      wid_destroy(&game->in_transit_item);
      t->log("Placed item: Request to remake inventory");
      game->request_remake_rightbar = true;
    }
    return true;
  }

  //
  // Over a slot?
  //
  auto wid_bag_container = is_mouse_over_any_bag();

  for (auto over : wid_find_all_at(point(x, y))) {
    if (over->name == "item slot") {
      auto slot = wid_get_int_context(over);
      game->level->inventory_assign(slot, t);
      wid_bag_container             = wid_inventory_bag->wid_bag_container;
      game->request_remake_rightbar = true;
      wid_inventory_select_requested(t);
      break;
    }

    if (over->name == "equip_weapon") {
      auto what = t;
      if (! what->is_weapon()) {
        TOPCON("Cannot equip %s as a weapon.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_armor") {
      auto what = t;
      if (! what->is_armor()) {
        TOPCON("Cannot equip %s as armor.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_cloak") {
      auto what = t;
      if (! what->is_cloak()) {
        TOPCON("Cannot equip %s as cloak.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_amulet") {
      auto what = t;
      if (! what->is_amulet()) {
        TOPCON("Cannot equip %s as amulet.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_boots") {
      auto what = t;
      if (! what->is_boots()) {
        TOPCON("Cannot equip %s as boots.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_helmet") {
      auto what = t;
      if (! what->is_helmet()) {
        TOPCON("Cannot equip %s as helmet.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_gauntlet") {
      auto what = t;
      if (! what->is_gauntlet()) {
        TOPCON("Cannot equip %s as gauntlet.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_shield") {
      auto what = t;
      if (! what->is_shield()) {
        TOPCON("Cannot equip %s as shield.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Equip the new item
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_ring1") {
      auto what = t;
      if (! what->is_ring()) {
        TOPCON("Cannot wear %s as a ring.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Wear the ring
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what, MONST_EQUIP_RING1);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }

    if (over->name == "equip_ring2") {
      auto what = t;
      if (! what->is_ring()) {
        TOPCON("Cannot wear %s as a ring.", what->text_the().c_str());
        sound_play("bonk");
        return false;
      }

      //
      // Wear the ring
      //
      player->log("Use %s", what->to_short_string().c_str());
      player->use(what, MONST_EQUIP_RING2);

      wid_destroy(&game->in_transit_item);
      wid_inventory_init();
      game->request_remake_rightbar = true;
      return true;
    }
  }

  if (! wid_bag_container) {
    t->log("Is not over any bag");
    wid_in_transit_item_drop();
    game->request_remake_inventory = true;
    return false;
  }

  auto bag_id = wid_get_thing_id_context(wid_bag_container);
  auto bag    = game->thing_find(bag_id);
  if (! bag) {
    wid_in_transit_item_drop();
    game->request_remake_inventory = true;
    return false;
  }

  auto       at = point(ascii_mouse_x, ascii_mouse_y);
  static int tlx, tly, brx, bry;
  wid_get_tl_x_tl_y_br_x_br_y(wid_bag_container, &tlx, &tly, &brx, &bry);
  at.x -= tlx;
  at.y -= tly;
  at.x -= 1;
  at.y -= 1;

  //
  // Try to place the item at the chosen location, or the last place thie
  // iteam was at, or last resort, anywhere.
  // /
  bag->log("Try to place %s at %d,%d", t->to_string().c_str(), at.x, at.y);
  if (bag->bag_can_place_at(t, at)) {
    wid_in_transit_item_place_in_bag(wid_bag_container, bag, t, at);
  } else if (t->maybe_itemsp() && bag->bag_can_place_at(t, t->itemsp()->last_bag_position)) {
    //
    // Place back where it was picked up
    //
    wid_in_transit_item_place_in_bag(wid_bag_container, bag, t, t->itemsp()->last_bag_position);
  } else {
    //
    // Place anywhere
    //
    point where;
    if (bag->bag_can_place_anywhere(t, where)) {
      wid_in_transit_item_place_in_bag(wid_bag_container, bag, t, where);
    } else {
      t->log("In transit item place failed");
      TOPCON("Could not fit that item. You can always drop the item if needed.");
    }
  }

  DBG3("Pressed in transit item; change state");
  wid_inventory_init();
  game->request_remake_rightbar = true;

  //
  // Moving things around your bag has a cost...
  //
  game->tick_begin("moved an in transit item");

  return true;
}

uint8_t wid_in_transit_item_drop(void)
{
  TRACE_AND_INDENT();
  DBG3("Drop in transit item");
  TRACE_AND_INDENT();
  if (! game->in_transit_item) {
    DBG3("No in transit item");
    return false;
  }

  auto id = wid_get_thing_id_context(game->in_transit_item);
  auto t  = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("Cannot find thing to drop");
    return false;
  }

  t->log("Drop from ether");
  game->level->player->drop_from_ether(t);
  wid_destroy(&game->in_transit_item);

  DBG3("Pressed in transit item; change state");
  wid_inventory_init();
  game->request_remake_rightbar = true;

  //
  // Moving things around your bag has a cost...
  //
  game->tick_begin("dropped an in transit item");

  return true;
}

uint8_t wid_bag_item_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Mouse down, item select");
  TRACE_AND_INDENT();
  if (game->in_transit_item) {
    return false;
  }

  auto id = wid_get_thing_id_context(w);
  auto t  = game->thing_find(id);
  if (unlikely(! t)) {
    return false;
  }

  if (wid_inventory_thing_selected == t) {
    wid_inventory_select_requested(nullptr);
  } else {
    wid_inventory_select_requested(t);
  }
  return true;
}

uint8_t wid_bag_item_mouse_held(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Mouse held down, item select");
  TRACE_AND_INDENT();
  if (game->in_transit_item) {
    return false;
  }

  auto id = wid_get_thing_id_context(w);
  auto t  = game->thing_find(id);
  if (unlikely(! t)) {
    return false;
  }

  game->wid_bag_move_item(t);

  return true;
}

bool Game::wid_bag_move_item(Thingp t)
{
  TRACE_AND_INDENT();
  DBG3("Chosen to move item");
  TRACE_AND_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (player && player->is_dead) {
    DBG3("Ignore input; player is dead");
    return false;
  }

  if (unlikely(! t)) {
    ERR("No thing to move");
    return false;
  }

  verify(MTYPE_THING, t);
  t->log("Chosen to move me");
  TRACE_AND_INDENT();

  Widp    wid_bag_container;
  ThingId bag_id;
  Thingp  bag = nullptr;

  for (auto b : game->bags) {
    for (auto w : wid_find_all_containing(b->wid_bag_container, "wid_bag item")) {
      player->log("+ current item %s", wid_get_name(w).c_str());
      if (wid_get_thing_id_context(w).id == t->id.id) {
        player->log("Moving bag thing %s", t->to_string().c_str());
        wid_bag_container = wid_get_parent(w);
        bag_id            = wid_get_thing_id_context(wid_bag_container);
        bag               = game->thing_find(bag_id);
      }
    }
  }

  //
  // If not moving a thing in a bag, is it equipped?
  //
  if (! bag) {
    if (player->is_equipped(t)) {
      //
      // This is ok, moving from equipment into the ether
      //
      t->log("Moving equipped thing");
      TRACE_AND_INDENT();
      t->unequip_me_from_owner("moved item into ether", true);
    } else if (! bag) {
      ERR("%s has no bag so cannot move it!", t->text_The().c_str());
      return false;
    }
  }

  //
  // No owner can happen if we could not move the item as we had no space
  // to carry. Just remove the transit itme.
  //
  auto old_owner = t->immediate_owner();

  if (bag) {
    bag->bag_remove(t);
  }

  if (old_owner) {
    old_owner->drop_into_ether(t);
  }

  if (bag) {
    while (bag->bag_compress()) {
    }
  }

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

  wid_set_thing_id_context(game->in_transit_item, t->id);
  wid_set_on_mouse_up(game->in_transit_item, wid_in_transit_item_place);
  wid_set_fg_tile(game->in_transit_item, t);

  wid_set_moveable(game->in_transit_item, true);
  wid_update(game->in_transit_item);

  DBG3("Remake the bag without the transit item");
  wid_inventory_init();
  game->request_remake_rightbar = true;

  return true;
}

void wid_bag_item_mouse_over_begin(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  if (game->in_transit_item) {
    return;
  }

  if (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) {
    return;
  }

  auto id = wid_get_thing_id_context(w);
  auto t  = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("Could not find thing ID context");
    return;
  }

  //
  // Create the wid info over the inventory
  //
  static int tlx, tly, brx, bry;
  wid_get_tl_x_tl_y_br_x_br_y(wid_get_top_parent(w), &tlx, &tly, &brx, &bry);
  tlx += 45;
  tly += 5;
  brx -= 1;
  bry -= 2;
  wid_inventory_over_requested(t);
}

void wid_bag_item_mouse_over_end(Widp w)
{
  if (game->in_transit_item) {
    return;
  }

  wid_inventory_over_requested(nullptr);
  BOTCON(" ");
}

uint8_t wid_bag_item_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  DBG3("Bag item key down");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Ignore");
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (player && player->is_dead) {
    DBG3("Ignore input; player is dead");
    return false;
  }

  if (wid_over != w) {
    DBG3("Pass key to topcon as not over wid");
    return wid_topcon_input(w, key);
  }

  if (game->state == Game::STATE_COLLECTING_ITEMS) {
    if (key->scancode == SDL_SCANCODE_ESCAPE) {
      DBG3("Escape pressed, clear collecting items state");
      TRACE_AND_INDENT();
      game->change_state(Game::STATE_NORMAL);
      return true;
    }
  }

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  auto id   = wid_get_thing_id_context(w);
  auto what = game->thing_find(id);
  if (! what) {
    DBG3("Cannot find thing");
    return false;
  }

  if (sdlk_eq(*key, game->config.key_drop)) {
    if (game->level->player->drop(what)) {
      game->tick_begin("drop");
    }

    game->request_remake_rightbar = true;
    game->wid_thing_info_create(game->level->player, false);
    return true;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      if (sdlk_eq(*key, game->config.key_action0)) {
        game->level->inventory_assign(9, what);
        wid_inventory_select(what);
        game->request_remake_rightbar = true;
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action1)) {
        game->level->inventory_assign(0, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action2)) {
        game->level->inventory_assign(1, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action3)) {
        game->level->inventory_assign(2, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action4)) {
        game->level->inventory_assign(3, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action5)) {
        game->level->inventory_assign(4, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action6)) {
        game->level->inventory_assign(5, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action7)) {
        game->level->inventory_assign(6, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action8)) {
        game->level->inventory_assign(7, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action9)) {
        game->level->inventory_assign(8, what);
        game->request_remake_rightbar = true;
        wid_inventory_select(what);
        CON("INF: Reassigned item to key.");
        return true;
      }
      break;
  }

  if (sdlk_eq(*key, game->config.key_drop)) {
    DBG3("Pressed drop key");
    TRACE_AND_INDENT();
    if (player->drop(what)) {
      game->tick_begin("drop");
    }
    game->request_remake_rightbar = true;
    game->wid_thing_info_create(game->level->player, false);
    return true;
  }

  if (sdlk_eq(*key, game->config.key_eat)) {
    DBG3("Pressed eat key");
    TRACE_AND_INDENT();
    player->use(what);
    if (game->state == Game::STATE_INVENTORY) {
      wid_inventory_init();
      game->request_remake_rightbar = true;
    }
    return true;
  }

  if (sdlk_eq(*key, game->config.key_use)) {
    DBG3("Pressed use key");
    player->use(what);
    if (game->state == Game::STATE_INVENTORY) {
      wid_inventory_init();
      game->request_remake_rightbar = true;
    }
    return true;
  }

  if (sdlk_eq(*key, game->config.key_throw)) {
    DBG3("Pressed throw key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini(); // To remove bag or other info
    player->throw_item_choose_target(what);
    return true;
  }

  DBG3("Pass key to topcon");
  return wid_topcon_input(w, key);
}

static void wid_bag_tick(Widp w)
{
  if (game->in_transit_item) {
    wid_move_to_abs(game->in_transit_item, ascii_mouse_x, ascii_mouse_y);
  }
}

WidBag::~WidBag()
{
  bag->log("Destroy bag");
  TRACE_AND_INDENT();
  wid_destroy(&wid_bag_container);

  auto b = std::find(game->bags.begin(), game->bags.end(), this);
  if (b != game->bags.end()) {
    game->bags.erase(b);
  }
}

WidBag::WidBag(Widp parent, Thingp bag_, bool highlight, point tl, point br, const std::string &title)
    : tl(tl), br(br)
{
  TRACE_AND_INDENT();
  bag = bag_;
  bag->log("Create bag");
  TRACE_AND_INDENT();

  {
    if (parent) {
      wid_bag_container = wid_new_container(parent, "wid_bag " + title);
    } else {
      wid_bag_container = wid_new_square_window("wid_bag " + title);
    }
    wid_set_ignore_scroll_events(wid_bag_container, true);
    wid_set_pos(wid_bag_container, tl, br);
    wid_set_style(wid_bag_container, UI_WID_STYLE_BAG);

    wid_set_on_tick(wid_bag_container, wid_bag_tick);
    wid_set_thing_id_context(wid_bag_container, bag->id);
  }

  wid_bag_add_items(wid_bag_container, bag);

  wid_update(wid_bag_container);

  game->bags.push_back(this);

  wid_actionbar_init();
}

Widp is_mouse_over_any_bag(void)
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
      // CON("    inventory %d %d %d", tlx, brx, x);
      return w;
    }
    // CON("NOT inventory %d %d %d", tlx, brx, x);
  }
  return nullptr;
}
