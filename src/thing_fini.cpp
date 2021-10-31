//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_world.h"

Thing::~Thing_(void)
{
  TRACE_AND_INDENT();
  verify(this);
  destroy();
  oldptr(this);
}

void Thing::destroy(void)
{
  TRACE_AND_INDENT();
  verify(this);

  if (is_loggable()) {
    auto immediate_owner = get_immediate_owner();
    if (immediate_owner) {
      auto top_owner = get_top_owner();
      if (top_owner) {
        dbg2("Is being destroyed with owner: %s", top_owner->to_string().c_str());
      }
      if (top_owner != immediate_owner) {
        dbg2("Is being destroyed with owner: %s", immediate_owner->to_string().c_str());
      }
    } else {
      dbg2("Is being destroyed with no owner");
    }
  }

  if (is_being_destroyed) {
    err("Death recursion in thing destroy");
    return;
  }
  is_being_destroyed = true;

  level_pop();
  level_leave();

  FOR_ALL_EQUIP(e) { unequip("unequip item as owner is destroyed", e); }

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
  point old_at((int) mid_at.x, (int) mid_at.y);

  delete_lights();
  delete_particle();

  for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
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

  if (monst_infop) {
    oldptr(monst_infop);
    delete monst_infop;
  }
}
