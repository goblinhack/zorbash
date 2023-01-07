//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_wid_buffbox.hpp"

bool Thing::buff_add(Thingp what)
{
  dbg("Try to add buff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    dbg("No; not a monst");
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
    if (item == what->id) {
      dbg("No; already carried");
      return true;
    }
  }

  if (is_player()) {
    if (! buffbox_id_insert(what)) {
      dbg("No; no space in buffbox");
      return false;
    }
  }

  itemsp()->buffs.push_front(what->id);
  what->owner_set(this);
  what->hide();

  dbg("Add buff %s", what->to_short_string().c_str());

  if (is_player()) {
    wid_buffbox_init();
  }

  return true;
}

bool Thing::buff_remove(Thingp what)
{
  if (! what) {
    return false;
  }

  dbg("Removing buff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = what->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove buff %s which is not owned", what->to_short_string().c_str());
    return false;
  }

  Thingp o = what->top_owner();
  if (o) {
    if (o->is_player()) {
      o->buffbox_id_remove(what);
    }
  }

  what->owner_unset();
  itemsp()->buffs.remove(what->id);
  game->set_request_to_remake_buffbox();

  dbg("Removed %s", what->to_short_string().c_str());
  return true;
}

Thingp Thing::buff_find(const std::string &what)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return nullptr;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->name() == what) {
        return t;
      }
    }
  }
  return nullptr;
}

void Thing::buff_remove_all(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return;
  }

  while (! itemsp()->buffs.empty()) {
    auto id = *itemsp()->buffs.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    buff_remove(t);
  }
}

bool Thing::buff_use(Thingp what)
{
  dbg("Try to use buff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  used(what, this, false /* remove after use */);
  return true;
}

bool Thing::buff_add(Tpp what)
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

  dbg("Add buff: %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  buff_add(t);

  return true;
}

bool Thing::buff_add_if_not_found(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == what)) {
      return true;
    }
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add buff: %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  buff_add(t);

  return true;
}

bool Thing::buff_remove(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == what)) {
      buff_remove(t);
      return true;
    }
  }
  return false;
}

void Thing::buff_tick(void)
{
  if (! maybe_itemsp()) {
    return;
  }

  if (itemsp()->buffs.empty()) {
    return;
  }

  dbg("Buff tick");
  TRACE_AND_INDENT();

  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      dbg("Buff (%s)", t->to_short_string().c_str());
      if (! t->on_tick()) {
        return;
      }
      if (is_dead) {
        return;
      }
    }
  }
}
