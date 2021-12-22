//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"
#include "my_world.hpp"

Thing::~Thing_(void)
{
  TRACE_AND_INDENT();
  verify(MTYPE_THING, this);
  destroy();
  oldptr(MTYPE_THING, this);
}

void Thing::destroy(void)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  if (is_loggable()) {
    auto immediate_owner = get_immediate_owner();
    if (immediate_owner) {
      auto top_owner = get_top_owner();
      if (top_owner) {
        dbg2("Is being destroyed, has top owner: %s", top_owner->to_string().c_str());
      }
      if (top_owner != immediate_owner) {
        dbg2("Is being destroyed, has immediate owner: %s", immediate_owner->to_string().c_str());
      }
    }
  }

  if (is_being_destroyed) {
    err("Death recursion in thing destroy");
    return;
  }
  is_being_destroyed = true;

  level_pop();
  level_leave();

  FOR_ALL_EQUIP(e) { unequip("unequip item as owner is destroyed", e, false); }

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

  FOR_ALL_THING_GROUPS(group)
  {
    auto f = level->all_things_to_be_destroyed[ group ].find(id);
    if (f != level->all_things_to_be_destroyed[ group ].end()) {
      dbg2("Remove from gc");
      level->all_things_to_be_destroyed[ group ].erase(f);
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

  if (level->cursor == this) {
    level->cursor = nullptr;
  }

  if (game->request_to_throw_item == this) {
    game->request_to_throw_item = nullptr;
  }

  if (game->request_to_fire_item == this) {
    game->request_to_fire_item = nullptr;
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

  if (maybe_infop()) {
    oldptr(MTYPE_INFOP, maybe_infop());
    delete _infop;
  }

  if (maybe_itemp()) {
    oldptr(MTYPE_ITEMP, maybe_itemp());
    delete _itemp;
  }

  if (maybe_aip()) {
    oldptr(MTYPE_AIP, maybe_aip());
    delete _aip;
  }
}
