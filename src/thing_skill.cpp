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
#include "my_wid_skillbox.hpp"

bool Thing::skill_add(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to add skill %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  if (! maybe_itemp()) {
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

  for (const auto &item : get_itemp()->skills) {
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

  get_itemp()->skills.push_front(what->id);
  what->set_owner(this);
  what->hide();

  dbg("Add skill %s", what->to_string().c_str());

  if (is_player()) {
    wid_skillbox_init();
  }

  return true;
}

bool Thing::skill_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Removing skill %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto existing_owner = what->get_immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove skill %s which is not owned", what->to_string().c_str());
    return false;
  }

  Thingp top_owner = get_top_owner();
  if (top_owner) {
    if (top_owner->is_player()) {
      top_owner->skillbox_id_remove(what);
    }
  }

  what->remove_owner();
  get_itemp()->skills.remove(what->id);
  game->request_remake_skillbox = true;

  dbg("Removed %s", what->to_string().c_str());
  return true;
}

void Thing::skill_remove_all(void)
{
  TRACE_AND_INDENT();
  if (! maybe_itemp()) {
    return;
  }

  while (! get_itemp()->skills.empty()) {
    auto id = *get_itemp()->skills.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    skill_remove(t);
  }
}

bool Thing::skill_use(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to use skill %s", what->to_string().c_str());
  used(what, this, false /* remove after use */);
  return true;
}

void Thing::skill_deactivate(Thingp what)
{
  TRACE_AND_INDENT();
  what->is_activated            = false;
  game->request_remake_skillbox = true;
}

void Thing::skill_activate(Thingp what)
{
  TRACE_AND_INDENT();
  what->is_activated            = true;
  game->request_remake_skillbox = true;
}

int Thing::skill_enchant_count(const uint32_t slot)
{
  TRACE_AND_INDENT();
  if (! maybe_itemp()) {
    return 0;
  }

  auto thing_id = get(get_itemp()->skillbox_id, slot);
  if (! thing_id) {
    return 0;
  }

  for (auto oid : get_itemp()->skills) {
    auto o = game->level->thing_find(oid);
    if (o) {
      if (o->id == thing_id) {
        return o->get_enchant();
      }
    }
  }

  return 0;
}

bool Thing::skill_add(Tpp what)
{
  TRACE_AND_INDENT();
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    err("Cannot learn skill");
    return false;
  }

  TOPCON("You learn %s skill.", t->text_the().c_str());
  skill_add(t);

  //
  // Drop a skillstone
  //
  auto found = false;
  for (const auto t : get_item_vector()) {
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

int Thing::get_skillstone_count(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  for (const auto t : get_item_vector()) {
    if (! t->is_skillstone()) {
      continue;
    }
    log("Found a skillstone: %s", t->to_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_learn_something(void)
{
  TRACE_AND_INDENT();

  //
  // Once skills are maxxed out, that's it
  //
  if (get_itemp()->skills.size() >= UI_INVENTORY_QUICK_ITEMS_MAX) {
    return false;
  }

  //
  // Look at the list of skills this thing knows. If we find
  // something that is not present, then we have something to learn.
  //
  for (auto tpp : tp_get_skills()) {
    bool already_learned = false;
    for (auto oid : get_itemp()->skills) {
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
  TRACE_AND_INDENT();

  std::vector< Tpp > cands;
  for (auto tpp : tp_get_skills()) {
    bool add = true;
    for (auto oid : get_itemp()->skills) {
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
  log("Add this skill: %s", chosen->name().c_str());
  return skill_add(chosen);
}
