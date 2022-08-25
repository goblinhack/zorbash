//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_skillbox.hpp"

bool Thing::skill_add(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Try to add skill %s", what->to_short_string().c_str());
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

  FOR_ALL_SKILLS(item)
  {
    if (item == what->id) {
      dbg("No; already carried");
      return false;
    }
  }

  if (is_player()) {
    if (! skillbox_id_insert(what)) {
      dbg("No; no space in skillbox");
      return false;
    }
  }

  itemsp()->skills.push_front(what->id);
  what->owner_set(this);
  what->hide();

  dbg("Add skill %s", what->to_short_string().c_str());

  if (is_player()) {
    wid_skillbox_init();
  }

  return true;
}

bool Thing::skill_remove(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Removing skill %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = what->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove skill %s which is not owned", what->to_short_string().c_str());
    return false;
  }

  Thingp o = what->top_owner();
  if (o) {
    if (o->is_player()) {
      o->skillbox_id_remove(what);
    }
  }

  what->remove_owner();
  itemsp()->skills.remove(what->id);
  game->request_remake_skillbox = true;

  dbg("Removed %s", what->to_short_string().c_str());
  return true;
}

void Thing::skill_remove_all(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return;
  }

  while (! itemsp()->skills.empty()) {
    auto id = *itemsp()->skills.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    skill_remove(t);
  }
}

bool Thing::skill_use(Thingp what)
{
  TRACE_NO_INDENT();
  dbg("Try to use skill %s", what->to_short_string().c_str());
  used(what, this, false /* remove after use */);
  return true;
}

void Thing::skill_deactivate(Thingp what)
{
  TRACE_NO_INDENT();
  what->is_activated            = false;
  game->request_remake_skillbox = true;
}

void Thing::skill_activate(Thingp what)
{
  TRACE_NO_INDENT();
  what->is_activated            = true;
  game->request_remake_skillbox = true;
}

int Thing::skill_enchant_count(const uint32_t slot)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return 0;
  }

  auto thing_id = get(itemsp()->skillbox_id, slot);
  if (! thing_id) {
    return 0;
  }

  FOR_ALL_SKILLS(oid)
  {
    auto o = game->level->thing_find(oid);
    if (o) {
      if (o->id == thing_id) {
        return o->enchant_get();
      }
    }
  }

  return 0;
}

bool Thing::skill_add(Tpp what)
{
  TRACE_NO_INDENT();
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    err("Cannot learn skill");
    return false;
  }

  if (is_player()) {
    msg("You learn %s skill.", t->text_the().c_str());
  }

  skill_add(t);

  //
  // Drop a skillstone
  //
  auto found = false;
  for (const auto t : item_vector()) {
    if (t->is_skillstone()) {
      t->dead("used");
      found = true;
      break;
    }
  }
  if (! found) {
    err("no skillstone found");
  }

  return true;
}

int Thing::skillstone_count(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  for (const auto t : item_vector()) {
    if (! t->is_skillstone()) {
      continue;
    }
    dbg("Found a skillstone: %s", t->to_short_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_learn_something(void)
{
  TRACE_NO_INDENT();

  //
  // Once skills are maxxed out, that's it
  //
  if (itemsp()->skills.size() >= UI_INVENTORY_QUICK_ITEMS_MAX) {
    return false;
  }

  //
  // Look at the list of skills this thing knows. If we find
  // something that is not present, then we have something to learn.
  //
  for (auto tpp : tp_get_skills()) {
    bool already_learned = false;
    FOR_ALL_SKILLS(oid)
    {
      auto o = game->level->thing_find(oid);
      if (o) {
        if (o->tp() == tpp) {
          already_learned = true;
          break;
        }
      }
    }
    if (already_learned) {
      continue;
    }
    return true;
  }
  return false;
}

bool Thing::learn_random_skill(void)
{
  TRACE_NO_INDENT();

  std::vector< Tpp > cands;
  for (auto tpp : tp_get_skills()) {
    bool add = true;
    FOR_ALL_SKILLS(oid)
    {
      auto o = game->level->thing_find(oid);
      if (o) {
        if (o->tp() == tpp) {
          add = false;
          break;
        }
      }
    }
    if (add) {
      cands.push_back(tpp);
    }
  }

  if (cands.empty()) {
    return false;
  }

  auto chosen = cands[ pcg_random_range(0, cands.size()) ];
  dbg("Add this skill: %s", chosen->name().c_str());
  return skill_add(chosen);
}
