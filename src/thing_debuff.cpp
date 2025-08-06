//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_wid_debuffbox.hpp"

bool Thing::debuff_add(Thingp debuff)
{
  if (! is_buffable()) {
    dbg("No; not buffable");
    return false;
  }

  dbg("Try to add debuff %s", debuff->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    dbg("No; not a monst");
    return false;
  }

  if (debuff->is_buff()) {
    err("Adding a buff as a debuff: %s", debuff->to_short_string().c_str());
    return false;
  }

  FOR_ALL_DEBUFFS(id)
  {
    if (id == debuff->id) {
      dbg("No; already carried");
      return false;
    }
  }

  //
  // There has to be a limit to misfortune. Plus we only have so much space in the box.
  //
  if (is_player()) {
    if (! debuffbox_id_insert(debuff)) {
      msg("You cannot receive any more debuffs!");
      debuff->dead("too many debuffs");
      return false;
    }
  }

  itemsp()->debuffs.push_back(debuff->id);
  debuff->owner_set(this);
  debuff->hide("add debuff");

  dbg("Add debuff %s", debuff->to_short_string().c_str());

  if (is_player()) {
    wid_debuffbox_init();
  }

  return true;
}

bool Thing::debuff_remove(Thingp debuff)
{
  if (! is_buffable()) {
    return false;
  }

  if (! debuff) {
    return false;
  }

  dbg("Removing debuff %s", debuff->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = debuff->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove debuff %s which is not owned", debuff->to_short_string().c_str());
    return false;
  }

  Thingp o = debuff->top_owner();
  if (o) {
    if (o->is_player()) {
      o->debuffbox_id_remove(debuff);
    }
  }

  debuff->owner_unset();

  auto items = itemsp();
  auto found = std::find(items->debuffs.begin(), items->debuffs.end(), debuff->id);
  if (found != items->debuffs.end()) {
    dbg("Found debuff %s", debuff->to_short_string().c_str());
    items->debuffs.erase(found);
  }

  dbg("Removed %s", debuff->to_short_string().c_str());
  debuff->dead("removed");

  game->set_request_to_remake_debuffbox();

  return true;
}

Thingp Thing::debuff_find(const std::string &debuff)
{
  TRACE_NO_INDENT();

  if (! is_buffable()) {
    return nullptr;
  }

  if (! maybe_itemsp()) {
    return nullptr;
  }

  FOR_ALL_DEBUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->name() == debuff) {
        return t;
      }
    }
  }
  return nullptr;
}

void Thing::debuff_remove_all(void)
{
  TRACE_NO_INDENT();

  if (! is_buffable()) {
    return;
  }

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

bool Thing::debuff_use(Thingp debuff)
{
  dbg("Try to use debuff %s", debuff->to_short_string().c_str());
  TRACE_AND_INDENT();

  UseOptions use_options;
  used(debuff, this, use_options);
  return true;
}

bool Thing::debuff_add(Tpp debuff)
{
  if (! is_buffable()) {
    dbg("No; not buffable");
    return false;
  }

  if (! maybe_itemsp()) {
    return false;
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(debuff, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add debuff: %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  debuff_add(t);

  return true;
}

bool Thing::debuff_add_if_not_found(Tpp debuff)
{
  if (! is_buffable()) {
    dbg("No; not buffable");
    return false;
  }

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == debuff)) {
      return true;
    }
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(debuff, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add debuff: %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  debuff_add(t);

  return true;
}

bool Thing::debuff_remove(Tpp debuff)
{
  if (! is_buffable()) {
    return false;
  }

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == debuff)) {
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
      dbg("Debuff (%s)", t->to_short_string().c_str());
      if (! t->on_tick()) {
        return;
      }
      if (is_dead) {
        return;
      }
    }
  }
}
