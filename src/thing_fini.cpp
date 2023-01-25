//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"

Thing::~Thing_(void)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, this);
  destroy();
  oldptr(MTYPE_THING, this);
}

void Thing::destroy(void)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, this);

  /*
   * If seeing a crash in printing the description of the thing this can be handy.
  if (maybe_infop()) {
  LOG("%p Destroy %" PRIX32 " leader %" PRIX32 " owner %" PRIX32, this, id.id, infop()->leader_id.id,
      infop()->owner_id.id);
  }
   */

  //
  // Make sure and set is_being_destroyed before any logging as that can cause
  // issues in thing to_string with detached owners.
  //
  if (is_being_destroyed) {
    err("Death recursion in thing destroy");
    return;
  }
  is_being_destroyed = true;

  if (is_loggable()) {
    dbg2("Destroy");
    auto i_o = immediate_owner();
    if (i_o) {
      auto top_o = top_owner();
      if (top_o) {
        dbg2("Is being destroyed, has top owner: %s", top_o->to_string().c_str());
      }
      if (top_o != i_o) {
        dbg2("Is being destroyed, has immediate owner: %s", i_o->to_string().c_str());
      }
    }
  }
  TRACE_AND_INDENT();

  level_pop();
  level_leave();

  FOR_ALL_EQUIP(e) { unequip("unequip item as owner is destroyed", e, false); }

  //
  // Remove buffs etc... in destroy as it can be intereting for the player to be
  // able to see what they had when dead.
  //
  skill_remove_all();
  buff_remove_all();
  debuff_remove_all();

  //
  // hooks remove must be after unequip
  //
  hooks_remove();

  //
  // Remove any references still to this item
  //
  remove_all_references();

  //
  // Pop from the map
  //
  point old_at((int) curr_at.x, (int) curr_at.y);

  delete_lights();
  delete_particle();

  {
    auto f = level->all_things_to_be_destroyed.find(id);
    if (f != level->all_things_to_be_destroyed.end()) {
      dbg2("Remove from gc");
      level->all_things_to_be_destroyed.erase(f);
    }
  }

  if (level->hover_over == this) {
    level->hover_over = nullptr;
  }

  if (level->highlight == this) {
    level->highlight = nullptr;
  }

  if (level->player == this) {
    level->player = nullptr;
  }

  for (auto b : game->bags) {
    if (b->bag == this) {
      b->bag = nullptr;
    }
  }

  {
    if (std::find(level->wid_leftbar_things.begin(), level->wid_leftbar_things.end(), id) !=
        level->wid_leftbar_things.end()) {
      dbg2("Remove from wid leftbar");
      level->wid_leftbar_things.remove(id);
    }
  }

  if (level->cursor == this) {
    dbg2("Removed cursor");
    level->cursor = nullptr;
  }

  if (game->request_to_throw_item == this) {
    game->request_to_throw_item  = nullptr;
    game->request_destination_ok = false;
  }

  if (game->request_to_use_item == this) {
    game->request_to_use_item    = nullptr;
    game->request_destination_ok = false;
  }

  if (game->current_wid_thing_info == this) {
    game->current_wid_thing_info = nullptr;
  }

  if (game->request_inventory_thing_over == this) {
    game->request_inventory_thing_over = nullptr;
  }

  if (game->request_inventory_thing_selected == this) {
    game->request_inventory_thing_selected = nullptr;
  }

  if (wid_inventory_thing_over == this) {
    wid_inventory_thing_over = nullptr;
  }

  if (wid_inventory_thing_selected == this) {
    wid_inventory_thing_selected = nullptr;
  }

  for (const auto w : wid_thing_info_window) {
    if (w->t == this) {
      game->wid_thing_info_destroy_immediate();
      break;
    }
  }

  if (has_external_particle) {
    err("Still has external particle");
  }

  if (has_internal_particle) {
    err("Still has external particle");
  }

  game->world.free_thing_id(this);

  auto infop = maybe_infop();
  if (infop) {
    oldptr(MTYPE_INFOP, infop);
    delete _infop;
  }

  //
  // Remove any thing references in widgets; due to say being in transit.
  //
  auto items = maybe_itemsp();
  if (items) {
    for (auto w : items->thing_wid) {
      for (auto which = 0; which < WID_THING_ID_MAX_CONTEXT; which++) {
        wid_clear_thing_id_context(w, which);
      }
    }
    items->thing_wid.clear();

    oldptr(MTYPE_ITEMP, items);
    delete _itemsp;
  }

  if (maybe_aip()) {
    oldptr(MTYPE_AIP, maybe_aip());
    delete _aip;
  }
}
