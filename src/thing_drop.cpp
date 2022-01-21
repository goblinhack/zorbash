//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::drop(Thingp what, Thingp target, bool stolen)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot drop null thing");
    return false;
  }

  if (stolen) {
    if (target) {
      dbg("Drop (being stolen) %s at %s", what->to_short_string().c_str(), target->to_string().c_str());
    } else {
      dbg("Drop (being stolen) %s", what->to_short_string().c_str());
    }
  } else {
    if (target) {
      dbg("Drop %s at %s", what->to_short_string().c_str(), target->to_string().c_str());
    } else {
      dbg("Drop %s", what->to_short_string().c_str());
    }
  }
  TRACE_AND_INDENT();

  auto top_owner       = what->get_top_owner();
  auto immediate_owner = what->get_immediate_owner();

  if (game->in_transit_item) {
    //
    // Such items are not owned by anyone
    //
  } else {
    //
    // Check we own it
    //
    if ((top_owner != this) && (immediate_owner != this)) {
      if (immediate_owner) {
        dbg("Immediate owner of %s is %s", what->to_short_string().c_str(), top_owner->to_string().c_str());
        dbg("Top owner of %s is %s", what->to_short_string().c_str(), what->get_top_owner()->to_string().c_str());
        err("Attempt to drop %s which is not carried and owned by %s", what->to_short_string().c_str(),
            immediate_owner->to_string().c_str());
      } else {
        err("Attempt to drop %s which is not carried and not owned", what->to_short_string().c_str());
      }
      return false;
    }
  }

  what->is_being_dropped = true;
  if (is_player()) {
    if (target) {
      inventory_shortcuts_remove(what, target);
    } else {
      inventory_shortcuts_remove(what);
    }
  }

  what->hooks_remove();
  what->remove_owner();

  if (is_player()) {
    if (has_external_particle || has_internal_particle) {
      //
      // Hide as the particle drop will reveal it
      //
      dbg("Defer making dropped player item visible: %s", what->to_short_string().c_str());
      what->hide();
    } else {
      //
      // No particle?
      //
      dbg("Make dropped player item visible: %s", what->to_short_string().c_str());
      what->visible();
    }
  } else {
    dbg("Make dropped item visible: %s", what->to_short_string().c_str());
    what->visible();
  }

  if (target) {
    what->move_to_immediately(target->curr_at);
  } else {
    what->move_to_immediately(curr_at);
  }

  if (immediate_owner) {
    immediate_owner->get_itemsp()->carrying.remove(what->id);
  }

  if (! stolen) {
    //
    // Prevent too soon re-carry
    //
    set_where_i_dropped_an_item_last(curr_at);
  }

  if (is_bag_item_container() || is_player()) {
    dbg("Update bag with drop of: %s", what->to_short_string().c_str());
    bag_remove(what);
    while (bag_compress()) {
    }
  }

  wid_inventory_fini();
  wid_thing_info_fini();

  if (stolen) {
    dbg("Dropped (being stolen) %s", what->to_short_string().c_str());
  } else {
    dbg("Dropped %s", what->to_short_string().c_str());

    if (is_player()) {
      sound_play("drop");
    }
  }
  what->is_being_dropped = false;
  what->set_tick_last_dropped(game->tick_current);
  check_all_carried_items_are_owned();
  check_all_carried_maps();

  return true;
}

//
// An item in between bags
//
bool Thing::drop_into_ether(Thingp what)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot drop into ether null thing");
    return false;
  }

  dbg("Dropping %s into the ether", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto top_owner       = what->get_top_owner();
  auto immediate_owner = what->get_immediate_owner();
  if ((top_owner != this) && (immediate_owner != this)) {
    if (immediate_owner) {
      dbg("Immediate owner of %s is %s", what->to_short_string().c_str(), top_owner->to_string().c_str());
      dbg("Top owner of %s is %s", what->to_short_string().c_str(), what->get_top_owner()->to_string().c_str());
      err("Attempt to drop into ether %s which is not carried and owned by %s", what->to_short_string().c_str(),
          immediate_owner->to_string().c_str());
    } else {
      err("Attempt to drop into ether %s which is not carried and not owned", what->to_short_string().c_str());
    }
    return false;
  }

  if (top_owner) {
    FOR_ALL_EQUIP(e)
    {
      if (what == top_owner->get_equip(e)) {
        top_owner->unequip("moved into ether", e, true);
      }
    }

    if (top_owner->is_player()) {
      top_owner->inventory_shortcuts_remove(what);
    }
  } else {
    //
    // This is ok, if we are moving items from a temporary bag
    //
  }

  dbg("Update bag with drop of: %s", what->to_short_string().c_str());
  bag_remove(what);
  while (bag_compress()) {
  }

  what->remove_owner();
  if (immediate_owner) {
    immediate_owner->get_itemsp()->carrying.remove(what->id);
  }
  game->request_remake_rightbar = true;

  dbg("Dropped %s into the ether", what->to_short_string().c_str());
  check_all_carried_items_are_owned();
  check_all_carried_maps();

  return true;
}

//
// An item in between bags
//
bool Thing::drop_from_ether(Thingp what)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot drop from ether null thing");
    return false;
  }

  dbg("Drop from ether %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto player = game->level->player;

  what->hooks_remove();
  what->remove_owner();
  what->hide();
  what->visible();
  what->move_to_immediately(player->curr_at);

  //
  // Prevent too soon re-carry
  //
  set_where_i_dropped_an_item_last(player->curr_at);

  //
  // Remove from the inventory
  //
  inventory_shortcuts_remove(what);

  wid_inventory_fini();
  wid_thing_info_fini();

  point e = (player->last_blit_tl + player->last_blit_br) / 2;

  auto w = game->in_transit_item;
  if (unlikely(! w)) {
    ERR("No in transit item");
    return false;
  }

  auto s = (w->abs_tl + w->abs_br) / 2;
  s.x    = (int) (((float) game->config.game_pix_width / (float) TERM_WIDTH) * (float) s.x);
  s.y    = (int) (((float) game->config.game_pix_height / (float) TERM_HEIGHT) * (float) s.y);

  game->level->new_external_particle(id, s, e, isize(TILE_WIDTH, TILE_HEIGHT), PARTICLE_SPEED_MS,
                                     tile_index_to_tile(what->tile_curr),
                                     (is_dir_br() || is_dir_right() || is_dir_tr()), true /* make_visible_at_end */);

  dbg("Dropped from ether %s", what->to_short_string().c_str());

  if (is_player()) {
    sound_play("drop");
  }
  what->set_tick_last_dropped(game->tick_current);
  check_all_carried_items_are_owned();
  check_all_carried_maps();

  return true;
}

bool Thing::drop(Thingp what) { return drop(what, nullptr); }

void Thing::drop_all(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return;
  }

  while (! get_itemsp()->carrying.empty()) {
    auto id = *get_itemsp()->carrying.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    drop(t);
  }
}
