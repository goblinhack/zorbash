//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_wid_buffbox.hpp"

bool Thing::buff_add(Thingp buff)
{
  dbg("Try to add buff %s", buff->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    dbg("No; not a monst");
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
    if (item == buff->id) {
      dbg("No; already carried");
      return true;
    }
  }

  //
  // There has to be a limit to. Plus we only have so much space in the box.
  //
  if (is_player()) {
    if (! buffbox_id_insert(buff)) {
      msg("You cannot receive any more buffs!");
      buff->dead("too many buffs");
      return false;
    }
  }

  itemsp()->buffs.push_back(buff->id);
  buff->owner_set(this);
  buff->hide("buff add");

  dbg("Add buff %s", buff->to_short_string().c_str());

  if (is_player()) {
    wid_buffbox_init();
  }

  game->set_request_to_remake_rightbar();
  return true;
}

bool Thing::buff_remove(Thingp buff)
{
  if (! buff) {
    return false;
  }

  dbg("Removing buff %s", buff->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = buff->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove buff %s which is not owned", buff->to_short_string().c_str());
    return false;
  }

  Thingp o = buff->top_owner();
  if (o) {
    if (o->is_player()) {
      o->buffbox_id_remove(buff);
    }
  }

  buff->owner_unset();

  auto items = itemsp();
  auto found = std::find(items->buffs.begin(), items->buffs.end(), buff->id);
  if (found != items->buffs.end()) {
    items->buffs.erase(found);
  }

  game->set_request_to_remake_buffbox();

  dbg("Removed %s", buff->to_short_string().c_str());
  buff->dead("removed");

  game->set_request_to_remake_rightbar();
  return true;
}

Thingp Thing::buff_find(const std::string &buff)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return nullptr;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->name() == buff) {
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

bool Thing::buff_use(Thingp buff)
{
  dbg("Try to use buff %s", buff->to_short_string().c_str());
  TRACE_AND_INDENT();

  used(buff, this, false /* remove after use */);
  return true;
}

bool Thing::buff_add(Tpp buff)
{
  if (! maybe_itemsp()) {
    return false;
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(buff, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add buff: %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  buff_add(t);

  return true;
}

bool Thing::buff_add_if_not_found(Tpp buff)
{
  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == buff)) {
      return true;
    }
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(buff, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add buff: %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  buff_add(t);

  return true;
}

bool Thing::buff_remove(Tpp buff)
{
  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == buff)) {
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
