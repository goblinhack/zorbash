//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_ui.hpp"
#include "my_wid_debuffbox.hpp"

bool Thing::debuff_add(Thingp what)
{
  dbg("Try to add debuff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    dbg("No; not a monst");
    return false;
  }

  auto existing_owner = what->immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      dbg("No; same owner");
      return false;
    }
    existing_owner->drop(what);
  }

  FOR_ALL_DEBUFFS(item)
  {
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

  itemsp()->debuffs.push_front(what->id);
  what->owner_set(this);
  what->hide();

  dbg("Add debuff %s", what->to_short_string().c_str());

  if (is_player()) {
    wid_debuffbox_init();
  }

  return true;
}

bool Thing::debuff_remove(Thingp what)
{
  dbg("Removing debuff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = what->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove debuff %s which is not owned", what->to_short_string().c_str());
    return false;
  }

  if (is_player()) {
    debuffbox_id_remove(what);
  }

  what->remove_owner();
  itemsp()->debuffs.remove(what->id);
  game->request_remake_debuffbox = true;

  dbg("Removed %s", what->to_short_string().c_str());
  return true;
}

void Thing::debuff_remove_all(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return;
  }

  while (! itemsp()->debuffs.empty()) {
    auto id = *itemsp()->debuffs.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    debuff_remove(t);
  }
}

bool Thing::debuff_use(Thingp what)
{
  dbg("Try to use debuff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  used(what, this, false /* remove after use */);
  return true;
}

bool Thing::debuff_add(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add debuff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();

  debuff_add(t);

  return true;
}

bool Thing::debuff_add_if_not_found(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }

  while (! itemsp()->debuffs.empty()) {
    auto id = *itemsp()->debuffs.begin();
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
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add debuff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();

  debuff_add(t);

  return true;
}

bool Thing::debuff_remove(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }
  FOR_ALL_DEBUFFS(item)
  {
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
  if (! maybe_itemsp()) {
    return;
  }
  if (itemsp()->debuffs.empty()) {
    return;
  }

  dbg("Debuff tick");
  TRACE_AND_INDENT();

  FOR_ALL_DEBUFFS(item)
  {
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
