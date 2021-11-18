//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_debuffbox.hpp"

bool Thing::debuff_add(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to add debuff %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    dbg("No; not a monst");
    return false;
  }

  auto existing_owner = what->get_immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      dbg("No; same owner");
      return false;
    }
    existing_owner->drop(what);
  }

  for (const auto &item : get_itemp()->debuffs) {
    if (item == what->id) {
      dbg("No; already carried");
      return false;
    }
  }

  if (is_player()) {
    if (! debuffbox_id_insert(what)) {
      dbg("No; no space in debuffbox");
      return false;
    }
  }

  get_itemp()->debuffs.push_front(what->id);
  what->set_owner(this);
  what->hide();

  dbg("Add debuff %s", what->to_string().c_str());

  if (is_player()) {
    wid_debuffbox_init();
  }

  return true;
}

bool Thing::debuff_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Removing debuff %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto existing_owner = what->get_immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove debuff %s which is not owned", what->to_string().c_str());
    return false;
  }

  if (is_player()) {
    debuffbox_id_remove(what);
  }

  what->remove_owner();
  get_itemp()->debuffs.remove(what->id);
  game->request_remake_debuffbox = true;

  dbg("Removed %s", what->to_string().c_str());
  return true;
}

void Thing::debuff_remove_all(void)
{
  TRACE_AND_INDENT();
  if (! maybe_itemp()) {
    return;
  }

  while (! get_itemp()->debuffs.empty()) {
    auto id = *get_itemp()->debuffs.begin();
    auto t  = level->thing_find(id);
    if (! t) {
      return;
    }
    debuff_remove(t);
  }
}

bool Thing::debuff_use(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to use debuff %s", what->to_string().c_str());
  used(what, this, false /* remove after use */);
  return true;
}

bool Thing::debuff_add(Tpp what)
{
  if (! maybe_itemp()) {
    return false;
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(what, mid_at);
  if (! t) {
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Add debuff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();
  debuff_add(t);

  return true;
}

bool Thing::debuff_add_if_not_found(Tpp what)
{
  if (! maybe_itemp()) {
    return false;
  }

  while (! get_itemp()->debuffs.empty()) {
    auto id = *get_itemp()->debuffs.begin();
    auto t  = level->thing_find(id);
    if (t) {
      if (t->tp() == what) {
        return true;
      }
    }
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(what, mid_at);
  if (! t) {
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Add debuff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();
  debuff_add(t);

  return true;
}

bool Thing::debuff_remove(Tpp what)
{
  if (! maybe_itemp()) {
    return false;
  }
  for (const auto &item : get_itemp()->debuffs) {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == what)) {
      debuff_remove(t);
      return true;
    }
  }
  return false;
}

void Thing::debuff_tick(void)
{
  if (! maybe_itemp()) {
    return;
  }
  if (get_itemp()->debuffs.empty()) {
    return;
  }

  TRACE_AND_INDENT();
  dbg("Debuff tick");
  TRACE_AND_INDENT();

  for (const auto &item : get_itemp()->debuffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      dbg("Debuff (%s)", t->to_string().c_str());
      if (! t->on_tick()) {
        return;
      }
      if (is_dead) {
        return;
      }
    }
  }
}
