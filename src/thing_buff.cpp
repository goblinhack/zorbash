//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_game.h"
#include "my_level.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_ui.h"
#include "my_vector_bounds_check.h"
#include "my_wid_buffbox.h"

bool Thing::buff_add(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to add buff %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  if (! monst_infop) {
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

  for (const auto &item : monst_infop->buffs) {
    if (item == what->id) {
      dbg("No; already carried");
      return false;
    }
  }

  if (is_player()) {
    if (! buffbox_id_insert(what)) {
      dbg("No; no space in buffbox");
      return false;
    }
  }

  monst_infop->buffs.push_front(what->id);
  what->set_owner(this);
  what->hide();

  dbg("Add buff %s", what->to_string().c_str());

  if (is_player()) {
    wid_buffbox_init();
  }

  return true;
}

bool Thing::buff_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Removing buff %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto existing_owner = what->get_immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove buff %s which is not owned", what->to_string().c_str());
    return false;
  }

  Thingp top_owner = get_top_owner();
  if (top_owner) {
    if (top_owner->is_player()) {
      top_owner->buffbox_id_remove(what);
    }
  }

  what->remove_owner();
  monst_infop->buffs.remove(what->id);
  game->request_remake_buffbox = true;

  dbg("Removed %s", what->to_string().c_str());
  return true;
}

void Thing::buff_remove_all(void)
{
  TRACE_AND_INDENT();
  if (! monst_infop) {
    return;
  }

  while (! monst_infop->buffs.empty()) {
    auto id = *monst_infop->buffs.begin();
    auto t  = level->thing_find(id);
    if (! t) {
      return;
    }
    buff_remove(t);
  }
}

bool Thing::buff_use(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to use buff %s", what->to_string().c_str());
  used(what, this, false /* remove after use */);
  return true;
}

bool Thing::buff_add(Tpp what)
{
  if (! monst_infop) {
    return false;
  }
  for (const auto &item : monst_infop->buffs) {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == what)) {
      return true;
    }
  }

  auto t = level->thing_new(what, mid_at);
  if (! t) {
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Add buff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();
  buff_add(t);

  return true;
}

void Thing::buff_tick(void)
{
  if (! monst_infop) {
    return;
  }
  if (monst_infop->buffs.empty()) {
    return;
  }

  TRACE_AND_INDENT();
  dbg("Buff tick");
  TRACE_AND_INDENT();

  for (const auto &item : monst_infop->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      dbg("Buff (%s)", t->to_string().c_str());
      if (! t->on_tick()) {
        return;
      }
      if (is_dead) {
        return;
      }
    }
  }
}
