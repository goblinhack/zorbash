//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"

void Thing::on_dropped(void)
{
  TRACE_NO_INDENT();

  auto on_dropped = tp()->on_dropped_do();
  if (std::empty(on_dropped)) {
    return;
  }

  auto t = split_tokens(on_dropped, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_dropped call [%s] expected mod:function, got %d elems", on_dropped.c_str(), (int) on_dropped.size());
  }
}

bool Thing::drop(Thingp what, Thingp target, DropOptions drop_options)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot drop null thing");
    return false;
  }

  if (drop_options.is_being_stolen) {
    if (target) {
      dbg("Drop (being stolen) %s at %s", what->to_short_string().c_str(), target->to_short_string().c_str());
    } else {
      dbg("Drop (being stolen) %s", what->to_short_string().c_str());
    }
    reset_collect_penalty(what);
  } else if (drop_options.is_able_to_be_equipped) {
    if (target) {
      dbg("Drop (being equipped) %s at %s", what->to_short_string().c_str(), target->to_short_string().c_str());
    } else {
      dbg("Drop (being equipped) %s", what->to_short_string().c_str());
    }
    reset_collect_penalty(what);
  } else if (drop_options.is_being_thrown) {
    if (target) {
      dbg("Drop (being thrown) %s at %s", what->to_short_string().c_str(), target->to_short_string().c_str());
    } else {
      dbg("Drop (being thrown) %s", what->to_short_string().c_str());
    }
    reset_collect_penalty(what);
  } else {
    if (target) {
      dbg("Drop %s at %s", what->to_short_string().c_str(), target->to_short_string().c_str());
    } else {
      dbg("Drop %s", what->to_short_string().c_str());
    }

    //
    // No penalties for the player. Allow them to pick and drop as they please.
    //
    if (is_monst() || (is_player() && game->robot_mode)) {
      add_collect_penalty(what);
    }
  }

  TRACE_AND_INDENT();

  auto top_owner       = what->top_owner();
  auto immediate_owner = what->immediate_owner();

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
        dbg("Immediate owner of %s is %s", what->to_short_string().c_str(), top_owner->to_short_string().c_str());
        dbg("Top owner of %s is %s", what->to_short_string().c_str(), what->top_owner()->to_string().c_str());
        err("Attempt to drop %s which is not carried and owned by %s", what->to_short_string().c_str(),
            immediate_owner->to_short_string().c_str());
      } else {
        err("Attempt to drop %s which is not carried and not owned", what->to_short_string().c_str());
      }
      return false;
    }
  }

  what->is_being_dropped = true;
  if (is_player()) {
    if (target) {
      inventory_shortcuts_remove(what, target, drop_options);
    } else {
      inventory_shortcuts_remove(what, drop_options);
    }
  }

  what->hooks_remove();
  what->owner_unset();

  if (is_player()) {
    if (has_external_particle || has_internal_particle) {
      //
      // Hide as the particle drop will reveal it
      //
      dbg("Defer making dropped player item visible: %s", what->to_short_string().c_str());
      what->hide("defer making dropped player item visible");
    } else {
      //
      // No particle?
      //
      if (! is_dead_or_dying()) {
        dbg("Make dropped player item visible: %s", what->to_short_string().c_str());
        what->visible("make dropped player item visible");
      } else {
        dbg("Keep dropped dead player item hidden: %s", what->to_short_string().c_str());
      }
    }
  } else {
    dbg("Make dropped item visible: %s", what->to_short_string().c_str());
    what->visible("make dropped item visible");
  }

  if (target) {
    what->move_to_immediately(target->curr_at);
  } else {
    what->move_to_immediately(curr_at);
  }

  if (immediate_owner) {
    dbg("Drop and remove from carrying list");
    TRACE_AND_INDENT();

    auto items = immediate_owner->itemsp();
    auto found = std::find(items->carrying.begin(), items->carrying.end(), what->id);
    if (found != items->carrying.end()) {
      items->carrying.erase(found);
    } else {
      dbg("Could not remove from carrying list");
    }
  }

  if (! drop_options.is_being_stolen) {
    //
    // Prevent too soon re-carry
    //
    where_i_dropped_an_item_last_set(curr_at);
  }

  if (is_bag_item_container() || is_player()) {
    dbg("Update bag with drop of: %s", what->to_short_string().c_str());
    bag_remove(what);
    while (bag_compress()) {}
  }

  wid_inventory_fini();
  wid_thing_info_fini("drop item");

  if (drop_options.is_being_thrown) {
    //
    // A message should already have been shown
    //
  } else if (drop_options.is_being_stolen) {
    dbg("Dropped (being stolen) %s", what->to_short_string().c_str());
    if (is_player()) {
      if (! is_dead_or_dying()) {
        msg("You feel lighter.");
      }
    }
  } else {
    dbg("Dropped %s", what->to_short_string().c_str());

    if (is_player()) {
      //
      // We need to tick here, to ensure that log messages do not get filtered.
      //
      game->tick_begin("drop item");

      if (! is_dead_or_dying()) {
        msg("You drop %s.", what->text_the().c_str());
        sound_play("drop");
        level->sound_sources_incr(curr_at.x, curr_at.y, what->noise_on_dropping());
      }
    } else if (is_bag_item_container()) {
      if (! drop_options.is_being_thrown && ! drop_options.is_able_to_be_equipped && ! drop_options.is_being_stolen) {
        msg("%s falls out of %s.", capitalize_first(what->text_the()).c_str(), text_the().c_str());
        level->sound_sources_incr(curr_at.x, curr_at.y, what->noise_on_dropping());
      }
    } else if (is_monst()) {
      if (! drop_options.is_being_thrown && ! drop_options.is_able_to_be_equipped && ! drop_options.is_being_stolen) {
        msg("%s drops %s.", capitalize_first(text_the()).c_str(), what->text_the().c_str());
        level->sound_sources_incr(curr_at.x, curr_at.y, what->noise_on_dropping());
      }
    }
  }

  what->is_being_dropped = false;
  what->tick_last_dropped_set(game->tick_current);
  if (! is_dead_or_dying()) {
    if (! drop_options.is_being_thrown && ! drop_options.is_able_to_be_equipped && ! drop_options.is_being_stolen) {
      what->on_dropped();
    }
  }
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

  auto top_owner       = what->top_owner();
  auto immediate_owner = what->immediate_owner();
  if ((top_owner != this) && (immediate_owner != this)) {
    if (immediate_owner) {
      dbg("Immediate owner of %s is %s", what->to_short_string().c_str(), top_owner->to_short_string().c_str());
      dbg("Top owner of %s is %s", what->to_short_string().c_str(), what->top_owner()->to_string().c_str());
      err("Attempt to drop into ether %s which is not carried and owned by %s", what->to_short_string().c_str(),
          immediate_owner->to_short_string().c_str());
    } else {
      err("Attempt to drop into ether %s which is not carried and not owned", what->to_short_string().c_str());
    }
    return false;
  }

  if (top_owner) {
    TRACE_NO_INDENT();
    FOR_ALL_EQUIP(e)
    {
      if (what == top_owner->equip_get(e)) {
        top_owner->unequip("moved into ether", e, true);
      }
    }

    if (top_owner->is_player()) {
      DropOptions drop_options;
      top_owner->inventory_shortcuts_remove(what, drop_options);
    }
  } else {
    //
    // This is ok, if we are moving items from a temporary bag
    //
  }

  {
    dbg("Update bag with drop of: %s", what->to_short_string().c_str());
    TRACE_AND_INDENT();

    bag_remove(what);
    while (bag_compress()) {}
    dbg("Updated bag with drop of: %s", what->to_short_string().c_str());
  }

  //
  // Safest to do this prior to owner_unset as owner_unset triggers a location check
  // which could potentially throw an error for a thing that has been unset but is
  // still on the carrying list.
  //
  if (immediate_owner) {
    dbg("Drop and remove from carrying list");
    TRACE_AND_INDENT();

    auto items = immediate_owner->itemsp();
    auto found = std::find(items->carrying.begin(), items->carrying.end(), what->id);
    if (found != items->carrying.end()) {
      items->carrying.erase(found);
    }
  }

  {
    dbg("Unset owner from drop of: %s", what->to_short_string().c_str());
    TRACE_AND_INDENT();
    what->owner_unset();
  }

  game->set_request_to_remake_rightbar();

  {
    dbg("Dropped %s into the ether", what->to_short_string().c_str());
    TRACE_AND_INDENT();
    check_all_carried_items_are_owned();
    check_all_carried_maps();
    dbg("Dropped %s into the ether finished", what->to_short_string().c_str());
  }

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

  what->hooks_remove();
  what->owner_unset();
  what->hide("drop from ether");
  what->visible("drop from ether");
  what->move_to_immediately(curr_at);

  //
  // Prevent too soon re-carry
  //
  where_i_dropped_an_item_last_set(curr_at);

  //
  // Remove from the inventory
  //
  DropOptions drop_options;
  inventory_shortcuts_remove(what, drop_options);

  wid_inventory_fini();
  wid_thing_info_fini("drop from ether");

  point e = (last_blit_tl + last_blit_br) / (short) 2;

  auto w = game->in_transit_item;
  if (unlikely(! w)) {
    ERR("No in transit item");
    return false;
  }

  auto s = (w->abs_tl + w->abs_br) / (short) 2;
  s.x    = (int) ((((float) game->config.game_pix_width) / ((float) TERM_WIDTH)) * ((float) s.x));
  s.y    = (int) ((((float) game->config.game_pix_height) / ((float) TERM_HEIGHT)) * ((float) s.y));

  auto callback = std::bind(&Thing::visible_callback, what);

  auto delay = 0;

  if (g_opt_ascii) {
    delay = PARTICLE_SPEED_DROPPED_ITEM_ASCII_MS;
  } else {
    delay = PARTICLE_SPEED_DROPPED_ITEM_PIXELART_MS;
  }

  if (! is_being_destroyed) {
    game->level->new_external_particle(id, s, e, isize(TILE_WIDTH, TILE_HEIGHT), delay,
                                       tile_index_to_tile(what->tile_curr),
                                       (is_dir_br() || is_dir_right() || is_dir_tr()), callback);
  }

  dbg("Dropped from ether %s", what->to_short_string().c_str());
  thing_sound_play("drop");

  what->tick_last_dropped_set(game->tick_current);
  check_all_carried_items_are_owned();
  check_all_carried_maps();

  return true;
}

bool Thing::drop(Thingp what)
{
  DropOptions drop_options;
  return drop(what, nullptr, drop_options);
}

bool Thing::drop(Thingp what, DropOptions drop_options) { return drop(what, nullptr, drop_options); }

void Thing::drop_all(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return;
  }

  while (! itemsp()->carrying.empty()) {
    auto id = *itemsp()->carrying.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    drop(t);
  }
}
